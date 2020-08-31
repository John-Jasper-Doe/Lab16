/**
 * @file rclss.cpp
 * @brief Main file in this project.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

/* See the license in the file "LICENSE.txt" in the root directory. */

#include "common/split.hpp"
#include "core/classification.hpp"
#include <boost/program_options.hpp>
#include <iostream>

/** @brief Anonymous namespace. */
namespace {

/** @brief Input data struct. */
struct param {
  std::string model_file{""};
  std::string clusters_file{""};
};

using param_t = param;

/** @brief Get option on cmd line. */
void get_param(const int argc, const char* const argv[], param_t& param) {
  namespace po = boost::program_options;

  // clang-format off
  po::options_description desc("Options: ");
  desc.add_options()
      ("help,h", "this help")
      ("model,m", po::value<std::string>(), "name of output model file")
      ("clust,c", po::value<std::string>(), "name of output clusters data file");
  // clang-format on

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  }
  catch (boost::program_options::error& err) {
    throw std::invalid_argument(err.what());
  }

  if (vm.count("help") || vm.count("h")) {
    std::cout << desc << "\n";
    exit(0);
  }

  if (vm.count("model"))
    param.model_file = vm["model"].as<std::string>() + std::string(".XXX");
  else if (vm.count("m"))
    param.model_file = vm["m"].as<std::string>() + std::string(".XXX");
  else
    throw std::invalid_argument("Number of clusters was not set");

  if (vm.count("clust"))
    param.clusters_file = vm["clust"].as<std::string>() + std::string(".XXX");
  else if (vm.count("c"))
    param.clusters_file = vm["c"].as<std::string>() + std::string(".XXX");
  else
    throw std::invalid_argument("Number of clusters was not set");
}

} /* :: */

/** @brief Main entry point */
int main(int argc, const char* argv[]) {
  param_t prm;

  try {
    get_param(argc, argv, prm);
  }
  catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  rclss::core::classification classific(prm.model_file, prm.clusters_file);
  std::size_t size = classific.exec();
  classific.print_result(std::cout);

  std::cout << "Size: " << size << std::endl;

  return EXIT_SUCCESS;
}
