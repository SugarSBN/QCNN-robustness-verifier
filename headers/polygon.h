/*
 * @Author: SuBonan
 * @Date: 2022-03-09 18:30:59
 * @LastEditTime: 2022-03-09 19:23:07
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
    public:
        Polygon(PureState center, int nnqubits, Circuit nc, double eps = 0.3);   
        
        vector<bool> verify(int ans);
};

#endif
