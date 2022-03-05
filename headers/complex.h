/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:47:02
 * @LastEditTime: 2022-03-05 08:54:57
 * @FilePath: \QCNN\headers\complex.h
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
        double real, image;
    public:
        Complex(){}
        Complex(double nreal, double nimage);

        double get_real() const;

        double get_image() const;
        
        friend Complex operator * (const Complex &A, const Complex &B);

        friend Complex operator + (const Complex &A, const Complex &B);

        friend ostream & operator << (ostream &os, const Complex &A);

        friend bool operator < (const Complex &A, const Complex &B);

        double norm() const;
};

#endif