#include <iostream>
#include <string>
#include <unistd.h>
#include <queue>
using namespace std;

class Object
{
public:
	Object() {}
	void Jump() {cout << "jump" << endl;}
	void Run() {cout << "run" << endl;}
};

class command
{
public:
	virtual ~command() {}
	virtual void Excute() = 0;

};

class JumpCommand: public command
{
public:
	JumpCommand(Object* ob): o(ob) {}
	virtual void Excute() {o->Jump();}
private:
	Object *o;
};

class RunCommand: public command
{
public:
	RunCommand(Object *ob): o(ob) {}
	virtual void Excute() {o->Run();}
private:
	Object *o;
};
Object *gl;
Object *GetSelectedUnit()
{
	return gl;
}

class EventHandler
{
public:
	command * handle(char msg)
	{
		Object *u = GetSelectedUnit();
		switch(msg)
		{
			case 'X':
			{
				return new JumpCommand(u);
			}
			break;
			case 'Y':
			{
				return new RunCommand(u);
			}
			break;
		}
	}
};
int main()
{
	gl = new Object();
	queue<command*> q;
	EventHandler *eh = new EventHandler();

	command *t;
	t = eh->handle('X');
	q.push(t);
	t = eh->handle('Y');
	q.push(t);

	while (!q.empty())
	{
		t = q.front();
		t->Excute();
		q.pop();
		sleep(1);
	}
	return 0;
}
