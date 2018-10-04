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

private:
	void Update(int const &c) override
	{
		std::cout << "Self-removing..." << std::endl;
		m_father.RemoveObserver(*this);
		std::cout << "Removed" << std::endl;
	}

	CObservableObject &m_father;
};

BOOST_AUTO_TEST_SUITE(Weather_tests)

	BOOST_AUTO_TEST_CASE(Notify_observers)
	{
		CObservableObject data;
		CSuicideObserver observer(data);
		data.RegisterObserver(observer);
		data.NotifyObservers();
	}

BOOST_AUTO_TEST_SUITE_END()