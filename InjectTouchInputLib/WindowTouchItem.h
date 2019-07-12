#pragma once

class WindowTouchItem
{
public:
	WindowTouchItem(int TouchID);
	~WindowTouchItem();

	void TouchDown(int xPos, int yPos);
	void TouchMove(int xPos, int yPos);
	void TouchUp();

	void* GetTouchInfo();

private:
	void SetTouchPoint(int xPos, int yPos);

private:
	void* TouchInfo;

	int lastXPos = 0;
	int lastYPos = 0;
};

