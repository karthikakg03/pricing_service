#pragma once 

#include "PricingServiceExport.h"
#include "ThreadPool.h"
#include "Portfolio.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

constexpr int number_of_trade = 3;

class DLLEXPORT PricerService {
private:
    std::queue<int> m_data;
    std::atomic_bool m_taskCompleted;
    std::mutex m_Mutex;
    std::condition_variable m_cv;
    int m_TradeCaheInput;
    std::unique_ptr<Portfolio> m_PortFolioObj;
    std::unique_ptr<DataManager> m_DataManagerObj;
public:

    PricerService(int TradeCaheInput)
        : m_taskCompleted(false)
        , m_TradeCaheInput(TradeCaheInput)
    {
        m_PortFolioObj = std::make_unique<Portfolio>();
        m_DataManagerObj = std::make_unique<DataManager>();
    }
    //Thread Tasks
    void producerTask();
    void consumerTask();

    //For Google test -  for simulating the Pricing service
    void startProducerThread();
    void startConsumerThread();
    void startPricingService();
};