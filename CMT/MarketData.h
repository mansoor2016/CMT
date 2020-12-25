#pragma once

#include <vector>

#include "StockData.h"

struct MarketData
{
	std::vector<StockData> data;

	MarketData(std::size_t reserve_size);

	void Push(StockData&& stock_data);
	void Push(std::vector<StockData>&& stock_data);
};