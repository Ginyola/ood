#include "stdafx.h"
#include "WeatherData.h"

#include <boost/test/unit_test.hpp>

class CObservableObject : public CObservable<int>
{

public:
	std::string PrintHello() const
	{
		return "HELLO";
	}

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
		m_father(&father) {};

	std::string AmIAlive()
	{
		return "Yes!";
	}

private:
	void Update(int const &c) override
	{
		m_father->RemoveObserver(*this);
		std::cout << "Self-removing..." << m_father->PrintHello() << std::endl;
	}

	std::unique_ptr<CObservableObject> m_father;
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