/*
 * @Author: SuBonan
 * @Date: 2022-03-05 08:55:36
 * @LastEditTime: 2022-03-05 08:58:29
 * @FilePath: \QCNN\headers\matrix.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _MATRIX_H
#define _MATRIX_H
#include"../headers/complex.h"
#include"../headers/gate.h"

class Matrix{
    private:
        Complex v[2][2];
    public:
        Complex* operator [] (int n);

        void print() const;

        Matrix(){}
        Matrix(Gate G, double alpha = 0);
};

#endif