#pragma once

#include <Utils/RandomNumberGenerator.hh>
#include <FunctionBase/FunctionBase.hh>
using namespace std;
//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

    class ConvexityTest {
    public:
        using Vec = FunctionBase::Vec; ///< Eigen::VectorXd
        using Mat = FunctionBase::Mat; ///< Eigen::MatrixXd

        ConvexityTest() {}

        ~ConvexityTest() {}

    public:

        /** Checks whether the function given as argument is convex or not.
         * If it is not, it should output a point not satisfying the convexity property
         * before returning false.
         * \param _function a function pointer that should be any class inheriting
         * from FunctionBase, e.g. FunctionQuadraticND
         * \param min the minimum value of all tested points' coordinate
         * \param max the maximum value of all tested points' coordinate
         * \param n_evals the number of evaluations/samples tested on the
         *        line between the two points on the function */
        static bool isConvex(FunctionBase* _function, const double min = -1000., const double max = 1000., const int n_evals = 10) {
            const int n = _function->n_unknowns();
            //randomly generate number from min to max
            RandomNumberGenerator rng(min, max);
            
            const int max_sampling_points(1000000);

            //------------------------------------------------------//
            //Todo: Add your code here
            double theta;
            double d_theta = 1.0 / n_evals;
            int cnt_t = 0;
            while (cnt_t != max_sampling_points) { // sample max_sampling_points times
                Vec x = rng.get_random_nd_vector(n);
                Vec y = rng.get_random_nd_vector(n); // generate two n-dimensional random points
                theta = 0.0;
                for(int k = 0; k < n_evals; k++) { // θ increased by a fixed delta n_evals-1 times.
                    Vec p = theta*x +(1-theta)*y;
                    if (_function->eval_f(p) > (theta*_function->eval_f(x) + (1-theta)*_function->eval_f(y))) {
                        Eigen::IOFormat fmt(Eigen::StreamPrecision, 0, ", ", "\n", "[", "]");
                        cout << "The function is not convex at " << p.transpose().format(fmt) << endl;
                        return false;
                    }
                        
                    theta = theta + d_theta;
                }
                cnt_t++;
            }
            std::cout << "We assume the function is convex after " << max_sampling_points << " times sampling." << endl;
            //------------------------------------------------------//
            //return false;
            return true; // changed here to true because otherwise needs "goto"
        }


    private:
        static void printPathInfo(FunctionBase::Vec p1, FunctionBase::Vec p2, FunctionBase::Vec p, double t) {
            std::cout << "path: p(t) = (1 - t) * p1 + t * p2; \nwith:\n"
                      << "  p1 = (" << p1.transpose() << ")\n"
                      << "  p2 = (" << p2.transpose() << ")\n"
                      << "  p (t = " << t << ") = (" << p.transpose() << ")" << std::endl;
        }

    };




}
