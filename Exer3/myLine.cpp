#include "myLine.h"

myLine::myLine(string unMarked){
	string test;
	this->unMarked = unMarked;
	this->marked = unMarked;
	marked.replace(1, 1, "X");

	flag = false;
}

string myLine::getMarked() const{
	return marked;
}
string myLine::getUnMarked() const{
	return unMarked;

}

bool myLine::getFlag() const{
	return flag;
}
void myLine::changeFlag(){
	this->flag = !flag;
}

myLine::~myLine(){}