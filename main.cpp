/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:31:13
 * @LastEditTime: 2022-03-05 10:01:52
 * @FilePath: \QCNN\main.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"./headers/circuit.h"
#include"./headers/simustate.h"

int main(){
    vector<vector<double> > images;
    freopen("images.txt", "r", stdin);
    int n, m;  cin >> n >> m;
    for (int i = 0;i < n;i++){
        vector<double> rua;
        for (int j = 0;j < m;j++){
            double d;   cin >> d;
            rua.push_back(d);
        }
        images.push_back(rua);
    }
    fclose(stdin);
    Circuit c = Circuit(8);
    cout << "Predict:" << endl;
    for (int i = 0;i < 3;i++){
        for (int j = 0;j < 3;j++){
            SimuStates a = SimuStates(8, images[i * 3 + j]);
            a.apply_circuit(c);
            cout << a.predict() << " ";
        }
        cout<<endl;
    }
    cout << "Real Number:" << endl;
    fclose(stdin);
    freopen("labels.txt", "r", stdin);
    int a;  cin >> a; cin >> a;
    for (int i = 0;i < 3;i++){
        for (int j = 0;j < 3;j++){
            cin >> a;
            cout << a << " ";
        }
        cout<<endl;
    }
    fclose(stdin);
}   