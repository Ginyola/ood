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
	double windDirection = 0;
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
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
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
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperature.AddValue(data.temperature);
		m_humidity.AddValue(data.humidity);
		m_pressure.AddValue(data.pressure);
		m_windForce.AddValue(data.windForce);
		m_windDirection.AddValue(data.windDirection);

		std::cout << "Temperature: " << std::endl;
		PrintStatistics(m_temperature);
		std::cout << "Humidity: " << std::endl;
		PrintStatistics(m_humidity);
		std::cout << "Pressure: " << std::endl;
		PrintStatistics(m_pressure);
		std::cout << "Wind Force: " << std::endl;
		PrintStatistics(m_windForce);
		std::cout << "Wind Diraction: " << std::endl;
		PrintWindDirection(m_windDirection);
	}

	void PrintWindDirection(CStatistics &data)
	{
		/*std::string diraction;
		if((windDirectionValue > 300) || ((windDirectionValue >= 0) && (windDirectionValue <= 60)))
		{
			diraction += "North";
		}

		if ((windDirectionValue >= 120) && (windDirectionValue <= 240))
		{
			diraction += "South";
		}

		if ((windDirectionValue >= 30) && (windDirectionValue <= 150))
		{
			if (!empty(diraction))
			{
				diraction += "-";
			}
			diraction += "West";
		}

		if ((windDirectionValue >= 210) && (windDirectionValue <= 330))
		{
			if (!empty(diraction))
			{
				diraction += "-";
			}
			diraction += "East";
		}*/
		double x = cos(data.GetAverageValue());
		double y = sin(data.GetAverageValue());

		std::cout << "Direction: " << atan2(y, x) << std::endl;
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
	CStatistics m_windDirection;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindForce() const
	{
		return m_windForce;
	}

	double GetWindDirection() const
	{
		return fmod(m_windDirection, static_cast<double>(360));;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windForce, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windForce = windForce;
		m_windDirection = windDirection;

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
		info.windDirection = GetWindDirection();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windForce = 0;
	double m_windDirection = 180;
};
