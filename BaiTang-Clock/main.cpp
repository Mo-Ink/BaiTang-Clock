#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>
#include <time.h>

#include "clearScreen.h"
#include "ring.h"
#include "Hello.h"
#include "smallegg.h"
#include "quit.h"

#pragma clang diagnostic ignored "-Winvalid-source-encoding"

using namespace std;

struct tm info; //ʱ��ṹ�� 
struct clock
{
	int h;
	int m;
	int s;
};
struct timer
{
	int h;
	int m;
	int s;
	int oh; //��ʱ������ʱ�� 
	int om;
	int os;
};
struct sw //stopwatch
{
	int h;
	int m;
	int s;
	int time;
};
vector<struct clock>clocks; //����vector
vector<struct timer>timers;//��ʱ��vector
vector<struct sw>sws;//������vector
struct sw stopwatch;
time_t t1, t2;//���ڼ��ʱ���Ƿ�仯 

inline void getTime() //ˢ��ʱ�亯�� 
{
	time_t curtime; //����ʱ�� 
	time(&curtime); // ��ȡʱ�� 
	t1 = curtime;
	localtime_s(&info, &t1); //�ṹ�帳ֵ
}

inline void setClock() // �������ú��� 
{
	char c = ' ';
	clearScreen();
	char str[26];
	asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
	cout << " ��ǰʱ�� = " << str << endl;
	cout << " ��1�������ӣ���2ɾ�����ӣ���3����������ӣ�������������" << endl;	//������� 
	do
	{
		if (_kbhit())
			c = _getch(); //�ַ���ȡ
	} while (c == ' ');
	if (c == '1')
	{
		struct clock tmp; //���������������vector 
		int temp = 0;//��ʱ���� 
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		cout << " ��˳������h m s���������hСʱm����s��ʱ����(24h��)" << endl;   //������� 
		do
		{
			if (temp != 0)
				cout << " ���ݴ�������������" << endl;
			cin.clear();
			cin.sync();
			cin >> tmp.h >> tmp.m >> tmp.s;
			temp++;
		} while (tmp.h > 23 || tmp.m > 59 || tmp.s > 59); //�����ݴ������������� 
		clocks.push_back(tmp);//����vector 
	}
	if (c == '2' && !clocks.empty())
	{
		int num, tot = 0;
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		if (!clocks.empty())
		{
			cout << " �����б�" << endl; //������� 
			for (int i = 0; i < clocks.size(); i++)
				cout << i + 1 << ' ' << clocks[i].h << "h " << clocks[i].m << "m " << clocks[i].s << "s " << endl;
		}
		cout << endl << " ������Ҫɾ�������ӵı�ţ�" << endl;
		do
		{
			if (tot != 0)
				cout << " ���ݴ�������������" << endl;
			cin.clear();
			cin.sync();
			cin >> num;
			tot++;
		} while (num <= 0 || num > clocks.size());
		clocks.erase(clocks.begin() + num - 1);
	}
	if (c == '3' && !clocks.empty())
	{
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		clocks.clear();
	}
}

inline void checkClock() //�������
{
	for (int i = 0; i < clocks.size(); i++)//������������ 
		if (clocks[i].h == info.tm_hour && clocks[i].m == info.tm_min && clocks[i].s == info.tm_sec)//�����ʱ���� 
		{
			int tmpin;
			ringClock(tmpin);//���� 
			if (tmpin == 2)//���ѡ������Ӻ����� 
			{
				struct clock tmp;
				tmp.h = clocks[i].h;
				tmp.m = clocks[i].m + 5;
				tmp.s = clocks[i].s;
				clocks.push_back(tmp);
			}
			clocks.erase(clocks.begin() + i);//ɾ������ 
		}
}

