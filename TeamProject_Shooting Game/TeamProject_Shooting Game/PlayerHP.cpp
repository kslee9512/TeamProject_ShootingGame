#include "PlayerHP.h"
#include "Image.h"
#include "UiManager.h"

HRESULT PlayerHP::Init()
{
	life = ImageManager::GetSingleton()->FindImage("Life");
	if (life == nullptr)
	{
		MessageBox(g_hWnd,
			"life°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}
	unlife = ImageManager::GetSingleton()->FindImage("Unlife");
	if (unlife == nullptr)
	{
		MessageBox(g_hWnd,
			"unlife°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void PlayerHP::Release()
{
	SAFE_RELEASE(life);
	SAFE_RELEASE(unlife);
}

void PlayerHP::Update()
{	
	
}

void PlayerHP::Render(HDC hdc)
{
	if (unlife)
	{
		for (int i = 3; i > 0; i--)
		{
			unlife->Render(hdc, 170 - (60 * i), 650);
		}
	}
	if (life)
	{
		for (int i = 0; i < UiManager::GetSingleton()->GetPlayerCurrHP(); i++)
		{
			life->Render(hdc, -10 + (60 * i), 650);
		}		
	}
}
