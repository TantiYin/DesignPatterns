#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

enum Event
{
	E_Run,
};

class Entity
{
public:
	Entity(string n): name(n) {}
	void run() {cout << name << ": run" << endl;}
private:
	string name;
};

class Observer
{
public:
	virtual void onNotify(Entity *entity, Event evnt) = 0;
};

class Subject
{
public:
	void notify(Entity *entity,	Event evnt)
	{
		for (const auto &o: list)
		{
			o->onNotify(entity, evnt);
		}
	}
	void addObserver(Observer *o)
	{
		list.push_back(o);
	}
	void removeObserver(Observer *o)
	{
		auto i = find(list.begin(), list.end(), o);
		if (i != list.end())
			list.erase(i);
	}
private:
	vector<Observer*> list;
};

class robot: public Observer
{
public:
	robot(string n): name(n) {}
	void onNotify(Entity *entity, Event evnt)
	{
		if (evnt == E_Run)
		{
			Run();
		}
	}
	void Run() {cout << name << ": run " << endl;}
private:
	string name;
};

class System
{
public:
	System(Entity *e): entity(e) {sub = new Subject();}
	void update()
	{
		entity->run();
		sub->notify(entity, E_Run);
	}

	Subject *sub;
private:
	Entity *entity;
};

int main()
{
	Entity *bob = new Entity("bob");
	Observer *j0 = new robot("j0");

	System *m = new System(bob);
	m->sub->addObserver(j0);
	m->update();

	return 0;
}
