#include <iostream>
#include <memory>

using namespace std;

struct IDuck
{
	virtual void Quack() = 0;
	virtual void Fly() = 0;
	virtual ~IDuck() = default;
};

class CMallardDuck : public IDuck
{
public:
	void Quack() override
	{
		cout << "Quack\n";
	}
	void Fly() override
	{
		cout << "I'm flying\n";
	}
};

void TestDuck(IDuck & duck)
{
	duck.Quack();
	duck.Fly();
}

struct ITurkey
{
	virtual void Gobble() = 0;
	virtual void Fly() = 0;
	virtual ~ITurkey() = default;
};

class CWildTurkey : public ITurkey
{
public:
	void Gobble() override
	{
		cout << "Gobble gobble\n";
	}
	void Fly() override
	{
		cout << "I'm flying a short distance\n";
	}
};


class CTurkeyAdapter : public IDuck
{
public:
	CTurkeyAdapter(ITurkey & turkey)
		:m_turkey(turkey)
	{}

	void Quack() override
	{
		m_turkey.Gobble();
	}
	void Fly() override
	{
		for (int i = 0; i < 5; ++i)
		{
			m_turkey.Fly();
		}
	}
private:
	ITurkey & m_turkey;
};

int main()
{
	CMallardDuck mallardDuck;
	TestDuck(mallardDuck);

	CWildTurkey wildTurkey;
	CTurkeyAdapter turkeyAdapter(wildTurkey);
	TestDuck(turkeyAdapter);
	return 0;
}