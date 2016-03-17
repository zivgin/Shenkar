#include <Windows.h>
#include <iostream>
#include "lable.h"

#define FIRST_ROW 10
#define FIRST_COLUMN 25

using namespace std;

Lable::Lable(DWORD _color, COORD _loc, int width, int height) : color(_color), loc(_loc)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, loc);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h, color);

	containerBuilder(h, loc, width, height);
}


void Lable::containerBuilder(HANDLE h, COORD _loc, int width, int height){
	int index = 0;


	//first line
	char corner = 201;
	cout << corner;

	while (index++ < width)
		cout << "=";
	index = 0;

	corner = 187;
	cout << corner << endl;

	//body of the container
	for (int i = 0; i < (height); i++){

		loc.Y += 1;
		SetConsoleCursorPosition(h, loc);
		cout << (char)186;

		int j = 0;
		while (j++ < width)
			cout << " ";

		cout << (char)186;
	}

	loc.Y += 1;
	SetConsoleCursorPosition(h, loc);

	//end line
	corner = 200;
	cout << corner;

	while (index++ < width)
		cout << "=";
	index = 0;

	corner = 188;
	cout << corner << endl;


	//getting the pointer to the begining
	loc.X = (FIRST_COLUMN)+1;
	loc.Y = FIRST_ROW + 1;
	SetConsoleCursorPosition(h, loc);
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