/*
 * @Author: SuBonan
 * @Date: 2022-03-09 18:33:20
 * @LastEditTime: 2022-03-23 11:41:28
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

double Polygon :: robust_bound() const{
    double res = 0;
    for (int i = 0;i < points.size() - 1;i++)   res = max(res, cal(i, i + 1));
    res = max(res, cal(0, points.size() - 1));
    return 1 - (1 + ((1 << nqubits) - 1) * res) / (1 << nqubits);
}

double Polygon :: cal(int i, int j) const{
    double costheta1 = ((1 << nqubits) * center_state.fidelity(points[i]) - 1) / ((1 << nqubits) - 1);
    double costheta2 = ((1 << nqubits) * center_state.fidelity(points[j]) - 1) / ((1 << nqubits) - 1);

    return max(costheta1, costheta2) * sqrt(2);
}