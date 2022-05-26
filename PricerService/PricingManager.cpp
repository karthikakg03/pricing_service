#include "PricingManager.h"

void PricerService::producerTask()
{
    //User input as list of trade_IDs
    //currently passing number of trade ids
    // creating the trades and market data inside the service
    //Producer thread can subcribe to any solace topic and get the 
    //EOD or LIVE update 
    // for the simplicity handled with trade id
    std::unique_lock<std::mutex> lock(m_Mutex);
    for (int i = 0; i < m_TradeCaheInput; ++i)
    {
        std::vector<int> trade_ids(number_of_trade);
        auto trades = m_PortFolioObj->loadTrades(trade_ids);
        m_DataManagerObj->buildPriceables(trades);
    }
    m_cv.notify_one();
    m_taskCompleted = true;
}

void PricerService::consumerTask()
{
    //Consumer thread reads the queue and process the input trade
    //price them according to the tradeType
    //Currently I have handled two types
    //IROptions and IRSwap
    //implemented a generic thread pool to process the pricing parall
    // the same thread pool can be used to fetch marketData from server
    // and read trades from tradeStore.
    do
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        auto data = m_DataManagerObj->getPriceable();
        while (m_DataManagerObj->getPriceable().empty())
        {
            m_cv.wait(lock, [&]() { return m_taskCompleted || !m_DataManagerObj->getPriceable().empty(); });
        }
        while (!m_DataManagerObj->getPriceable().empty()) 
        {
            auto results = m_DataManagerObj->PricePriceables();
            for (auto&& result : results) {
                std::cout << '\n' << result.get() << ' ';
            }
            std::cout << results.size() << " Trades priced successfully " << std::endl;
            m_DataManagerObj->clearQueue();
        }
    } while (!m_taskCompleted);
}

void PricerService::startPricingService() {
    startProducerThread();
    startConsumerThread();
}

void PricerService::startProducerThread()
{
    std::thread producer_thread(&PricerService::producerTask, this);

    producer_thread.join();
}
void PricerService::startConsumerThread()
{
    std::thread consumer_thread(&PricerService::consumerTask, this);

    consumer_thread.join();
}