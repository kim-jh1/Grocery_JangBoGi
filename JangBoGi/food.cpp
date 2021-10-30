#define _CRT_SECURE_NO_WARNINGS 

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
		//this->recipe = recipe;
		recipe[0] = recipe1;
		recipe[1] = recipe2;
		recipe[2] = recipe3;
		this->state = state;
	}
	// constructor

	string getName() const { return name; }// 이름게터
	string getRecipe() const; // 만들 수 있는 음식 게터
	string getState() const { return state; } // state 게터
	int getFYear() const { return f_year; } // 유통기한 년
	int getFMonth() const { return f_month; } // 유통기한 월
	int getFDay() const { return f_day; } // 유통기한 일

	void setName(string name); // 이름 세터
	void setShelfDate(int f_year, int f_month, int f_day); // 유통기한 세터
	void setMakeFood(string recipe1, string recipe2, string recipe3); // 만들 수 있는 요리 세터
	void setState(); // 보관상태 세터
	void showMakeFood();

	void showLeftDate(); //유통기한 며칠 남았는지
	void showState(); //현재 보관상태
	void CheckAll(); //식재료명, 유통기한, 보관상태 출력

};
void ShowAllFood(vector<Food>& food); //해당 Food목록의 전체 식재료명 출력


string Food::getRecipe() const {
	string FullRecipe;
	for (int i = 0; i < 3; i++) {
		if (recipe[i] != "NO" && recipe[i] != "No") {
			FullRecipe += recipe[i];
			if ((i < 2) && ((recipe[i + 1] != "NO") && (recipe[i + 1] != "No")))
				FullRecipe += ", ";
		}
	}
	if (FullRecipe == "")
		return "만들 수 있는 요리가 없습니다.";
	return FullRecipe + "입니다.";
}

void Food::setName(string name) // 이름 세터
{
	this->name = name;
}

void Food::setShelfDate(int f_year, int f_month, int f_day)
{
	int days = 0;
	if ((thisYear <= f_year) && (f_year <= thisYear + 100))
	{
		if (1 <= f_month && f_month <= 12)
		{
			if (f_month == 1 || f_month == 3 || f_month == 5 || f_month == 7 || f_month == 8 || f_month == 10 || f_month == 12) {
				days = 31;
			}
			else if (f_month == 2) {
				days = 28;
			}
			else
				days = 30;

			if ((1 <= f_day) && (f_day < days)) {
				this->f_year = f_year;
				this->f_month = f_month;
				this->f_day = f_day;
			}
			else {
				cout << getName() << "의 일을 다시 입력하시오(1~" << days << ")\n" << endl;
				return;
			}

		}
		else {
			cout << getName() << "의 월을 다시 입력하시오(1~12)\n" << endl;
			return;
		}
	}
	else {
		cout << getName() << "의 년을 다시 입력하시오(" << thisYear << "~)\n" << endl;
		return;
	}
}

void Food::setMakeFood(string recipe1 = "No", string recipe2 = "NO", string recipe3 = "NO") {
	recipe[0] = recipe1;
	recipe[1] = recipe2;
	recipe[2] = recipe3;
}

void Food::setState() {
	string state;
	cout << getName() << "의 보관상태를 입력하시오 : ";
	cin >> state;
	while (1) {
		if (state == "상온" || state == "냉장" || state == "냉동")
		{
			this->state = state;   return;
		}
		else {  //세가지 상태에 해당 안되면 재입력.
			cout << "재입력 : ";
			cin >> state;
		}
	}
}

void Food::showLeftDate() {
	if (state == "미") //현재 사용자의 냉장고에 미보관이면 유통기한 출력X
		return;
	time_t shelfdate, today;
	double diff; //유통기한과 현재시각 비교
	int day; //비교 후 남은 일수 넣음
	struct tm user_stime; //현재시각 넣을 곳
	user_stime.tm_year = f_year - 1900;
	user_stime.tm_mon = f_month - 1;
	user_stime.tm_mday = f_day;
	user_stime.tm_hour = 0, user_stime.tm_min = 0, user_stime.tm_sec = 0, user_stime.tm_isdst = 0;
	shelfdate = mktime(&user_stime); //유통기한
	time(&today); //현재시각
	diff = difftime(shelfdate, today);
	day = diff / (60 * 60 * 24); //남은 날

	cout << getName() << "의 유통기한은 " << day << "일 남았습니다." << endl;
}

