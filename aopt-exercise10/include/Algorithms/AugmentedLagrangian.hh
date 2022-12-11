#pragma once

#include <FunctionBase/FunctionBaseSparse.hh>
#include <Functions/AugmentedLagrangianProblem.hh>
#include <Utils/OptimizationStatistic.hh>
#include <Algorithms/NewtonMethods.hh>
#include "LBFGS.hh"


//== NAMESPACES ===============================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    class AugmentedLagrangian {
    public:
        // LA typedefs
        typedef FunctionBaseSparse::Vec Vec;

        static Vec solve(FunctionBaseSparse *_obj, const Vec& _initial_x, const std::vector<FunctionBaseSparse*>& _constraints, const std::vector<FunctionBaseSparse*>& _squared_constraints,
                const double _eta = 1e-4, const double _tau = 1e-4, const int _max_iters = 20) {
            std::cout << "******** Augmented Lagrangian ********" << std::endl;

            double mu = 10,
            tau = 1./mu,
            eta = std::pow(mu, -0.1),
            hnorm = 0.,
            //previous hnorm
            hnormp = std::numeric_limits<double>::max(),
            tau2 = _tau*_tau;

            //vector of nu and vector of constraint value
            Vec nu(_constraints.size()), h(_constraints.size());
            nu.setZero();
            h.setZero();

            //initialize the augmented lagrangian problem for the unconstrained solver
            AugmentedLagrangianProblem problem(_obj, _constraints, _squared_constraints, nu, mu);
            auto opt_st = std::make_unique<AOPT::OptimizationStatistic>(&problem);

            //get starting point
            Vec x = _initial_x;
            //store previous point
            Vec x_p = x;

            //allocate gradient storage
            Vec g(problem.n_unknowns());

            //------------------------------------------------------//
            //TODO: implement the augmented lagrangian method.
            //Hints: 1. Use projected newton method to solve for an approximated x.
            //          If the maximum iteration is reached and if the norm of the constraints
            //          gets larger, one can say it diverges for simplicity.
            //       2. Use set_mu(...) and set_nu(...) functions in AugmentedLagrangianProblem
            //          class to apply the change of nu and mu
            
                 
            bool newton_converged = true;
            auto stats_problem = opt_st.get();
            for (size_t i = 0; i < _max_iters; i++) {
                // hint 2
                problem.set_nu(nu);
                problem.set_mu(mu);
                // approx x
                x = NewtonMethods::solve_with_projected_hessian(stats_problem, newton_converged, x); 
                // hint 1
                if (!newton_converged) { //  maximum iteration is reached
                    x = x_p;
                    break;
                }
                problem.eval_constraints(x, h);
                hnorm = h.squaredNorm();
                if (hnorm > hnormp) { // the norm of the constraints get larger
                    x = x_p;
                    break;
                }
                hnormp = hnorm;
                x_p = x;
                // Augmented Lagrangian Function
                stats_problem->eval_gradient(x, g);
                const auto g_lagrangian_sqr_norm = g.squaredNorm();
                
                if (hnorm <= eta) { // norm(h(x_{k+1})) <= η_k
                    if (hnorm <= _eta && g_lagrangian_sqr_norm <= tau2) { // test for convergence
                        break; // stop with approximate solution x_k
                    }
                    // update multipliers and tighten tolerances
                    nu += mu * h; 
                    eta /= std::pow(mu, 0.9); 
                    tau /= mu; 
                }
                else {
                    // increase penalty parameter, reset tolerances
                    mu *= 100; 
                    eta = 1 / std::pow(mu, 0.1); 
                    tau = 1 / mu; 
                }
            }
            
            //------------------------------------------------------//

            opt_st->print_statistics();

            return x;
        }
    };
    //=============================================================================

}



