1. QCQP to SOCP : Hamedi Zahra

2. Linear Programming : Colmenar Herrera Marta

3. Programming Exercise : Shunyu Wu
    - SpringElement2D
        - With the help of the Mass Spring System - introduction video, it's quite straight forword to calculate gradient and hessian. 
    - setup spring graph()
        - read SpringGraph.hh and understand how to add edge and vetrex
        - following the logic of the figure showed on page4 of Exercise3.pdf, draw horizontal lines 1-0, 2-1, ...,
        vertical lines 3-0, 4-1, .. the rule of the two index is that the difference is n_grid_x+1, 
        top-left to bottom-right diagal, 3-1, 4-2, ... rule: diff=n_grid_x
        top-right to bottom-left diagal, 4-0, 5-1, ... rule: diff=n_grid_x+2
        - generate _nodes.csv, _edges.csv
            - ./Build/bin/MassSpringProblemEvaluation 1 1 10 10 /Users/shunyuwu/Workspace/aopt/aopt-exercise3/
    - MassSpringProblem2D
        - for hessian, extract 2 by 2 block w.r.t pi_ix, pj_iy and fill it in global H(pi_ix, pj_iy) 2 by 2 block
