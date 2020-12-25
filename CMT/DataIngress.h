#pragma once

#include <memory>

#include "MarketData.h"

class IDataIngress
{
public:
	virtual void IngestData(std::shared_ptr<MarketData> data) = 0;
};