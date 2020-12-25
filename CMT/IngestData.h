#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void IngestData(po::variables_map configuration);
