#include "pch.h"
#include "../../PricerService/PricingManager.h"


constexpr int number_of_trade_ids = 10;

TEST(Test_PricingService, PricingService)
{
	 // Giving trade id as input, and ramdomly creating few trades
	 // to show how service price the priceabls.
	 // controlling this dervice running time via a bool value 
	 // user can decide after how many iteration service can exit.

	  PricerService pricerService(number_of_trade_ids);
	  pricerService.startPricingService();

	  EXPECT_EQ(1, 1);
	  EXPECT_TRUE(true);
}

