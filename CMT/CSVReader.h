#pragma once

#include <memory>
#include <fstream>
#include <boost/program_options.hpp>

#include "DataIngress.h"
#include "MarketData.h"

namespace po = boost::program_options;

class CSVReader : public IDataIngress
{
	std::fstream datafile;
public:
	CSVReader(const po::variables_map& config);
	[[nodiscard]] void IngestData(std::shared_ptr<MarketData> market_data) override;
};
