/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:06:56
 * @LastEditTime: 2022-03-05 16:29:27
 * @FilePath: \QCNN-robustness-verifier\src\state.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/state.h"
State :: State(int nnqubits, vector<pair<double, PureState> > nrho){
    rho = nrho;
    nqubits = nnqubits;
}

void State :: apply_operator(Operator G){
    for (int i = 0;i < rho.size();i++)  rho[i].second.apply_operator(G);
}

void State :: apply_circuit(Circuit c){
    for (int i = 0;i < rho.size();i++)  rho[i].second.apply_circuit(c);
}

double State :: measure() const{
    double one = 0;
    for (int i = 0;i < rho.size();i++)  one += rho[i].second.measure() * rho[i].first;
    return one;
}

int State :: predict() const{
    return measure() < 0.5 ? 0 : 1;
}

Matrix State :: density_operator() const{
    Matrix res = Matrix((1 << nqubits), (1 << nqubits));
    for (int i = 0;i < rho.size();i++){
        res = res + (rho[i].first * (rho[i].second.to_vector() * rho[i].second.to_vector().dagger()));
    }
    return res;
}

Matrix State :: bloch_vector() const{
    
}