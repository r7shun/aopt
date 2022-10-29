#pragma once

#include <FunctionBase/FunctionBase.hh>
#include <vector>
//== NAMESPACES ===============================================================

namespace AOPT {

//== CLASS DEFINITION =========================================================
    class OptimalityChecker {
    public:
        using Vec = Eigen::VectorXd;

        OptimalityChecker(const double _epsilon = 1e-13) : eps_(_epsilon) {}


        /** Checks whether a particular optimization problem satisfies the KKT conditions
         *
         * \param _objective pointer to the objective function, which should be any function
         *        inheriting from FunctionBase
         *
         * \param _inequality_constraints an array containing the inequalities,
         *        each representend as a function inheriting from FunctionBase,
         *        such that _inequality_constraints[i].eval_f(x) <= 0 for all i
         *        if x is in the feasible set
         *
         * \param _equality_constraints an array containing the equalities,
         *        each representend as a function inheriting from FunctionBase,
         *        such that _equality_constraints[i].eval_f(x) == 0 for all i
         *        if x is in the feasible set
         *
         * \param _query_point the point at which the KKT conditions should be checked
         *
         * \param _lambda the lambda coefficients of the dual problem.
         *        It should be of the same dimension as _inequality_constraints since
         *        there is one lambda factor per inequality in the dual problem
         * \param _nu the nu coefficients of the dual problem.
         *        It should be of the same dimension as _equality_constraints since
         *        there is one nu factor per equality in the dual problem
         * */
        bool is_KKT_satisfied(FunctionBase *_objective, const std::vector<FunctionBase *>& _inequality_constraints,
                              const std::vector<FunctionBase *>& _equality_constraints,
                              const Vec& _query_point, const Vec& _lambda, const Vec& _nu) {
            //------------------------------------------------------//
            //Todo:
            //1. check only condition 4 in case there are no constraints
            //2. check inequality constraints (cond. 1.)
            //3. check equality constraints (cond. 1.)
            //4. check lambda (cond. 2.)
            //5. check complementary slackness (cond. 3.)
            //6. check gradient (cond. 4.)
            //------------------------------------------------------//

            // 1
            assert(_objective->n_unknowns() == _query_point.size());
            if(_inequality_constraints.empty() && _equality_constraints.empty()) {
                Vec g_eval(_objective->n_unknowns());
                g_eval.setZero();
                _objective->eval_gradient(_query_point, g_eval);
                if(g_eval.norm() < eps_) return true;
                else return false;
            } else if(_inequality_constraints.size() != _lambda.size() || _equality_constraints.size() != _nu.size()) 
                return false;

            
            // 2
            for (size_t i = 0; i < _inequality_constraints.size(); i++) {
                assert(_inequality_constraints[i]->n_unknowns() == _query_point.size());
                if (_inequality_constraints[i]->eval_f(_query_point) > eps_) 
                    return false;
                
            }
            // 3
            for (size_t i = 0; i < _equality_constraints.size(); i++) {
                assert(_equality_constraints[i]->n_unknowns() == _query_point.size());
                if (std::abs(_equality_constraints[i]->eval_f(_query_point)) > eps_) 
                    return false;
                
            }
            
            // 4
            if (_lambda.minCoeff() < -eps_) // check >= 0
                return false;
            

            // 5
            for (size_t i = 0; i < _inequality_constraints.size(); i++) {
                if (std::abs(_lambda[i]*_inequality_constraints[i]->eval_f(_query_point)) > eps_) 
                    return false;
            }

            // 6
            Vec g_sum(_objective->n_unknowns());
            Vec g_eval(_objective->n_unknowns());
            g_sum.setZero();
            g_eval.setZero();
            _objective->eval_gradient(_query_point, g_eval);
            g_sum = g_eval;


            for (size_t i = 0; i < _inequality_constraints.size(); i++) {
                _inequality_constraints[i]->eval_gradient(_query_point, g_eval);
                g_sum += _lambda[i] * g_eval;
            }

            for (size_t i = 0; i < _equality_constraints.size(); i++) {
                _equality_constraints[i]->eval_gradient(_query_point, g_eval);
                g_sum += _nu[i] * g_eval;

            }

            if (g_sum.norm() > eps_) 
                return false;
            // if all pass
            return true;
        }

    private:
        double eps_;
    };
//=============================================================================
}



