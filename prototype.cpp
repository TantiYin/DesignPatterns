#include <iostream>
#include <string>

using namespace std;

class Monster
{
public:
	Monster(string n): name(n) {}
	void display() {cout << name << endl;}

	Monster *clone()
	{
		return new Monster(name);
	}
private:
	string name;
};

class Spawner
{
public:
	Monster * spawn(Monster *o)
	{
		return o->clone();
	}
};

int main()
{
	Monster *cow = new Monster("cow");
	Spawner *spawner = new Spawner();
	Monster *cow2 = spawner->spawn(cow);
	cow->display();
	cow2->display();
	return 0;
}
