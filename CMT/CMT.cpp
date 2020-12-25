
#include <string>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "ReadConfiguration.h"
#include "IngestData.h"

namespace po = boost::program_options;
namespace fs = std::filesystem;



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

