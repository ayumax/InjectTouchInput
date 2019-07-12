// InjectTouchInputTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "stdafx.h"
#include "WindowTouchManager.h"

int main()
{
	::Sleep(3000);

	WindowTouchManager manager;

	manager.InitTouches(1);

	manager.TouchDown(0, 100, 300);
	manager.UpdateAllTouch();
	::Sleep(10);

	manager.TouchMove(0, 100, 350);
	manager.UpdateAllTouch();
	::Sleep(10);

	manager.TouchMove(0, 200, 400);
	manager.UpdateAllTouch();
	::Sleep(10);

	manager.TouchMove(0, 200, 430);
	manager.UpdateAllTouch();
	::Sleep(10);

	manager.TouchUp(0);
	manager.UpdateAllTouch();

}
