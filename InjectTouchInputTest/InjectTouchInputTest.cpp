// InjectTouchInputTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "stdafx.h"
#include "WindowTouchManager.h"

int main()
{
	::Sleep(000);

	WindowTouchManager manager;

	manager.InitTouches(2);

	manager.TouchDown(0, 100, 300);
	manager.UpdateAllTouch();

	Sleep(50);

	manager.TouchMove(0, 100, 300);
	manager.UpdateAllTouch();

	manager.TouchDown(1, 100, 300);
	manager.UpdateAllTouch();

	Sleep(50);

	manager.TouchMove(0, 100, 300);
	manager.UpdateAllTouch();


	manager.TouchMove(0, 100, 350);
	manager.UpdateAllTouch();
	
	Sleep(50);

	manager.TouchUp(0);
	manager.UpdateAllTouch();
	Sleep(50);

	manager.TouchUp(1);
	manager.UpdateAllTouch();

}
