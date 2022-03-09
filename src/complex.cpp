/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:47:38
 * @LastEditTime: 2022-03-07 16:32:33
 * @FilePath: \QCNN-robustness-verifier\src\complex.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/complex.h"
#include <iomanip>

Complex :: Complex(double nreal, double nimage){
    real = nreal; image = nimage;
}

double Complex :: get_real() const {return real;}
        
double Complex :: get_image() const {return image;}

Complex operator * (const Complex &A, const Complex &B){
    double nreal = A.real * B.real - A.image * B.image;
    double nimage = A.real * B.image + A.image * B.real;
    return Complex(nreal, nimage);
}

Complex operator + (const Complex &A, const Complex &B){
    return Complex(A.real + B.real, A.image + B.image);
}

Complex operator - (const Complex &A, const Complex &B){
    return Complex(A.real - B.real, A.image - B.image);
}

ostream & operator << (ostream &os, const Complex &A){
    os << "(" << setw(5) << A.real << " + " << setw(5) << A.image << "i)";
    return os;
}

bool operator < (const Complex &A, const Complex &B){
    return A.norm() > B.norm();
}

double Complex :: norm() const{
    return sqrt(real * real + image * image);
}

Complex Complex :: dagger() const{
    return Complex(real, -image);
}