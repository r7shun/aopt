#pragma once

#include <FunctionBase/FunctionBaseSparse.hh>
#include "LineSearch.hh"

//== NAMESPACES ===============================================================

namespace AOPT {

    /* Performs a gradient descent on a given problem.
     * This can work with any Problem with a FunctionBase-style interface since
     * the gradient descent method is rather generic mathematically */
    class GradientDescent {
    public:
        typedef FunctionBaseSparse::Vec Vec; ///< Eigen::VectorXd


        /**
         * \param _problem a pointer to a specific Problem, which can be any type that
         *        has the same interface as FunctionBase's (i.e. with eval_f, eval_gradient, etc.)
         * \param _initial_x  the x starting point
         * \param _eps the stopping criterion below which we consider the method
         *             to be done
         * \param _max_iters a capping number of iterations in case you would end-up with a
         *             bad configuration where the successive attemps of finding the
         *             minimum kind of oscillate around the actual minimum without
         *             finding it
         *
         * \return the minimum found by the method. */
        template <class Problem>
        static Vec solve(Problem *_problem, const Vec& _initial_x, const double _eps = 1e-4, const int _max_iters = 1000000) {
            std::cout << "******** Gradient Descent ********" << std::endl;

            // squared epsilon for stopping criterion
            double e2 = _eps * _eps;

            // get starting point
            Vec x = _initial_x;

            // allocate gradient storage
            Vec g(_problem->n_unknowns());
            int iter(0);

            //------------------------------------------------------//
            //TODO: implement the gradient descent
            
            double fp = 1e10;

            while (iter < _max_iters) {
                _problem->eval_gradient(x, g);
                Vec dx = -g;
                double alpha = LineSearch::backtracking_line_search(_problem, x, g, dx, 1.);
                x = x - alpha * g;
                double g2 = g.dot(g);
                double f = _problem->eval_f(x);

                if (g2 <= e2 || f >= fp) break;       
                fp = f;
                iter++;
            }   

            //------------------------------------------------------//

            return x;
        }
    };
}



