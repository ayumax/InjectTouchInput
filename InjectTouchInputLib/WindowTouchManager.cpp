#include "stdafx.h"
#include "WindowTouchManager.h"

WindowTouchManager::WindowTouchManager()
{
	InitializeTouchInjection(10, TOUCH_FEEDBACK_NONE);
}

WindowTouchManager::~WindowTouchManager()
{
	for (int i = 0; i < (int)Touches.size(); ++i)
	{
		delete Touches[i];
	}

	Touches.clear();
}

void WindowTouchManager::InitTouches(int TouchCount)
{
	for (int i = 0; i < TouchCount; ++i)
	{
		WindowTouchItem* touchItem = new WindowTouchItem(i);

		Touches.push_back(touchItem);
	}
}

void WindowTouchManager::TouchDown(int TouchID, int xPos, int yPos)
{
	if (TouchID >= (int)Touches.size()) return;

	Touches[TouchID]->TouchDown(xPos, yPos);
}

void WindowTouchManager::TouchMove(int TouchID, int xPos, int yPos)
{
	if (TouchID >= (int)Touches.size()) return;

	Touches[TouchID]->TouchMove(xPos, yPos);
}

void WindowTouchManager::TouchUp(int TouchID)
{
	if (TouchID >= (int)Touches.size()) return;

	Touches[TouchID]->TouchUp();
}

void WindowTouchManager::UpdateAllTouch()
{
	POINTER_TOUCH_INFO* touchInfos = new POINTER_TOUCH_INFO[Touches.size()];
	::memset(touchInfos, 0, sizeof(POINTER_TOUCH_INFO) * Touches.size());

	int setIndex = 0;
	for (int i = 0; i < (int)Touches.size(); ++i)
	{
		auto _touchItem = Touches[i];
		if (_touchItem->IsEnabledTouch())
		{
			::memcpy(&touchInfos[setIndex], _touchItem->GetTouchInfo(), sizeof(POINTER_TOUCH_INFO));
			setIndex++;
		}
	}

	if (setIndex > 0)
	{
		if (!InjectTouchInput(setIndex, touchInfos))
		{
			DWORD dwError = ::GetLastError();
			OutputDebugStringA("fail");
		}

		for (int i = 0; i < (int)Touches.size(); ++i)
		{
			auto _touchItem = Touches[i];
			if (_touchItem->IsEnabledTouch())
			{
				_touchItem->UpdateTouchNextState();
			}
		}
	}

	

	delete [] touchInfos;
}