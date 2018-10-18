#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}

	double GetCost() const override
	{
		return 0;
	}

private:
	std::string m_description;
};

enum CoffieSize
{
	STANDARD,
	DOUBLE
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee", CoffieSize size = CoffieSize::STANDARD)
		:CBeverage(description)
		, m_size(size)
	{}

	double GetCost() const override 
	{
		return 60; 
	}
protected:
	CoffieSize m_size;
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const std::string& description = "Capuccino", CoffieSize size = CoffieSize::STANDARD)
		: CCoffee(description, size)
	{
		if (m_size == CoffieSize::DOUBLE)
		{
			CCoffee("Double Capuccino");
		}
	}

	double GetCost() const override 
	{
		return (CoffieSize::DOUBLE) ? 120 : 80;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const std::string& description = "Latte", CoffieSize size = CoffieSize::STANDARD)
		: CCoffee(description, size)
	{
		if (m_size == CoffieSize::DOUBLE)
		{
			CCoffee("Double Latte");
		}
	}

	double GetCost() const override 
	{
		return (CoffieSize::DOUBLE) ? 130 : 90;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class CBlackTea : public CTea
{
	CBlackTea()
		:CTea("Black Tea")
	{}
};

class CGreenTea : public CTea
{
	CGreenTea()
		:CTea("Green Tea")
	{}
};

class CRedTea : public CTea
{
	CRedTea()
		:CTea("Red Tea")
	{}
};

class CCannabisTea : public CTea
{
	CCannabisTea()
		:CTea("Funny Tea")
	{}
};


enum MilkshakeSize
{
	SMALL,
	MEDIUM,
	LARGE
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(const std::string& description = "Milkshake", MilkshakeSize size = MilkshakeSize::SMALL)
		:CBeverage(description)
		, m_size(size)
	{
		if (m_size == MilkshakeSize::SMALL)
		{
			CBeverage("Small milkshake");
		};

		if (m_size == MilkshakeSize::MEDIUM)
		{
			CBeverage("Medium milkshake");
		};

		if (m_size == MilkshakeSize::LARGE)
		{
			CBeverage("Large milkshake");;
		};
	}

	double GetCost() const override 
	{ 
		double cost;

		if(m_size == MilkshakeSize::SMALL)
		{
			cost = 50;
		};

		if (m_size == MilkshakeSize::MEDIUM)
		{
			cost = 60;
		};

		if (m_size == MilkshakeSize::LARGE)
		{
			cost = 80;
		};

		return cost; 
	}
private:
	MilkshakeSize m_size;
};
