#include <iostream>
using namespace std;

class product
{
public:
	product() {}
	void display()
	{
		cout << a << ":" << b << endl;
	}
	int a = 0;
	int b = 0;
};

class Builder
{
public:
	Builder() {}

	virtual void buildparta() = 0;
	virtual void buildpartb() = 0;
	virtual product getProduct() = 0;
};

class Director
{
public:
	Director(Builder *b)
	{
		pb = b;
	}
	void build()
	{
		pb->buildparta();
		pb->buildpartb();
	}
private:
	Builder *pb;
};

class abuilder: public Builder
{
public:
	abuilder() {pro = new product();}
	virtual void buildparta()
	{
		pro->a = 10;
	}
	virtual void buildpartb()
	{
		pro->b = 20;
	}
	product getProduct()
	{
		return *pro;
	}
private:
	product *pro;
};

class bbuilder: public Builder
{
public:
	bbuilder() {pro = new product();}
	virtual void buildparta()
	{
		pro->a = 50;
	}
	virtual void buildpartb()
	{
		pro->b = 60;
	}
	product getProduct()
	{
		return *pro;
	}
private:
	product *pro;
};

int main()
{
	Builder *p = new abuilder();
	Director *h = new Director(p);
	h->build();
	product a = p->getProduct();
	p = new bbuilder();
	h = new Director(p);
	h->build();
	product b = p->getProduct();
	a.display();
	b.display();
	return 0;
}