inline void setTimer() // ��ʱ�����ú��� 
{
	char c = ' ';
	clearScreen();
	getTime();
	char str[26];
	asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
	cout << " ��ǰʱ�� = " << str << endl;
	cout << " ��1���ü�ʱ������2ɾ����ʱ������3������м�ʱ����������������" << endl;	//������� 
	cout << " ��ʱ����֧�ֿ����ʱ��������Ҫ��ʹ�����ӹ��ܣ�" << endl;
	do
	{
		if (_kbhit())
			c = _getch(); //�ַ���ȡ
	} while (c == ' ');
	if (c == '1')
	{
		struct timer tmp;//���������������vector
		int temp = 0;
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		cout << " ��˳������h m s���������hСʱm����s�������" << endl;
		do
		{
			if (temp != 0)
				cout << " ���ݴ�������������" << endl;
			getTime();
			cin.clear();
			cin.sync();
			cin >> tmp.h >> tmp.m >> tmp.s;
			temp++;
		}											//�����ʱʱ�������ͨ��			
		while (tmp.h > 23 || tmp.m > 59 || tmp.s > 59 || ((info.tm_hour + tmp.h) * 3600 + (info.tm_min + tmp.m) * 60 + (info.tm_sec + tmp.s) >= 86100));
		getTime(); //��ȡʱ�� 
		tmp.oh = tmp.h + info.tm_hour;
		tmp.om = tmp.m + info.tm_min;
		tmp.os = tmp.s + info.tm_sec; //��������ʱ�� 
		if (tmp.oh >= 24)
			tmp.oh = tmp.oh % 24;
		if (tmp.om >= 60)
			tmp.om = tmp.om % 60;
		if (tmp.os >= 60)
			tmp.os = tmp.os % 60;
		timers.push_back(tmp);//����vector 
	}
	if (c == '2' && !timers.empty())
	{
		int num, tot = 0;
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		if (!timers.empty())
		{
			cout << " ��ʱ���б�" << endl; //������� 
			for (int i = 0; i < timers.size(); i++)
				cout << i + 1 << ' ' << timers[i].h << "h " << timers[i].m << "m " << timers[i].s << "s " << endl;
		}
		cout << endl << " ������Ҫɾ�������ӵı�ţ�" << endl;
		do
		{
			if (tot != 0)
				cout << " ���ݴ�������������" << endl;
			cin.clear();
			cin.sync();
			cin >> num;
			tot++;
		} while (num <= 0 || num > timers.size());
		timers.erase(timers.begin() + num - 1);
	}
	if (c == '3' && !timers.empty())
	{
		clearScreen();
		char str[26];
		asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
		cout << " ��ǰʱ�� = " << str << endl;
		timers.clear();
	}
}

inline void checkTimer() //����ʱ��
{
	for (int i = 0; i < timers.size(); i++)//������������ 
	{
		if (timers[i].oh * 3600 + timers[i].om * 60 + timers[i].os <= info.tm_hour * 3600 + info.tm_min * 60 + info.tm_sec)//�����ʱ���� 
		{
			ringTimer();//���� 
			timers.erase(timers.begin() + i);//ɾ����ʱ�� 
		}
		else
		{
			int tmp, tmpo, tmpinfo;
			tmpinfo = info.tm_hour * 3600 + info.tm_min * 60 + info.tm_sec;
			tmpo = timers[i].oh * 3600 + timers[i].om * 60 + timers[i].os;
			tmp = tmpo - tmpinfo;
			timers[i].h = tmp / 3600;
			timers[i].m = tmp / 60 % 60;
			timers[i].s = tmp % 60;
		}
	}
}

