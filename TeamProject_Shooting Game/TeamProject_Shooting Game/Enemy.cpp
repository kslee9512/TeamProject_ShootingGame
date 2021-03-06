#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionChecker.h"
#include "UiManager.h"

HRESULT Enemy::Init(CollisionChecker* collisionChecker, int posX, int posY)
{
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, 
            "Enemy가 로드안됨!", "실패!", MB_OK);
        return E_FAIL;
    }

    imageDmg = ImageManager::GetSingleton()->FindImage("Damage");
    if (imageDmg == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss가 안됨!", "실패!", MB_OK);
        return E_FAIL;
    }
    imageDst = ImageManager::GetSingleton()->FindImage("Destroy");
    if (imageDst == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss가 안됨!", "실패!", MB_OK);
        return E_FAIL;
    }

    checkTimer = 0;
    enemyType = ENEMYTYPE::BOSS;
    currFrameX = 0;
    updateCount = 0;
    enterType = 0;
    pos.x =  posX;
    pos.y = posY;
    size = 80;
    name = "NormalEnemy";
    hitBox = { 0, 0, 0, 0 };
    isAlive = true;
    endMovePattern = false;
    moveSpeed = 200.0f;
    enterStage = false;
    angle = 0.0f;
    dir = 1;
    verticalDir = 1;
    enemyStatus = NONE;
    // �̻��� �Ŵ���
    this->collisionChecker = collisionChecker;
    missileMgr = new MissileManager();
    missileMgr->Init(collisionChecker, this);
    fireCount = 0;
    changeStatusTimer = 0.0f;
    enemyCurrHP = 4;
    enemyDmg = 1;
    IsEnemyDmg = false;
    randMissile = 0;
    IsBossAlive = true;
    return S_OK;
}

HRESULT Enemy::BossInit(CollisionChecker* collisionChecker, int posX, int posY)
{
    image = ImageManager::GetSingleton()->FindImage("Boss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss가 안됨!", "실패!", MB_OK);
        return E_FAIL;
    }
    imageDmg = ImageManager::GetSingleton()->FindImage("Damage");
    if (imageDmg == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss가 안됨!", "실패!", MB_OK);
        return E_FAIL;
    }
    imageDst = ImageManager::GetSingleton()->FindImage("Destroy");
    if (imageDst == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss가 안됨!", "실패!", MB_OK);
        return E_FAIL;
    }
    checkTimer = 0;
    enemyType = ENEMYTYPE::BOSS;
    enemyDamage = ENEMYDAMAGE::DAMAGE; //DESTROY DAMAGE
    currFrameX = 0;
    updateCount = 0;
    enterType = 0;
    pos.x = posX;
    pos.y = posY;
    size = 80;
    name = "NormalEnemy";
    hitBox = { 0, 0, 0, 0 };
    isAlive = true;
    endMovePattern = false;
    moveSpeed = 200.0f;
    enterStage = false;
    angle = 0.0f;
    dir = 1;
    verticalDir = 1;
    enemyStatus = NONE;
    // �̻��� �Ŵ���
    missileMgr = new MissileManager();
    this->collisionChecker = collisionChecker;
    missileMgr->Init(collisionChecker, this);
    fireCount = 0;
    collisionChecker->AddActiveEnemy(this);
    fireCount = 0;
    currElapsed = 0;
    randElapsed = 0;

    enemyCurrHP = 50;
    enemyDmg = 1;
    IsEnemyDmg = false;
    changeStatusTimer = 0.0f;
    randMissile = 0;
    IsBossAlive = true;
    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missileMgr);
}

