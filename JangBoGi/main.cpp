#include "home.h"
#include "menu.h"
#include "food.h"
#include "add.h"

int main()
{
	refrigerator* ref = new refrigerator("NULL", 0);
	while (1)
	{
		init();
		title();
		int menucode = menudraw();
		if (menucode == 0)
		{
			ref->setPosition("fridge");
			while (1) {
				ref->show_inventory();
				ref->getKey();
				Sleep(300);
				system("cls");
			}
		}
		else if (menucode == 1)
		{
			ref->setPosition("meat");
			while (1) {
				while (1) {
					ref->show_ingredient();
					ref->getKey();
					Sleep(300);
					system("cls");
				}
			}
		}
		else if (menucode == 2)
		{
			add();
			system("cls");
		}
		else if (menucode == 3)
		{
			return 0;
			system("cls");
		}
	}
	return 0;
}