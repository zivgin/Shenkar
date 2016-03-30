#include <iostream>
#include <Windows.h>
#include "comboBox.h"
using namespace std;


int main(void) {

	
	DWORD cNumRead, i;
	INPUT_RECORD irInBuf[128];

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	DWORD fdwMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	DWORD c = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	COORD cor = { 25, 5 };
	string text = "Choose Number";
	ComboBox cb(c, cor, text, hStdin, hStdout);

	


	while (1) {
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,			// input buffer handle 
			irInBuf,		// buffer to read into 
			128,			// size of read buffer 
			&cNumRead))		// number of records read 

			cb.ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			switch (irInBuf[i].EventType) {
			case KEY_EVENT: // keyboard input
				cb.KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
				if (irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) cb.mousePressed(irInBuf[i].Event.MouseEvent);
				else if (irInBuf[i].Event.MouseEvent.dwEventFlags == MOUSE_MOVED) cb.mouseMoved(irInBuf[i].Event.MouseEvent);
				break;

			}
		}
	}
}

