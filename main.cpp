/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:31:08
 * @LastEditTime: 2022-03-05 16:14:23
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
    PureState q0 = PureState(2, vector<double>{1, 0, 0, 0});
    PureState q1 = PureState(2, vector<double>{0.5, 0.5, 0.5, 0.5});
    State rho = State(2, vector<pair<double, PureState> >{make_pair(0.3, q0), make_pair(0.7, q1)});
    cout << rho.density_operator() << endl;
    return 0;
}