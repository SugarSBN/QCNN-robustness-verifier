/*
 * @Author: SuBonan
 * @Date: 2022-03-17 11:48:46
 * @LastEditTime: 2022-03-23 15:14:44
 * @FilePath: \QCNN-robustness-verifier\headers\verifier.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _VERIFIER_H
#define _VERIFIER_H

#include"circuit.h"
#include"polygon.h"

class Verifier{
    private:
        int nqubits;
        Circuit c;
        PureState q;
        int predict;
        Polygon poly;
        double poly_param;
        double robust_bound;
    public:
        Verifier(Circuit nc, PureState nq, int nnqubits);

        void work();

        double get_robust_bound() const;

        bool random_sampling_check(int samples = 10) const;
};

#endif
