#pragma once
#include "../PricerModeEnum.h"
#include "Priceable.h"
#include "ITrade.h"
#include "marketData.h"
#include "IPricer.h"
#include "Portfolio.h"

#include <deque> 
#include <memory>
#include <future>

class tasks;
class Data;

class DataManager
{
	private:

		std::deque<std::shared_ptr<Priceable>> m_data;

	public:
		// function to load priceabls from upstream
		void buildPriceables(std::vector<ITrade*>& trades);

		std::vector< std::future<double> > PricePriceables();

		std::unique_ptr<IPricer> getPricer(TradeType);

		std::deque<std::shared_ptr<Priceable>> getPriceable() {
			return m_data;
		}

		void clearQueue()
		{
			m_data.clear();
		}
};
