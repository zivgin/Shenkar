#include <iostream>
#include <Windows.h>
#include "Lable.h"
#include "myLine.h"


#define FIRST_ROW 10
#define FIRST_COLUMN 30

using namespace std;

//Global
HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD, COORD&, myLine*);
VOID MouseEventProc(MOUSE_EVENT_RECORD);

int main(void) {

	DWORD cNumRead, i;
	INPUT_RECORD irInBuf[128];

	DWORD fdwMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	if (!SetConsoleMode(hStdin, fdwMode)) {}
	//ErrorExit("SetConsoleMode"); 

	cout << "1. Press escape button at any time to exit\n";
	cout << "2. Use the arrow keys to guide trough the menu\n";
	cout << "3. Press the space bar key for choosing an option";


	//regular text color
	DWORD c = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	COORD cor = { FIRST_COLUMN, FIRST_ROW };

	myLine _text[3] = {
		{ "[ ] hello" },
		{ "[ ] hello world" },
		{ "[ ] hello another row" }
	};

	/*
	string _text[3];
	_text[0] = "[ ] hello";
	_text[1] = "[ ] hello world";
	_text[2] = "[ ] hello another row";

	string _Markedtext[3];
	_Markedtext[0] = "[X] hello";
	_Markedtext[1] = "[X] hello world";
	_Markedtext[2] = "[X] hello another row";
	*/

	Lable l(c, cor, _text);

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	//c = marked text color
	c = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;



	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, c);
	cout << _text[0].getUnMarked();





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

			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				cor.X = FIRST_COLUMN;
					SetConsoleCursorPosition(h, cor);

				KeyEventProc(irInBuf[i].Event.KeyEvent, cor, _text);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;
				/*
			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;
				*/
			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}



			/*
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
			*/
		}
	}
}

VOID ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

//	ExitProcess(0);
}


VOID KeyEventProc(KEY_EVENT_RECORD ker, COORD& _tempCor, myLine* _text) {
	//printf("Key event: ");
	
	if (ker.bKeyDown){

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD c = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		//setting the marked color
		DWORD m = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;

		if ((((ker).uChar).AsciiChar == '8' && (((ker).uChar)).UnicodeChar == 56) || ((ker).wVirtualKeyCode == VK_UP))			//can be done with VK_NUMPAD8 as well
		{

			//setting the normal color back
			SetConsoleTextAttribute(h, c);

			//print the text again unmarked
			if (_text[_tempCor.Y - FIRST_ROW].getFlag() == false)
				cout << _text[_tempCor.Y - FIRST_ROW].getUnMarked();

			else
				cout << _text[_tempCor.Y - FIRST_ROW].getMarked();


			//move to the next line
			_tempCor.Y = ((_tempCor.Y > FIRST_ROW) ? _tempCor.Y - 1 : FIRST_ROW+2);
			SetConsoleCursorPosition(h, _tempCor);

			//setting the marked color
			SetConsoleTextAttribute(h, m);

			//print the line again - this time marked
			if (_text[_tempCor.Y - FIRST_ROW].getFlag() == false)
				cout << _text[_tempCor.Y - FIRST_ROW].getUnMarked();

			else
				cout << _text[_tempCor.Y - FIRST_ROW].getMarked();

		}

		//can be done with VK_NUMPAD2 as well
		else if ((((ker).uChar).AsciiChar == '2' && (((ker).uChar)).UnicodeChar == 50) || ((ker).wVirtualKeyCode == VK_DOWN))
		{
			//setting the normal color back
			SetConsoleTextAttribute(h, c);

			//print the text again unmarked
			if (_text[_tempCor.Y - FIRST_ROW].getFlag() == false)
				cout << _text[_tempCor.Y - FIRST_ROW].getUnMarked();

			else
				cout << _text[_tempCor.Y - FIRST_ROW].getMarked();
			

			//move to the next line
			_tempCor.Y = ((_tempCor.Y < FIRST_ROW + 2) ? _tempCor.Y + 1 : FIRST_ROW);
			SetConsoleCursorPosition(h, _tempCor);

			//setting the marked color
			SetConsoleTextAttribute(h, m);

			//print the line again - this time marked
			if (_text[_tempCor.Y - FIRST_ROW].getFlag() == false)
				cout << _text[_tempCor.Y - FIRST_ROW].getUnMarked();
			
			else
				cout << _text[_tempCor.Y - FIRST_ROW].getMarked();

		}

		//space bar
		else if ((ker).wVirtualKeyCode == VK_SPACE){
			if (_text[_tempCor.Y - FIRST_ROW].getFlag() == false){
				cout << _text[_tempCor.Y - FIRST_ROW].getMarked();
				_text[_tempCor.Y - FIRST_ROW].changeFlag();
			}
			else{
				cout << _text[_tempCor.Y - FIRST_ROW].getUnMarked();
				_text[_tempCor.Y - FIRST_ROW].changeFlag();
			}
		}

		// if escape key was pressed - end program
		else if((ker).wVirtualKeyCode == VK_ESCAPE){
			system("CLS");
			exit(1);
		}
	}
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