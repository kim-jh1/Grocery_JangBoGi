#include "add.h"
#include "food.h"
#include "home.h"

void add()
{
	system("cls");
	int key;
	string a;
	string r1, r2, r3;
	int i;
	cout << "�߰��� ���� ������ �Է��ϼ��� (1: ��� 2: ���� 3:ä�� 4:���� 5:�ҽ�) ";
	cin >> a >> i;
	if (i == 1)
	{
		if (!(isexist_meat(a)))
		{
			FILE* writeFile = fopen("meat.txt", "a");
			cout << "ù��° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r1;
			cout << "�ι�° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r2;
			cout << "����° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r3;
			fprintf(writeFile, a.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r1.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r2.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r3.c_str());
			fprintf(writeFile, "\n");
			fclose(writeFile);
			return;
		}
		else
		{
			cout << "�̹� �����ϴ� ����� �Դϴ�.\n";
			cout << "�����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�";
			key = keyControl();
			if(key==4)
				return;
		}

	}
	else if (i == 2)
	{
		if (!(isexist_fish(a)))
		{
			FILE* writeFile = fopen("fish.txt", "a");
			cout << "ù��° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r1;
			cout << "�ι�° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r2;
			cout << "����° �����Ǹ� �Է��ϼ��� (���ٸ� x�� �Է��ϼ���): ";
			cin >> r3;
			fprintf(writeFile, a.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r1.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r2.c_str());
			fprintf(writeFile, " ");
			fprintf(writeFile, r3.c_str());
			fprintf(writeFile, "\n");
			fclose(writeFile);
			return;
		}
		else
		{
			cout << "�̹� �����ϴ� ����� �Դϴ�.\n";
			cout << "�����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�";
			key = keyControl();
			if (key == 4)
				return;
		}
	}
	else if (i == 3)
	{
		if (!(isexist_veget(a)))
		{
			FILE* writeFile = fopen("veget.txt", "a");
			fprintf(writeFile, a.c_str());
			fprintf(writeFile, "\n");
			fclose(writeFile);
			return;
		}
		else
		{
			cout << "�̹� �����ϴ� ����� �Դϴ�.\n";
			cout << "�����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�";
			key = keyControl();
			if (key == 4)
				return;
		}
	}
	else if (i == 4)
	{
		if (!(isexist_fruit(a)))
		{
			FILE* writeFile = fopen("fruit.txt", "a");
			fprintf(writeFile, a.c_str());
			fprintf(writeFile, "\n");
			fclose(writeFile);
			return;
		}
		else
		{
			cout << "�̹� �����ϴ� ����� �Դϴ�.\n";
			cout << "�����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�";
			key = keyControl();
			if (key == 4)
				return;
		}
	}
	else if (i == 5)
	{
		if (!(isexist_sauce(a)))
		{
			FILE* writeFile = fopen("sauce.txt", "a");
			fprintf(writeFile, "\n");
			fprintf(writeFile, a.c_str());
			fprintf(writeFile, "\n");
			fclose(writeFile);
			return;
		}
		else
		{
			cout << "�̹� �����ϴ� ����� �Դϴ�.\n";
			cout << "�����̽��ٸ� ������ ���� ȭ������ ���ư��ϴ�";
			key = keyControl();
			if (key == 4)
				return;
		}
	}
	else
	{
		cout << "�߸��� �����Դϴ�\n";
		return;
	}
}

bool isexist_meat(string s)
{
	FILE* readFile = fopen("meat.txt", "r"); //r �� �б���
	if (readFile != NULL) 
	{
		char buf[2048];
		while (!feof(readFile))
		{
			fgets(buf, sizeof(buf), readFile);
			char name[32];


			char* ptr = strtok(buf, " ");
			strcpy(name, ptr);
			if (name == s)
			{
				return true;
			}
		}
	}
		return false;
}

bool isexist_fish(string s)
{
	FILE* readFile = fopen("fish.txt", "r"); //r �� �б���
	if (readFile != NULL)
	{
		char buf[2048];
		while (!feof(readFile))
		{
			fgets(buf, sizeof(buf), readFile);
			char name[32];


			char* ptr = strtok(buf, " ");
			strcpy(name, ptr);
			if (name == s)
			{
				return true;
			}
		}
	}
	return false;
}

bool isexist_veget(string s)
{
	FILE* readFile = fopen("veget.txt", "r"); //r �� �б���
	if (readFile != NULL)
	{
		char buf[2048];
		while (!feof(readFile))
		{
			fgets(buf, sizeof(buf), readFile);
			char name[32];


			char* ptr = strtok(buf, " ");
			strcpy(name, ptr);
			if (name == s)
			{
				return true;
			}
		}
	}
	return false;
}

bool isexist_fruit(string s)
{
	FILE* readFile = fopen("fruit.txt", "r"); //r �� �б���
	if (readFile != NULL)
	{
		char buf[2048];
		while (!feof(readFile))
		{
			fgets(buf, sizeof(buf), readFile);
			char name[32];


			char* ptr = strtok(buf, " ");
			strcpy(name, ptr);
			if (name == s)
			{
				return true;
			}
		}
	}
	return false;
}

bool isexist_sauce(string s)
{
	FILE* readFile = fopen("sauce.txt", "r"); //r �� �б���
	if (readFile != NULL)
	{
		char buf[2048];
		while (!feof(readFile))
		{
			fgets(buf, sizeof(buf), readFile);
			char name[32];


			char* ptr = strtok(buf, " ");
			strcpy(name, ptr);
			if (name == s)
			{
				return true;
			}
		}
	}
	return false;
}