#include <iostream>
using namespace std;

class templ
{
public:
	templ() {}
	int display()
	{
		cout << getSize() << endl;
		test();
	}
	virtual int getSize() = 0;	//将具体操作延迟到子类
	virtual void test() {cout << "templ" << endl;}
};

class rectangle: public templ
{
public:
	rectangle(int l, int w):len(l), wid(w) {}
	virtual int getSize() {return len * wid;}
	void test() {cout << "rectangle" << endl;}
private:
	int len, wid;
};

class circle: public templ
{
public:
	circle(int r): rad(r) {}
	virtual int getSize() {return 3 * rad * rad;}
	void test() {cout << "circle" << endl;}
private:
	int rad;
};

int main()
{
	templ *shape1 = new rectangle(5, 3);
	templ *shape2 = new circle(3);
	shape1->display();
	shape2->display();
	return 0;
}
