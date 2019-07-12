#pragma once
#include "WindowTouchItem.h"

class WindowTouchManager
{
public:
	WindowTouchManager();
	~WindowTouchManager();

	void InitTouches(int TouchCount);
	void TouchDown(int TouchID, int xPos, int yPos);
	void TouchMove(int TouchID, int xPos, int yPos);
	void TouchUp(int TouchID);
	void UpdateAllTouch();

private:
	std::vector<WindowTouchItem*> Touches;
};

