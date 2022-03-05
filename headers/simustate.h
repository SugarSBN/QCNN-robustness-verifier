/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:17:37
 * @LastEditTime: 2022-03-05 09:26:45
 * @FilePath: \QCNN\headers\simustate.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _SIMUSTATE_H
#define _SIMUSTATE_H
#include<vector>
#include<cstdio>
#include<string>
#include<algorithm>
#include<map>
#include<iostream>
#include"../headers/complex.h"
#include"../headers/gate.h"
#include"../headers/matrix.h"
#include"../headers/circuit.h"

using namespace std;

class SimuStates{
    /*
        (states : vector<pair<Complex, string> >) is the quantum states, e.g [(1/sqrt(2), "¦0⟩"), (1/sqrt(2), "¦1⟩")]
        (nqubits : int)                           is the number of qubits of the state.
    */
    private:
        vector<pair<Complex, string> > states;
        int nqubits;
        string toString(int n) const;

    public:
        SimuStates(int nnqubits, vector<double> value);

        int size() const;

        void apply_operator(Operator G);

        void apply_circuit(Circuit c);

        int predict() const;
        
        friend ostream & operator << (ostream &os, SimuStates A);
};
#endif
