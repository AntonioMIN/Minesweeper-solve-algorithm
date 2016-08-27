#pragma once
#include<deque>
using namespace std;

struct point
{
	int h, w;
	point(int _h = 0, int _w = 0)
	{
		h = _h;
		w = _w;
	}
};
/*
Array dir and function isInside() in minesweeper.h
*/
class player
{
private:
	int map_h, map_w, bomb_count, virtual_bomb_count;
	const int INF = 0x7fffffff;
	bool VIRTUAL_MAP_MAIN = true;
	deque<point> GROUP;
	deque<deque<bool> > vis, touched;
	MAP virtual_map, virtual_map_main, map;

	inline int get_Flagcount(const int h, const int w)
	{
		int ret = 0;
		for (int i = 0; i < 8; i++)
		{
			int H = h + dir[i][0], W = w + dir[i][1];
			if (isInside(map_h, map_w, H, W) && virtual_map[H][W] == -3) ret++;
		}
		return ret;
	}

	void MSA_dfs(int index, int mine_count, int dir_inx, bool isFirst)
	{
		if (virtual_bomb_count < 0) return;
		if (GROUP.size() == index)
		{// Possible virtual map
			if (VIRTUAL_MAP_MAIN)
			{
				virtual_map_main = virtual_map;
				VIRTUAL_MAP_MAIN = false;
			}
			else
			{
				const int INF = 0x7fffffff;
				for (int i = 0; i < map_h; i++)
				{
					for (int j = 0; j < map_w; j++)
					{
						if (virtual_map_main[i][j] != virtual_map[i][j]) virtual_map_main[i][j] = INF;
					}
				}
			}
			return;
		}

		if (isFirst)
		{
			for (int i = 0; i < 8; i++)
			{
				int H = GROUP[index].h + dir[i][0], W = GROUP[index].w + dir[i][1];
				if (isInside(map_h, map_w, H, W)) touched[H][W] = true;
			}
		}

		// Step check
		if (mine_count < 0) return;
		if (mine_count == 0)
		{// Next index
			int Mine_count = 0;
			if (GROUP.size() != index + 1) Mine_count = virtual_map[GROUP[index + 1].h][GROUP[index + 1].w] - get_Flagcount(GROUP[index + 1].h, GROUP[index + 1].w);
			deque<point> locked;
			for (int r = 0; r < 8; r++)
			{
				int H = GROUP[index].h + dir[r][0], W = GROUP[index].w + dir[r][1];
				if (isInside(map_h, map_w, H, W) && !vis[H][W] && virtual_map[H][W] == -2)
				{
					locked.push_back(point(H, W));
					vis[H][W] = true;
				}
			}
			MSA_dfs(index + 1, Mine_count, 0, true);
			// Unlock around blocks in locked.
			for (int i = 0; i < locked.size(); i++)
			{
				vis[locked[i].h][locked[i].w] = false;
			}
			return;
		}

		// Marking virtual flag
		for (int i = dir_inx; i < 8; i++)
		{
			int H = GROUP[index].h + dir[i][0], W = GROUP[index].w + dir[i][1];
			if (isInside(map_h, map_w, H, W) && !vis[H][W] && virtual_map[H][W] == -2)
			{
				virtual_map[H][W] = -3;
				virtual_bomb_count--;
				MSA_dfs(index, mine_count - 1, i + 1, false);
				virtual_bomb_count++;
				virtual_map[H][W] = -2;
			}
		}
	}
	// Union-find
	deque<deque<int> > get_related()
	{
		deque<deque<int> > ret(bfs.size());
		deque<int> V(bfs.size());
		MAP T = map_playing;
		for (int i = 0; i < bfs.size(); i++)
		{
			ret[i].push_back(i);
			V[i] = i;
		}
		for (int i = 0; i < bfs.size(); i++)
		{
			int h = bfs[i].h, w = bfs[i].w, root = i + 10;
			for (int j = 0; j < 8; j++)
			{
				int H = h + dir[j][0], W = w + dir[j][1];
				if (isInside(map_h, map_w, H, W))
				{
					if (T[H][W] == -2) T[H][W] = root;
					else if (T[H][W] >= 10 && V[T[H][W] - 10] != V[root - 10])
					{
						int A = V[root - 10], B = V[T[H][W] - 10];
						if (ret[A].size() < ret[B].size())
						{
							int t = A; A = B; B = t;
						}
						while (ret[B].size())
						{
							V[ret[B].back()] = A;
							ret[A].push_back(ret[B].back());
							ret[B].pop_back();
						}
					}
				}
			}
		}
		int inx = 0;
		while (inx < ret.size())
		{
			if (ret[inx].empty()) ret.erase(ret.begin() + inx);
			else inx++;
		}
		return ret;
	}

public:
	MAP map_playing;
	deque<point> bfs;

