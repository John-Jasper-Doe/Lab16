/**
 * @file classification.cpp
 * @brief Implimentation of the class "Classification".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include "classification.hpp"
#include "common/split.hpp"

/** @brief The namespace of the "Clustering" project. */
namespace rclss {
/** @brief The namespace of the "Core" */
namespace core {

namespace {

double euclid_distance(const coretypes::core::sample_t& lhs, const coretypes::core::sample_t& rhs) {
  return std::sqrt(std::pow(rhs(0) - lhs(0), 2) + std::pow(rhs(1) - rhs(1), 2));
}

} /* :: */

using namespace coretypes::core;

classification::classification(const std::string& model_file,
                               const std::string& clusters_file) noexcept
  : model_file_{std::move(model_file)}
  , clusters_file_{std::move(clusters_file)}
  , cluster_number_{0} {}

std::size_t classification::exec() {
  dlib::kcentroid<kernel_type> kc;
  dlib::kkmeans<kernel_type> test(kc);

  dlib::deserialize(model_file_) >> test;
  dlib::deserialize(clusters_file_) >> clusters_;

  std::string tmp{""};
  while (std::getline(std::cin, tmp)) {
    if (tmp.empty()) {
      continue;
    }

    std::vector<std::string> splitted = common::split(tmp);
    check(splitted);

    /* convert */
    sample_t sample;
    for (std::size_t j = 0; j != COLUMNS - 1; ++j) {
      sample(static_cast<long>(j)) = std::stod(splitted[j]);
    }

    cluster_number_ = test(sample);
    form_result(sample, clusters_[cluster_number_]);
  }

  return clusters_.size();
}

void classification::print_result(std::ostream& os) noexcept {
  for (sample_t& row : clusters_[cluster_number_]) {
    for (long i = 0; i != row.size(); ++i) {
      if (i != 0) {
        os << ';';
      }
      os << row(i);
    }
    os << '\n';
  }
}

void classification::check(std::vector<std::string>& data) {
  if (data.size() != COLUMNS - 1) {
    throw std::runtime_error("Invalid input format");
  }

  for (const auto& s : data) {
    if (s.empty()) {
      throw std::runtime_error("Invalid input format: there must not be any skipped cells");
    }
  }
}

void classification::form_result(const sample_t& sample, datas_t& clusters) {
  std::sort(clusters.begin(), clusters.end(), [&sample](const sample_t& lhs, const sample_t& rhs) {
    return euclid_distance(sample, lhs) < euclid_distance(sample, rhs);
  });
}

} /* core:: */
} /* rclss:: */
