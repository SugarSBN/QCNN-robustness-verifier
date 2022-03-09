/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:47:02
 * @LastEditTime: 2022-03-07 16:32:16
 * @FilePath: \QCNN-robustness-verifier\headers\complex.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _COMPLEX_H
#define _COMPLEX_H

#include<iostream>
#include<cmath>
using namespace std;

class Complex{
    private:
        double real = 0, image = 0;
        
    public:
        Complex(){}
        Complex(double nreal, double nimage);

        double get_real() const;

        double get_image() const;
        
        friend Complex operator * (const Complex &A, const Complex &B);

        friend Complex operator + (const Complex &A, const Complex &B);

        friend Complex operator - (const Complex &A, const Complex &B);

        friend ostream & operator << (ostream &os, const Complex &A);

        friend bool operator < (const Complex &A, const Complex &B);

        double norm() const;

        Complex dagger() const;
};

#endif