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
public:
	CSuicideObserver(CObservableObject &father) :
		m_father(father) {};

	unsigned GetNotificationNumber() const
	{
		return m_notificationCount;
	}

private:
	void Update(int const &c) override
	{
		++m_notificationCount;
		m_father.RemoveObserver(*this);
	}

	CObservableObject &m_father;
	unsigned m_notificationCount = 0;
};


BOOST_AUTO_TEST_SUITE(Weather_tests)

	BOOST_AUTO_TEST_CASE(Notify_observers)
	{
		CObservableObject data;
		CSuicideObserver observer(data);

		auto before = observer.GetNotificationNumber();

		data.RegisterObserver(observer);
		data.NotifyObservers();
		data.NotifyObservers();
		data.NotifyObservers();
		data.NotifyObservers();
		data.NotifyObservers();

		auto after = observer.GetNotificationNumber();
		std::cout << "Before: " << before << " After: " << after << std::endl;

		BOOST_CHECK((before == 0) && (after == 1));
	}

	BOOST_AUTO_TEST_CASE(Observers_notifying_with_priority)
	{
		CWeatherData data;

		CDisplay firstDisplay(1);
		CDisplay secondDisplay(2);
		CDisplay thirdDisplay(3);
		CDisplay forthDisplay(4);
		CDisplay fifthDisplay(5);

		data.RegisterObserver(firstDisplay);
		data.RegisterObserver(thirdDisplay);
		data.RegisterObserver(secondDisplay);
		data.RegisterObserver(fifthDisplay);
		data.RegisterObserver(forthDisplay);

		data.NotifyObservers();
	}

BOOST_AUTO_TEST_SUITE_END()