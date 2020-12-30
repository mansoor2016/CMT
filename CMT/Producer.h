#pragma once

#include <memory>

#include "MarketData.h"

class IProducer
{
public:
	virtual void Publish(std::shared_ptr<MarketData> data) const = 0;

	virtual ~IProducer() = default;
};