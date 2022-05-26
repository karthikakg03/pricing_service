#pragma once
#include "marketData.h"
#include "ITrade.h"
#include <memory>

class IPricer;
class ITrade;
class MarketData;
//Priceables class for trade and market data
// which also have which pricer is
//  reqired for this priceabls
class Priceable
{
	private:
		double m_pv = 0.0;
	
		std::unique_ptr<IPricer> m_pricer;
		std::unique_ptr<ITrade> m_trade;
		std::unique_ptr<MarketData> m_marketData;

	public:
		Priceable() {}

		void setMarketData(std::unique_ptr<MarketData>& mkData)
		{
			m_marketData = std::move(mkData);
		}

		void setPricer(std::unique_ptr<IPricer>& pricer)
		{
			m_pricer = std::move(pricer);
		}

		void setTrade(std::unique_ptr<ITrade>& trade)
		{
			m_trade = std::move(trade);
		}

		IPricer* getPricer() {
			return m_pricer.get();
		}
		ITrade* getTade() {
			return m_trade.get();
		}
		MarketData* getMarketData() {
			return m_marketData.get();
		}
};