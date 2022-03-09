/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:06:56
 * @LastEditTime: 2022-03-07 18:47:44
 * @FilePath: \QCNN-robustness-verifier\src\state.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/state.h"
#include<cmath>

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
    vector<Matrix> basis0 = vector<Matrix>{Matrix(I), Matrix(X), Matrix(Y), Matrix(Z)};
    vector<Matrix> basis = vector<Matrix>{Matrix(I), Matrix(X), Matrix(Y), Matrix(Z)};
    for (int qbits = 1;qbits < nqubits;qbits++){
        for (int i = 0;i < basis0.size();i++)
            for (int j = 0;j < (1 << qbits) * (1 << qbits);j++)
                basis.push_back(basis0[i] ^ basis[j]);
        for (int i = 0;i < (1 << qbits) * (1 << qbits);i++)
            basis.erase(basis.begin());
    } 
    basis.erase(basis.begin());
    // normalization
    for (int i = 0;i < basis.size();i++)    basis[i] = sqrt((1 << nqubits) - 1) * basis[i];
    Matrix res = Matrix(basis.size(), 1);
    Matrix p = density_operator();
    for (int i = 0;i < basis.size();i++){
        Complex tmp = Complex((1 << nqubits), 0) * (p * basis[i]).trace() - basis[i].trace();
        res.set_value(i, 0, Complex(tmp.get_real() / ((1 << nqubits) * (1 << nqubits) - (1 << nqubits)), 0));
    }
    return res;
}


double State :: fidelity(State q) const{
    
}