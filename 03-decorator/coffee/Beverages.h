#pragma once

#include "IBeverage.h"
#include <iostream>

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
	CCoffee(std::string& description)
		:CBeverage(description)
	{}

	double GetCost() const override 
	{
		return 60; 
	}
protected:
	CCoffee(std::string& description, CoffieSize size)
		: CBeverage(description)
		, m_size(size)
	{};
	CoffieSize m_size = CoffieSize::STANDARD;
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffieSize size)
		: CCoffee(GetCapuccinoDescription(size), size)
	{
	}

	double GetCost() const override 
	{
		return (CoffieSize::DOUBLE) ? 120 : 80;
	}

private:
	std::string GetCapuccinoDescription(CoffieSize size)
	{
		std::string description;
		if (size == CoffieSize::DOUBLE)
		{
			description = "Double Capuccino";
		}
		else
		{
			description = "Capuccino";
		}

		return description;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffieSize size)
		: CCoffee(GetLatteDescription(size), size)
	{
	}

	double GetCost() const override 
	{
		return (CoffieSize::DOUBLE) ? 130 : 90;
	}

private:
	std::string GetLatteDescription(CoffieSize size)
	{
		std::string description;
		if (size == CoffieSize::DOUBLE)
		{
			description = "Double Latte";
		}
		else
		{
			description = "Latte";
		}

		return description;
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
	CMilkshake(MilkshakeSize size)
		:CBeverage(GetMilksakeDescription(size))
		, m_size(size)
	{
	}

	double GetCost() const override 
	{ 
		double cost;

		if(m_size == MilkshakeSize::SMALL)
		{
			cost = 50;
		}

		if (m_size == MilkshakeSize::MEDIUM)
		{
			cost = 60;
		}

		if (m_size == MilkshakeSize::LARGE)
		{
			cost = 80;
		}

		return cost; 
	}
private:
	std::string GetMilksakeDescription(MilkshakeSize size)
	{
		std::string description;
		if (m_size == MilkshakeSize::SMALL)
		{
			description = "Small milkshake";
		}

		if (m_size == MilkshakeSize::MEDIUM)
		{
			description = "Medium milkshake";
		}

		if (m_size == MilkshakeSize::LARGE)
		{
			description = "Large milkshake";
		}

		return description;
	}

	MilkshakeSize m_size;
};
