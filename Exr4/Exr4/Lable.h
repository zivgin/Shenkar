#ifndef LABLE_H
#define LABLE_H 
#include <string>
#include "myLine.h"

using namespace std;

class Lable{
private:
	DWORD color;
	COORD loc;
	string text[3];

public:
	Lable(DWORD, COORD, myLine[]);
	Lable(DWORD, COORD, string[]);
	Lable(const Lable&);
	~Lable();

};

#endif