#include <Windows.h>
#include <iostream>
#include "comboBox.h"
#include <vector>
using namespace std;


DWORD fdwSaveOldMode;
vector<string> arr = { "Num1", "Num2", "Num3", "Num4" }; //drop down options
bool isPressed = false;									//indicates if the options are open
int selectedCell = -1;									//indicates which optiion is selected
int lastMouseOver = -1;									
int keyOver = 1;

ComboBox::ComboBox(DWORD _color, COORD _loc, string _text, HANDLE _hStdin, HANDLE _hStdout) : color(_color), loc(_loc), text(_text), hStdin(_hStdin), hStdout(_hStdout) {
	SetConsoleTextAttribute(_hStdout, color);
	SetConsoleCursorPosition(_hStdout, loc);
	drawComboBox(text);
}

ComboBox::~ComboBox() {

}

void ComboBox::drawComboBox(string text) {
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	colorBack = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	clearBack = cbi.wAttributes;
	COORD tmpLoc = loc;
	for (int i = 0; i <= BOX_VERTICAL_SPACE; i++) {
		tmpLoc.Y += 1;
		SetConsoleCursorPosition(hStdout, tmpLoc);
		for (int j = 0; j <= BOX_HORIZONTAL_SPACE; j++) {
			if (i == 0) {
				if (j == 0) cout << TOP_LEFT_CHAR;
				else if (j == BOX_HORIZONTAL_SPACE) cout << TOP_RIGHT_CHAR << endl;
				else cout << VERT_CHAR;
			}
			else if (i == BOX_VERTICAL_SPACE) {
				if (j == 0) cout << BOTTOM_LEFT_CHAR;
				else if (j == BOX_HORIZONTAL_SPACE) cout << BOTTOM_RIGHT_CHAR;
				else cout << VERT_CHAR;
			}
			else {
				if (j == 0) cout << HORZ_CHAR;
				else if (j == BOX_HORIZONTAL_SPACE) cout << HORZ_CHAR << endl;
				else if (j == 1 || j > text.length() + 1) cout << ' ';
				else cout << text[j - 2];
			}
		}
	}

}


void ComboBox::KeyEventProc(KEY_EVENT_RECORD ker) {

	if (ker.bKeyDown) {
		COORD tmpCord;
		if (lastMouseOver != -1) {
			DWORD written = 0;
			tmpCord = loc;
			tmpCord.Y = loc.Y + (lastMouseOver + 1) * BOX_VERTICAL_SPACE;
			FillConsoleOutputAttribute(hStdout, (WORD)clearBack, BOX_HORIZONTAL_SPACE + 1, tmpCord, &written);
		}
		tmpCord = loc;
		tmpCord.Y += BOX_VERTICAL_SPACE + 1;
		if (ker.wVirtualKeyCode == VK_RETURN) {
			if (!isPressed) {
				for (int c = 0; c < arr.size(); c++) {
					for (int i = 0; i <= BOX_VERTICAL_SPACE - 1; i++) {
						tmpCord.Y += 1;
						SetConsoleCursorPosition(hStdout, tmpCord);
						for (int j = 0; j <= BOX_HORIZONTAL_SPACE; j++) {
							if (i == BOX_VERTICAL_SPACE - 1) {
								if (j == 0) cout << BOTTOM_LEFT_CHAR;
								else if (j == BOX_HORIZONTAL_SPACE) cout << BOTTOM_RIGHT_CHAR;
								else cout << VERT_CHAR;
							}
							else {
								if (j == 0) cout << HORZ_CHAR;
								else if (j == BOX_HORIZONTAL_SPACE) cout << HORZ_CHAR << endl;
								else if (j == 1 || j > arr[c].size() + 1) cout << ' ';
								else cout << arr[c][j - 2];
							}
						}
					}
				}
				isPressed = true;
			}
			else{
				if (keyOver > 0) {
					selectedCell = keyOver - 1;
					if (selectedCell != 0) drawComboBox(arr[selectedCell - 1]);
				}
				closeOptions(loc);
			}
		}
		else if (ker.wVirtualKeyCode == VK_DOWN) {
			if (isPressed) {
				if (keyOver <= arr.size()) {
					COORD newCord = loc;
					newCord.Y = loc.Y + (keyOver + 1) * BOX_VERTICAL_SPACE;
					DWORD written = 0;
					FillConsoleOutputAttribute(hStdout, (WORD)colorBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);
					newCord.Y -= BOX_VERTICAL_SPACE;
					FillConsoleOutputAttribute(hStdout, (WORD)clearBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);
					keyOver++;
				}
			}
		}
		else if (ker.wVirtualKeyCode == VK_UP) {
			if (isPressed) {
				if (keyOver > 2) {
					COORD newCord = loc;
					newCord.Y = loc.Y + (keyOver - 1) * BOX_VERTICAL_SPACE;
					DWORD written = 0;
					FillConsoleOutputAttribute(hStdout, (WORD)colorBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);
					newCord.Y += BOX_VERTICAL_SPACE;
					FillConsoleOutputAttribute(hStdout, (WORD)clearBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);
					keyOver--;
				}
			}
		}
	}
}