void Enemy::Update()
{
    currElapsed += TimerManager::GetSingleton()->GetElapsedTime();
    randElapsed += TimerManager::GetSingleton()->GetElapsedTime();

    if (randElapsed >= 0.5f)
    {
        randomX = rand() % 40;
        randomY = rand() % 5;
        randElapsed = 0;
    }


    if (isAlive)
    {
        if (enemyType == ENEMYTYPE::BOSS && enemyStatus == ENEMYSTATUS::MOVE)
        {
            changeStatusTimer += TimerManager::GetSingleton()->GetElapsedTime();
        }
        Enterance();
        Move();
        hitBox = GetRectToCenter(pos.x, pos.y, 100, 200);
        missileMgr->Update();

        if (enemyStatus == ENEMYSTATUS::MOVE && changeStatusTimer >= 3.0f)
        {
            srand(time(NULL));
            SetStatus(ENEMYSTATUS::FIRE);
            randMissile = rand() % 4;
            changeStatusTimer = 0.0f;
        }
        // 미사일 발사

        if (enemyStatus == ENEMYSTATUS::FIRE && enemyDamage != ENEMYDAMAGE::DESTROY && enemyType == ENEMYTYPE::BOSS)
        {
            changeStatusTimer += TimerManager::GetSingleton()->GetElapsedTime();
            if (missileMgr)
            {
                // �Լ� ȣ�� �ֱ⸦ �ٲ㺸��.
                fireCount++;
                if (fireCount % 20 == 0)
                {
                    fireCount = 0;
                    missileMgr->Fire(randMissile);
                }
            }
            if (changeStatusTimer >= 3.0f)
            {
                SetStatus(ENEMYSTATUS::MOVE);
                changeStatusTimer = 0.0f;
            }
        }
        
        // �ִϸ��̼� ������
        if (enemyType == ENEMYTYPE::NORMAL)
        {
            updateCount++;
            if (updateCount == 5)
            {
                currFrameX++;
                if (currFrameX >= 10)
                {
                    currFrameX = 0;
                }
                updateCount = 0;
            }
        }

        //if (enemyStatus == ENEMYSTATUS::FIRE)    SetStatus(ENEMYSTATUS::MOVE);

        if (enemyType == ENEMYTYPE::BOSS)
        {
            if (currElapsed >= 0.2f)
            {
                currFrameX++;
                if (currFrameX >= 4)
                {
                    currFrameX = 0;
                }
                currElapsed = 0;
            }
        }
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        SetSpecial(missileMgr->GetSpecial());
        if (IsEnemyDmg)
        {
            enemyCurrHP -= enemyDmg;
            UiManager::GetSingleton()->SetScore(UiManager::GetSingleton()->GetScore() + 10);
            IsEnemyDmg = false;
        }

        if (image && enemyType == ENEMYTYPE::NORMAL)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
            RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
            if (enemyCurrHP == 0)
            {
                enemyDamage = ENEMYDAMAGE::DESTROY;
            }
            if (image && enemyDamage == ENEMYDAMAGE::DESTROY && enemyCurrHP == 0)  // 폭발
            {
                imageDst->FrameRender(hdc, pos.x, pos.y, currFrameX + 1, 0, true);
            }
        }
        else if (image && enemyType == ENEMYTYPE::BOSS)
        {
            //image->Render(hdc, pos.x, pos.y, true);
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);

            if (image && enemyDamage == ENEMYDAMAGE::DAMAGE && enemyCurrHP <= 30)  // 화재1
            {
                imageDmg->FrameRender(hdc, pos.x - 200, pos.y - 120, currFrameX, 0, true);

                if (image && enemyDamage == ENEMYDAMAGE::DAMAGE && enemyCurrHP <= 20)  // 화재2
                {
                    imageDmg->FrameRender(hdc, pos.x + 150, pos.y - 80, currFrameX, 0, true);

                    if (image && enemyDamage == ENEMYDAMAGE::DAMAGE && enemyCurrHP <= 10)  // 화재3
                    {
                        imageDmg->FrameRender(hdc, pos.x - 100, pos.y - 60, currFrameX, 0, true);

                        if (enemyCurrHP <= 0)
                        {
                            enemyDamage = ENEMYDAMAGE::DESTROY;
                            UiManager::GetSingleton()->SetScore(UiManager::GetSingleton()->GetScore() + 10000);
                        }
                    }
                }
            }
            if (image && enemyDamage == ENEMYDAMAGE::DESTROY && enemyCurrHP <= 0)  // 폭발
            {
                imageDst->FrameRender(hdc, (pos.x - 150) + randomX*10, (pos.y - 50) + randomY*10, currFrameX + 1, 0, true);

                pos.y += 0.1f;
                if (pos.y >= 300)
                {
                    isAlive = false;        
                    IsBossAlive = false;
                }
            }
        }

        if (missileMgr)
        {
            missileMgr->Render(hdc);
        }
    }
}

