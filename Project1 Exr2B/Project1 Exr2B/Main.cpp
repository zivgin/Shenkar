#include <windows.h>
#include <stdio.h>
#include "Lable.h"

//box size
#define FIRST_ROW 10
#define FIRST_COLUMN 25

#define WIDTH 30
#define HEIGHT 5

using namespace std;


// Get the standard input & output handle. 
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD, COORD&);
VOID MouseEventProc(MOUSE_EVENT_RECORD, COORD&);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	cout << "1. Press escape button at any time to exit\n";
	cout << "2. Use the arrow keys to guide trough the menu\n";
	cout << "3. Press the space bar key for choosing an option\n";

	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 

	//regular text color
	DWORD c = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	COORD cor = { FIRST_COLUMN, FIRST_ROW };


	//c = marked text color
	DWORD m = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;


	Lable l(c, cor, WIDTH, HEIGHT);
	cor.X++;
	cor.Y++;

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

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent, cor);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent, cor);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}



VOID KeyEventProc(KEY_EVENT_RECORD ker, COORD& _tempCor) {
	//printf("Key event: ");

	if (ker.bKeyDown){

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD c = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		//setting the marked color
		DWORD m = FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
		SetConsoleTextAttribute(h, m);

		if ((((ker).uChar).AsciiChar == '8' && (((ker).uChar)).UnicodeChar == 56) || ((ker).wVirtualKeyCode == VK_UP))			//can be done with VK_NUMPAD8 as well
		{
			//moving upward
			if (_tempCor.Y > FIRST_ROW + 1){
				_tempCor.Y--;
				SetConsoleCursorPosition(h, _tempCor);
			}
		}


		//can be done with VK_NUMPAD2 as well
		else if ((((ker).uChar).AsciiChar == '2' && (((ker).uChar)).UnicodeChar == 50) || ((ker).wVirtualKeyCode == VK_DOWN))
		{
			//moving downward
			if (_tempCor.Y < FIRST_ROW + HEIGHT){
				_tempCor.Y++;
				SetConsoleCursorPosition(h, _tempCor);
			}

		}


		//can be done with VK_NUMPAD4 as well
		else if ((((ker).uChar).AsciiChar == '4' && (((ker).uChar)).UnicodeChar == 52) || ((ker).wVirtualKeyCode == VK_LEFT))
		{
			//moving left
			if (FIRST_COLUMN+1 < _tempCor.X){
				_tempCor.X--;
				SetConsoleCursorPosition(h, _tempCor);
			}

		}



		//can be done with VK_NUMPAD6 as well
		else if ((((ker).uChar).AsciiChar == '6' && (((ker).uChar)).UnicodeChar == 54) || ((ker).wVirtualKeyCode == VK_RIGHT))
		{
			//moving right
			if (FIRST_COLUMN + WIDTH - 1> _tempCor.X){
				_tempCor.X++;
				SetConsoleCursorPosition(h, _tempCor);
			}

		}

		//if backspace
		else if ((ker).wVirtualKeyCode == VK_BACK){
			if (FIRST_COLUMN + 1<_tempCor.X){
				_tempCor.X--;
				SetConsoleCursorPosition(h, _tempCor);
				SetConsoleTextAttribute(h, c);
				cout << " ";
				//_tempCor.X--;
				SetConsoleCursorPosition(h, _tempCor);
				SetConsoleTextAttribute(h, m);
			}
		}


		//enter key
		else if ((ker).wVirtualKeyCode == VK_RETURN){
			if (FIRST_ROW + HEIGHT>_tempCor.Y)
				_tempCor.Y++;
			_tempCor.X = FIRST_COLUMN + 1;
			SetConsoleCursorPosition(h, _tempCor);
		}
		// if escape key was pressed - end program
		else if ((ker).wVirtualKeyCode == VK_ESCAPE){
			system("CLS");
			exit(1);
		}


		else
			if (_tempCor.X < (FIRST_COLUMN + WIDTH)){
				cout << (ker).uChar.AsciiChar;
				_tempCor.X++;
			}

			else if ((_tempCor.X == FIRST_COLUMN + WIDTH) && (_tempCor.Y < FIRST_ROW + HEIGHT)){
				_tempCor.Y++;
				_tempCor.X = FIRST_COLUMN + 1;
				SetConsoleCursorPosition(h, _tempCor);
				cout << (ker).uChar.AsciiChar;
			}

			else if ((_tempCor.X < FIRST_COLUMN + WIDTH) && (_tempCor.Y == FIRST_ROW + HEIGHT)){
				cout << (ker).uChar.AsciiChar;
				_tempCor.X++;
			}
	}

}



VOID MouseEventProc(MOUSE_EVENT_RECORD mer, COORD& _tempCor)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			if (((FIRST_COLUMN<((mer).dwMousePosition).X) && (((mer).dwMousePosition).X<FIRST_COLUMN+WIDTH + 1)) &&
				((FIRST_ROW<((mer).dwMousePosition).Y) && (((mer).dwMousePosition).Y<FIRST_ROW + HEIGHT + 1))){
			_tempCor.X = ((mer).dwMousePosition).X;
			_tempCor.Y = ((mer).dwMousePosition).Y;

			SetConsoleCursorPosition(h, _tempCor);
			}
		}
		/*
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		*/
		else
		{
			//printf("button press?\n");
		}
		break;
	case DOUBLE_CLICK:
		//printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		//printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		//printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel\n");
		break;
	default:
		//printf("unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
