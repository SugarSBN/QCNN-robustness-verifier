/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:31:13
 * @LastEditTime: 2022-03-05 14:59:26
 * @FilePath: \QCNN-robustness-verifier\predict.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"./headers/circuit.h"
#include"./headers/purestate.h"

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
    fclose(stdin);
    Circuit c = Circuit(8);
    cout << "Predict:" << endl;
    for (int i = 0;i < 3;i++){
        for (int j = 0;j < 3;j++){
            PureState q = PureState(8, images[i * 3 + j]);
            q.apply_circuit(c);
            cout << q.predict() << " ";
        }
        cout<<endl;
    }
    cout << "Real Number:" << endl;
    fclose(stdin);
    freopen("labels.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0;i < 3;i++){
        for (int j = 0;j < 3;j++){
            cin >> n;
            cout << n << " ";
        }
        cout<<endl;
    }
    fclose(stdin);
}   