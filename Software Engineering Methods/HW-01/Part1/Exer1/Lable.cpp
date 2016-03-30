#include <Windows.h>
#include <iostream>
#include "lable.h"

Lable::Lable(DWORD _color, COORD _loc, string _text) : color(_color), loc(_loc), text(_text)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(h, loc);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h, color);
	cout << text << endl;
}

Lable::~Lable() {

}






//
//VOID ErrorExit (LPSTR lpszMessage) 
//{ 
//    fprintf(stderr, "%s\n", lpszMessage); 
//
//    // Restore input mode on exit.
//
//    SetConsoleMode(hStdin, fdwSaveOldMode);
//
//    ExitProcess(0); 
//}