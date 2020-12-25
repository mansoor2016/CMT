#pragma once

#include <vector>

#include "StockData.h"
#include "MarketData.h"


MarketData::MarketData(std::size_t size) :
	data()
{
	data.reserve(size);
}

void MarketData::Push(StockData&& stock_data) 
{ 
	data.push_back(stock_data);
}

void MarketData::Push(std::vector<StockData>&& stock_data) 
{ 
	data.insert(data.end(), stock_data.begin(), stock_data.end()); 
}