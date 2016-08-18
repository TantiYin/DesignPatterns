#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class CTerrain
{
public:
	CTerrain(int F, bool B): mFriction(F), bWater(B) {}
	int mFriction = 1;
	bool bWater = false;
};

class CWorld
{
public:
	CWorld(int X1, int Y1): mX(X1), mY(Y1) {}
	void LoadTerrain()
	{
		mA = new CTerrain(1, false);
		mB = new CTerrain(2, false);
		mC = new CTerrain(3, true);
	}
	void GenerateWorld()
	{
		mTiles = vector<vector<CTerrain*>>(mX, vector<CTerrain*>(mY, nullptr));
		for (int i = 0; i < mX; ++i)
		{
			for (int j = 0; j < mY; ++j)
			{
				if (rand() % 10 < 5)
					mTiles[i][j] = mA;
				else
					mTiles[i][j] = mC;
			}
		}
	}
	CTerrain* GetTile(int Row, int Col)
	{
		return mTiles[Row][Col];
	}
private:
	vector<vector<CTerrain*>> mTiles;
	int mX = 10;
	int mY = 10;

	CTerrain *mA, *mB, *mC;
};

int main()
{
	int X = 10, Y = 10;
	CWorld* World = new CWorld(X, Y);
	World->LoadTerrain();
	World->GenerateWorld();
	for (int i = 0; i < X; ++i)
	{
		for (int j = 0; j < Y; ++j)
		{
			CTerrain* Tile = World->GetTile(i, j);
			cout << Tile->mFriction << " ";
		}
		cout << endl;
	}
	return 0;
}
