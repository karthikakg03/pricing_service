#pragma once

#include <memory>

class ITrade;

class MarketData
{
	//std::unordered_map<std::string, std::unique_ptr<Data>> m_marketData;

public:
	//fetch the marketdata according to the riskfactor factor associated witht he trade.
	std::unique_ptr<MarketData> FetchMarketData(const ITrade& trade)
	{
		//build marketData
		// and return it 
		return std::unique_ptr<MarketData>();
	}
};