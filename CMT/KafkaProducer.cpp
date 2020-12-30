
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

    delete conf;
    this->producer_name = producer->name();
}

KafkaProducer::~KafkaProducer()
{
    const int timeout = 15'000;
    this->producer->flush(timeout);
}

void KafkaProducer::Publish(std::shared_ptr<MarketData> data) const
{
    StockData* stock_data = &data->data[0];

    RdKafka::ErrorCode resp = 
        producer->produce(
            this->topic, 
            this->partition,
            RdKafka::Producer::RK_MSG_COPY,
            (void*)stock_data,
            2,
            NULL,
            0,
            0,
            NULL);

    //std::string errs(RdKafka::err2str(resp));
}
