/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:55:36
 * @LastEditTime: 2022-03-16 08:41:59
 * @FilePath: \QCNN-robustness-verifier\headers\matrix.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _MATRIX_H
#define _MATRIX_H
#include<vector>
#include"complex.h"
#include"gate.h"
using namespace std;
class Matrix{
    private:
        vector<vector<Complex> > v;
    public:
        int w, h;
        
        vector<Complex> operator [] (int n);

        void print() const;

        void set_value(int i, int j, Complex c);

        Matrix(){}
        
        Matrix(int nh, int nw);

        Matrix(Gate G, double alpha = 0);

        Matrix dagger() const;

        Complex trace() const;

        friend Matrix operator * (Matrix A, Matrix B);

        friend Matrix operator * (double p, Matrix B);

        friend Matrix operator + (Matrix A, Matrix B);

        friend Matrix operator ^ (Matrix A, Matrix B);      // tensor product

        friend ostream & operator << (ostream &os, Matrix A);
};

#endif