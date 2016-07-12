#include <iostream>
#include <unistd.h>
using namespace std;

class GameObject;

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(GameObject *obj) = 0;
};

class DemoInputComponent: public InputComponent
{
public:
	virtual void Update(GameObject *obj);
private:
	static const int DELTA = 10;
};

class AInputComponent: public InputComponent
{
public:
	virtual void Update(GameObject *obj);
};

class GameObject
{
public:
	GameObject(InputComponent *input): m_pInput(input) {}
	~GameObject() {}

	void Update();

public:
	int m_iX, m_iY;
	int m_iV;
private:
	InputComponent *m_pInput;
};

void DemoInputComponent::Update(GameObject *obj)
{
	obj->m_iX += DELTA;
	obj->m_iY += DELTA;
	obj->m_iV += DELTA;
	cout << "go ahead,demo" << endl;
}

void AInputComponent::Update(GameObject *obj)
{
	cout << "go left" << endl;
}

void GameObject::Update()
{
	m_pInput->Update(this);
}

int main()
{
	GameObject *bob = new GameObject(new AInputComponent());
	while (true)
	{
		bob->Update();
		sleep(1);
	}
	return 0;
}
