/*
 * @Author: SuBonan
 * @Date: 2022-03-09 18:30:59
 * @LastEditTime: 2022-03-23 11:41:39
 * @FilePath: \QCNN-robustness-verifier\headers\polygon.h
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#ifndef _POLYGON_H
#define _POLYGON_H
#include"purestate.h"
#include"circuit.h"
class Polygon{
    private:
        vector<PureState> points;
        PureState center_state;
        Circuit c;
        int nqubits;

        double cal(int i, int j) const;

    public:
        Polygon(PureState center, int nnqubits, Circuit nc, double eps = 0.3);   
        
        Polygon(){}
        
        vector<bool> verify(int ans);

        double robust_bound() const;
};

#endif
