#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay()
	{};

	CDisplay(unsigned priority)
		: m_priority(priority)
	{};

	void SetPriority(unsigned priority)
	{
		m_priority = priority;
	}

	unsigned GetPriority() const
	{
		return m_priority;
	}

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/

	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	unsigned m_priority = 0;
};

class CStatistics
{
public:
	void AddValue(double value)
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}

		m_accValue += value;
		++m_countAcc;
	}

	double GetMinValue() const
	{
		return m_minValue;
	}

	double GetMaxValue() const
	{
		return m_maxValue;
	}

	double GetAverageValue() const
	{
		return m_countAcc ? m_accValue / m_countAcc : 0;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperature.AddValue(data.temperature);
		m_humidity.AddValue(data.humidity);
		m_pressure.AddValue(data.pressure);

		std::cout << "Temperature: " << std::endl;
		PrintStatistics(m_temperature);
		std::cout << "Humidity: " << std::endl;
		PrintStatistics(m_humidity);
		std::cout << "Pressure: " << std::endl;
		PrintStatistics(m_pressure);
	}

	void PrintStatistics(CStatistics &data)
	{
		std::cout << "Max: " << data.GetMaxValue() << std::endl;
		std::cout << "Min: " << data.GetMinValue() << std::endl;
		std::cout << "Average: " << data.GetAverageValue() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CStatistics m_temperature;
	CStatistics m_humidity;
	CStatistics m_pressure;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// ����������� � �������� �������
	double GetTemperature() const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
