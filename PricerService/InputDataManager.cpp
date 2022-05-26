
#include "InputDataManager.h"
#include "ThreadPool.h"


void DataManager::buildPriceables(std::vector<ITrade*>& trades)
{	
	//Build the priceable object
	
	// according to the trade riskfactor, load the Market data from server
	std::string rolType;

	auto MarketDataObj(std::make_unique<MarketData>());

	for (auto& trade : trades) {

		auto PriceableObj(std::make_unique<Priceable>());
		auto mkData = MarketDataObj->FetchMarketData(*trade);
		PriceableObj->setMarketData(mkData);

		auto pricer = getPricer(trade->getTradeType());
		PriceableObj->setPricer(pricer);

		auto tradeObj(std::make_unique<ITrade>(*trade));
		PriceableObj->setTrade(tradeObj);

		m_data.push_back(std::move(PriceableObj));
	}
}

std::unique_ptr<IPricer> DataManager::getPricer(TradeType type)
{
	switch (type)
	{
		case TradeType::IRSwap:
			return std::make_unique<IRSwapPricer>();
		case TradeType::IROption:
			return std::make_unique<IROptionPricer>();
		default:
			throw std::runtime_error("invalid Trade Type");
	}
}

std::vector< std::future<double> > DataManager::PricePriceables()
{
	//Use of thread pool for pricing the priceabls.
	size_t num_threads = std::thread::hardware_concurrency();
	ThreadPool pool(num_threads);

	std::vector< std::future<double> > results;

	for (auto& priceable : m_data)
	{
		results.emplace_back(
			pool.enqueue([&] {return priceable->getPricer()->price(priceable->getTade(), priceable->getMarketData());
				})
		);
	}
	return results;
}





