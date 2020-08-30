/**
 * @file rclst.cpp
 * @brief Main file in this project.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

/* See the license in the file "LICENSE.txt" in the root directory. */

#include "common/split.hpp"
#include "core/clusterization.hpp"
#include <boost/program_options.hpp>
#include <iostream>

/** @brief Anonymous namespace. */
namespace {

/** @brief Input data struct. */
struct param {
  std::size_t k_means{0};
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
      ("kmeans,k", po::value<std::size_t>(), "number of clusters for k-means algorithm")
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

  if (vm.count("kmeans"))
    param.k_means = vm["kmeans"].as<std::size_t>();
  else if (vm.count("k"))
    param.k_means = vm["k"].as<std::size_t>();
  else
    throw std::invalid_argument("Number of clusters was not set");

  if (vm.count("model"))
    param.model_file = vm["model"].as<std::string>();
  else if (vm.count("m"))
    param.model_file = vm["m"].as<std::string>();
  else
    throw std::invalid_argument("Number of clusters was not set");

  if (vm.count("clust"))
    param.clusters_file = vm["clust"].as<std::string>();
  else if (vm.count("c"))
    param.clusters_file = vm["c"].as<std::string>();
  else
    throw std::invalid_argument("Number of clusters was not set");
}

/**
 * @brief Fill empty cells of vector of rows with average by column.
 * @param [in] skipped_coordinates - map for skipped cordinates.
 * @param [out] result - vector of rows.
 */
void fill_spaces(
    std::map<rclst::core::column_ix_t, std::vector<rclst::core::row_ix_t>> skipped_coordinates,
    std::vector<rclst::core::sample_t>& result) {
  using pair_t = std::pair<const rclst::core::column_ix_t, std::vector<rclst::core::row_ix_t>>;

  for (const pair_t& p : skipped_coordinates) {
    const rclst::core::column_ix_t& column_ix = p.first;
    const std::vector<rclst::core::row_ix_t>& skipped_row_ixes = p.second;

    double sum = 0.0;
    for (std::size_t row_ix = 0; row_ix != result.size(); ++row_ix) {
      sum += result[row_ix](static_cast<long>(column_ix));
    }

    std::size_t count = result.size() - skipped_row_ixes.size();
    double avg = sum / count;
    for (rclst::core::row_ix_t row_ix : skipped_row_ixes) {
      result[row_ix](static_cast<long>(column_ix)) = avg;
    }
  }
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
rclst::core::datas_t read_from(std::istream& istrm) {
  std::vector<rclst::core::sample_t> res;
  std::map<rclst::core::column_ix_t, std::vector<rclst::core::row_ix_t>> skipped_coordinates;

  std::string tmp{""};
  while (std::getline(istrm, tmp)) {
    if (tmp.empty()) {
      continue;
    }

    std::vector<std::string> splitted = common::split(tmp);
    if (splitted.size() != rclst::core::COLUMNS) {
      throw std::runtime_error("Wrong input format");
    }

    if (splitted[rclst::core::COLUMNS - 1].empty() || splitted[rclst::core::COLUMNS - 2].empty()) {
      continue;
    }

    std::size_t row_ix = res.size();
    for (std::size_t i = 0; i != splitted.size(); ++i) {
      if (splitted[i].empty()) {
        auto it = skipped_coordinates.find(i);
        if (it == skipped_coordinates.end())
          skipped_coordinates[i] = {std::vector<rclst::core::row_ix_t>{row_ix}};
        else
          it->second.push_back(row_ix);
      }
    }

    rclst::core::sample_t sample;
    for (std::size_t j = 0; j != rclst::core::COLUMNS - 1; ++j) {
      if (!splitted[j].empty())
        sample(static_cast<long>(j)) = std::stod(splitted[j]);
      else
        sample(static_cast<long>(j)) = 0.0;
    }

    const unsigned long long floor = std::stoull(splitted[rclst::core::COLUMNS - 2]);
    const unsigned long long max_floor = std::stoull(splitted[rclst::core::COLUMNS - 1]);
    if (floor == 1 || floor == max_floor)
      sample(rclst::core::COLUMNS - 2) = 0.0;
    else
      sample(rclst::core::COLUMNS - 2) = 1.0;
    res.push_back(std::move(sample));
  }

  fill_spaces(skipped_coordinates, res);
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

  rclst::core::datas_t input_data = read_from(std::cin);
  rclst::core::clusterize clust(std::move(input_data));

  clust.serialize(prm.k_means, prm.model_file, prm.clusters_file);

  std::cout << "Save model to file: " << prm.model_file << std::endl;
  std::cout << "Save clusters data to file: " << prm.clusters_file << std::endl;

  return EXIT_SUCCESS;
}
