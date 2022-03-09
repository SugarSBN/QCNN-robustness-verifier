/*
 * @Author: SuBonan
 * @Date: 2022-03-09 18:33:20
 * @LastEditTime: 2022-03-09 19:23:18
 * @FilePath: \QCNN-robustness-verifier\src\polygon.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/polygon.h"

Polygon :: Polygon(PureState center, int nnqubits, Circuit nc, double eps){
    points.clear();
    nqubits = nnqubits;
    c = nc;

    center_state = center;
    center.apply_operator(Operator(RY, 0, vector<int>{}, eps));
    points.push_back(center);
    
    center = center_state;
    center.apply_operator(Operator(RY, 1, vector<int>{}, eps));
    points.push_back(center);
    
    center = center_state;
    center.apply_operator(Operator(RY, 0, vector<int>{}, -eps));
    points.push_back(center);

    center = center_state;
    center.apply_operator(Operator(RY, 1, vector<int>{}, -eps));
    points.push_back(center);
}

vector<bool> Polygon :: verify(int ans){
    PureState tmp;
    vector<bool> res;
    for (int i = 0;i < points.size();i++){
        tmp = points[i];
        tmp.apply_circuit(c);
        res.push_back(tmp.predict() == ans);
    }
    return res;
}