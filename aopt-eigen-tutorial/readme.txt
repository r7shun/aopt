# aopt Eigentutorial

problem: in sparse matrix part, just adding triplets.push_back(i,j,V_ij) caused Segmentation fault: 11. 
Solution: add sparseA.resize(5,5); 
