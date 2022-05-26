#pragma once

#include "InputDataManager.h"
#include <vector>

class ITrade;

class Portfolio
{
private:
	std::vector<ITrade*> m_trades;

public:

	std::vector<ITrade*> loadTrades(std::vector<int>& trade_ids)
	{
		//connect to upstream
		//load the trade 	
		//serialized proto format trades received from server
		//can use the thread pool here to load the threads from upstream
		// now randomly creating few thread objects so simulate the service.

		m_trades = std::vector<ITrade*>{ new IROption, new IRSwap, new IROption };
		return getTrades();
	}
	std::vector<ITrade*> getTrades()
	{
		return m_trades;
	}
};