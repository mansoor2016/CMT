
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include "ReadConfiguration.h"

namespace po = boost::program_options;
namespace ba = boost::algorithm;

/// <summary>
/// Read configuration from both command line arguments and environmental variables.
/// </summary>
/// <param name="argc">argc</param>
/// <param name="argv">argv</param>
/// <returns>Map object containing configuration settings.</returns>
auto ReadConfiguration(int argc, char** argv) -> po::variables_map
{
    po::options_description desc_env("Options:");

    desc_env.add_options()
        (
            "mode",
            po::value<std::string>()->default_value("1"),
            "Mode options [1,2]."
            )
        (
            "datafile",
            po::value<std::string>()->default_value(R"(.\market_data.csv)"),
            "Filepath to input market data."
            );

    po::variables_map vm;

    po::store(po::parse_command_line(argc, argv, desc_env), vm);
    po::store(
        po::parse_environment(
            desc_env,
            [](const auto& arg) 
            {
                return ba::to_lower_copy(arg) == "mode" ? "mode" : "";
            }),
        vm);

    po::notify(vm);
    return vm;
}
