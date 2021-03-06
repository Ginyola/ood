// SimUDuck_functional.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

using FlyBehavior = function<void()>;
using QuackBehavior = function<void()>;
using DanceBehavior = function<void()>;

FlyBehavior FlyWithWings()
{
	unsigned departureCount = 0;

	return [=]() mutable
	{
		cout << "I'm flying with wings!! " << ++departureCount << " time(-s)" << endl;
	};
};

FlyBehavior FlyNoWay()
{
	return[]() {};
}

DanceBehavior PerformValse()
{
	return []()
	{
		cout << "Perform valse" << endl;
	};
};

DanceBehavior PerformMenuet()
{
	return []()
	{
		cout << "Perform menuet" << endl;
	};
};

DanceBehavior CanTDance()
{
	return []() {};
}

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

QuackBehavior StandardQuackBehavior()
{
	return []()
	{
		cout << "Quack Quack!!!" << endl;
	};
}

QuackBehavior SqueakBehavior()
{
	return []() 
	{
		cout << "Squeek!!!" << endl;
	};
}

QuackBehavior MuteQuackBehavior()
{
	return []() {};
}

class Duck
{
public:
	Duck(FlyBehavior const& flyBehavior,
		QuackBehavior const& quackBehavior,
		DanceBehavior const& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehavior const& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(DanceBehavior const& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = danceBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), StandardQuackBehavior(), PerformValse())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), StandardQuackBehavior(), PerformMenuet())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay(), MuteQuackBehavior(), CanTDance())
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay(), SqueakBehavior(), CanTDance())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay(), StandardQuackBehavior(), CanTDance())
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	mallarDuck.Fly();
	mallarDuck.SetFlyBehavior(FlyWithWings());
	mallarDuck.Fly();



	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings());
	PlayWithDuck(modelDuck);

	return 0;
}
