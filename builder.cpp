#include <iostream>
using namespace std;

class CProduct
{
public:
    CProduct() {}
    void Display()
    {
        cout << mA << ":" << mB << endl;
    }
    int mA = 0;
    int mB = 0;
};

class CBuilder
{
public:
    CBuilder() {}

    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual CProduct GetProduct() = 0;
};

class CDirector
{
public:
    CDirector(CBuilder* b)
    {
        mpB = b;
    }
    void Build()
    {
        mpB->BuildPartA();
        mpB->BuildPartB();
    }
private:
    CBuilder* mpB;
};

class CABuilder: public CBuilder
{
public:
    CABuilder() {mPro = new CProduct();}
    virtual void BuildPartA()
    {
        mPro->mA = 10;
    }
    virtual void BuildPartB()
    {
        mPro->mB = 20;
    }
    CProduct GetProduct()
    {
        return *mPro;
    }
private:
    CProduct* mPro;
};

class CBBuilder: public CBuilder
{
public:
    CBBuilder() {mPro = new CProduct();}
    virtual void BuildPartA()
    {
        mPro->mA = 50;
    }
    virtual void BuildPartB()
    {
        mPro->mB = 60;
    }
    CProduct GetProduct()
    {
        return *mPro;
    }
private:
    CProduct* mPro;
};

int main()
{
    CBuilder* pBuilder = new CABuilder();
    CDirector* pDirector = new CDirector(pBuilder);
    pDirector->Build();
    CProduct ProductA = pBuilder->GetProduct();
    pBuilder = new CBBuilder();
    pDirector = new CDirector(pBuilder);
    pDirector->Build();
    CProduct ProductB = pBuilder->GetProduct();
    ProductA.Display();
    ProductB.Display();
    return 0;
}
