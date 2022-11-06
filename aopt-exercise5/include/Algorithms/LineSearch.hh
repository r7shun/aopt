#pragma once

#include <FunctionBase/FunctionBaseSparse.hh>

//== NAMESPACES ===============================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

    class LineSearch {
    public:
        typedef FunctionBaseSparse::Vec Vec;
        typedef FunctionBaseSparse::SMat SMat;

        /** Back-tracking line search method
         *
         * \param _problem a pointer to a specific Problem, which can be any type that
         *        has the same interface as FunctionBase's (i.e. with eval_f, eval_gradient, etc.)
         * \param _x starting point of the method. Should be of the same dimension as the Problem's
         * \param _g gradient at the starting point.
         * \param _dx delta x
         * \param _t0 inital step of the method
         * \param _alpha and _tau variation constant, as stated by the method's definition
         * \return the final step t computed by the back-tracking line search */
        template <class Problem>
        static double backtracking_line_search(Problem *_problem,
                                               const Vec &_x,
                                               const Vec &_g,
                                               const Vec &_dx,
                                               const double _t0,
                                               const double _alpha = 0.5,
                                               const double _tau = 0.75) {
            
            double t(0);
            
            //------------------------------------------------------//
            //TODO: implement the backtracking line search algorithm
            double f0 = _problem->eval_f(_x);
            t = _t0;
            double f1 = _problem->eval_f(_x + t * _dx);
            double g0 = _g.dot(_dx);

            // descent direction
            if (g0 > 0)  return t;

            while (!(f1 <= f0 + _alpha * t * g0)) {
                t *= _tau;
                f1 = _problem->eval_f(_x + t * _dx);

            }
            //------------------------------------------------------//

            return t;
        }


    private:
        
    };
//=============================================================================
}



