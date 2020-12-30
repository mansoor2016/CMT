
#include <memory>
#include <iostream>
#include <stdexcept>

#include "CSVReader.h"
#include "MarketData.h"
#include "KafkaProducer.h"
#include "ReadConfiguration.h"

int main(int argc, char** argv)
{
    try
    {
        const auto configuration = ReadConfiguration(argc, argv);
        
        std::shared_ptr<MarketData> market_data = std::make_shared<MarketData>(50'000);

        auto data_reader = std::make_unique<CSVReader>(configuration);        
        data_reader->IngestData(market_data);

        auto producer = std::make_unique<KafkaProducer>();
        producer->Publish(market_data);

        return 0;
    }
    catch (std::exception ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Encountered unhandled exception." << std::endl;
    }

    return -1;
}

