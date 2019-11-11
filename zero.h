//Last Upgrade 2016-05-10
//made in gvvvv1123@gmail.com
#ifndef ZERO_HEADER
#define ZERO_HEADER

#include<stdlib.h>
#include<time.h>
#include<cstdlib>
#include<cassert>
#include<deque>
using namespace std;
void cls();
void pause();
int myRandom();
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

int myRandom()
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

void pause()
{
	system("pause");
}
#endif