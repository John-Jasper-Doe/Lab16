/**
 * @file clusterization.cpp
 * @brief Implimentation of the class "Clusterize".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include "clusterization.hpp"

/** @brief The namespace of the "Clustering" project. */
namespace kkmeans {
/** @brief The namespace of the "Core" */
namespace core {

clusterize::clusterize(datas_t&& input) noexcept : input_{std::move(input)} {}

clust_datas_t clusterize::exec(std::size_t k) {
  // Here we declare an instance of the kcentroid object.  It is the object used to
  // represent each of the centers used for clustering.  The kcentroid has 3 parameters
  // you need to set.  The first argument to the constructor is the kernel we wish to
  // use.  The second is a parameter that determines the numerical accuracy with which
  // the object will perform part of the learning algorithm.  Generally, smaller values
  // give better results but cause the algorithm to attempt to use more dictionary vectors
  // (and thus run slower and use more memory).  The third argument, however, is the
  // maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
  // it to control the runtime complexity.
  dlib::kcentroid<kernel_type> kc(kernel_type(0.000001), 0.01, 16);

  // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
  // that are configured with the parameters from the kc object we defined above.
  dlib::kkmeans<kernel_type> test(kc);

  clust_datas_t res;
  core::datas_t initial_centers;

  // tell the kkmeans object we made that we want to run k-means with k clusters
  test.set_number_of_centers(k);

  // You need to pick some initial centers for the k-means algorithm.  So here
  // we will use the dlib::pick_initial_centers() function which tries to find
  // n points that are far apart (basically).
  pick_initial_centers(static_cast<long>(k), initial_centers, input_, test.get_kernel());

  // now run the k-means algorithm on our set of samples.
  test.train(input_, initial_centers);

  // now loop over all our samples and print out their predicted class.  In this example
  // all points are correctly identified.
  for (const auto& point : input_) {
    res.emplace_back(clust_data{point(0), point(1), test(point)});
  }

  return res;
}

} /* core:: */
} /* kkmeans:: */
