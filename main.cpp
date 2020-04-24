#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>
using namespace std;

struct tm *info; //ʱ��ṹ�� 
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
vector<struct clock>clocks; //�������� 
vector<struct timer>timers;//��ʱ������ 
time_t t1,t2;//���ڼ��ʱ���Ƿ�仯 

inline void clearScreen() //���� 
{
    system("cls");
}

inline void Hello()
{
	cout<< "BaiTangClock Ver1.3.0" << endl;
	cout<< "Made by Mo_Ink/������һ��" <<endl;
	cout <<"Github: Mo-Ink" << endl;
	cout <<"Bilibili: ������һ��" << endl;
	cout<< "----δ�������ֹת��----" << endl;
	Sleep(2500);  
}

inline void getTime() //ˢ��ʱ�亯�� 
{
	time_t curtime; //����ʱ�� 
	time(&curtime); // ��ȡʱ�� 
	t1=curtime;
	info = localtime( &curtime ); //�ṹ�帳ֵ
}

inline void setClock() // �������ú��� 
{
	char c=' ';
	clearScreen();
	string s = asctime(info); //ʱ���ַ��� 
	cout << "��ǰʱ�� = " << s;
	cout << "��1�������ӣ���2ɾ�����ӣ���3����������ӣ�������������" << endl;	//������� 
	do
	{
		if(_kbhit())
			c=getch(); //�ַ���ȡ
	}while(c==' ');
	if(c=='1')
	{
		struct clock tmp; //���������������vector 
		int temp=0;//��ʱ���� 
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s; 
		cout << "��˳������h m s���������hСʱm����s��ʱ����(24h��)" << endl;   //������� 
		do
		{
			if(temp!=0)
				cout << "���ݴ�������������" << endl;
			cin >> tmp.h >> tmp.m >> tmp.s;
			temp++;
		}
		while(tmp.h>23||tmp.m>59||tmp.s>59); //�����ݴ������������� 
		clocks.push_back(tmp);//����vector 
		cout << "���ӽ���" << tmp.h <<"ʱ " << tmp.m << "�� " << tmp.s <<"��ʱ���壡" <<endl;
		Sleep(1800); //�ȴ�2.8s
	}
	if(c=='2'&&!clocks.empty())
	{
		int num,tot=0;
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s << endl; //������� 
		if(!clocks.empty())
		{
			cout << "�����б�" << endl; //������� 
			for(int i=0;i<clocks.size();i++)
				cout << i+1 << ' ' << clocks[i].h << "h " << clocks[i].m << "m " << clocks[i].s << "s " <<endl;
		}
		cout << endl << "������Ҫɾ�������ӵı�ţ�" << endl;
		do
		{
			if(tot!=0)
				cout << "���ݴ�������������" << endl;
			cin >> num;
			tot++;
		}while(num<=0||num>clocks.size());
		clocks.erase(clocks.begin()+num-1);
		cout << "��ɾ����" << endl;
		Sleep(1000);
	}
	if(c=='3'&&!clocks.empty())
	{
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s << endl; //������� 
		clocks.clear();
		cout << "�������" << endl;
		Sleep(1000);
	}
}

