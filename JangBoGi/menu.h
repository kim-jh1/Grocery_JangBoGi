#pragma once

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

class refrigerator {
private:
	std::string position;
	int cursor;
	vector<string> arr_frig;
	vector<string> arr_free;
	vector<string> arr_room;

	vector<string> arr_meat;
	vector<string> arr_fish;
	vector<string> arr_vege;
	vector<string> arr_frit;
	vector<string> arr_sauc;

public:
	refrigerator(string, int);
	void setPosition(string);
	void setFood(vector<string>, string);
	void textcolor(int, int);
	void getKey();
	void show_inventory();
	void show_ingredient();
};