void Enemy::Move()
{
    if (enemyStatus == ENEMYSTATUS::ENTERANCE)
    {
        if (enterType == 0)
        {
            SlideEnterance_01();
        }
        else if (enterType == 1)
        {
            PointEnterance_01();
        }
        else if (enterType == 2)
        {
            SlideEnterance_02();
        }
        else if (enterType == 3)
        {
            PointEnterance_02();
        }
        else if (enterType == 6 )
        {
            BossEnterance();
        }
    }
    else if (enemyStatus == ENEMYSTATUS::MOVE)
    {
        HorizonMove();
        VerticalMove();
    }
}

void Enemy::Enterance()
{
    if (enemyStatus == ENEMYSTATUS::NONE)
    {
        srand(time(NULL));
        enterType = rand() % 4;

        if (enterType == 0)
        {
            SetPos({ 0, 150 });
        }
        else if (enterType == 1)
        {
            SetPos({ WINSIZE_X / 2, 0 });
        }
        else if (enterType == 2)
        {
            SetPos({ WINSIZE_X, 150 });
        }
        else if (enterType == 3)
        {
            SetPos({ WINSIZE_X / 2, 0 });
        }
        if (enemyType == ENEMYTYPE::BOSS)
        {
            enterType = 6;
            SetPos({ WINSIZE_X / 2, WINSIZE_Y });
        }
        SetStatus(ENEMYSTATUS::ENTERANCE);
    }
}

void Enemy::SlideEnterance_01() // �̵�����
{
    pos.x += 800 * TimerManager::GetSingleton()->GetElapsedTime();

    if (pos.x >= 300)
    {
        SetStatus(ENEMYSTATUS::MOVE);
    }
}

void Enemy::SlideEnterance_02()
{
    pos.x -= 800 * TimerManager::GetSingleton()->GetElapsedTime();

    if (pos.x <= 700)
    {
        SetStatus(ENEMYSTATUS::MOVE);
    }
}

void Enemy::PointEnterance_01() //�������
{
    if (endMovePattern == false)
    {
        pos.y += sin(0) + 1000 * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y >= 500)
        {
            endMovePattern = true;
        }
    }
    else if (endMovePattern == true)
    {
        pos.y -= 300 * (TimerManager::GetSingleton()->GetElapsedTime());
        pos.x += moveSpeed * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y <= 150)
        {
            endMovePattern = false;
            SetStatus(ENEMYSTATUS::MOVE);
        }
    }
}

void Enemy::PointEnterance_02()
{
    if (endMovePattern == false)
    {
        pos.y += sin(0) + 1000 * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y >= 500)
        {
            endMovePattern = true;
        }
    }
    else if (endMovePattern == true)
    {
        pos.y -= 300 * (TimerManager::GetSingleton()->GetElapsedTime());
        pos.x -= moveSpeed * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y <= 150)
        {
            endMovePattern = false;
            SetStatus(ENEMYSTATUS::MOVE);
        }
    }
}

void Enemy::BossEnterance()
{
    checkTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (endMovePattern != true)
    {
        pos.y -= 2000 * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y < -300)
        {
            endMovePattern = true;
        }
    }
    if (endMovePattern == true && checkTimer >= 1)
    {
        pos.y += moveSpeed * (TimerManager::GetSingleton()->GetElapsedTime());
        if (pos.y >= 150)
        {
            checkTimer = 0;
            endMovePattern = false;
            SetStatus(ENEMYSTATUS::MOVE);
        }
    }
}

void Enemy::HorizonMove() 
{
    checkTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (pos.x > WINSIZE_X-200 || pos.x < 200)
    {
        dir *= -1;
        if (checkTimer >= 3)
        {
            checkTimer = 0;
        }
    }
    pos.x -= -dir * moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
}

void Enemy::VerticalMove()
{
    if (pos.y > 200 || pos.y < 150)
    {
        verticalDir *= -1;
    }
    pos.y += -verticalDir * 70 * TimerManager::GetSingleton()->GetElapsedTime();
}
