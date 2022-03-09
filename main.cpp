/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:31:08
 * @LastEditTime: 2022-03-07 18:32:34
 * @FilePath: \QCNN-robustness-verifier\main.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"./headers/circuit.h"
#include"./headers/purestate.h"
#include"./headers/state.h"
#include<iostream>
using namespace std;

int main(){
    vector<double> v;
    for (int i = 0; i < (1 << 8);i++)   v.push_back(0);
    v[0] = 1;
    State q = State(2, vector<pair<double, PureState> > {
        make_pair(1, PureState(2, vector<Complex>{Complex(0.5, 0.5), Complex(0, 0), Complex(0.5, -0.5), Complex(0, 0)})),
        });

    q.standardize();
    return 0;
}