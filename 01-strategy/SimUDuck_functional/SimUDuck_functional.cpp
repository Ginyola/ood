// SimUDuck_functional.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

using FlyBehavior = function<void()>;
//using QuackBehavior = function<void()>;
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
	return[=]() {};
}

DanceBehavior PerformValse()
{
	return [=]() mutable
	{
		cout << "Perform valse" << endl;
	};
};

DanceBehavior PerformMenuet()
{
	return [=]() mutable
	{
		cout << "Perform menuet" << endl;
	};
};

DanceBehavior CanTDance()
{
	return[=]() {};
}

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
public:
	Duck(FlyBehavior const& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		DanceBehavior const& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(danceBehavior)
	{
		assert(m_quackBehavior);
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
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
	unique_ptr<IQuackBehavior> m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), make_unique<QuackBehavior>(), PerformValse())
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
		: Duck(FlyWithWings(), make_unique<QuackBehavior>(), PerformMenuet())
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
		: Duck(FlyNoWay(), make_unique<MuteQuackBehavior>(), CanTDance())
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
		: Duck(FlyNoWay(), make_unique<SqueakBehavior>(), CanTDance())
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
		: Duck(FlyNoWay(), make_unique<QuackBehavior>(), CanTDance())
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
