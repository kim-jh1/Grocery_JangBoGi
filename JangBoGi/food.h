#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma once

#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <cstring>
using namespace std;

class Food
{
	string name; // 재료이름
	string recipe[3]; // 만들 수 있는 요리 종류
	int f_year = 0, f_month = 0, f_day = 0; // 유통기한
	string state = "미"; // 재료 보관 상태( 냉장, 냉동, 상온)

	time_t today = time(NULL);
	struct tm* t = localtime(&today);
	int thisYear = t->tm_year + 1900;

public:
	//Food() :name(), makeFood(), f_year(), f_month(), f_day(), state() {}
	Food(string name, string recipe1 = "NO", string recipe2 = "NO", string recipe3 = "NO", int f_year = 0, int f_month = 0, int f_day = 0, string state = "미")
	{
		this->name = name;
		this->f_year = f_year;
		this->f_month = f_month;
		this->f_day = f_day;

		recipe[0] = recipe1;
		recipe[1] = recipe2;
		recipe[2] = recipe3;
		this->state = state;
	}
	// constructor

	string getName() const { return name; }// 이름게터
	string getRecipe() const; // 만들 수 있는 음식 게터
	//string getRecipe() const;
	string getState() const { return state; } // state 게터
	int getFYear() const { return f_year; } // 유통기한 년
	int getFMonth() const { return f_month; } // 유통기한 월
	int getFDay() const { return f_day; } // 유통기한 일

	void setName(string name); // 이름 세터
	void setShelfDate(int f_year, int f_month, int f_day); // 유통기한 세터
	//void setMakeFood(string recipe1, string recipe2, string recipe3); // 만들 수 있는 요리 세터
	void setMakeFood();
	void setState(); // 보관상태 세터
	void showMakeFood();

	void showLeftDate(); //유통기한 며칠 남았는지
	void showState(); //현재 보관상태
	void CheckAll(); //식재료명, 유통기한, 보관상태 출력

};
void ShowAllFood(vector<Food>& food); //해당 Food목록의 전체 식재료명 출력
void addData(vector<Food>& food);
void addIn(vector<Food>& food, string name, string r1, string r2, string r3);
void addIn(vector<Food>& food, string name);
void writeInFile(vector<Food>& food);
void readInFile(vector<Food>& food);