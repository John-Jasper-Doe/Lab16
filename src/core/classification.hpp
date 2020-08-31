/**
 * @file classification.hpp
 * @brief Definition of the class "Classification".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_CLASSIFICATION_HPP_
#define CORE_CLASSIFICATION_HPP_

#include "coretype.hpp"

/** @brief The namespace of the "Clustering" project. */
namespace rclss {
/** @brief The namespace of the "Core" */
namespace core {

/** @brief The Classification class. */
class classification {
  std::string model_file_;
  std::string clusters_file_;
  unsigned long cluster_number_;
  std::map<unsigned long, coretypes::core::datas_t> clusters_;

public:
  /** @brief Constructor with params */
  explicit classification(const std::string& model_file, const std::string& clusters_file) noexcept;

  /** @brief Run execution */
  std::size_t exec();

  void print_result(std::ostream& os) noexcept;

protected:
  void check(std::vector<std::string>& data);
  void form_result(const coretypes::core::sample_t& sample, coretypes::core::datas_t& clusters);
};

} /* core:: */
} /* rclss:: */

#endif /* CORE_CLASSIFICATION_HPP_ */
