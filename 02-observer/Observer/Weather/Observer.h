#pragma once

#include <set>
#include <functional>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer) override
	{
		m_observers.insert(&observer);
		++m_observersAmount;
	}

	void NotifyObservers() override
	{
		auto currentObserversAmount = m_observersAmount;

		T data = GetChangedData();
		auto clone(m_observers);

		for (auto & observer : clone)
		{
			observer->Update(data);
		}
		
		if (currentObserversAmount != m_observersAmount)
		{
			cout << "Houston have a loss :( "
				<< currentObserversAmount << " " 
				<< m_observersAmount 
				<< endl;
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		m_observers.erase(&observer);
		--m_observersAmount;
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType *> m_observers;
	int m_observersAmount = 0;
};