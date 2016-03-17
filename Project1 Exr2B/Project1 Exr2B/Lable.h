#ifndef LABLE_H
#define LABLE_H 
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Lable{
private:
	DWORD color;
	COORD loc;
	string text[3];

public:
	Lable(DWORD, COORD, int, int);
	Lable(const Lable&);

	//methods
	void containerBuilder(HANDLE h, COORD _loc, int, int);

	//destructor
	~Lable();

};

#endif