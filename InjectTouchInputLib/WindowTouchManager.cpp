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

	for (int i = 0; i < (int)Touches.size(); ++i)
	{
		::memcpy(&touchInfos[i], Touches[i]->GetTouchInfo(), sizeof(POINTER_TOUCH_INFO));
	}

	if (!InjectTouchInput((uint32_t)Touches.size(), touchInfos))
	{
		OutputDebugStringA("fail");
	}

	delete [] touchInfos;
}