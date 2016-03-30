#ifndef MYLINE_H
#define MYLINE_H
#include <iostream>
#include <string>
using namespace std;

class myLine{
private:
	string unMarked;
	string marked;
	bool flag;

public:
	myLine(string);

	string getMarked() const;
	string getUnMarked() const;

	bool getFlag() const;
	void changeFlag();

	~myLine();

};

#endif