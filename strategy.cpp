class Strategy
{
public:
	Strategy(int l, int r): a(l), b(r) {}
	virtual int GetResult() = 0;
protected:
	int a = 0, b = 0;
};

class Add: public Strategy
{
public:
	Add():Strategy(0, 0) {}
	Add(int l, int r): Strategy(l, r) {}
	virtual int GetResult() {return a + b;}
};

class Sub: public Strategy
{
public:
	Sub(): Strategy(0, 0) {}
	Sub(int l, int r): Strategy(l, r) {}
	virtual int GetResult() {return a - b;}
};

class Mul: public Strategy
{
public:
	Mul(int l, int r): Strategy(l, r) {}
	virtual int GetResult() {return a * b;}
};

#include <iostream>
using namespace std;

class StrategyAgency
{
public:
	StrategyAgency(int type, int l, int r)
	{
		switch(type)
		{
			case 1:
			{
				strategy = new Add(l, r);
			}
			break;
			case 2:
			{
				strategy = new Sub(l, r);
			}
			break;
			case 3:
			{
				strategy = new Mul(l, r);
			}
			break;
		}
	}
	int GetResult() {return strategy->GetResult();}
private:
	Strategy *strategy;
};
int main()
{
	int type;
	cin >> type;
	int l, r;
	cin >> l >> r;
	for (int i = 0; i < 100000; ++i)
	{
		StrategyAgency sa(type, l, r);
		cout << sa.GetResult() << endl;
	}
	return 0;
}
