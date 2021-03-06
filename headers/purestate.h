/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:17:37
 * @LastEditTime: 2022-03-16 09:53:05
 * @FilePath: \QCNN-robustness-verifier\headers\purestate.h
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
#include<queue>
#include"complex.h"
#include"gate.h"
#include"matrix.h"
#include"circuit.h"

using namespace std;

class PureState{
    /*
        (states : vector<pair<Complex, string> >) is the quantum states, e.g [(1/sqrt(2), "¦0⟩"), (1/sqrt(2), "¦1⟩")]
        (nqubits : int)                           is the number of qubits of the state.
    */
    private:
        vector<pair<Complex, string> > states;
        int nqubits;
        string toString(int n) const;

    public:
        PureState(){}
        
        PureState(int nnqubits, vector<double> value);
        
        PureState(int nnqubits, vector<Complex> value);

        int size() const;

        void apply_operator(Operator G);

        void apply_circuit(Circuit c);

        Matrix bloch_vector() const;
        
        int predict() const;

        double robust_boundary_guan() const;
        
        double measure() const;

        Matrix to_vector() const;
        
        double fidelity(PureState q) const;

        friend ostream & operator << (ostream &os, PureState A);
};
#endif
