#pragma once

#include <FunctionBase/ParametricFunctionBase.hh>

//== NAMESPACES ===============================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

    class ConstrainedSpringElement2D : public ParametricFunctionBase {
    public:
        ConstrainedSpringElement2D() : ParametricFunctionBase() {}

        // number of unknowns
        inline virtual int n_unknowns() final { return 2; }

        /** evaluates the spring element's energy
         * \param _x the spring's current position
         * \param _coeffs _coeffs[0] is the penalty factor,
         *                _coeffs[1] and _coeffs[2] are the desired point coordinates
         * \return the energy of the spring */
        inline virtual double eval_f(const Vec &_x, const Vec &_coeffs) final {
            //------------------------------------------------------//
            //Todo: implement the function f(x) = 1/2 * penalty * ((x[0] - px)^2 + (x[1] - py)^2)
          
            double penalty = _coeffs[0];
            double px = _coeffs[1];
            double py = _coeffs[2];
            double x0 = _x[0];
            double x1 = _x[1];
            return 0.5 * penalty * ((x0 - px) * (x0 - px) + (x1 - py) * (x1 - py));
            //------------------------------------------------------//
        }

        /** evaluates the spring element's energy gradient
         * \param _x the spring's current position
         * \param _coeffs _coeffs[0] is the penalty factor,
         *                _coeffs[1] and _coeffs[2] are the desired point coordinates
         * \param _g gradient output */
        inline virtual void eval_gradient(const Vec &_x, const Vec &_coeffs, Vec &_g) final {
            //------------------------------------------------------//
            //Todo: implement the gradient and store in _g
            double penalty = _coeffs[0];
            double px = _coeffs[1];
            double py = _coeffs[2];
            double x0 = _x[0];
            double x1 = _x[1];
            _g[0] = penalty * (x0 - px);
            _g[1] = penalty * (x1 - py);
            //------------------------------------------------------//
        }

        /** evaluates the spring element's energy Hessian
         * \param _x the spring's current position
         * \param _coeffs _coeffs[0] is the penalty factor,
         *                _coeffs[1] and _coeffs[2] are the desired point coordinates
         * \param _H Hessian output */
        inline virtual void eval_hessian(const Vec &_x, const Vec &_coeffs, Mat &_H) final {
            //------------------------------------------------------//
            //Todo: implement the hessian matrix and store in _H
            double penalty = _coeffs[0];
            _H(0, 0) = penalty;
            _H(0, 1) = 0;
            _H(1, 0) = 0;
            _H(1, 1) = penalty;
            //------------------------------------------------------//
        }
    };

    //=============================================================================
}





