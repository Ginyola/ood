#include "stdafx.h"
#include "WeatherData.h"

#include <boost/test/unit_test.hpp>

class CObservableObject : public CObservable<int>
{

protected:
	int GetChangedData()const override
	{
		return 0;
	};
};

class CSuicideObserver : public IObserver<int>
{
private:
	void Update(int const &c) override
	{
		std::unique_ptr<CSuicideObserver> ptr(this);
		ptr.reset();
	}

};

BOOST_AUTO_TEST_SUITE(Weather_tests)

	BOOST_AUTO_TEST_CASE(Notify_observers)
	{
		CObservableObject data;
		CSuicideObserver observer;
		data.RegisterObserver(observer);
		data.NotifyObservers();
	}
BOOST_AUTO_TEST_SUITE_END()