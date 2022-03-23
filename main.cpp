/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:31:08
 * @LastEditTime: 2022-03-23 15:17:01
 * @FilePath: \QCNN-robustness-verifier\main.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */

#include"./headers/circuit.h"
#include"./headers/purestate.h"
#include"./headers/state.h"
#include"./headers/polygon.h"
#include"./headers/verifier.h"
#include<iostream>

using namespace std;

int main(){
    vector<vector<double> > images;
    freopen("images.txt", "r", stdin);
    int n, m;  cin >> n >> m;
    for (int i = 0;i < n;i++){
        vector<double> tmp;
        for (int j = 0;j < m;j++){
            double d;   cin >> d;
            tmp.push_back(d);
        }
        images.push_back(tmp);
    }
    for (int i = 0;i < 10;i++){
        Circuit c = Circuit(8);
        PureState q = PureState(8, images[i]);
        Verifier v = Verifier(c, q, 8);
        v.work();
        q.apply_circuit(c);

        printf("%d:\n", i);
        printf("Guan's robust bound: %lf\n", q.robust_boundary_guan());
        if (v.random_sampling_check(100))   printf("Verified\n");
        //cout << i << ": " << q.robust_boundary_guan() << " " << v.get_robust_bound() << endl;
    }
   
    return 0;
}
