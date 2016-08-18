#include <iostream>
#include <string>
#include <unistd.h>
#include <queue>
using namespace std;

class CObject
{
public:
	CObject() {}
	void Jump() {cout << "jump" << endl;}
	void Run() {cout << "run" << endl;}
};

class CCommand
{
public:
	virtual ~CCommand() {}
	virtual void Execute() = 0;

};

class CJumpCommand: public CCommand
{
public:
	CJumpCommand(CObject* Object): mObject(Object) {}
	virtual void Execute() {mObject->Jump();}
private:
	CObject* mObject;
};

class CRunCommand: public CCommand
{
public:
	CRunCommand(CObject* Object): mObject(Object) {}
	virtual void Execute() {mObject->Run();}
private:
	CObject *mObject;
};

CObject* gUnit;
CObject* GetSelectedUnit()
{
	return gUnit;
}

class CEventHandler
{
public:
	CCommand* Handle(char Msg)
	{
		CObject* Unit = GetSelectedUnit();
		switch(Msg)
		{
			case 'X':
			{
				return new CJumpCommand(Unit);
			}
			break;
			case 'Y':
			{
				return new CRunCommand(Unit);
			}
			break;
		}
	}
};

int main()
{
	gUnit = new CObject();
	queue<CCommand*> Queue;
	CEventHandler* Eventhandler = new CEventHandler();

	CCommand* OneCommand;
	OneCommand = Eventhandler->Handle('X');
	Queue.push(OneCommand);
	OneCommand = Eventhandler->Handle('Y');
	Queue.push(OneCommand);

	while (!Queue.empty())
	{
		OneCommand = Queue.front();
		OneCommand->Execute();
		Queue.pop();
		sleep(1);
	}
	return 0;
}
