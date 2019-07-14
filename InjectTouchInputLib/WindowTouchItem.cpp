#include "stdafx.h"
#include "WindowTouchItem.h"

WindowTouchItem::WindowTouchItem(int TouchID)
{
	TouchInfo = new POINTER_TOUCH_INFO();
	memset(TouchInfo, 0, sizeof(POINTER_TOUCH_INFO));
	POINTER_TOUCH_INFO* _TouchInfo = (POINTER_TOUCH_INFO*)TouchInfo;

	_TouchInfo->pointerInfo.pointerType = PT_TOUCH;
	_TouchInfo->pointerInfo.pointerId = TouchID;
	_TouchInfo->touchFlags = TOUCH_FLAG_NONE;
	_TouchInfo->touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
	_TouchInfo->orientation = 90;
	_TouchInfo->pressure = 32000;
}

WindowTouchItem::~WindowTouchItem()
{
	if (TouchInfo)
	{
		delete TouchInfo;
		TouchInfo = nullptr;
	}
}

void WindowTouchItem::TouchDown(int xPos, int yPos)
{
	SetTouchPoint(xPos, yPos);
	((POINTER_TOUCH_INFO*)TouchInfo)->pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

	isEnable = true;
}

void WindowTouchItem::TouchMove(int xPos, int yPos)
{
	SetTouchPoint(xPos, yPos);
	((POINTER_TOUCH_INFO*)TouchInfo)->pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
}

void WindowTouchItem::TouchUp()
{
	SetTouchPoint(lastXPos, lastYPos);
	((POINTER_TOUCH_INFO*)TouchInfo)->pointerInfo.pointerFlags = POINTER_FLAG_UP;
}

void WindowTouchItem::SetTouchPoint(int xPos, int yPos)
{
	POINTER_TOUCH_INFO* _TouchInfo = (POINTER_TOUCH_INFO*)TouchInfo;

	_TouchInfo->pointerInfo.ptPixelLocation.x = xPos;
	_TouchInfo->pointerInfo.ptPixelLocation.y = yPos;

	_TouchInfo->rcContact.top = yPos - 2;
	_TouchInfo->rcContact.bottom = yPos + 2;
	_TouchInfo->rcContact.left = xPos - 2;
	_TouchInfo->rcContact.right = xPos + 2;

	lastXPos = xPos;
	lastYPos = yPos;
}

void* WindowTouchItem::GetTouchInfo()
{
	return TouchInfo;
}

bool WindowTouchItem::IsEnabledTouch()
{
	return isEnable;
}

void WindowTouchItem::UpdateTouchNextState()
{
	POINTER_TOUCH_INFO* _TouchInfo = (POINTER_TOUCH_INFO*)TouchInfo;
	if (_TouchInfo->pointerInfo.pointerFlags == (POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT))
	{
		_TouchInfo->pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	}
	else if (_TouchInfo->pointerInfo.pointerFlags == POINTER_FLAG_UP)
	{
		isEnable = false;
	}
}

