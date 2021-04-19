#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionChecker.h"

HRESULT Enemy::Init(CollisionChecker* collisionChecker, int posX, int posY)
{
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, 
            "Enemy에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
        return E_FAIL;
    }
    checkTimer = 0;
    enemyType = ENEMYTYPE::NORMAL;
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
    enemyStatus = NONE;
    // 미사일 매니저
    this->collisionChecker = collisionChecker;
    missileMgr = new MissileManager();
    missileMgr->Init(collisionChecker, this);
    fireCount = 0;
    return S_OK;
}

HRESULT Enemy::BossInit(CollisionChecker* collisionChecker, int posX, int posY)
{
    image = ImageManager::GetSingleton()->FindImage("Boss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd,
            "Boss에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
        return E_FAIL;
    }
    checkTimer = 0;
    enemyType = ENEMYTYPE::BOSS;
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
    enemyStatus = NONE;
    // 미사일 매니저
    missileMgr = new MissileManager();
    this->collisionChecker = collisionChecker;
    missileMgr->Init(collisionChecker, this);
    fireCount = 0;
    collisionChecker->AddActiveEnemy(this);
    fireCount = 0;
    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missileMgr);

}

void Enemy::Update()
{
    if (isAlive)
    {
        Enterance();
        Move();
        hitBox = GetRectToCenter(pos.x, pos.y, 100, 200);
        if (enemyStatus == ENEMYSTATUS::FIRE)
        {
            // 미사일 발사
            if (missileMgr)
            {
                // 함수 호출 주기를 바꿔보자.
                fireCount++;
                if (fireCount % 20 == 0)
                {
                    fireCount = 0;
                    missileMgr->Fire();
                }
                    missileMgr->Update();
            }
        }
        // 애니메이션 프레임
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
    }

}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {

        if (image && enemyType == ENEMYTYPE::NORMAL)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
            RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
        }
        else if (image && enemyType == ENEMYTYPE::BOSS)
        {
            image->Render(hdc, pos.x, pos.y, true);
            Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
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

void Enemy::SlideEnterance_01() // 이동등장
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

void Enemy::PointEnterance_01() //기습등장
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

void Enemy::HorizonMove() // 기본 이동
{
    checkTimer += TimerManager::GetSingleton()->GetElapsedTime();
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
        if (checkTimer >= 3)
        {
            checkTimer = 0;
        }
    }
    pos.x -= -dir * moveSpeed * TimerManager::GetSingleton()->GetElapsedTime();
}