	player(deque<deque<int> >& _map,int _bomb_count)
	{
		// -2 : Blocked
		map = _map;
		map_h = map.size();
		map_w = map[0].size();
		bomb_count = _bomb_count;
		map_playing = deque<deque<int> >(map_h, deque<int>(map_w, -2));
	}

	bool click(const int h, const int w)
	{
		if (map[h][w] == -1)
		{
			GameOver(h, w);
			return false;
		}
		deque<point> ret;
		if (map[h][w] == 0)
		{
			// Flow fill
			deque< deque<bool> > vis = deque< deque<bool> >(map.size(), deque<bool>(map[0].size(), false));
			deque<point> bfs_flowfill;
			bfs_flowfill.push_back(point(h, w));
			vis[h][w] = true;
			while (bfs_flowfill.size())
			{
				point T = bfs_flowfill.front();
				bfs_flowfill.pop_front();
				map_playing[T.h][T.w] = map[T.h][T.w];
				ret.push_back(point(T.h, T.w));
				for (int i = 0; i < 8; i++)
				{
					int H = T.h + dir[i][0], W = T.w + dir[i][1];
					if (isInside(map_h, map_w, H, W) && !vis[H][W] && map_playing[H][W] == -2)
					{
						if (map[H][W] == 0) bfs_flowfill.push_back(point(H, W));
						if (map[H][W] != -1)
						{
							vis[H][W] = true;
							map_playing[H][W] = map[H][W];
							ret.push_back(point(H, W));
						}
					}
				}
			}
		}
		else
		{
			map_playing[h][w] = map[h][w];
			ret.push_back(point(h, w));
		}
		for (int i = 0; i < ret.size(); i++)
		{
			if (map_playing[ret[i].h][ret[i].w] != 0) bfs.push_back(ret[i]);
		}
		return true;
	}

	inline void marking_flag(const int h, const int w)
	{
		// -3 : Flag
		bomb_count--;
		map_playing[h][w] = -3;
	}

	bool game_done()
	{
		for (int i = 0; i < map_h; i++)
		{
			for (int j = 0; j < map_w; j++)
			{
				if (map[i][j] != -1 && map_playing[i][j] == -2) return false;
			}
		}
		return true;
	}

	void map_playing_print()
	{
		for (int i = 0; i < map_h; i++)
		{
			for (int j = 0; j < map_w; j++)
			{
				if (map_playing[i][j] == -3) textcolor(13);
				else if (map_playing[i][j] == -2) textcolor(12);
				printf("%3d", map_playing[i][j]);
				textcolor(-1);
			}
			printf("\n");
		}
	}

	void map_playing_print_file()
	{
		FILE *op = fopen("map_list.txt", "a+");
		for (int i = 0; i < map_h; i++)
		{
			for (int j = 0; j < map_w; j++)
			{
				fprintf(op, "%3d", map_playing[i][j]);
			}
			fprintf(op, "\n");
		}
		fprintf(op, "---------------------------------\n");
	}

	
	// Minesweeper Solve Algorithm
	bool MSA()
	{// Success : true, Fail : false
		virtual_map = map_playing;
		virtual_map_main.clear();
		VIRTUAL_MAP_MAIN = true;
		virtual_bomb_count = bomb_count;
		vis = deque<deque<bool> >(map_h, deque<bool>(map_w, false));
		touched = deque<deque<bool> >(map_h, deque<bool>(map_w, false));

		deque<deque<int> > related = get_related();
		printf("## deque bfs size : %d\n", bfs.size());
		printf("## Related block group count : %d\n", related.size());
		for (int i = 0; i < related.size(); i++)
		{
			GROUP.clear();
			for (int j = 0; j < related[i].size(); j++) GROUP.push_back(bfs[related[i][j]]);
			MSA_dfs(0, map_playing[GROUP[0].h][GROUP[0].w] - get_Flagcount(GROUP[0].h, GROUP[0].w), 0, true);
		}

		// no-changed block, changed block = INF
		bool ret = false;
		for (int i = 0; i < map_h; i++)
		{
			for (int j = 0; j < map_w; j++)
			{
				if (virtual_map_main[i][j] != INF)
				{
					if (virtual_map_main[i][j] == -2 && touched[i][j])
					{
						click(i, j);
						ret = true;
					}
					else if (virtual_map_main[i][j] != map_playing[i][j] && virtual_map_main[i][j] == -3)
					{
						marking_flag(i, j);
						ret = true;
					}
				}
			}
		}
		return ret;
	}
	
	

};