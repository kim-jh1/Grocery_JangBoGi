#include "food.h"

string Food::getRecipe() const {
	string FullRecipe;
	for (int i = 0; i < 3; i++) {
		if (recipe[i] != "NO" && recipe[i] != "No") {
			FullRecipe += recipe[i];
			if ((i < 2) && ((recipe[i + 1] != "NO") && (recipe[i + 1] != "No")))
				FullRecipe += " ";
		}
	}
	if (FullRecipe == "")
		return "";
	return FullRecipe;
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

void Food::setMakeFood() {
	cout << getName() << "으로 만들 수 있는 음식 목록을 재설정합니다.";
	cin >> recipe[0] >> recipe[1] >> recipe[2];
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

void addData(vector<Food>& food) { //vector<Food>& food 에 추가할 때
	while (1) {
		if (food[0].getName() == "소등심" || food[0].getName() == "생태") { //레시피까지 입력해야하는 육류, 어류
			string name = "";
			string recipe1 = "";
			string recipe2 = "";
			string recipe3 = "";
			cout << "이름(q입력시 종료): ";
			cin >> name;
			if (name == "q") {
				writeInFile(food);
				return;
			}
			cout << "레시피 입력 ";
			cin >> recipe1 >> recipe2 >> recipe3;
			addIn(food, name, recipe1, recipe2, recipe3);
		}
		else { //레시피 입력 안해도 되는 채소, 음료, 소스, etc
			string name = "";
			cout << "이름(q입력시 종료): ";
			cin >> name;
			if (name == "q") {
				writeInFile(food);
				return;
			}
			addIn(food, name);
		}
	}
}
void addIn(vector<Food>& food, string name, string r1, string r2, string r3) // 하나의 식재료 추가
{
	food.push_back(Food(name, r1, r2, r3)); //식재료 추가	
	writeInFile(food);
}
void addIn(vector<Food>& food, string name) // 하나의 식재료 추가
{
	food.push_back(Food(name)); //식재료 추가	
	writeInFile(food);
}

//파일에 미리 입력된 데이터 외에 추가할 때 사용됨.
void writeInFile(vector<Food>& food) { // txt파일들에 식재료들 write
	if (food[0].getName() == "소등심") {
		FILE* writeFile = fopen("meat.txt", "w");
		int i = 0, j = 1;
		while (i < food.size()) {
			fprintf(writeFile, food[i].getName().c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, food[i].getRecipe().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	else if (food[0].getName() == "생태") {
		FILE* writeFile = fopen("fish.txt", "w");
		int i = 0, j = 1;
		while (i < food.size()) {
			fprintf(writeFile, food[i].getName().c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, food[i].getRecipe().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	else if (food[0].getName() == "가지") { //veget[0].getName()
		FILE* writeFile = fopen("veget.txt", "w");
		int i = 0, j = 1;
		while (i < food.size()) {  //첫 데이터 입력 -> 개행 -> 데이터입력 -> ... -> 개행 -> 데이터입력    ,,,,,, 개행을 한번 덜 해줘야돼서 j=1로 둠.
			fprintf(writeFile, food[i].getName().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	else if (food[0].getName() == "고수") {
		FILE* writeFile = fopen("sauce.txt", "w");
		int i = 0, j = 1;
		while (i < food.size()) {
			fprintf(writeFile, food[i].getName().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	else if (food[0].getName() == "우유") {
		FILE* writeFile = fopen("drink.txt", "w");
		int i = 0, j = 1;
		while (i < food.size()) {
			fprintf(writeFile, food[i].getName().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	else if (food[0].getName() == "박력분") {
		FILE* writeFile = fopen("other.txt", "w");
		int i = 0;
		int j = 1;
		while (i < food.size()) {
			fprintf(writeFile, food[i].getName().c_str());
			if (j < food.size()) {
				fprintf(writeFile, "\n");
			}
			i++;
			j++;
		}
		fclose(writeFile);
	}
	return;
} // 입력해서 쓰는게 아니라 else 처리 안해줌. 

void readInFile(vector<Food>& food) { // 파일에 저장된 해당 식재료의 목록 콘솔창에 출력
	int i = 0;
	if (food[0].getName() == "소등심") {
		FILE* readFile = fopen("meat.txt", "r"); //r 은 읽기모드
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			int sizeRecipe = food[i].getRecipe().size();
			char name[50], recipe[50];
			fgets(name, sizeName + 2, readFile);
			printf("%s", name);
			fgets(recipe, sizeRecipe + 2, readFile);
			printf("%s", recipe);
			i++;
		}
	}
	else if (food[0].getName() == "생태") {
		FILE* readFile = fopen("fish.txt", "r");
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			int sizeRecipe = food[i].getRecipe().size();
			char name[20], recipe[50];
			fgets(name, sizeName + 2, readFile);
			printf("%s", name);
			fgets(recipe, sizeRecipe + 2, readFile);
			printf("%s", recipe);
			i++;
		}
	}
	else if (food[0].getName() == "가지") {
		FILE* readFile = fopen("veget.txt", "r");
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			char name[20];
			fgets(name, sizeName + 2, readFile);
			printf("%s", name);

			i++;
		}
	}
	else if (food[0].getName() == "고수") {
		FILE* readFile = fopen("sauce.txt", "r");
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			char name[20];
			fgets(name, sizeName + 2, readFile);
			printf("%s", name);

			i++;
		}
	}
	else if (food[0].getName() == "우유") {
		FILE* readFile = fopen("drink.txt", "r");
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			char name[20];
			fgets(name, sizeName + 2, readFile);
			printf("%s", name);

			i++;
		}
	}
	else if (food[0].getName() == "박력분") {
		FILE* readFile = fopen("other.txt", "r");
		while (i < food.size()) {
			int sizeName = food[i].getName().size();
			char name[20];
			fgets(name, sizeName + 2, readFile); // \n 의 크기는 2
			printf("%s", name);

			i++;
		}
	}
	cout << endl;
	return;
}

void init(vector<Food>& food, string s) { //s에 맞는 식재료 목록으로 초기화함 ex) init(food, "육류") ---> meat.txt에 작성된 식재료들로 food 벡터가 초기화됨.

	if (s == "육류") {
		FILE* readFile = NULL;
		readFile = fopen("meat.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];
				char recipe1[32];
				char recipe2[32];
				char recipe3[32];

				char* ptr = strtok(buf, " ");
				strcpy(name, ptr);

				ptr = strtok(NULL, " ");
				strcpy(recipe1, ptr);

				ptr = strtok(NULL, " ");
				strcpy(recipe2, ptr);

				ptr = strtok(NULL, "\n");
				strcpy(recipe3, ptr);

				Food new_food(name, recipe1, recipe2, recipe3);
				food.push_back(new_food);
			}
		}
	}
	if (s == "어류") {
		FILE* readFile = NULL;
		readFile = fopen("fish.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];
				char recipe1[32];
				char recipe2[32];
				char recipe3[32];

				char* ptr = strtok(buf, " ");
				strcpy(name, ptr);
				ptr = strtok(NULL, " ");
				strcpy(recipe1, ptr);
				ptr = strtok(NULL, " ");
				strcpy(recipe2, ptr);
				ptr = strtok(NULL, "\n");
				strcpy(recipe3, ptr);
				Food new_food(name, recipe1, recipe2, recipe3);
				food.push_back(new_food);
			}
		}
	}
	if (s == "채소") {
		FILE* readFile = NULL;
		readFile = fopen("veget.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];

				char* ptr = strtok(buf, "\n");
				strcpy(name, ptr);
				Food new_food(name);
				food.push_back(new_food);
			}
		}
	}
	if (s == "소스") {
		FILE* readFile = NULL;
		readFile = fopen("sauce.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];

				char* ptr = strtok(buf, "\n");
				strcpy(name, ptr);
				Food new_food(name);
				food.push_back(new_food);
			}
		}
	}
	if (s == "음료") {
		FILE* readFile = NULL;
		readFile = fopen("drink.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];

				char* ptr = strtok(buf, "\n");
				strcpy(name, ptr);
				Food new_food(name);
				food.push_back(new_food);
			}
		}
	}
	if (s == "기타") {
		FILE* readFile = NULL;
		readFile = fopen("other.txt", "r");
		if (readFile != NULL) {
			char buf[2048];
			while (!feof(readFile)) {
				fgets(buf, sizeof(buf), readFile);

				char name[32];

				char* ptr = strtok(buf, "\n");
				strcpy(name, ptr);
				Food new_food(name);
				food.push_back(new_food);
			}
		}
	}

}

//int main(void)
//{
//	vector<Food> meat = {
//		Food("소등심", "스테이크", "구이", "불고기"), Food("소목심", "국", "장조림", "불고기"), Food("소앞다리", "육회", "스튜", "탕"), Food("소갈비", "불갈비", "찜", "탕"), Food("소양지", "국", "찌개", "육개장"),
//		Food("소사태", "육회", "탕", "찜"), Food("소우둔", "산적", "장조림", "불고기"), Food("설도","산적","장조림", "육포"), Food("채끝", "스테이크", "전골", "샤브샤브"), Food("안심", "산적", "구이"),
//		Food("돼지목살", "수육", "보쌈", "김치찌개"), Food("돼지등심", "돈가스", "탕수육", "잡채"), Food("돼지안심", "장조림", "꼬치구이", "탕수육"), Food("돼지갈비", "떡갈비", "양념갈비"), Food("돼지 앞다리살", "불고기", "찌개", "국"),
//		Food("삼겹살", "베이컨", "구이", "불고기"), Food("돼지 뒷다리살", "수육", "보쌈", "장조림"), Food("돼지 사태", "장조림", "찌개", "수육"), Food("돼지 항정살", "구이"), Food("돼지 가브리살", "구이"),
//		Food("통닭", "백숙", "삼계탕", "통구이"), Food("닭가슴살", "찜", "구이", "볶음"), Food("닭 안심", "찜", "튀김"), Food("닭다리", "바비큐", "조림", "찜"), Food("닭 날개", "조림", "스프", "튀김"),
//		Food("닭 모래주머니", "구이", "볶음", "꼬치구이"), Food("닭발", "볶음"), Food("통오리", "찜", "백숙", "오븐구이"), Food("오리가슴살", "스테이크", "장조림", "양념구이"), Food("오리 목살", "주물럭", "구이"), Food("오리 날개", "튀김", "볶음", "오븐구이"),
//		Food("오리 안심", "주물럭", "구이", "볶음"), Food("양 목살", "스튜", "탕", "찜"), Food("양 갈비새김", "튀김", "구이"), Food("양 안심", "스테이크" ,"꼬치"), Food("양 등심", "스테이크", "꼬치"),
//		Food("양 어깨살", "전골", "샤브샤브", "불고기"), Food("양 뱃살", "전골", "중국요리"), Food("양 다릿살", "볶음", "튀김", "구이"), Food("양 갈비살", "스테이크","구이","볶음"), Food("양 숄더랙", "구이", "찜"),
//		Food("양 늑간살", "볶음", "꼬치", "구이"), Food("양 앞다리살", "구이", "찜", "탕"), Food("양 뒷다리살", "전골", "수육", "카레"), Food("양 럼프", "스테이크", "육회"), Food("양 토시살", "구이", "볶음", "꼬치")
//	};
//	vector<Food> fish = { Food("생태","찌개","찜"), Food("동태","찌개","찜","전"), Food("북어"), Food("굴비"), Food("갈치","조림","구이"),Food("가자미","조림","구이"),Food("고등어","구이","조림"), Food("참치","회","볶음밥","주먹밥"), Food("명태"),Food("새우"),Food("오징어","국","삶음","볶음"),Food("연어","연어장","튀김"),Food("낙지","볶음","연포탕","전골"), Food("연어","연어장","튀김"),Food("낙지","볶음","전골"),Food("문어","숙회","조림","초회"),Food("장어","구이","덮밥"),Food("우럭","회","매운탕","조림"),Food("광어","회","조림","스테이크"),Food("해삼","물회","탕","전"),Food("홍어","회","무침","전골"),Food("삼치","조림","구이"),Food("아귀","아구찜"),Food("조기","구이","찜"),Food("꽁치","구이"),Food("전어","구이"),Food("재첩","재첩국"),Food("동죽","탕","칼국수"),Food("모시조개","국","탕","숙회"),Food("바지락","칼국수","순두부찌개","미역국"),Food("피조개","전골","무침","구이"),Food("가리비","회","구이","찜"),Food("홍합","탕","찜"),Food("가리맛조개","볶음","국물요리","구이"),Food("백합","구이","국물요리","찜"),Food("키조개","샤브샤브","구이","회"),Food("꼬막","양념꼬막","무침","비빔밥"),Food("전복","간장조림","버터구이","전복찜"),Food("우렁이","된장국","된장찌개","초무침"),Food("게","양념게장","간장게장","탕") };
//	vector<Food> vegetable = { Food("가지"),Food("감자"),Food("갓"),Food("겨자잎"),Food("경수채"),Food("고구마"),Food("고사리"),Food("고추"),Food("깻잎"), Food("다채"), Food("당근"), Food("대파"), Food("더덕"), Food("도라지"), Food("래디쉬"), Food("롤라로사"), Food("마늘"), Food("머위"), Food("무"), Food("미나리"), Food("배추"), Food("버섯"), Food("봄동"), Food("부추"), Food("브로콜리"), Food("비트"), Food("상추"), Food("생강"), Food("숙주나물"), Food("순무"), Food("시금치"), Food("신선초"), Food("실파"), Food("쌈추"), Food("쑥"), Food("쑥갓"), Food("아보카도"), Food("아스파라거스"), Food("아욱"), Food("애호박"), Food("양배추"), Food("양상추"), Food("양파"), Food("연근"), Food("오이"), Food("우엉"), Food("인삼"), Food("적채"), Food("죽순"), Food("청경채"), Food("치커리"), Food("콜라비"), Food("콩나물"), Food("파프리카"), Food("호박"), Food("느타리버섯"), Food("새송이버섯"), Food("송이버섯"), Food("양송이버섯"), Food("팽이버섯"), Food("표고버섯") };
//	vector<Food> sauce = { Food("고수"),Food("고추장"),Food("고춧가루"),Food("국간장"),Food("된장"),Food("로즈마리"),Food("루타바가"),Food("멸치액젓"),Food("바질"),Food("박하"),Food("산마늘"),Food("새우젓"),Food("설탕"),Food("셀러리"),Food("소금"),Food("식용류"),Food("식초"),Food("쑥갓"),Food("아티초크"),Food("진간장"),Food("타임"),Food("파슬리"),Food("후추"),Food("굴소스"),Food("제육볶음양념"),Food("돼지불고기양념"),Food("닭갈비양념"),Food("닭볶음탕양념"),Food("소갈비양념") };
//	vector<Food> drink = { Food("우유"), Food("이온음료"), Food("쥬스"), Food("두유"), Food("유제품") };
//	vector<Food> other = {
//		Food("밀가루 박력분"), Food("밀가루 중력분"), Food("밀가루 강력분"), Food("소면"), Food("당면"), Food("칼국수면"), Food("밀면"), Food("냉면"), Food("쫄면"), Food("메밀면")
//	};
//	meat[0].CheckAll();
//	meat[1].CheckAll();
//
//	ShowAllFood(meat);
//	return 0;
//}