#pragma once
#include<deque>
using namespace std;
typedef deque<deque<int> > MAP;
int dir[8][2] = { 1,0,1,1,0,1,-1,1,-1,0,-1,-1,0,-1,1,-1 };
inline bool isInside(const int h, const int w, const int H, const int W)
{
	return (0 <= H && H < h && 0 <= W && W < w);
}
void Minesweeper_make_map_sub(MAP &ret, const int h, const int w, const int H, const int W, const int cursor_h, const int cursor_w)
{
	if (W >= w) Minesweeper_make_map_sub(ret, h, w, H + 1, 0, cursor_h, cursor_w);
	else if (H >= h) Minesweeper_make_map_sub(ret, h, w, 0, 0, cursor_h, cursor_w);
	else if (ret[H][W] == -1 || (cursor_h == H && cursor_w == W)) Minesweeper_make_map_sub(ret, h, w, H, W + 1, cursor_h, cursor_w);
	else ret[H][W] = -1;
}
MAP Minesweeper_make_map(const int h, const int w, int c, const int cursor_h, const int cursor_w)
{
	MAP ret(h, deque<int>(w, 0));
	if (h*w - 1 < c) c = h*w - 1;
	for (int i = 0; i < c; i++)
	{
		int H = myRandom() % h;
		int W = myRandom() % w;
		if (!ret[H][W] && cursor_h != H && cursor_w != W) ret[H][W] = -1;
		else Minesweeper_make_map_sub(ret, h, w, H, W, cursor_h, cursor_w);
	}
	// Marking number
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (ret[i][j] != -1) continue;
			for (int k = 0; k < 8; k++)
			{
				int th = i + dir[k][0], tw = j + dir[k][1];
				if (isInside(h, w, th, tw) && ret[th][tw] != -1) ret[th][tw]++;
			}
		}
	}
	return ret;
}