inline void setStopwatch()
{
	clearScreen();
	cout << endl << " ������QvQ" << endl;
	bool swon = false;
	stopwatch.h = 0;
	stopwatch.m = 0;
	stopwatch.s = 0;
	stopwatch.time = 0;
	while (true)
	{
		char c = ' ';
		t2 = t1;//t1,t2У׼ 
		getTime(); //��ȡʱ�� 
		if (t1 != t2)
		{
			clearScreen();
			char str[26];
			asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
			cout << " ��ǰʱ�� = " << str << endl;
			cout << " ��1��ʼ/��ͣ����2���ѣ���3���㣬���������˳�" << endl;
			if (swon)
			{
				stopwatch.time++;
				stopwatch.h = stopwatch.time / 3600;
				stopwatch.m = stopwatch.time / 60 % 60;
				stopwatch.s = stopwatch.time % 60;
			}									// ����ֵķ���ʵ�ָ�ʽ��������� 
			cout << " " << stopwatch.h / 10 << stopwatch.h % 10 << ":" << stopwatch.m / 10 << stopwatch.m % 10 << ":" << stopwatch.s / 10 << stopwatch.s % 10 << endl << endl;
			if (!sws.empty())
			{
				cout << " �����б�" << endl;
				for (int i = 0; i < sws.size(); i++) // ����ֵķ���ʵ�ָ�ʽ��������� 
					cout << " " << (i + 1) / 10 << (i + 1) % 10 << " " << sws[i].h / 10 << sws[i].h % 10 << ":" << sws[i].m / 10 << sws[i].m % 10 << ":" << sws[i].s / 10 << sws[i].s % 10 << endl;
			}
			checkClock();
			checkTimer();
		}
		if (_kbhit())
			c = _getch(); //�ַ���ȡ 
		if (c == '1')
			swon = !swon;
		if (c == '2' && swon)
		{
			struct sw tmp; //���������������vector 
			tmp.h = stopwatch.h;
			tmp.m = stopwatch.m;
			tmp.s = stopwatch.s;
			sws.push_back(tmp);//����vector 
		}
		if (c == '3')
		{
			stopwatch.h = 0;
			stopwatch.m = 0;
			stopwatch.s = 0;
			stopwatch.time = 0;
			sws.clear();
		}
		if (c != '1' && c != '2' && c != '3' && c != ' ')
			break;
		if (sws.size() > 23)
			sws.clear();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	SetConsoleTitle(TEXT("BaiTangClock Ver1.5 | Made by Mo_Ink"));
	Hello();
	while (true)
	{
		char c = ' ';
		t2 = t1;//t1,t2У׼ 
		getTime(); //��ȡʱ�� 
		if (t1 != t2) //��t1ˢ�º���t2����ͬ��ˢ�»��� 
		{
			clearScreen(); //ˢ�� 
			char str[26];
			asctime_s(str, sizeof str, &info); //ʱ���ַ��� 
			cout << " ��ǰʱ�� = " << str << endl;
			showRing();
			cout << endl;
			cout << " ��N�ɽ������ӹ���" << endl;
			cout << " ��M�ɽ����ʱ������" << endl;
			cout << " ��S�ɽ���������" << endl;
			cout << " ��R�ɽ�����������" << endl;
			cout << " ��Q���˳�����" << endl << endl;
			if (!clocks.empty())
			{
				cout << " �����б�" << endl;
				for (int i = 0; i < clocks.size(); i++)
					cout << " " << i + 1 << ' ' << clocks[i].h << "h " << clocks[i].m << "m " << clocks[i].s << "s " << endl;
			}
			cout << endl;
			if (!timers.empty())
			{
				cout << " ��ʱ���б�" << endl;
				for (int i = 0; i < timers.size(); i++)
					cout << " " << i + 1 << ' ' << timers[i].h << "h " << timers[i].m << "m " << timers[i].s << "s " << endl;
			}
		}
		if (_kbhit())
			c = _getch(); //�ַ���ȡ 
		if (c == 'n' || c == 'N')
			setClock();
		if (c == 'm' || c == 'M')
			setTimer();
		if (c == 'r' || c == 'R')
			setRing();
		if (c == 's' || c == 'S')
			setStopwatch();
		if (c == 'Q' || c == 'q')
			quit();
		if (c == '~')
			egg();
		checkClock();
		checkTimer();
	}
}
