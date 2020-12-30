#pragma once

#include <memory>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include "Producer.h"
#include "MarketData.h"

class KafkaProducer : public IProducer
{
	std::unique_ptr<RdKafka::Producer> producer;
	std::string producer_name;

	const std::string topic = "StockData";
	const std::string brokers = "kafkaserver:9092";

	const int32_t partition = RdKafka::Topic::PARTITION_UA;
public:
	KafkaProducer();

	~KafkaProducer();

	void Publish(std::shared_ptr<MarketData> data) const override;
};
