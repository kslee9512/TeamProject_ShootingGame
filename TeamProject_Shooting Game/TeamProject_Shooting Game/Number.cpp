#include "Number.h"
#include "Image.h"

HRESULT Number::Init()
{
	number_10000 = ImageManager::GetSingleton()->FindImage("Number");
	if (number_10000 == nullptr)
	{
		MessageBox(g_hWnd,
			"Number°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}
	number_1000 = ImageManager::GetSingleton()->FindImage("Number");
	if (number_1000 == nullptr)
	{
		MessageBox(g_hWnd,
			"Number°¡ ¾ÈµÊ!", "½ÇÆÐ!", MB_OK);
		return E_FAIL;
	}
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

	score_10000 = 0;
	score_1000 = 0;
	score_100 = 0;
	score_10 = 0;
	score_1 = 0;

	scoreAdd = 1;

	return S_OK;
}

void Number::Release()
{
	SAFE_RELEASE(number_10000);
	SAFE_RELEASE(number_1000);
	SAFE_RELEASE(number_100);
	SAFE_RELEASE(number_10);
	SAFE_RELEASE(number_1);
}

void Number::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD9))
	{
		if (!(score_10000 >= 9 && score_1000 >= 9 && score_100 >= 9 && score_10 >= 9 && score_1 >= 9))
		{
			score_1 += scoreAdd;
			if (score_1 >= 10)
			{
				score_10 += 1;
				score_1 = 0;

				if (score_10 >= 10)
				{
					score_100 += 1;
					score_10 = 0;

					if (score_100 >= 10)
					{
						score_1000 += 1;
						score_100 = 0;

						if (score_1000 >= 10)
						{
							score_10000 += 1;
							score_1000 = 0;

							if (score_10000 >= 10)
							{
								score_10000 = 0;
							}
						}
					}
				}
			}
		}
		else
		{
			score_10000 = 9;
			score_1000 = 9;
			score_100 = 9;
			score_10 = 9;
			score_1 = 9;
		}
	}
}

void Number::Render(HDC hdc)
{
	if (number_10000)
	{
		number_10000->FrameRender(hdc, 80, 80, score_10000, 0, true);
	}
	if (number_1000)
	{
		number_1000->FrameRender(hdc, 105, 80, score_1000, 0, true);
	}
	if (number_100)
	{
		number_100->FrameRender(hdc, 130, 80, score_100, 0, true);
	}
	if (number_10)
	{
		number_1->FrameRender(hdc, 155, 80, score_10, 0, true);
	}
	if (number_1)
	{
		number_1->FrameRender(hdc, 180, 80, score_1, 0, true);
	}
}
