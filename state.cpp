#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Entity;
class State
{
public:
	virtual void handleInput(Entity *obj, char in) = 0;
	virtual void update(Entity *obj) = 0;
};

class Entity
{
public:
	void handleInput(char input)
	{
		currentS->handleInput(this, input);
	}
	void update()
	{
		currentS->update(this);
	}
	void changeState(State *newS)
	{
		currentS = newS;
	}

	void setState(State *init)
	{
		currentS = init;
	}
	void work() {++tired; cout << "working..." << endl;}
	void sleep() {tired = 0; cout << "sleeping..." << endl;}
	bool istired() {return tired > 10;}
	bool isRecovery() {return tired <= 0;}
private:
	int tired = 0;
	State *currentS;
};

class sleepState;
class workState: public State
{
public:
	//manual
	virtual void handleInput(Entity* obj, char in);
	//auto
	virtual void update(Entity *obj);
	static State* instance()
	{
		static State *ins = new workState();
		return ins;
	}
};

class sleepState: public State
{
public:
	virtual void handleInput(Entity *obj, char in);
	virtual void update(Entity *obj);
	static State* instance()
	{
		static State *ins = new sleepState();
		return ins;
	}
};
void workState::handleInput(Entity* obj, char in)
{
	if (in == 'b')
	{
		obj->changeState(sleepState::instance());
	}
}

void workState::update(Entity *obj)
{
	obj->work();
	if (obj->istired())
	{
		obj->changeState(sleepState::instance());
	}
}

void sleepState::handleInput(Entity *obj, char in)
{}

void sleepState::update(Entity *obj)
{
	obj->sleep();
	if (obj->isRecovery())
	{
		obj->changeState(workState::instance());
	}
}

int main()
{
	Entity * bob = new Entity();
	bob->setState(workState::instance());
	while (true)
	{
		bob->update();
		sleep(1);
	}
	return 0;
}
