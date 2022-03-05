/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:56:23
 * @LastEditTime: 2022-03-05 09:15:49
 * @FilePath: \QCNN\src\matrix.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */

#include"../headers/matrix.h"

Complex* Matrix :: operator [] (int n){
    return v[n];
}

void Matrix :: print() const{
    for (int i = 0;i < 2;i++){
        for (int j = 0;j < 2;j++)
            cout << v[i][j] << " ";
        cout << endl;                
    }
}

Matrix :: Matrix(Gate G, double alpha) {
    if (G == H){
        for (int i = 0;i < 2;i++)   for (int j = 0;j < 2;j++)   v[i][j] = Complex(1.0 / sqrt(2), 0);
        v[1][1] = v[1][1] * Complex(-1, 0);
    }
    if (G == I){
        v[0][0] = Complex(1, 0); v[0][1] = Complex(0, 0);
        v[1][0] = Complex(0, 0); v[1][1] = Complex(1, 0);
    }
    if (G == X){
        v[0][0] = Complex(0, 0); v[0][1] = Complex(1, 0);
        v[1][0] = Complex(1, 0); v[1][1] = Complex(0, 0);
    }
    if (G == Y){
        v[0][0] = Complex(0, 0); v[0][1] = Complex(0, -1);
        v[1][0] = Complex(0, 1); v[1][1] = Complex(0, 0);
    }
    if (G == Z){
        v[0][0] = Complex(1, 0); v[0][1] = Complex(0, 0);
        v[1][0] = Complex(0, 0); v[1][1] = Complex(-1, 0);
    }
    if (G == RX){
        v[0][0] = Complex(cos(alpha / 2), 0); v[0][1] = Complex(0, -sin(alpha / 2));
        v[1][0] = Complex(0, -sin(alpha / 2)); v[1][1] = Complex(cos(alpha / 2), 0);
    }
    if (G == RY){
        v[0][0] = Complex(cos(alpha / 2), 0); v[0][1] = Complex(-sin(alpha / 2), 0);
        v[1][0] = Complex(sin(alpha / 2), 0); v[1][1] = Complex(cos(alpha / 2), 0);
    }
    if (G == RZ){
        v[0][0] = Complex(cos(alpha / 2), -sin(alpha / 2)); v[0][1] = Complex(0, 0);
        v[1][0] = Complex(0, 0); v[1][1] = Complex(cos(alpha / 2), sin(alpha / 2));
    }
}