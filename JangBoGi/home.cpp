#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "menu.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

int keyControl();
void title();
int menudraw();
void gotoxy(int x, int y);
void show_menu();
void current();
void init();

int main()
{
	while (1)
	{
		init();
		title();
		int menucode = menudraw();
		if (menucode == 0)
		{
			current();
		}
		else if (menucode == 1)
		{
			show_menu();
		}
		else if (menucode == 2)
			return 0;
		system("cls");
		
	}
	return 0;
}

void title()
{
	printf("\n\n\n\n");
	printf("		      ##    ###    ##    ##  ######   ########   #######   ######   #### \n");
	printf("		      ##   ## ##   ###   ## ##    ##  ##     ## ##     ## ##    ##   ##  \n");
	printf("		      ##  ##   ##  ####  ## ##        ##     ## ##     ## ##         ##  \n");
	printf("		      ## ##     ## ## ## ## ##   #### ########  ##     ## ##   ####  ##  \n");
	printf("		##    ## ######### ##  #### ##    ##  ##     ## ##     ## ##    ##   ##  \n");
	printf("		##    ## ##     ## ##   ### ##    ##  ##     ## ##     ## ##    ##   ##  \n");
	printf("		 ######  ##     ## ##    ##  ######   ########   #######   ######   #### \n");
	printf("\n");
}

int menudraw()
{
	int x = 50;
	int y = 12;
	gotoxy(x-2 , y);
	printf("> 현 황");
	gotoxy(x, y+1);
	printf("재 료");
	gotoxy(x, y+2);
	printf("종 료");
	while (1)
	{
		int n = keyControl();
		switch (n)
		{
		case UP:
			if (y > 12)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		case DOWN:
			if (y < 14)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		case SUBMIT:
			return y - 12;
		}
	}
}

void gotoxy(int x, int y)
{
	HANDLE consoleHandel = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandel, pos);
}

int keyControl()
{
	int key = _getch();

	if (key == 32)
		return SUBMIT;

	if (key == 224)
	{
		key = _getch();
		if (key == 72)
			return UP;
		else if (key == 75)
			return LEFT;
		else if (key == 77)
			return RIGHT;
		else if (key == 80)
			return DOWN;
	}
}

void show_menu()
{
	while (1) {
		status();
		getKey();
		Sleep(300);
		system("cls");
	}
}

void current()
{
	system("cls");
	printf("구현예정\n");
	printf("스페이스바를 누르면 메인으로 돌아갑니다");
	while (1)
	{
		if (keyControl() == SUBMIT)
			break;
	}
}
void init()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}