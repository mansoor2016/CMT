
#include <string>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include <boost/program_options.hpp>


#include "ReadConfiguration.h"

namespace po = boost::program_options;
namespace fs = std::filesystem;

void IngestData(po::variables_map configuration)
{
    fs::path market_data = configuration[""]
}

void PublishToKafka()
{

}


int main(int argc, char** argv)
{
    try
    {
        auto configuration = ReadConfiguration(argc, argv);
        IngestData(configuration);

        PublishToKafka();

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

