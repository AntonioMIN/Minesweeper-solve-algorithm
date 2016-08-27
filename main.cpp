#include<stdio.h>
#include<deque>
#include"zero.h"
#include"minesweeper.h"
#include"player.h"
using namespace std;

#define DEBUGGING false

void logo()
{
	cls();
	textcolor(13);
	printf("MineSweeper Hack\n\n");
	textcolor(-1);
}
/*
Minesweeper map mark
Bomb : -1
Number : 0~8
*/
int main()
{
	// 16 30 99 - MS Minesweeper size
	logo();
	int h, w, c;
	int cursor_h, cursor_w;
	h = 16;
	w = 30;
	c = 99;
	int Total = 0, success = 0;
	while (true)
	{
		// Start New Game
		cursor_h = random() % h;
		cursor_w = random() % w;

		MAP map = Minesweeper_make_map(h, w, c, cursor_h, cursor_w);
		player Player(map, c);
		// First Click
		Player.click(cursor_h, cursor_w);
		if (Total>0) printf("Total : %d\tSuccess : %d\tFail : %d\tSuccess rate : %.2lf\n", Total, success, Total - success, (double)success / (double)Total);
		printf("# Algorithm init..\n");
		Total++;
		while (true)
		{
			if (Player.game_done())
			{
				printf("## Game over..Success\n");
				success++;
				break;
			}
			int inx = 0;
			bool FIRST_STEP_BREAK = true;
			// First step work
			printf("@ First step\n");
			while (inx < Player.bfs.size())
			{
				int H = Player.bfs[inx].h, W = Player.bfs[inx].w;
				int block_cnt = 0, flag_cnt = 0;
				// Counting around block
				for (int i = 0; i < 8; i++)
				{
					int th = H + dir[i][0], tw = W + dir[i][1];
					if (isInside(h, w, th, tw) && (Player.map_playing[th][tw] == -2 || Player.map_playing[th][tw] == -3)) block_cnt++;
					if (isInside(h, w, th, tw) && (Player.map_playing[th][tw] == -3)) flag_cnt++;
				}
				// ³²Àº ºí·°µéÀº ¸ðµÎ ÆøÅº
				if (block_cnt == Player.map_playing[H][W])
				{
					FIRST_STEP_BREAK = false;
					for (int i = 0; i < 8; i++)
					{
						int th = H + dir[i][0], tw = W + dir[i][1];
						if (isInside(h, w, th, tw) && Player.map_playing[th][tw] == -2) Player.marking_flag(th, tw);
					}
					Player.bfs.erase(Player.bfs.begin() + inx);
					continue;
				}
				// ¸ðµç ÆøÅº¿¡ ±ê¹ß ¸¶Å·
				if (flag_cnt == Player.map_playing[H][W])
				{
					FIRST_STEP_BREAK = false;
					for (int i = 0; i < 8; i++)
					{
						int th = H + dir[i][0], tw = W + dir[i][1];
						if (isInside(h, w, th, tw) && Player.map_playing[th][tw] == -2) Player.click(th, tw);
					}
					Player.bfs.erase(Player.bfs.begin() + inx);
					continue;
				}
				inx++;
			}

			// Click other block
			if (FIRST_STEP_BREAK)
			{
				printf("@ Algorithm\n");
				if (Player.bfs.size() && Player.MSA()) continue;
				
				printf("@ Luck\n");
				int nextClick_h, nextClick_w;
				while (true)
				{
					nextClick_h = random() % h;
					nextClick_w = random() % w;
					if (Player.map_playing[nextClick_h][nextClick_w] == -2) break;
				}
				if (!Player.click(nextClick_h, nextClick_w))
				{
					if(DEBUGGING) Player.map_playing_print_file();
					printf("## Game over..Bad Luck\n");
					break;
				}
			}
		}
		// End Game
		printf("Game end..\n");
		Player.map_playing_print();
		// pause();
	}
	return 0;
}