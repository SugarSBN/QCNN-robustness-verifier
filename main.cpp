/*
 * @Author: SuBonan
 * @Date: 2022-03-05 15:31:08
 * @LastEditTime: 2022-03-09 19:26:59
 * @FilePath: \QCNN-robustness-verifier\main.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */

#include"./headers/circuit.h"
#include"./headers/purestate.h"
#include"./headers/state.h"
#include"./headers/polygon.h"
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
    Circuit c = Circuit(8);
    PureState q = PureState(8, images[0]);

//    Polygon p = Polygon(q, 8, c, 1.0);
    Polygon p = Polygon(q, 8, c, 1.3);
//    Polygon p = Polygon(q, 8, c, 1.5);  // 1 0 0 1
//    Polygon p = Polygon(q, 8, c, 2.0);
    
    q.apply_circuit(c);
    int cls = q.predict();
    vector<bool> ans = p.verify(cls);
    for (int i = 0;i < ans.size();i++)  cout << ans[i] << endl;
    return 0;
}
