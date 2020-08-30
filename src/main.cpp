/**
 * @file main.cpp
 * @brief Main file in this project.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

/* See the license in the file "LICENSE.txt" in the root directory. */

#include "core/clusterization.hpp"
#include <boost/program_options.hpp>
#include <iostream>

/** @brief Anonymous namespace. */
namespace {

/** @brief Input data struct. */
struct param {
  std::size_t k_means{0};
};

using param_t = param;

/** @brief Get option on cmd line. */
void get_param(const int argc, const char* const argv[], param_t& param) {
  namespace po = boost::program_options;

  // clang-format off
  po::options_description desc("Options: ");
  desc.add_options()
      ("help,h", "this help")
      ("kmeans,k", po::value<std::size_t>(), "number of clusters for k-means algorithm");
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

  if (vm.count("kmeans"))
    param.k_means = vm["kmeans"].as<std::size_t>();
  else if (vm.count("k"))
    param.k_means = vm["k"].as<std::size_t>();
  else
    throw std::invalid_argument("Number of clusters was not set");
}

/**
 * @brief Reading data from an input stream.
 *
 * @details
 * Data is received from the input stream, then read line by line, parsed and
 * formed into a data vector.
 *
 * @param [in] istrm - the input stream where the data comes from.
 * @return Data vector ready.
 */
kkmeans::core::datas_t read_from(std::istream& istrm) {
  std::vector<kkmeans::core::sample_t> res;

  while (istrm) {
    std::string line;
    istrm >> line;

    if (!line.empty()) {
      kkmeans::core::sample_t dot;
      std::size_t sep_pos = line.find(';');
      dot(0) = std::stod(line.substr(0, sep_pos));
      dot(1) = std::stod(line.substr(sep_pos + 1, line.size() - sep_pos - 1));
      res.push_back(std::move(dot));
    }
  }

  return res;
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

  kkmeans::core::datas_t input_data = read_from(std::cin);
  kkmeans::core::clusterize clust(std::move(input_data));
  kkmeans::core::clust_datas_t output_data = clust.exec(prm.k_means);

  for (const auto& data : output_data) {
    std::cout << data.x << ';' << data.y << ';' << data.clust << '\n';
  }

  return EXIT_SUCCESS;
}
