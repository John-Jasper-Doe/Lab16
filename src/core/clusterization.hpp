/**
 * @file clusterization.hpp
 * @brief Definition of the class "Clusterize".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_CLUSTERIZATION_HPP_
#define CORE_CLUSTERIZATION_HPP_

#include <dlib/clustering.h>
#include <vector>

/** @brief The namespace of the "Clustering" project. */
namespace kkmeans {
/** @brief The namespace of the "Core" */
namespace core {

// Here we declare that our samples will be 2 dimensional column vectors.
// (Note that if you don't know the dimensionality of your vectors at compile time
// you can change the 2 to a 0 and then set the size at runtime)
using sample_t = dlib::matrix<double, 2, 1>;

/** @brief Input data type. */
using datas_t = std::vector<sample_t>;

/** @brief The Output data struct. */
struct clust_data {
  double x{.0};
  double y{.0};
  std::size_t clust{0};
};
using clust_datas_t = std::vector<core::clust_data>;

/** @brief The Clusterize class. */
class clusterize {
  // Now we are making a typedef for the kind of kernel we want to use.  I picked the
  // radial basis kernel because it only has one parameter and generally gives good
  // results without much fiddling.
  using kernel_type = dlib::radial_basis_kernel<sample_t>;

  datas_t input_;

public:
  /** @brief Constructor with params */
  explicit clusterize(datas_t&& input) noexcept;

  /** @brief Calculated */
  clust_datas_t exec(std::size_t k);
};

} /* core:: */
} /* kkmeans:: */

#endif /* CORE_CLUSTERIZATION_HPP_ */
