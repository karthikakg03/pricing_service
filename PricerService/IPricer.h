#pragma once 

#include <memory>
#include <iostream>

class ITrade;
class MarketData;

class IPricer {

protected:
	double m_pv = 0.0;

public:
	virtual double price(ITrade* trade, MarketData* marketData) = 0;
	virtual ~IPricer() = default;
};

class IRSwapPricer : public IPricer
{
public:
	double price(ITrade* trade, MarketData* marketData) override
	{
		//to return a result 
		//trade pv id returning
		m_pv = 1234.7685;
		return m_pv;
	}
};

class IROptionPricer : public IPricer
{
public:
	double price(ITrade* trade, MarketData* marketData) override
	{
		//to return a result 
		//trade pv id returning
		m_pv = 98745.7685;
		return m_pv;
	}
};
