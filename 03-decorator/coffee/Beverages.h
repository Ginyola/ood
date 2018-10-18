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
	CCapuccino()
	{
		if (m_size == CoffieSize::DOUBLE)
		{
			CCoffee("Capuccino");
		}
		else
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
	CLatte() 
	{
		if (m_size == CoffieSize::DOUBLE)
		{
			CCoffee("Latte");
		}
		else
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
	CTea() 
		:CBeverage("Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
