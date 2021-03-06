#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
#include <cstdlib>
//window size must be 1016*1008
int permY = 0;
HWND eveWindow;
void pressKey(WORD key, int x);
void ClickMouse(int x, int y);
void DoubleClickMouse(int x, int y);
void RightClickMouse(int x, int y);
void ClickUp(int x, int y);
void ClickDown(int x, int y);
void MoveMouse(int x, int y, int rmouse);
bool IsBlack(int x, int y);
bool IsYellow(int x, int y);
void undock();
void dock();
int warp();
void recallDrones();
void launchDrones();
int checkInvetory();
int checkDamage();
void unload();
int mine();
void target();
void KeyUp(WORD key, int x);
void KeyDown(WORD key, int x);
int belt = 0;
bool IsWhite(int x, int y);
void shutdown();
int colour;
int check = 0;
int main(int argc, CHAR *argv[])
{
	srand(time(NULL));
	POINT ptMouse;
	RECT windowPosition;
	eveWindow = FindWindow(NULL, TEXT("EVE - Miner Esubria"));
	COLORREF color1;
	COLORREF color2;
	COLORREF color3;
	HDC hDC;

	if (eveWindow == NULL)
	{
		cout << "Could not find EVE window, closing. make sure EVE is open \n" ;
			system("pause");
		return 0;
	}
	SetForegroundWindow(eveWindow);
	Sleep(2000);

	GetWindowRect(eveWindow, &windowPosition);
	GetCursorPos(&ptMouse);

	cout << "everything Checks out\n" ;
	cout << "------------------------------------\n" ;
	while (true) {
		check = 0;
		undock();
		cout << "undocked\n";
		warp();
		cout << "warped\n";
		launchDrones();
		cout << "drones launched\n";
		hDC = GetDC(NULL);

		color3 = GetPixel(hDC, 776 + windowPosition.left, 249 + windowPosition.top);
		ReleaseDC(GetDesktopWindow(), hDC);
		if (GetRValue(color3) > 120)
		{
			check = 1;
			belt++;
			cout << "belt empty\n";
		}
		else {
			target();
			cout << "targeted\n";
			mine();
			cout << "mining\n";
		}


		while (check ==0)
		{
			shutdown();
			if (checkInvetory() == 1)
			{
				check = 1;
				cout << "inventory full\n";
			}
			else if (checkDamage() == 1)
			{
				check = 1;
				cout << "taking damage\n";
				belt++;
			}
			Sleep(1000);
			hDC = GetDC(NULL);

			color3 = GetPixel(hDC, 644+windowPosition.left, 114+windowPosition.top);
			ReleaseDC(GetDesktopWindow(), hDC);
			colour = GetRValue(color3);
			//cout << to_string(colour)+"\n";
			if (GetRValue(color3) < 170)
			{
				target();
				cout << "targeted\n";
				mine();
				cout << "mining\n";
				
			}
			hDC = GetDC(NULL);
			color3 = GetPixel(hDC, 780+windowPosition.left, 238+windowPosition.top);
			ReleaseDC(GetDesktopWindow(), hDC);
			if (GetRValue(color3)>120)
			{
				check = 1;
				belt++;
				cout << "belt empty\n";
			}

		}
		if (belt >= 16)
		{
			belt = 0;
		}
		recallDrones();
		cout << "drones recalled\n";
		dock();
		cout << "docked\n";
		unload();
		cout << "unloaded\n";
	}
	return 0;
}
void recallDrones()
{
	KeyDown(VK_SHIFT, 1);
	Sleep(100);
	pressKey(0x52, 1);
	KeyUp(VK_SHIFT, 1);
	//Sleep(7000);

}
void launchDrones()
{
	KeyDown(VK_SHIFT, 1);
	Sleep(100);
	pressKey(0x46, 1);
	KeyUp(VK_SHIFT, 1);

}
int checkInvetory()
{
	if (IsBlack(367, 646) == false)
		return 1;
	else
		return 0;
}
int checkDamage()
{
	if (IsBlack(502, 871) == false)
		return 1;
	else
		return 0;
}
void unload()
{
	MoveMouse(300, 800, 2);
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	int mX = ptMouse.x;
	int mY = ptMouse.y;
	Sleep(100);
	MoveMouse(335, 810, 1);
	MoveMouse(240, 700, 4);
	MoveMouse(132, 735, 5);
	Sleep(2000);

}
int mine()
{
	int check = 0;
	COLORREF color;
	HDC hDC;
	/*while (check == 0)
	{

		hDC = GetDC(NULL);
		if (hDC == NULL)
			return 1;
		color = GetPixel(hDC, 523, 978);
		if (color == CLR_INVALID)
			return 1;
		ReleaseDC(GetDesktopWindow(), hDC);
		if (GetRValue(color) > 110)
			check = 1;
	}*/
	pressKey(VK_F1, 1);
	pressKey(VK_F2,1);
	Sleep(200);
	KeyDown(VK_CONTROL, 1);
	Sleep(200);
	pressKey(VK_SPACE, 1);
	Sleep(150);
	KeyUp(VK_CONTROL, 1);
	//MoveMouse(701, 114, 1);
	return 0;
}
void target()
{
	int check = 0;

	MoveMouse(627, 220, 6);


	ClickMouse(627, 220 );

	MoveMouse(644, 114, 1);
	KeyDown(VK_MENU, 1);

	pressKey(VK_F1, 1);
	pressKey(VK_F2, 1);
	KeyUp(VK_MENU, 1);
	Sleep(25000);
	check = 0;
	while (check == 0)
	{
		shutdown();
		if (IsBlack(508, 985) == true)
			check = 1;
	}
	MoveMouse(765, 114, 1);
	KeyDown(VK_MENU, 1);

	pressKey(VK_F1, 1);
	KeyUp(VK_MENU, 1);
	Sleep(5000);
}
int warp()
{
	MoveMouse(85, 154, 1);
	Sleep(100 + rand() % 100);
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	int mX = ptMouse.x;
	int mY = ptMouse.y;
	MoveMouse(125, 190, 6);
	Sleep(100 + rand() % 100);
	MoveMouse(271, 190, 6);
	MoveMouse(271, 190+(20*belt), 6);
	Sleep(100 + rand() % 100);
	MoveMouse(463, 190+ (20 * belt), 1);
	Sleep(20000);
	int check = 0;
	while (check == 0)
	{
		shutdown();
		if (IsBlack(508,985)==true)
			check = 1;
	}
	Sleep(10000);
	KeyDown(VK_CONTROL, 1);
	Sleep(200);
	pressKey(VK_SPACE, 1);
	Sleep(150);
	KeyUp(VK_CONTROL, 1);
	return 0;
}
void undock()
{
	MoveMouse(900, 211, 1);

	int check = 0;

		while (check == 0)
		{
			shutdown();
			if (IsBlack(27,88) == true)
			{
				check = 1;
			}
		
		}
		while (check == 1)
		{
			shutdown();
			if (IsBlack(27, 88) == false)
			{
				check = 2;
			}
		}

		Sleep(5000);
		KeyDown(VK_CONTROL, 1);
		Sleep(200);
		pressKey(VK_SPACE, 1);
		Sleep(150);
		KeyUp(VK_CONTROL, 1);


}
void dock()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	int mX = ptMouse.x;
	int mY = ptMouse.y;
	MoveMouse(85, 154, 1);
	Sleep(100 + rand() % 100);
	MoveMouse(122, 250, 6);
	Sleep(100 + rand() % 100);
	MoveMouse(339, 250, 6);
	Sleep(100 + rand() % 100);
	MoveMouse(576, 250, 6);
	MoveMouse(576, 310, 1);
	Sleep(100 + rand() % 100);
	int check = 0;
	int check2 = 0;
	while (check == 0)
	{
		cout << to_string(check)+"\n";
		shutdown();
		if (IsBlack(508, 985) == false)
			check = 1;
		if (check2 > 30000)
		{
			shutdown();
			if (IsBlack(508, 985) == true)
			{
				GetCursorPos(&ptMouse);
				mX = ptMouse.x;
				mY = ptMouse.y;
				MoveMouse(85, 154, 1);
				Sleep(100);
				MoveMouse(122, 250, 6);
				Sleep(100);
				MoveMouse(339, 250, 6);
				Sleep(100);
				MoveMouse(576, 250, 6);
				MoveMouse(576, 310, 1);
				Sleep(100);
				check2 = 0;
			}
		}
		Sleep(1);
		check2++;
	}
	while (check == 1)
	{
		cout << to_string(check) + "\n";
		shutdown();
		if (IsBlack(27, 88) == true)
		{
			check = 2;
		}

	}
	while (check == 2)
	{
		cout << to_string(check) + "\n";
		shutdown();
		if (IsBlack(27, 88) == false)
		{
			check = 3;
		}
	}
	Sleep(5000);
}
void pressKey(WORD key, int x)
{
	int y = 0;
		while (y <= x)
		{
			SetForegroundWindow(eveWindow);
				Sleep(200 + rand() % 250);
				INPUT* keyClick;
				keyClick = new INPUT;
				keyClick->ki.wVk = key;
				keyClick->type = INPUT_KEYBOARD;
				keyClick->ki.dwFlags = 0;
				keyClick->ki.time = 0;
				keyClick->ki.wScan = 0;
				keyClick->ki.dwExtraInfo = 0;

				SendInput(1, keyClick, sizeof(INPUT));
				Sleep(100);
				keyClick->ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, keyClick, sizeof(INPUT));
				y++;
		}
}
void KeyUp(WORD key, int x)
{

		SetForegroundWindow(eveWindow);
		Sleep(200 + rand() % 250);
		INPUT* keyClick;
		keyClick = new INPUT;
		keyClick->ki.wVk = key;
		keyClick->type = INPUT_KEYBOARD;
		keyClick->ki.dwFlags = 0;
		keyClick->ki.time = 0;
		keyClick->ki.wScan = 0;
		keyClick->ki.dwExtraInfo = 0;
		keyClick->ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, keyClick, sizeof(INPUT));

}
void KeyDown(WORD key, int x)
{
		SetForegroundWindow(eveWindow);
		Sleep(200 + rand() % 250);
		INPUT* keyClick;
		keyClick = new INPUT;
		keyClick->ki.wVk = key;
		keyClick->type = INPUT_KEYBOARD;
		keyClick->ki.dwFlags = 0;
		keyClick->ki.time = 0;
		keyClick->ki.wScan = 0;
		keyClick->ki.dwExtraInfo = 0;

		SendInput(1, keyClick, sizeof(INPUT));
}
void ClickMouse(int x, int y)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
void DoubleClickMouse(int x, int y)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
void RightClickMouse(int x, int y)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
}
void ClickDown(int x, int y)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(100);

}
void ClickUp(int x, int y)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(100);

}
void MoveMouse(int x, int y, int rmouse)
{
	SetForegroundWindow(eveWindow);
	Sleep(200 + rand() % 250);
	POINT ptMouse;
	RECT windowPosition;
	GetWindowRect(eveWindow,&windowPosition);
	int finalX =( windowPosition.left + x);
	int finalY = (windowPosition.top + y);
	GetCursorPos(&ptMouse);
	int mX = ptMouse.x;
	int mY = ptMouse.y;

	while (mX != finalX || mY != finalY)
	
	{
		shutdown();
		GetCursorPos(&ptMouse);
		mX = ptMouse.x;
		mY = ptMouse.y;
		int dy = 0;
		int dx = 0;

		if (finalX > mX)
		{
			if (mX != finalX)
			{
				dx = 2 + rand() % 2;
			}
		}
		else
		{
			if (mX != finalX)
			{
				dx = -2 - rand() % 2;
			}
		}
		if (finalY > mY)
		{
			if (mY != finalY)
			{
				dy = 2 + rand() % 2;
			}
		}
		else
		{
			if (mY != finalY)
			{
				dy = -2 - rand() % 2;
			}
		}
		SetCursorPos(mX + (dx), mY + (dy));
		SetForegroundWindow(eveWindow);
		Sleep(1);

	}
	if (rmouse == 1)
		ClickMouse(finalX, finalY);
	else if (rmouse == 2)
		RightClickMouse(finalX, finalY);
	else if (rmouse == 3)
		DoubleClickMouse(finalX, finalY);
	else if (rmouse == 4)
		ClickDown(finalX, finalY);
	else if (rmouse == 5)
		ClickUp(finalX, finalY);


}
bool IsYellow(int x, int y)
{
	SetForegroundWindow(eveWindow);
	RECT windowPosition;
	GetWindowRect(eveWindow, &windowPosition);
	int finalX = windowPosition.left + x;
	int finalY = windowPosition.right + y;
	bool result;
	COLORREF color;
	HDC hDC;
	hDC = GetDC(NULL);
	if (hDC == NULL)
		return 3;
	color = GetPixel(hDC, finalX, finalY);
	if (color == CLR_INVALID)
		return 1;
	ReleaseDC(GetDesktopWindow(), hDC);
	if ((GetRValue(color) ==25) && (GetGValue(color) ==25) && (GetBValue(color) ==25))
	{ 
		result = true;
	}
	else
	{
		result = false;

	}
	Sleep(10);
	return result;
}
bool IsWhite(int x, int y)
{
	SetForegroundWindow(eveWindow);
	RECT windowPosition;
	GetWindowRect(eveWindow, &windowPosition);
	int finalX = windowPosition.left + x;
	int finalY = windowPosition.right + y;
	bool result;
	COLORREF color;
	HDC hDC;
	hDC = GetDC(NULL);
	if (hDC == NULL)
		return 3;
	color = GetPixel(hDC, finalX, finalY);
	if (color == CLR_INVALID)
		return 1;
	ReleaseDC(GetDesktopWindow(), hDC);
	if ((GetRValue(color) >200) && (GetGValue(color) >200) && (GetBValue(color) >200))
	{
		result = true;
	}
	else
	{
		result = false;

	}
	Sleep(10);
	return result;
}
bool IsBlack(int x, int y)
{
	SetForegroundWindow(eveWindow);
	RECT windowPosition;
	GetWindowRect(eveWindow, &windowPosition);
	int finalX = windowPosition.left + x;
	int finalY = windowPosition.top + y;
	bool result;
	COLORREF color;
	HDC hDC;
	hDC = GetDC(NULL);
	if (hDC == NULL)
		return 3;
	color = GetPixel(hDC, finalX, finalY);
	if (color == CLR_INVALID)
		return 1;
	ReleaseDC(GetDesktopWindow(), hDC);
	if ((GetRValue(color) <GetGValue(color)+5) && (GetRValue(color) >(GetGValue(color)-5) )&&(GetRValue(color) < GetBValue(color) + 5) && (GetRValue(color) > (GetBValue(color) - 5)))
	{
		result = true;
	}
	else
	{
		result = false;

	}
	Sleep(10);
	return result;
}
void shutdown()
{
	if (GetAsyncKeyState(0x58) & 0x8000)
	{
		abort();
	}
}