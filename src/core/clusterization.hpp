/**
 * @file clusterization.hpp
 * @brief Definition of the class "Clusterize".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_CLUSTERIZATION_HPP_
#define CORE_CLUSTERIZATION_HPP_

#include "coretype.hpp"

/** @brief The namespace of the "Clustering" project. */
namespace rclst {
/** @brief The namespace of the "Core" */
namespace core {

/** @brief The Clusterize class. */
class clusterize {
  coretypes::core::datas_t input_;

public:
  /** @brief Constructor with params */
  explicit clusterize(coretypes::core::datas_t&& input) noexcept;

  /** @brief Calculated */
  void serialize(std::size_t k, const std::string& model_filename,
                 const std::string& clusters_file);
};

} /* core:: */
} /* rclst:: */

#endif /* CORE_CLUSTERIZATION_HPP_ */
