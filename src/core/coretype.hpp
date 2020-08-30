/**
 * @file coretype.hpp
 * @brief Definition of common types.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CORE_CORETYPE_HPP_
#define CORE_CORETYPE_HPP_

#include <dlib/clustering.h>
#include <vector>

namespace coretypes {
/** @brief The namespace of the "Core" */
namespace core {

// Here we declare that our samples will be 2 dimensional column vectors.
// (Note that if you don't know the dimensionality of your vectors at compile time
// you can change the 2 to a 0 and then set the size at runtime)
const size_t COLUMNS = 8;
using sample_t = dlib::matrix<double, COLUMNS - 1, 1>;

/** @brief Input data type. */
using datas_t = std::vector<sample_t>;

// Now we are making a typedef for the kind of kernel we want to use.  I picked the
// radial basis kernel because it only has one parameter and generally gives good
// results without much fiddling.
using kernel_type = dlib::radial_basis_kernel<sample_t>;

using column_ix_t = size_t;
using row_ix_t = size_t;

/** @brief The Output data struct. */
struct clust_data {
  double x{.0};
  double y{.0};
  std::size_t clust{0};
};
using clust_datas_t = std::vector<core::clust_data>;

} /* coretypes:: */
} /* core:: */

#endif /* CORE_CORETYPE_HPP_ */
