#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

auto ReadConfiguration(int argc, char** argv)->po::variables_map;