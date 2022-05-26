#pragma once

enum class ePricerMode
{
	ePricerMode_invalid,
	Pricing
};

enum class PricerType
{
	PricerType_invalid,
	IRSwapPricer,
	IROptionPricer
};

enum class TradeType
{
	TradeType_invalid,
	IRSwap,
	IROption
};
