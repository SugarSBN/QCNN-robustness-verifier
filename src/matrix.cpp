/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:56:23
 * @LastEditTime: 2022-03-05 16:11:32
 * @FilePath: \QCNN-robustness-verifier\src\matrix.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */

#include"../headers/matrix.h"
vector<Complex> Matrix :: operator [] (int n){
    return v[n];
}

void Matrix :: print() const{
    for (int i = 0;i < w;i++){
        for (int j = 0;j < h;j++)
            cout << v[i][j] << " ";
        cout << endl;                
    }
}

Matrix :: Matrix(int nh, int nw){
    w = nw; h = nh;
    v.clear();  
    for (int i = 0;i < nh;i++)  {
        v.push_back(vector<Complex>{});
        v[i].resize(nw);
    }
}
Matrix :: Matrix(Gate G, double alpha) {
    Matrix(2, 2);
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

Matrix Matrix :: dagger() const{
    Matrix res = Matrix(w, h);
    for (int i = 0;i < res.h;i++)
        for (int j = 0;j < res.w;j++)
            res.set_value(i, j, v[j][i].dagger());
    return res;
}

Matrix operator * (Matrix A, Matrix B){
    Matrix res = Matrix(A.h, B.w);
    for (int i = 0;i < A.h;i++)
        for (int j = 0;j < B.w;j++)
            for (int k = 0;k < A.w;k++)
                res.set_value(i, j, res[i][j] + (A[i][k] * B[k][j]));
    return res;
}

Matrix operator * (double p, Matrix B){
    Matrix res = Matrix(B.h, B.w);
    for (int i = 0;i < B.h;i++)
        for (int j = 0;j < B.w;j++)
            res.set_value(i, j, B[i][j] * Complex(p, 0));
    return res;
}

Matrix operator + (Matrix A, Matrix B){
    Matrix res = Matrix(A.h, B.w);
    for (int i = 0;i < A.h;i++)
        for (int j = 0;j < B.w;j++)
            res.set_value(i, j, A[i][j] + B[i][j]);
    return res;
}

ostream & operator << (ostream &os, Matrix A){
    for (int i = 0;i < A.h;i++){
        os << "| ";
        for (int j = 0;j < A.w;j++) os << A[i][j] << " ";
        os << "|" << endl;
    }    
    return os;
}

void Matrix :: set_value(int i, int j, Complex c){
    v[i][j] = c;
}
