#pragma once

#include <memory>

#include "Producer.h"
#include "MarketData.h"

class KafkaProducer : public IProducer
{
public:
	KafkaProducer(std::shared_ptr<MarketData> data);

	void Produce() override;
};
