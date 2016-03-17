#include <Windows.h>
#include <iostream>
#include "lable.h"
#include "myLine.h"
using namespace std;

Lable::Lable(DWORD _color, COORD _loc, string _text[3]) : color(_color), loc(_loc)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, loc);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h, color);
	int index = 0;
	for (index = 0; index < 3; index++){
		cout << _text[index];
		_loc.Y = _loc.Y + 1;
		SetConsoleCursorPosition(h, _loc);
	}
	_loc.Y = _loc.Y - (index);
	SetConsoleCursorPosition(h, _loc);

}


Lable::Lable(DWORD _color, COORD _loc, myLine _lines[3]) : color(_color), loc(_loc)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, loc);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h, color);
	int index = 0;
	for (index = 0; index < 3; index++){
		cout << _lines[index].getUnMarked();
		_loc.Y = _loc.Y + 1;
		SetConsoleCursorPosition(h, _loc);
	}
	_loc.Y = _loc.Y - (index);
	SetConsoleCursorPosition(h, _loc);

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