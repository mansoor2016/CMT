
#include <string>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <filesystem>

#include <boost/program_options.hpp>

#include "CSVReader.h"
#include "StockData.h"
#include "MarketData.h"

namespace fs = std::filesystem;
namespace po = boost::program_options;

CSVReader::CSVReader(const po::variables_map& config)
{
    fs::path market_data_filepath = config["datafile"].as<std::string>();

    if (!fs::exists(market_data_filepath))
    {
        throw fs::filesystem_error("Could not locate: " + market_data_filepath.string(), {});
    }

    this->datafile = std::fstream(market_data_filepath.string());
}


void CSVReader::IngestData(std::shared_ptr<MarketData> market_data)
{
    
    std::string data_line;

    while (std::getline(this->datafile, data_line))
    {
        try
        {
            auto stock_data = StockData(std::move(data_line));
            market_data->data.emplace_back(stock_data);
        }
        catch (std::bad_cast ex)
        {
            // Ignore for now
        }
    }
}