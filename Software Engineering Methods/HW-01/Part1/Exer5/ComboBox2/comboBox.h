#ifndef COMBOBOX_H
#define COMBOBOX_H 

#include <string>
using namespace std;

#define BOX_VERTICAL_SPACE 2
#define BOX_HORIZONTAL_SPACE 19
#define HORZ_CHAR '\xBA'
#define VERT_CHAR '\xCD'
#define TOP_LEFT_CHAR '\xC9'
#define TOP_RIGHT_CHAR '\xBB'
#define BOTTOM_LEFT_CHAR '\xC8'
#define BOTTOM_RIGHT_CHAR '\xBC'

class ComboBox{
private:
	DWORD color;
	COORD loc;
	string text;
	DWORD colorBack;			//giving the text a colored background when the cursor hover over it											
	DWORD clearBack;			//clears the background
	HANDLE hStdin;
	HANDLE hStdout;
	

public:
	ComboBox(DWORD, COORD, string, HANDLE, HANDLE);
	ComboBox(const ComboBox&);
	~ComboBox();

	void drawComboBox(string);				//creating the visual box
	void KeyEventProc(KEY_EVENT_RECORD);	
	void closeOptions(COORD);				
	void mousePressed(MOUSE_EVENT_RECORD);	
	void mouseMoved(MOUSE_EVENT_RECORD);
	VOID ErrorExit(LPSTR);

};

#endif