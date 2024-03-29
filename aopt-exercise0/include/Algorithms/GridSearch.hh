#pragma once

#include <Functions/FunctionQuadratic2D.hh>
#include <Functions/FunctionQuadraticND.hh>
#include <Functions/FunctionNonConvex2D.hh>
#include <vector>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    class GridSearch {
    public:
        using Vec = FunctionBase::Vec;
        using Mat = FunctionBase::Mat;

        GridSearch(const int _n_cells = 10) : n_cells_(_n_cells){}
        ~GridSearch() {}

    public:

        /** Evaluation of a 2D function over the whole grid to find its minimum
         *
         * \param _func a pointer to any 2D function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define a square in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_2d(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            std::cout<<"Grid searching the minimum of a 2-D function..."<<std::endl;
            double f = 0., fmin = std::numeric_limits<double>::max();
            
            Vec x_min(2);
            
            //------------------------------------------------------//
            //Todo: implement the 2d version of the grid search
            // algorithm to find minimum value of _func between _x_l and _x_u
            //------------------------------------------------------//
            // iterate the 2d grid with for loop
            // convert to uniform grid for simplicity
            const Vec& step = (_x_u - _x_l) / n_cells_;
            Vec p(2); // current iterated point
            for (double xp = _x_l(0); xp <= _x_u(0); xp = xp + step(0)) {
                for (double yp = _x_l(1); yp <= _x_u(1); yp = yp + step(1)) {
                    p << xp,yp;
                    if (_func->eval_f(p) < fmin) {
                        x_min = p;
                        fmin = _func->eval_f(p);
                    }
                }
            }

            //------------------------------------------------------//
            _f_min = fmin;
            std::cout<<"Minimum value of the function is: "<<fmin<<" at x:\n"<<x_min<<std::endl;
            return 0;
        }



        /** Evaluation of an ND function over the whole grid to find its minimum
         *  using an iterative approach
         *
         * \param _func a pointer to any ND function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define an ND cuboid in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_nd(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            int n = _func->n_unknowns();
            if (_x_l.size() != n || _x_u.size() != n) {
                std::cout << "Error: input limits are not of correct dimension!" << std::endl;
                return -1;
            }
            std::cout << "Grid searching the minimum of a " << n << "-D function..." << std::endl;

            double f_min = std::numeric_limits<double>::max();
            Vec x_min(n);
            //------------------------------------------------------//
            //Todo: implement the nd version of the grid search
            // algorithm to find minimum value of a nd quadratic function
            // set f_min with the minimum, which is then stored in the referenced argument _f_min
            // recursive approach 
            double xlow = _x_l(0);
            double step = (_x_u(0) - _x_l(0)) / n_cells_;

            Vec p(n); 
            int l = n - 1; // recursive level from _x(n-1) to _x(0)
            grid_search_recursive_helper(_func, xlow, step, l, p, x_min, f_min);
            //------------------------------------------------------//
            _f_min = f_min;
            std::cout << "Minimum value of the function is: " << f_min << " at x:\n" << x_min << std::endl;

            return 0;
        }



    private:
        int n_cells_;
        int grid_search_recursive_helper(FunctionBase* _func, const double xlow, const double step, int l, Vec& p, Vec& x_min, double& f_min) const {
            // recursive to 0, evaluate f
            if (l == 0) {
                if (_func->eval_f(p) < f_min) {
                    x_min = p;
                    f_min = _func->eval_f(p);
                }
            } else {
                for (int i=0; i <= n_cells_; i++) {
                    p(l) = xlow + i * step;
                    grid_search_recursive_helper(_func, xlow, step, l-1, p, x_min, f_min);
                }
            }
            return 0;
        }
    };

    //=============================================================================
}





