# aopt exercise0

1. Implementing objective functions 
1.1 Quadratic function
1.1.1 2D
    - eval_f pretty straight forward, extract x=_x(0) and y=_x(1) from Eigen::VectorXd Vec, and use pow(x,2)
    - csv export command: ./Build/bin/CsvExporter quad2d.csv 1 -10 -10 10 10 20 20
    - generated plot: quad2d.png