#ifndef LABLE_H
#define LABLE_H 
#include <string>
using namespace std;

class Lable{
private:
	DWORD color;
	COORD loc;
	string text;

public:
	Lable(DWORD, COORD, string);
	Lable(const Lable&);
	~Lable();

};

#endif