void ComboBox:: mousePressed(MOUSE_EVENT_RECORD mer) {
	COORD tmpCord = loc;
	if (mer.dwMousePosition.X >= tmpCord.X && mer.dwMousePosition.X <= tmpCord.X + BOX_HORIZONTAL_SPACE && mer.dwMousePosition.Y > tmpCord.Y && mer.dwMousePosition.Y <= tmpCord.Y + BOX_VERTICAL_SPACE + 1) {
		if (!isPressed) {
			tmpCord.Y += BOX_VERTICAL_SPACE + 1;
			for (int c = 0; c < arr.size(); c++) {
				for (int i = 0; i <= BOX_VERTICAL_SPACE - 1; i++) {
					tmpCord.Y += 1;
					SetConsoleCursorPosition(hStdout, tmpCord);
					for (int j = 0; j <= BOX_HORIZONTAL_SPACE; j++) {
						if (i == BOX_VERTICAL_SPACE - 1) {
							if (j == 0) cout << BOTTOM_LEFT_CHAR;
							else if (j == BOX_HORIZONTAL_SPACE) cout << BOTTOM_RIGHT_CHAR;
							else cout << VERT_CHAR;
						}
						else {
							if (j == 0) cout << HORZ_CHAR;
							else if (j == BOX_HORIZONTAL_SPACE) cout << HORZ_CHAR << endl;
							else if (j == 1 || j > arr[c].size() + 1) cout << ' ';
							else cout << arr[c][j - 2];
						}
					}
				}
			}
			if (selectedCell != -1) {
				COORD newCord = loc;
				newCord.Y = loc.Y + (selectedCell + 1) * BOX_VERTICAL_SPACE;
				DWORD written = 0;
				FillConsoleOutputAttribute(hStdout, (WORD)colorBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);
			}
			SetConsoleTextAttribute(hStdout, clearBack);
			isPressed = true;
		}
		else closeOptions(tmpCord);
	}
	else if (mer.dwMousePosition.X >= loc.X && mer.dwMousePosition.X <= loc.X + BOX_HORIZONTAL_SPACE && mer.dwMousePosition.Y > loc.Y + BOX_VERTICAL_SPACE  && mer.dwMousePosition.Y <= loc.Y + (arr.size() + 1)*BOX_VERTICAL_SPACE + 1) {
		int selected = ((mer.dwMousePosition.Y - loc.Y + 1) / BOX_VERTICAL_SPACE) - 1;
		selectedCell = selected;
		drawComboBox(arr[selected - 1]);
		closeOptions(loc);
	}
	else closeOptions(loc);
}

void ComboBox:: mouseMoved(MOUSE_EVENT_RECORD mer) {
	if (isPressed) {
		if (mer.dwMousePosition.X >= loc.X && mer.dwMousePosition.X <= loc.X + BOX_HORIZONTAL_SPACE && mer.dwMousePosition.Y > loc.Y + BOX_VERTICAL_SPACE  && mer.dwMousePosition.Y < loc.Y + (arr.size() + 1)*BOX_VERTICAL_SPACE) {
			if (keyOver != 1) {
				DWORD written = 0;
				COORD tmpCord = loc;
				tmpCord.Y = loc.Y + (keyOver)* BOX_VERTICAL_SPACE;
				FillConsoleOutputAttribute(hStdout, (WORD)clearBack, BOX_HORIZONTAL_SPACE + 1, tmpCord, &written);
			}
			int selected = ((mer.dwMousePosition.Y - loc.Y + 1) / BOX_VERTICAL_SPACE) - 1;
			COORD newCord = loc;
			newCord.Y = loc.Y + (lastMouseOver + 1)* BOX_VERTICAL_SPACE;
			SetConsoleCursorPosition(hStdout, newCord);

			DWORD written = 0;
			FillConsoleOutputAttribute(hStdout, (WORD)clearBack, BOX_HORIZONTAL_SPACE + 1, newCord, &written);

			newCord.Y = loc.Y + (selected + 1)* BOX_VERTICAL_SPACE;
			SetConsoleCursorPosition(hStdout, newCord);
			SetConsoleTextAttribute(hStdout, colorBack);

			for (int i = 0; i < BOX_VERTICAL_SPACE - 1; i++) {
				for (int j = 0; j <= BOX_HORIZONTAL_SPACE; j++) {
					if (j == 0) cout << HORZ_CHAR;
					else if (j == BOX_HORIZONTAL_SPACE) cout << HORZ_CHAR << endl;
					else if (j == 1 || j > arr[selected - 1].size() + 1) cout << ' ';
					else cout << arr[selected - 1][j - 2];
				}
			}
			SetConsoleTextAttribute(hStdout, clearBack);
			lastMouseOver = selected;
		}
	}
}

void ComboBox:: closeOptions(COORD cord) {
	cord.Y += BOX_VERTICAL_SPACE + 1;
	for (int c = 0; c < arr.size(); c++) {
		for (int i = 0; i <= BOX_VERTICAL_SPACE - 1; i++) {
			cord.Y += 1;
			SetConsoleCursorPosition(hStdout, cord);
			for (int j = 0; j <= BOX_HORIZONTAL_SPACE; j++) {
				cout << ' ';
			}
		}
	}
	isPressed = false;
	keyOver = 1;
}

void ComboBox :: ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
}