inline void ringClock(int &x) //���庯�� 
{
	PlaySound("data\ring.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP); //�������� 
	char c=' ';
	cout << "�����õ�ʱ�䵽�ˣ�����1����������2����Ӻ�����������" << endl;
	do
	{
		if(_kbhit())
			c=getch(); //�ַ���ȡ
	}while(c==' ');
	if(c=='2')
		x=2;
	else
		x=1;
	PlaySound(NULL,NULL,SND_FILENAME|SND_ASYNC|SND_LOOP); //�ر����� 
}

inline void checkClock() //�������
{
	for(int i=0;i<clocks.size();i++)//������������ 
		if(clocks[i].h==info->tm_hour&&clocks[i].m==info->tm_min&&clocks[i].s==info->tm_sec)//�����ʱ���� 
		{
			int tmpin;
			ringClock(tmpin);//���� 
			if(tmpin==2)//���ѡ������Ӻ����� 
			{
				struct clock tmp;
				tmp.h=clocks[i].h;
				tmp.m=clocks[i].m+5;
				tmp.s=clocks[i].s;
				clocks.push_back(tmp);
			}
			clocks.erase(clocks.begin()+i);//ɾ������ 
		}
}

inline void setTimer() // ��ʱ�����ú��� 
{
	char c=' ';
	clearScreen();
	string s = asctime(info); //ʱ���ַ��� 
	cout << "��ǰʱ�� = " << s;
	cout << "��1���ü�ʱ������2ɾ����ʱ������3������м�ʱ����������������" << endl;	//������� 
	do
	{
		if(_kbhit())
			c=getch(); //�ַ���ȡ
	}while(c==' ');
	if(c=='1')
	{
		struct timer tmp;//���������������vector
		int temp=0;
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s; 
		cout << "��˳������h m s���������hСʱm����s�������" << endl; 
		do
		{
			if(temp!=0)
				cout << "���ݴ�������������" << endl;
			cin >> tmp.h >> tmp.m >> tmp.s;
			temp++;
		}
		while(tmp.h>23||tmp.m>59||tmp.s>59||(tmp.h+info->tm_hour)>=24);
		tmp.oh=tmp.h+info->tm_hour; 
		tmp.om=tmp.m+info->tm_min;
		tmp.os=tmp.s+info->tm_sec;
		if(tmp.oh>=24) 
			tmp.oh=tmp.oh%24;
		if(tmp.om>=60)
			tmp.om=tmp.om%60;
		if(tmp.os>=60)
			tmp.os=tmp.os%60;
		timers.push_back(tmp);//����vector 
		cout << "��ʱ������" << tmp.h <<"ʱ " << tmp.m << "�� " << tmp.s <<"������壡" <<endl;
		Sleep(1800); //�ȴ�2.8s
	}
	if(c=='2'&&!timers.empty())
	{
		int num,tot=0;
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s << endl; //������� 
		if(!timers.empty())
		{
			cout << "��ʱ���б�" << endl; //������� 
			for(int i=0;i<timers.size();i++)
				cout << i+1 << ' ' << timers[i].h << "h " << timers[i].m << "m " << timers[i].s << "s " <<endl;
		}
		cout << endl << "������Ҫɾ�������ӵı�ţ�" << endl;
		do
		{
			if(tot!=0)
				cout << "���ݴ�������������" << endl;
			cin >> num;
			tot++;
		}while(num<=0||num>timers.size());
		timers.erase(timers.begin()+num-1);
		cout << "��ɾ����" << endl;
		Sleep(1000);
	}
	if(c=='3'&&!timers.empty())
	{
		clearScreen();
		string s = asctime(info); //ʱ���ַ��� 
		cout << "��ǰʱ�� = " << s << endl; //������� 
		timers.clear();
		cout << "�������" << endl;
		Sleep(1000);
	}
}

inline void checkTimer() //����ʱ��
{
	for(int i=0;i<timers.size();i++)//������������ 
	{
		if(timers[i].oh==info->tm_hour&&timers[i].om==info->tm_min&&timers[i].os<=info->tm_sec)//�����ʱ���� 
		{
			int tmpin;
			ringClock(tmpin);//���� 
			if(tmpin==2)//���ѡ������Ӻ����� 
			{
				struct timer tmp;
				tmp.h=0;
				tmp.m=5;
				tmp.s=0;
				tmp.oh=timers[i].h;
				tmp.om=timers[i].m+5;
				tmp.os=timers[i].s;
				timers.push_back(tmp);
			}
			timers.erase(timers.begin()+i);//ɾ����ʱ�� 
		}
		else
		{
			int tmp,tmpo,tmpinfo;
			tmpinfo=info->tm_hour*3600+info->tm_min*60+info->tm_sec;
			tmpo=timers[i].oh*3600+timers[i].om*60+timers[i].os;
			tmp=tmpo-tmpinfo;
			timers[i].h=tmp/3600;
			timers[i].m=tmp/60%60;
			timers[i].s=tmp%60;
		}
	}
}

int main()
{
	SetConsoleTitle("BaiTangClock Ver1.3.0 | Made by Mo_Ink");
	Hello();
	while(true)
	{
		char c = ' ';
		t2=t1;//t1,t2У׼ 
		getTime(); //��ȡʱ�� 
		if(t1!=t2) //��t1ˢ�º���t2����ͬ��ˢ�»��� 
		{
			clearScreen(); //ˢ�� 
			string s = asctime(info); //ʱ���ַ��� 
			cout << "��ǰʱ�� = " << s;
			cout << "��n�ɽ������ӹ���" << endl ;
			cout << "��m�ɽ����ʱ������" << endl << endl;  
			if(!clocks.empty())
			{
				cout << "�����б�" << endl;
				for(int i=0;i<clocks.size();i++)
					cout << i+1 << ' ' << clocks[i].h << "h " << clocks[i].m << "m " << clocks[i].s << "s " <<endl;
			}
			cout << endl;
			if(!timers.empty())
			{
				cout << "��ʱ���б�" << endl;
				for(int i=0;i<timers.size();i++)
					cout << i+1 << ' ' << timers[i].h << "h " << timers[i].m << "m " << timers[i].s << "s " <<endl;
			}
		}
		if(_kbhit())
			c=getch(); //�ַ���ȡ 
		if(c=='n'||c=='N')
			setClock();
		if(c=='m'||c=='M')
			setTimer();
		checkClock();
		checkTimer();
	} 
} 
