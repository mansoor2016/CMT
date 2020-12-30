
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include "MarketData.h"
#include "KafkaProducer.h"

KafkaProducer::KafkaProducer()
{      
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    std::string errstr;
    if (conf->set("bootstrap.servers", brokers, errstr) != RdKafka::Conf::CONF_OK) 
    {
        throw std::runtime_error(errstr);
    }
    
    producer.reset(RdKafka::Producer::create(conf, errstr));
    if (!producer)
    {
        throw std::runtime_error(errstr);
    }
    producer->poll(0);

    delete conf;
    this->producer_name = producer->name();
}

KafkaProducer::~KafkaProducer()
{
    const int timeout = 15'000;
    this->producer->flush(timeout);

    if (this->producer->outq_len() > 0)
    {
        std::cerr   << "% " << producer->outq_len() 
                    << " message(s) were not delivered" 
                    << std::endl;
    }
}

RdKafka::ErrorCode KafkaProducer::Publish(StockData stock_data) const
{
    return producer->produce(
        stock_data.name,
        this->partition,
        RdKafka::Producer::RK_MSG_COPY,
        const_cast<char*>(stock_data.ToString().c_str()),
        stock_data.ToString().size(),
        NULL,
        0,
        0,
        NULL);
}

void KafkaProducer::Publish(std::shared_ptr<MarketData> market_data) const
{
    for (auto stock_data : market_data->data)
    {
        RdKafka::ErrorCode resp = Publish(stock_data);

		if (resp == RdKafka::ERR__QUEUE_FULL)
		{
			this->producer->poll(1000);
		}
    }
}
