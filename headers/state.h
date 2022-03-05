/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:02:57
 * @LastEditTime: 2022-03-05 16:29:17
 * @FilePath: \QCNN-robustness-verifier\headers\state.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _STATE_H
#define _STATE_H
#include<vector>
#include"purestate.h"
using namespace std;
class State{
    private:
        vector<pair<double, PureState> > rho;
        int nqubits;
    public:
        State(int nnqubits, vector<pair<double, PureState> > nrho);

        void apply_operator(Operator G);

        void apply_circuit(Circuit c);

        double measure() const;
        
        int predict() const;
        
        Matrix density_operator() const;

        Matrix bloch_vector() const;
        
        friend ostream & operator << (ostream &os, PureState A);        
};
#endif
