#include <Utils/OptimalityChecker.hh>
#include <Functions/FunctionQuadraticND.hh>
#include <vector>
#include <iostream>


int main(int _argc, const char* _argv[]) {
    AOPT::FunctionQuadraticND::Mat A(2, 2);
    A.setZero();
    AOPT::FunctionQuadraticND::Vec b(2);
    b.setZero();

    //-------------------------------------------------------------------------------//
    //Todo: set up the optimization problem by populating the various
    //matrices and vectors coefficients
    //1. set objective function
    A << 2, 0,
         0, -4;
    b << 0, 0;
    AOPT::FunctionQuadraticND obj_func(A, b, 0);

    //2. inequality constraints
    std::vector<AOPT::FunctionBase*> ineq_cons;
    A << 2, 0,
              0, 0;
    b<< 8, -1;
    ineq_cons.push_back(new AOPT::FunctionQuadraticND(A, b, 14));

    A.setZero();
    b << -1, 0;
    ineq_cons.push_back(new AOPT::FunctionQuadraticND(A, b, -10));

    //3. equality constraints
    std::vector<AOPT::FunctionBase*> eq_cons;
    A.setZero();
    b << 1, -1;

    eq_cons.push_back(new AOPT::FunctionQuadraticND(A, b, 4));


    //4. set lambdas and vs
   AOPT::FunctionQuadraticND::Vec lambda(2);
    lambda << 4, 0;

    AOPT::FunctionQuadraticND::Vec nu(1);
    nu << -12;

    //5. set query point
    AOPT::OptimalityChecker::Vec x(2);
    x << -2, 2;
    //-------------------------------------------------------------------------------//

    //TODO: uncomment this to test your implementation
    //NOTE: you can change the variables name if you want
    //check
    
    AOPT::OptimalityChecker oc;
    if(oc.is_KKT_satisfied(&obj_func, ineq_cons, eq_cons, x, lambda, nu))
        std::cout<<"\nThe query point satisfies the KKT condition."<<std::endl;
    else
        std::cout<<"\nThe query point does NOT satisfy the KKT condition."<<std::endl;
    
    return 0;
}

