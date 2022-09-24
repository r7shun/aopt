# aopt exercise0

1. Implementing objective functions 
1.1 Quadratic function
1.1.1 2D
    - eval_f pretty straight forward, extract x=_x(0) and y=_x(1) from Eigen::VectorXd Vec, and use pow(x,2)
    - csv export command: ./Build/bin/CsvExporter quad2d.csv 1 -10 -10 10 10 20 20
    - generated plot: quad2d.png (inside aopt-exercise0/)
1.1.2 ND
    -  mismatched types ‘const Eigen::MatrixBase<Derived>’ and ‘double’
         return (0.5*((_x.transpose()*A_*_x)) + b_.transpose()*_x + c_);
        - solution: static_cast<double>

1.2 non-convex function
    - easy implement
    - run  ./Build/bin/CsvExporter nonconvex.csv 0 -2 -2 2 2 100 100 
    - generate nonconvex.png as in pdf

2. Grid Search
2.1 2D
    - use nested for loop to iterate over whole Grid
2.2 ND
    - recursive approach to iterate over n dim functions (the idea is that the level of nested for loop is dynamic n)
    - start from dim n-1 to 0 