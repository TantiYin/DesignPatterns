#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Component
{
public:
	Component(): size(0) {}
	Component(int sz): size(sz) {}
	virtual int GetSize() = 0;
	virtual void Add(Component *c) = 0;
	virtual void Remove(Component *c) = 0;
protected:
	int size = 0;
};

class Leaf: public Component
{
public:
	Leaf(int sz): Component(sz) {}
	int GetSize() {return size;}
	void Add(Component *c) {}
	void Remove(Component *c) {}
};

class Composite: public Component
{
public:
	Composite(int sz): Component(sz) {}
	Composite(): Component() {}
	int GetSize()
	{
		size = 0;
		for (const auto &i: children)
		{
			size += i->GetSize();
		}
		return size;
	}
	void Add(Component *c) {children.push_back(c);}
	void Remove(Component *c)
	{
		auto i = find(children.begin(), children.end(), c);
		if (i != children.end()) children.erase(i);
	}
private:
	vector<Component*>  children;
};

int main()
{
	Leaf *mouse = new Leaf(10);
	Leaf *mouse2 = new Leaf(20);
	Composite *bag = new Composite();
	bag->Add(mouse);
	bag->Add(mouse2);
	cout << bag->GetSize() << endl;
	return 0;
}
