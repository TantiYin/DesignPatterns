#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

enum class EEvent
{
	Run,
};

class CEntity
{
public:
	CEntity(string Name): mName(Name) {}
	void Run() {cout << mName << ": run" << endl;}
private:
	string mName;
};

class CObserver
{
public:
	virtual void OnNotify(CEntity* Entity, EEvent Evnt) = 0;
};

class CSubject
{
public:
	void Notify(CEntity* Entity, EEvent Evnt)
	{
		for (const auto& Observer: mList)
		{
			Observer->OnNotify(Entity, Evnt);
		}
	}
	void AddObserver(CObserver* Observer)
	{
		mList.push_back(Observer);
	}
	void RemoveObserver(CObserver* Observer)
	{
		auto Iter = find(mList.begin(), mList.end(), Observer);
		if (Iter != mList.end())
			mList.erase(Iter);
	}
private:
	vector<CObserver*> mList;
};

class CRobot: public CObserver
{
public:
	CRobot(string Name): mName(Name) {}
	void OnNotify(CEntity* Entity, EEvent Evnt)
	{
		if (Evnt == EEvent::Run)
		{
			Run();
		}
	}
	void Run() {cout << mName << ": run " << endl;}
private:
	string mName;
};

class CSystem
{
public:
	CSystem(CEntity* Entity): mEntity(Entity) {mSub = new CSubject();}
	void Update()
	{
		mEntity->Run();
		mSub->Notify(mEntity, EEvent::Run);
	}

	CSubject* mSub;
private:
	CEntity* mEntity;
};

int main()
{
	CEntity* Bob = new CEntity("bob");
	CObserver* J0 = new CRobot("j0");

	CSystem* M = new CSystem(Bob);
	M->mSub->AddObserver(J0);
	M->Update();

	return 0;
}
