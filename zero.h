//Last Upgrade 2016-05-10
//made in gvvvv1123@gmail.com
#ifndef ZERO_HEADER
#define ZERO_HEADER

#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<cstdlib>
#include<cassert>
#include<deque>
using namespace std;
void cls();
void pointhind(int c);
void pointmove(int x, int y);
void pause();
void textcolor(int x);
int random();
#define sleep(n) Sleep(n)

template <class _type>
class soque
{
private:
	deque<_type> stc;
public:
	void push(_type val)
	{
		if (stc.empty()) stc.push_back(val);
		else
		{
			int m, L = 0, R = stc.size() - 1;
			while (L <= R)
			{
				m = (L + R) / 2;
				if (stc[m] == val || L == R) break;
				if (stc[m] < val) L = m + 1;
				if (stc[m] > val) R = m - 1;
			}
			if (stc[m] < val) m++;
			stc.insert(stc.begin() + m, val);
		}
	}
	void erase(int tar)
	{
		if (tar >= 0 && tar < stc.size())
		{
			stc.erase(stc.begin() + tar);
		}
	}
	_type& operator[] (const int index)
	{
		return stc[index];
	}
	unsigned int size()
	{
		return stc.size();
	}
};

void pointhind(int c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case 0:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case 1:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void textcolor(int x)
{
	if (x != -1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else if (x == -1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int random()
{
	static bool _RANDOM_ = false;
	if (!_RANDOM_)
	{
		srand((unsigned)time(NULL));
		_RANDOM_ = true;
	}
	return rand();
}

void cls()
{
	system("cls");
}

void pointmove(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void pause()
{
	system("pause");
}
#endif