#include "stdafx.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 10, 0);
	wd.SetMeasurements(4, 0.8, 761, 5, 90);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 759, 9, 1000);
	wd.SetMeasurements(-10, 0.8, 761, 2, 12);
	return 0;
}