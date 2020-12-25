
#include <memory>
#include <iostream>
#include <stdexcept>

#include "CSVReader.h"
#include "MarketData.h"
#include "KafkaProducer.h"
#include "ReadConfiguration.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        const auto configuration = ReadConfiguration(argc, argv);
        
        std::shared_ptr<MarketData> market_data;
        auto data_reader = std::make_unique<CSVReader>(configuration);        
        data_reader->IngestData(market_data);

        auto producer = std::make_unique<KafkaProducer>(market_data);
        producer->Produce();

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

