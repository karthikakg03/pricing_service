#pragma once

#include "../PricerModeEnum.h"

//Interface for Trade types
//Currently handled IROption and IRSwap

class ITrade {

protected:
	TradeType product_Type = TradeType::IRSwap;

public:
	virtual TradeType getTradeType()
	{
		return product_Type;
	}

	virtual ~ITrade() = default;

};

class IRSwap : public ITrade {

public:
	IRSwap()
	{
		product_Type = TradeType::IRSwap;
	}
};

class IROption : public ITrade {

public:
	IROption()
	{
		product_Type = TradeType::IROption;
	}
};