#include <windows.h>
#include <stdio.h>
#include "Lable.h"

//box size
#define FIRST_ROW 10
#define FIRST_COLUMN 25

#define WIDTH 20
#define HEIGHT 1

using namespace std;


// Get the standard input & output handle. 
HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD fdwSaveOldMode;
string line;


VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD, COORD&);
VOID MouseEventProc(MOUSE_EVENT_RECORD, COORD&);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int main(VOID)
{
	DWORD cNumRead, fdwMode, i, count=0;
	INPUT_RECORD irInBuf[WIDTH];

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
			WIDTH,         // size of read buffer 
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
	int i, currentPos = _tempCor.X - 26;
	if (ker.bKeyDown){

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD c = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		//setting the marked color
		DWORD m = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		SetConsoleTextAttribute(h, m);
		//Up & Down control
		/*
		if ((((ker).uchar).asciichar == '8' && (((ker).uchar)).unicodechar == 56) || ((ker).wvirtualkeycode == vk_up))			//can be done with vk_numpad8 as well
		{
			//moving upward
			if (_tempcor.y > first_row + 1){
				_tempcor.y--;
				setconsolecursorposition(h, _tempcor);
			}
		}


		//can be done with vk_numpad2 as well
		else if ((((ker).uchar).asciichar == '2' && (((ker).uchar)).unicodechar == 50) || ((ker).wvirtualkeycode == vk_down))
		{
			//moving downward
			if (_tempcor.y < first_row + height){
				_tempcor.y++;
				setconsolecursorposition(h, _tempcor);
			}

		}
*/		

		//can be done with VK_NUMPAD4 as well
		//else
		if ((((ker).uChar).AsciiChar == '4' && (((ker).uChar)).UnicodeChar == 52) || ((ker).wVirtualKeyCode == VK_LEFT))
		{
			//moving left
			if (FIRST_COLUMN + 1 < _tempCor.X){
				_tempCor.X--;
				SetConsoleCursorPosition(h, _tempCor);
			}

		}



		//can be done with VK_NUMPAD6 as well
		else if ((((ker).uChar).AsciiChar == '6' && (((ker).uChar)).UnicodeChar == 54) || ((ker).wVirtualKeyCode == VK_RIGHT))
		{
			//moving right
			if (FIRST_COLUMN + WIDTH - 1 >= _tempCor.X){
				//case1: |_
				if (currentPos == line.length() && currentPos == 0){}
				//case2: a_bc / abc_
				else if (currentPos >= 0 && currentPos + 1 <= line.length()){
					_tempCor.X++;
					SetConsoleCursorPosition(h, _tempCor);
				}
			}

		}

		//if backspace
		else if ((ker).wVirtualKeyCode == VK_BACK){
			if (FIRST_COLUMN + 1 < _tempCor.X){
				if (currentPos >= 0 && currentPos + 1 <= line.length()){
					for (i = currentPos; i < line.length(); i++){
						line[i - 1] = line[i];
						_tempCor.X--;
						SetConsoleCursorPosition(h, _tempCor);
						cout << line[i];
						_tempCor.X += 2;
						SetConsoleCursorPosition(h, _tempCor);
					}
					line.pop_back();
					_tempCor.X--;
					SetConsoleCursorPosition(h, _tempCor);
					SetConsoleTextAttribute(h, c);
					cout << " ";
					_tempCor.X = (currentPos - 1) + 26; //return to last position
					SetConsoleCursorPosition(h, _tempCor);
					SetConsoleTextAttribute(h, m);
				}
				else{
					_tempCor.X--;
					SetConsoleCursorPosition(h, _tempCor);
					SetConsoleTextAttribute(h, c);
					line.pop_back();
					cout << " ";
					SetConsoleCursorPosition(h, _tempCor);
					SetConsoleTextAttribute(h, m);
				}
			}
		}


		//enter key
		else if ((ker).wVirtualKeyCode == VK_RETURN){
			if (FIRST_ROW + HEIGHT > _tempCor.Y)
				_tempCor.Y++;
			_tempCor.X = FIRST_COLUMN + 1;
			SetConsoleCursorPosition(h, _tempCor);
		}
		// if escape key was pressed - end program
		else if ((ker).wVirtualKeyCode == VK_ESCAPE){
			system("CLS");
			exit(1);
		}


		else{ //key pressed
			if (_tempCor.X < (FIRST_COLUMN + WIDTH) && line.length() < WIDTH){
				if (currentPos >= 0 && currentPos + 1 <= line.length()){
					line += ker.uChar.AsciiChar;
					for (i = line.length() - 1; i >= currentPos; i--){
						line[i] = line[i - 1];
					}
					line[currentPos] = ker.uChar.AsciiChar;
					for (i = currentPos; i < line.length(); i++){
						cout << line[i];
						_tempCor.X++;
						SetConsoleCursorPosition(h, _tempCor);
					}
					_tempCor.X = (currentPos + 1) + 26;
					SetConsoleCursorPosition(h, _tempCor);
					currentPos++;
				}
				else{
					line += ker.uChar.AsciiChar;
					cout << line[currentPos];
					_tempCor.X++;
				}

				/*else if ((_tempCor.X == FIRST_COLUMN + WIDTH) && (_tempCor.Y < FIRST_ROW + HEIGHT)){
					_tempCor.Y++;
					_tempCor.X = FIRST_COLUMN + 1;
					SetConsoleCursorPosition(h, _tempCor);
					line += ker.uChar.AsciiChar;
					cout << line[currentPos];
					}

					else if ((_tempCor.X < FIRST_COLUMN + WIDTH) && (_tempCor.Y == FIRST_ROW + HEIGHT)){
					line += ker.uChar.AsciiChar;
					cout << line[currentPos];
					_tempCor.X++;
					}*/
			}

		}
	}
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer, COORD& _tempCor)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	int currentPos = _tempCor.X - 26;
	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			if (((FIRST_COLUMN < ((mer).dwMousePosition).X) && (((mer).dwMousePosition).X < FIRST_COLUMN + WIDTH + 1)) &&
				((FIRST_ROW < ((mer).dwMousePosition).Y) && (((mer).dwMousePosition).Y < FIRST_ROW + HEIGHT + 1))){
				if (((mer).dwMousePosition).X -26 <= line.length()){ //<--desable/enable mouse
					_tempCor.X = ((mer).dwMousePosition).X;
					_tempCor.Y = ((mer).dwMousePosition).Y;

					SetConsoleCursorPosition(h, _tempCor);
				};
			
			};
		}

		else{}

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