void Food::showState() {
	cout << "현재 " << getState() << "보관 중입니다." << endl;
}

void Food::showMakeFood() {
	cout << getName() << "으로 만들 수 있는 음식은 " << getRecipe() << endl;
}//만들 수 있는 음식

//보관 중인 해당 식재료의 이름, 보관상태, 유통기한 한번에 보여줌.
void Food::CheckAll() {
	showMakeFood();
	showLeftDate();
	showState();
	cout << endl;
}

//해당 Food목록의 전체 식재료명 출력
void ShowAllFood(vector<Food>& food) {
	for (Food a : food) {
		cout << a.getName() << endl;
	}
}

int main(void)
{
	vector<Food> meat = {
		Food("소등심", "스테이크", "구이", "불고기"), Food("소목심", "국", "장조림", "불고기"), Food("소앞다리", "육회", "스튜", "탕"), Food("소갈비", "불갈비", "찜", "탕"), Food("소양지", "국", "찌개", "육개장"),
		Food("소사태", "육회", "탕", "찜"), Food("소우둔", "산적", "장조림", "불고기"), Food("설도","산적","장조림", "육포"), Food("채끝", "스테이크", "전골", "샤브샤브"), Food("안심", "산적", "구이"),
		Food("돼지목살", "수육", "보쌈", "김치찌개"), Food("돼지등심", "돈가스", "탕수육", "잡채"), Food("돼지안심", "장조림", "꼬치구이", "탕수육"), Food("돼지갈비", "떡갈비", "양념갈비"), Food("돼지 앞다리살", "불고기", "찌개", "국"),
		Food("삼겹살", "베이컨", "구이", "불고기"), Food("돼지 뒷다리살", "수육", "보쌈", "장조림"), Food("돼지 사태", "장조림", "찌개", "수육"), Food("돼지 항정살", "구이"), Food("돼지 가브리살", "구이"),
		Food("통닭", "백숙", "삼계탕", "통구이"), Food("닭가슴살", "찜", "구이", "볶음"), Food("닭 안심", "찜", "튀김"), Food("닭다리", "바비큐", "조림", "찜"), Food("닭 날개", "조림", "스프", "튀김"),
		Food("닭 모래주머니", "구이", "볶음", "꼬치구이"), Food("닭발", "볶음"), Food("통오리", "찜", "백숙", "오븐구이"), Food("오리가슴살", "스테이크", "장조림", "양념구이"), Food("오리 목살", "주물럭", "구이"), Food("오리 날개", "튀김", "볶음", "오븐구이"),
		Food("오리 안심", "주물럭", "구이", "볶음"), Food("양 목살", "스튜", "탕", "찜"), Food("양 갈비새김", "튀김", "구이"), Food("양 안심", "스테이크" ,"꼬치"), Food("양 등심", "스테이크", "꼬치"),
		Food("양 어깨살", "전골", "샤브샤브", "불고기"), Food("양 뱃살", "전골", "중국요리"), Food("양 다릿살", "볶음", "튀김", "구이"), Food("양 갈비살", "스테이크","구이","볶음"), Food("양 숄더랙", "구이", "찜"),
		Food("양 늑간살", "볶음", "꼬치", "구이"), Food("양 앞다리살", "구이", "찜", "탕"), Food("양 뒷다리살", "전골", "수육", "카레"), Food("양 럼프", "스테이크", "육회"), Food("양 토시살", "구이", "볶음", "꼬치")
	};
	vector<Food> fish = { Food("생태","찌개","찜"), Food("동태","찌개","찜","전"), Food("북어"), Food("굴비"), Food("갈치","조림","구이"),Food("가자미","조림","구이"),Food("고등어","구이","조림"), Food("참치","회","볶음밥","주먹밥"), Food("명태"),Food("새우"),Food("오징어","국","삶음","볶음"),Food("연어","연어장","튀김"),Food("낙지","볶음","연포탕","전골"), Food("연어","연어장","튀김"),Food("낙지","볶음","전골"),Food("문어","숙회","조림","초회"),Food("장어","구이","덮밥"),Food("우럭","회","매운탕","조림"),Food("광어","회","조림","스테이크"),Food("해삼","물회","탕","전"),Food("홍어","회","무침","전골"),Food("삼치","조림","구이"),Food("아귀","아구찜"),Food("조기","구이","찜"),Food("꽁치","구이"),Food("전어","구이"),Food("재첩","재첩국"),Food("동죽","탕","칼국수"),Food("모시조개","국","탕","숙회"),Food("바지락","칼국수","순두부찌개","미역국"),Food("피조개","전골","무침","구이"),Food("가리비","회","구이","찜"),Food("홍합","탕","찜"),Food("가리맛조개","볶음","국물요리","구이"),Food("백합","구이","국물요리","찜"),Food("키조개","샤브샤브","구이","회"),Food("꼬막","양념꼬막","무침","비빔밥"),Food("전복","간장조림","버터구이","전복찜"),Food("우렁이","된장국","된장찌개","초무침"),Food("게","양념게장","간장게장","탕") };
	vector<Food> vegetable = { Food("가지"),Food("감자"),Food("갓"),Food("겨자잎"),Food("경수채"),Food("고구마"),Food("고사리"),Food("고추"),Food("깻잎"), Food("다채"), Food("당근"), Food("대파"), Food("더덕"), Food("도라지"), Food("래디쉬"), Food("롤라로사"), Food("마늘"), Food("머위"), Food("무"), Food("미나리"), Food("배추"), Food("버섯"), Food("봄동"), Food("부추"), Food("브로콜리"), Food("비트"), Food("상추"), Food("생강"), Food("숙주나물"), Food("순무"), Food("시금치"), Food("신선초"), Food("실파"), Food("쌈추"), Food("쑥"), Food("쑥갓"), Food("아보카도"), Food("아스파라거스"), Food("아욱"), Food("애호박"), Food("양배추"), Food("양상추"), Food("양파"), Food("연근"), Food("오이"), Food("우엉"), Food("인삼"), Food("적채"), Food("죽순"), Food("청경채"), Food("치커리"), Food("콜라비"), Food("콩나물"), Food("파프리카"), Food("호박"), Food("느타리버섯"), Food("새송이버섯"), Food("송이버섯"), Food("양송이버섯"), Food("팽이버섯"), Food("표고버섯") };
	vector<Food> sauce = { Food("고수"),Food("고추장"),Food("고춧가루"),Food("국간장"),Food("된장"),Food("로즈마리"),Food("루타바가"),Food("멸치액젓"),Food("바질"),Food("박하"),Food("산마늘"),Food("새우젓"),Food("설탕"),Food("셀러리"),Food("소금"),Food("식용류"),Food("식초"),Food("쑥갓"),Food("아티초크"),Food("진간장"),Food("타임"),Food("파슬리"),Food("후추"),Food("굴소스"),Food("제육볶음양념"),Food("돼지불고기양념"),Food("닭갈비양념"),Food("닭볶음탕양념"),Food("소갈비양념") };
	vector<Food> drink = { Food("우유"), Food("이온음료"), Food("쥬스"), Food("두유"), Food("유제품") };
	vector<Food> other = {
		Food("밀가루 박력분"), Food("밀가루 중력분"), Food("밀가루 강력분"), Food("소면"), Food("당면"), Food("칼국수면"), Food("밀면"), Food("냉면"), Food("쫄면"), Food("메밀면")
	};
	meat[0].CheckAll();
	meat[1].CheckAll();

	ShowAllFood(meat);
	return 0;
}