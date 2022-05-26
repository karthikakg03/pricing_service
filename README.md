# Pricing Service (PS)
Pricing service used to price different financial products in Fixed Income.
PS is implemented with IRSwap and IROption.

# Input to Service
Pricing service will take input as list of TradeID.
It can be extended to use trade data and market data as inputs or extended to subscribe a solace topic to fetch liveUpdate/EOD from a different server for different regions and asofDate's.

# Producer Thread
Producer thread is used to fetch input data and build a priceable.
Priceable contain trade, marketdata and type of pricer needed to price the trade.
	if the user is providing the tradeid as input,this trade can be fetched from cache or live server.
	after introspecting the trade, we can get list of riskfactors and fetch the marketdatas from the server.
	According to the trades product type, we select the pricer.
	Above all the three datas are used to build the priceable.
Once the priceable is constructed, its push to a deque for further processing.

# Consumer Thread
Consumer thread is used to fetch the priceables from deque and according to the pricer the price functionality is executed.
Consumer thread is using a thread pool and push each pricing task to that pool.
Thread pool price the priceabls parallely and makes the service faster.
Producer thread can signal to consumer thread via a bool value to exit from the service.

# Results of the  Pricing Service
From thread pool, futures return the price functions return value.
Each pricers, price function will return presentValue(PV).
Later it can be extended to complete pricing result.

# google Test to simulate the Service.
Created a google test to similate the Pricing service.
Test invokes the service and results can be seen on output screen.

# Thread pool
Created a thread pool to impove the performance of the service.
As its a generic thread pool it can be used in many places consumer thread as well as in producer thread tasks.
currently it will creates number of workers according to the hardware cuncurrency. 
Each workers execute on independent task and return the results via futures, which can be collected at user level.

# Suggestions
This is a basic implementation of Pricing service,
This can be extended to do a serializaion for trade and marketdata to google proto format.
We can fetch the market data and cache it for repeated usage instead of quering the server multiple times.
Implementing trade cache is usefull while we are fetching liveUpdate/EOD from a different servers.
Risk result cache will be useful to validate the results for differnt asofdates EOD/Live Update trades.





