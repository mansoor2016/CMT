#include <string>

#include <stdexcept>
#include <filesystem>

#include <boost/program_options.hpp>

#include "IngestData.h"

namespace fs = std::filesystem;
namespace po = boost::program_options;

void IngestData(po::variables_map configuration)
{
    fs::path market_data = configuration["datafile"].as<std::string>();

    if (!fs::exists(market_data))
    {
        throw fs::filesystem_error("Could not locate: " + market_data.string(), {});
    }
}