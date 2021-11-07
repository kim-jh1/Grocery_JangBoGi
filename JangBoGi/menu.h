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

	vector<string> arr_frig; //냉장
	vector<string> arr_free; //냉동
	vector<string> arr_room; //실온

	vector<string> arr_meat; //육류
	vector<string> arr_fish; //어류
	vector<string> arr_vege; //채소
	vector<string> arr_frit; //과일
	vector<string> arr_sauc; //소스

public:
	refrigerator(string, int);
	void setPosition(string);
	void setFood(vector<string>, string);
	void textcolor(int, int);
	void getKey();
	void show_inventory();
	void show_ingredient();
};