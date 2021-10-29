#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

static bool fridge = true;
static bool freezer = false;
static bool room = false;
static bool in_fridge = false;
static bool in_freezer = false;
static bool in_room = false;
static int cursor = 0;

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool getKey() {
	char c;
	if (_kbhit()) {
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				if (freezer == true) {
					freezer = false;
					fridge = true;
				}
				else if (room == true) {
					room = false;
					freezer = true;
				}
				break;
			case RIGHT:
				if (fridge == true) {
					fridge = false;
					freezer = true;
				}
				else if (freezer == true) {
					freezer = false;
					room = true;
				}
				break;
			case UP:
				if (cursor == 1) {
					if (in_fridge == true) {
						in_fridge = false;
						fridge = true;
						cursor -= 1;
					}
					else if (in_freezer == true) {
						in_freezer = false;
						freezer = true;
						cursor -= 1;
					}
					else if (in_room == true) {
						in_room = false;
						room = true;
						cursor -= 1;
					}
				}
				else {
					cursor -= 1;
				}
				break;
			case DOWN:
				if (cursor == 0) {
					if (fridge == true) {
						fridge = false;
						in_fridge = true;
						cursor += 1;
					}
					else if (freezer == true) {
						freezer = false;
						in_freezer = true;
						cursor += 1;
					}
					else if (room == true) {
						room = false;
						in_room = true;
						cursor += 1;
					}
				}
				else {
					cursor += 1;
				}
				break;
			}
		}
	}
	return true;
}

void status() //³ÃÀå, ³Ãµ¿, ½Ç¿Â ¸®½ºÆ®¸¦ ÀÎÀÚ·Î ¹Þ°í Ãâ·Â
{
	cout << "|";
	if (fridge == true) {
		textcolor(WHITE, RED);
		cout << left << setw(20) << "³ÃÀå°í";
		textcolor(WHITE, BLACK);
	}
	else {
		cout << left << setw(20) << "³ÃÀå°í";
	}

	cout << "|";
	if (freezer == true) {
		textcolor(WHITE, RED);
		cout << left << setw(20) << "³Ãµ¿½Ç";
		textcolor(WHITE, BLACK);
	}
	else {
		cout << left << setw(20) << "³Ãµ¿½Ç";
	}

	cout << "|";
	if (room == true) {
		textcolor(WHITE, RED);
		cout << left << setw(20) << "½Ç¿Â";
		textcolor(WHITE, BLACK);
	}
	else {
		cout << left << setw(20) << "½Ç¿Â";
	}
	cout << "|";
	cout << endl;

	cout << "===============================================================\n";
	for (int i = 1; i <= 20; i++) {
		if (in_fridge == true && cursor == i) {
			textcolor(WHITE, RED);
			cout << "|" << left << setw(20) << "³ÃÀåÀ½½Ä" << "|";
			textcolor(WHITE, BLACK);
		}
		else {
			cout << "|" << left << setw(20) << "³ÃÀåÀ½½Ä" << "|";
		}

		if (in_freezer == true && cursor == i) {
			textcolor(WHITE, RED);
			cout << left << setw(20) << "³Ãµ¿À½½Ä" << "|";
			textcolor(WHITE, BLACK);
		}
		else {
			cout << left << setw(20) << "³Ãµ¿À½½Ä" << "|";
		}

		if (in_room == true && cursor == i) {
			textcolor(WHITE, RED);
			cout << left << setw(20) << "½Ç¿ÂÀ½½Ä" << "|" << endl;
			textcolor(WHITE, BLACK);
		}
		else {
			cout << left << setw(20) << "½Ç¿ÂÀ½½Ä" << "|" << endl;
		}
	}
}

int main(void)
{
	while (1) {
		status();
		getKey();
		Sleep(300);
		system("cls");
	}

	return 0;
}