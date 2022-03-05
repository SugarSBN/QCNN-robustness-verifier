/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:59:44
 * @LastEditTime: 2022-03-05 09:13:56
 * @FilePath: \QCNN\headers\circuit.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _CIRCUIT_H
#define _CIRCUIT_H

#include"../headers/gate.h"

#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<vector>
using namespace std;

struct Operator{
    /*
        Quantum Operator.
        (G : Gate)                      is the corresponding quantum gate;
        (target_qubit : int)            is the qubit on which the gate applys
        (controll_qubits : vector<int>) is the controll qubits, the gate functs iff controll_qubit = ¦1⟩
        (alpha : double)                is the parameter (if the gate is a parameterized gate)
    */
    Gate G;
    int target_qubit;
    vector<int> controll_qubits;
    double alpha = 0;

    Operator(Gate nG, int nt, vector<int> nc, double nalpha = 0){
        G = nG;
        target_qubit = nt;
        controll_qubits = nc;
        alpha = nalpha;
    }
};

using namespace std;
class Circuit{
    /*
        read file from "../ansatz_circuit.txt" as the circuit
    */
    private:
        vector<Operator> operators;
        int nqubits;
    public:
        Circuit(int nnqubits);

        friend ostream & operator << (ostream &os, const Circuit &A);

        vector<Operator> get_operators() const;
};

#endif
