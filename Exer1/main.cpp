#include <iostream>
#include <Windows.h>
#include "Lable.h"

using namespace std;

//Global
HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);

int main(void) {

	DWORD cNumRead, i;
	INPUT_RECORD irInBuf[128];

	DWORD fdwMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	if (!SetConsoleMode(hStdin, fdwMode)) {}
		//ErrorExit("SetConsoleMode"); 


	DWORD c = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	COORD cor = { 7, 7 };
	string text = "hello";
	Lable l(c, cor, text);

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	while (1)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 

			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++) {
			switch (irInBuf[i].EventType) {
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			default:
				//ErrorExit("Unknown event type");
				break;
			}
		}
	}
}

VOID ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

//	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker) {
	//printf("Key event: ");

	//if (ker.bKeyDown)
		//printf("key pressed\n");
	//else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");

	/*switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}*/
}