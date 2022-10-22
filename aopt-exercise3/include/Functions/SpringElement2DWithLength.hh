#pragma once

#include <FunctionBase/ParametricFunctionBase.hh>

//== NAMESPACES ===============================================================

namespace AOPT {


//== CLASS DEFINITION =========================================================

/* This class evaluates the energy with a spring with length.
 * It is very similar to the SpringElement2D except it has an addition parameter
 * l_ab which represents the length of the spring at rest. */
    class SpringElement2DWithLength : public ParametricFunctionBase {
    public:
        // E'_ab(x) = 1/2 * k * (((x[0] - x[2])^2 + (x[1] - x[3])^2) - l^2)^2
        // constructor
        SpringElement2DWithLength() : ParametricFunctionBase() {}

        // number of unknowns
        inline virtual int n_unknowns() override { return 4; }

        /** evaluates the spring element's energy
         * \param _x contains x_a and x_b contiguously,
         *           i.e. _x = [x_a, x_b], i.e. _x is of dimension 4
         * \param _coeffs stores the constants k and l,
         *                i.e. _coeffs[0] = k, _coeffs[1] = l */
        inline virtual double eval_f(const Vec &_x, const Vec &_coeffs) override {
            //------------------------------------------------------//
            //Todo: implement the function f(x) = 1/2 * k * (((x[0] - x[2])^2 + (x[1] - x[3])^2) - l^2)^2
            return 0.5 * _coeffs[0] * std::pow((std::pow(_x[0] - _x[2], 2) + std::pow(_x[1] - _x[3], 2)) - std::pow(_coeffs[1], 2),2);
            //------------------------------------------------------//
        }


        /** evaluates the spring element's energy gradient
         * \param _x contains x_a and x_b contiguously,
         *           i.e. _x = [x_a, x_b], i.e. _x is of dimension 4
         * \param _coeffs stores the constants k and l,
         *                i.e. _coeffs[0] = k, _coeffs[1] = l
         * \param _g the output gradient, which should also be of dimension 4 */
        inline virtual void eval_gradient(const Vec &_x, const Vec &_coeffs, Vec &_g) override {
            //------------------------------------------------------//
            //Todo: implement the gradient and store in _g
            const double common = 2 * _coeffs[0] * ((std::pow(_x[0] - _x[2], 2) + std::pow(_x[1] - _x[3], 2)) - std::pow(_coeffs[1], 2));
            _g << common*(_x[0]-_x[2]), common*(_x[1]-_x[3]), common*(_x[2]-_x[0]), common*(_x[3]-_x[1]);
                    
            //------------------------------------------------------//
        }

        /** evaluates the spring element's energy Hessian
         * \param _x contains x_a and x_b contiguously,
         *           i.e. _x = [x_a, x_b], i.e. _x is of dimension 4
         * \param _coeffs stores the constants k and l,
         *                i.e. _coeffs[0] = k, _coeffs[1] = l
         * \param _H the output Hessian, which should be a 4x4 Matrix */
        inline virtual void eval_hessian(const Vec &_x, const Vec &_coeffs, Mat &_H) override {
            //------------------------------------------------------//
            //Todo: implement the hessian matrix and store in _H
            // ax=x0, ay=x1, bx=x2, by=x3
            const double common = 2 * _coeffs[0] * ((std::pow(_x[0] - _x[2], 2) + std::pow(_x[1] - _x[3], 2)) - std::pow(_coeffs[1], 2));
            const double daxax = common + 4 * _coeffs[0] * std::pow(_x[0]-_x[2],2); // same -dbxax, dbxbx
            const double daxay = 4*_coeffs[0] * (_x[0]-_x[2]) * (_x[1]-_x[3]); // same as dayax, -daybx, -dbxay, dbxby, -dbyax, dbybx
            const double dayay = common + 4 * _coeffs[0] * std::pow(_x[1]-_x[3],2); // same as -dbyay, dbyby

            _H <<    daxax,  daxay, -daxax, -daxay,
                     daxay,  dayay, -daxay, -dayay,
                    -daxax, -daxay,  daxax,  daxay,
                    -daxay, -dayay,  daxay,  dayay;

            //------------------------------------------------------//
        }
    };

//=============================================================================
}


