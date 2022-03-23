/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:19:29
 * @LastEditTime: 2022-03-23 11:18:44
 * @FilePath: \QCNN-robustness-verifier\src\purestate.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/purestate.h"

int PureState :: size() const{
    return states.size();
}

string PureState :: toString(int n) const{
    string res = "";
    for (int i = 0;i < nqubits;i++){
        res = (n % 2 ? '1' : '0') + res;
        n /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

PureState::PureState(int nnqubits, vector<double> value){
    nqubits = nnqubits;
    states.clear();
    if (value.size() != (1 << nqubits)){
        states.push_back(make_pair(Complex(1, 0), toString(0)));
        return;
    }
    for (int i = 0;i < (1 << nqubits);i++){
        states.push_back(make_pair(Complex(value[i], 0), toString(i)));
    }
}

PureState::PureState(int nnqubits, vector<Complex> value){
    nqubits = nnqubits;
    states.clear();
    if (value.size() != (1 << nqubits)){
        states.push_back(make_pair(Complex(1, 0), toString(0)));
        return;
    }
    for (int i = 0;i < (1 << nqubits);i++){
        states.push_back(make_pair(value[i], toString(i)));
    }
}


void PureState::apply_operator(Operator G){
    vector<pair<Complex, string> > new_states;
    map<string, Complex> mapping;
    
    for (int i = 0;i < size();i++){
        string now_state = states[i].second;

        bool controlled = 1;
        for (int j = 0;j < G.controll_qubits.size();j++)  if (now_state[nqubits - G.controll_qubits[j] - 1] != '1'){
            controlled = 0;
            break;
        }
        if (!controlled){
            new_states.push_back(states[i]);
            continue;
        }

        int d[2] = {1, 0};
        if (now_state[nqubits - G.target_qubit - 1] == '1') swap(d[0], d[1]);
        Matrix m = Matrix(G.G, G.alpha);
        Complex amplitude_zero, amplitude_one;
        amplitude_zero = m[0][0] * Complex(d[0], 0) + m[0][1] * Complex(d[1], 0);
        amplitude_one = m[1][0] * Complex(d[0], 0) + m[1][1] * Complex(d[1], 0);
        now_state[nqubits - G.target_qubit - 1] = '0';

        if (!mapping.count(now_state))  mapping[now_state] = states[i].first * amplitude_zero;  
        else mapping[now_state] = mapping[now_state] + states[i].first * amplitude_zero;

        now_state[nqubits - G.target_qubit - 1] = '1';

        if (!mapping.count(now_state))  mapping[now_state] = states[i].first * amplitude_one;  
        else mapping[now_state] = mapping[now_state] + states[i].first * amplitude_one;
    }
    for (map<string, Complex>::iterator it = mapping.begin();it != mapping.end();it++)  new_states.push_back(make_pair(it -> second, it -> first));
    states = new_states;
}

void PureState::apply_circuit(Circuit c){
    auto operators = c.get_operators();
    for (int i = 0;i < operators.size();i++){
        apply_operator(operators[i]);
    }
}

double PureState :: measure() const{
    double zero, one;
    for (int i = 0;i < states.size();i++){
        double prob = states[i].first.norm() * states[i].first.norm();
        if (states[i].second[nqubits - 1] == '0') zero += prob;
        else one += prob;
    }
    return one;
}

double PureState :: robust_boundary_guan() const{
    double zero, one;
    for (int i = 0;i < states.size();i++){
        double prob = states[i].first.norm() * states[i].first.norm();
        if (states[i].second[nqubits - 1] == '0') zero += prob;
        else one += prob;
    }
    return (sqrt(zero) - sqrt(one)) * (sqrt(zero) - sqrt(one)) / 2;
}

int PureState::predict() const{
    return measure() < 0.5 ? 0 : 1;
}

int to_num(string s, int len){
    int res = 0;
    for (int i = len - 1;i >= 0;i--)    res = (res << 1) | (s[i] - '0');
    return res;
}
Matrix PureState :: to_vector() const{
    Matrix res = Matrix((1 << nqubits), 1);
    for (int i = 0;i < states.size();i++)      res.set_value(to_num(states[i].second, nqubits), 0, states[i].first);
    return res;
}

ostream & operator << (ostream &os, PureState A){
    for (int i = 0;i < A.size();i++) if (fabs(A.states[i].first.get_real()) > 1e-10 || fabs(A.states[i].first.get_image()) > 1e-10){
        os << A.states[i].first << "|" << A.states[i].second << "> " << (i == A.size() - 1 ? "" : "+\n");
    }
    return os;
};

Matrix PureState :: bloch_vector() const{
    vector<Matrix> basis0;
    basis0.push_back(Matrix(I));basis0.push_back(Matrix(X));basis0.push_back(Matrix(Y));basis0.push_back(Matrix(Z));
    queue<Matrix> basis1;
    basis1.push(Matrix(I));basis1.push(Matrix(X));basis1.push(Matrix(Y));basis1.push(Matrix(Z));
    for (int qbits = 1;qbits < nqubits;qbits++){
        for (int j = 0;j < (1 << qbits) * (1 << qbits);j++){
            Matrix bas = basis1.front(); basis1.pop();
            for (int i = 0;i < basis0.size();i++){
                basis1.push(basis0[i] ^ bas);
            }
        }
    }
    basis1.pop();
    vector<Matrix> basis;
    while(!basis1.empty()) {
        basis.push_back(basis1.front());
        basis1.pop();
    }
    cout << basis.size() << endl;
    // normalization
    for (int i = 0;i < basis.size();i++)    basis[i] = sqrt((1 << nqubits) - 1) * basis[i];
    Matrix res = Matrix(basis.size(), 1);
    Matrix p = to_vector() * to_vector().dagger();
    for (int i = 0;i < basis.size();i++){
        cout << i << " / " << basis.size() << endl;
        Complex tmp = Complex((1 << nqubits), 0) * (p * basis[i]).trace() - basis[i].trace();
        res.set_value(i, 0, Complex(tmp.get_real() / ((1 << nqubits) * (1 << nqubits) - (1 << nqubits)), 0));
    }
    return res;
}

double PureState :: fidelity(PureState q) const{
    Complex c = (to_vector().dagger() * q.to_vector())[0][0];
    return (c.dagger() * c).get_real();
}
