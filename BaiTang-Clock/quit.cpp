#include <iostream>
#include <Windows.h>
#include "clearScreen.h"
#pragma clang diagnostic ignored "-Winvalid-source-encoding"
using namespace std;

void quit()
{
	clearScreen();
	cout << endl;
	cout << " ��л��ʹ�ñ����򣡱������д��Ľ������в���֮������£�" << endl;
	cout << " �����ڲ��ú�رգ�" << endl;
	Sleep(1500);
	exit(0);
}