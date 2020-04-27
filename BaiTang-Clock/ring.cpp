#include <iostream>
#include <windows.h>
#include <Mmsystem.h>
#include <conio.h>
#include "resource.h"
#include "clearScreen.h"
#pragma comment(lib,"winmm.lib")
#pragma clang diagnostic ignored "-Winvalid-source-encoding"
using namespace std;

int ring = 1;

#define ringDef MAKEINTRESOURCE(IDR_WAVE1)
#define ringBman MAKEINTRESOURCE(IDR_WAVE2)
#define ringJi MAKEINTRESOURCE(IDR_WAVE3)
#define ringCrp MAKEINTRESOURCE(IDR_WAVE4)

void ringClock(int& x) //���庯�� 
{
	if (ring == 1)
		PlaySound(ringDef, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	if (ring == 2)
		PlaySound(ringBman, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	if (ring == 3)
		PlaySound(ringJi, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //��������  
	if (ring == 4)
		PlaySound(ringCrp, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	char c = ' ';
	cout << " �����õ�ʱ�䵽�ˣ�����1����������2��������Ӻ��ٴ���������" << endl;
	do
	{
		if (_kbhit())
			c = _getch(); //�ַ���ȡ
	} while (c == ' ');
	if (c == '2')
		x = 2;
	else
		x = 1;
	PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP); //�ر����� 
}

void ringTimer() //���庯�� 
{
	if (ring == 1)
		PlaySound(ringDef, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	if (ring == 2)
		PlaySound(ringBman, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	if (ring == 3)
		PlaySound(ringJi, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //��������  
	if (ring == 4)
		PlaySound(ringCrp, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); //�������� 
	char c = ' ';
	cout << " �����õ�ʱ�䵽�ˣ��������������" << endl;
	do
	{
		if (_kbhit())
			c = _getch(); //�ַ���ȡ
	} while (c == ' ');
	PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP); //�ر����� 
}

void showRing()
{
	cout << " ��ǰ������";
	if (ring == 1)
		cout << "1.Ĭ��" << endl;
	if (ring == 2)
		cout << "2.����̧��" << endl;
	if (ring == 3)
		cout << "3.����̫��" << endl;
	if (ring == 4)
		cout << "4.Creeper?" << endl;
}

void setRing()
{
	int n, tot = 0;
	clearScreen();
	cout << endl;
	cout << " ��ѡ������" << endl;	//������� 
	cout << " 1.Ĭ��" << endl;
	cout << " 2.����̧��" << endl;
	cout << " 3.����̫��" << endl;
	cout << " 4.Creeper?" << endl << endl;
	cout << " ��������Ҫ���������:" << endl;
	do
	{
		if (tot != 0)
			cout << " ���ݴ�������������" << endl;
		cin.clear();
		cin.sync();
		cin >> n;
		tot++;
	} while (n != 1 && n != 2 && n != 3 && n != 4);
	ring = n;
}