#include "Number.h"
#include "Image.h"

HRESULT Number::Init()
{
	number_100 = ImageManager::GetSingleton()->FindImage("Number");
	if (number_100 == nullptr)
	{
		MessageBox(g_hWnd,
			"Number°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}
	number_10 = ImageManager::GetSingleton()->FindImage("Number");
	if (number_10 == nullptr)
	{
		MessageBox(g_hWnd,
			"Number°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}
	number_1 = ImageManager::GetSingleton()->FindImage("Number");
	if (number_1 == nullptr)
	{
		MessageBox(g_hWnd,
			"Number°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}

	scoreHundredPlus = 0;
	scoreTenPlus = 9;
	scorePlus = 9;

	scoreAdd = 1;

	return S_OK;
}

void Number::Release()
{
	SAFE_RELEASE(number_100);
	SAFE_RELEASE(number_10);
	SAFE_RELEASE(number_1);
}

void Number::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD9))
	{
		if (!(scoreHundredPlus >= 8 && scoreTenPlus >= 8 && scorePlus >= 8))
		{
			scorePlus += scoreAdd;
			if (scorePlus >= 10)
			{
				scoreTenPlus += 1;
				scorePlus = 0;

				if (scoreTenPlus >= 10)
				{
					scoreHundredPlus += 1;
					scoreTenPlus = 0;
				}
			}
		}
		else
		{
			scoreHundredPlus = 8;
			scoreTenPlus = 8;

			scorePlus = 8;
		}
	}
}

void Number::Render(HDC hdc)
{

	if (number_100)
	{
		number_100->FrameRender(hdc, 80, 80, scoreHundredPlus, 0, true);
	}
	if (number_10)
	{
		number_10->FrameRender(hdc, 105, 80, scoreTenPlus, 0, true);
	}
	if (number_1)
	{
		number_1->FrameRender(hdc, 130, 80, scorePlus, 0, true);
	}
}
