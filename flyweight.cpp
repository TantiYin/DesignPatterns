#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Terrain
{
public:
	Terrain(int f, bool b): friction(f), isWater(b) {}
	int friction = 1;
	bool isWater = false;
};

class world
{
public:
	world(int x1, int y1): x(x1), y(y1) {}
	void LoadTerrain()
	{
		a = new Terrain(1, false);
		b = new Terrain(2, false);
		c = new Terrain(3, true);
	}
	void GenerateWorld()
	{
		tiles = vector<vector<Terrain*>>(x, vector<Terrain*>(y, nullptr));
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (rand() % 10 < 5)
					tiles[i][j] = a;
				else
					tiles[i][j] = c;
			}
		}
	}
	Terrain * GetTile(int row, int col)
	{
		return tiles[row][col];
	}
private:
	vector<vector<Terrain*>> tiles;
	int x = 10;
	int y = 10;

	Terrain *a, *b, *c;
};

int main()
{
	int x = 10, y = 10;
	world *w = new world(x, y);
	w->LoadTerrain();
	w->GenerateWorld();
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			Terrain *t = w->GetTile(i, j);
			cout << t->friction << " ";
		}
		cout << endl;
	}
	return 0;
}
