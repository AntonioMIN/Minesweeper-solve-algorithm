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
	h = 6;
	w = 6;
	c = 10;
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
			if (Player.minesolve1())
			{
				printf("@ Algorithm\n");
				if (Player.MSA()) continue;
				
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