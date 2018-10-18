#pragma once
#include "Observer.h"
#include <algorithm>
#include <cmath>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windForce = 0;
	double windDiraction = 0;
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
		m_windForce.AddValue(data.windForce);


		std::cout << "Temperature: " << std::endl;
		PrintStatistics(m_temperature);
		std::cout << "Humidity: " << std::endl;
		PrintStatistics(m_humidity);
		std::cout << "Pressure: " << std::endl;
		PrintStatistics(m_pressure);
		std::cout << "Wind Force: " << std::endl;
		PrintStatistics(m_windForce);
		std::cout << "Wind Diraction: " << std::endl;
		PrintWindDirection(data.windDiraction);
	}

	void PrintWindDirection(double const windDiractionValue)
	{
		std::string diraction;
		if((windDiractionValue > 300) || ((windDiractionValue >= 0) && (windDiractionValue <= 60)))
		{
			diraction += "North";
		}

		if ((windDiractionValue >= 120) && (windDiractionValue <= 240))
		{
			diraction += "South";
		}

		if ((windDiractionValue >= 30) && (windDiractionValue <= 150))
		{
			if (!empty(diraction))
			{
				diraction += "-";
			}
			diraction += "West";
		}

		if ((windDiractionValue >= 210) && (windDiractionValue <= 330))
		{
			if (!empty(diraction))
			{
				diraction += "-";
			}
			diraction += "East";
		}

		std::cout << "Direction: " << diraction << std::endl;
		std::cout << "----------------" << std::endl;
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
	CStatistics m_windForce;
	CStatistics m_windDiraction;
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

	double GetWindForce() const
	{
		return m_windForce;
	}

	double GetWindDiraction() const
	{
		return fmod(m_windDirection, static_cast<double>(360));;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windForce, double windDiraction)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windForce = windForce;
		m_windDirection = windDiraction;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windForce = GetWindForce();
		info.windDiraction = GetWindDiraction();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windForce = 0;
	double m_windDirection = 180;
};
