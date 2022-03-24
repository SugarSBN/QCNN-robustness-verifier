/*
 * @Author: SuBonan
 * @Date: 2022-03-17 11:49:14
 * @LastEditTime: 2022-03-24 10:21:11
 * @FilePath: \QCNN-robustness-verifier\src\verifier.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/verifier.h"
#include<ctime>
#include<cstdio>

Verifier :: Verifier(Circuit nc, PureState nq, int nnqubits){
    c = nc;
    q = nq;
    nq.apply_circuit(c);
    predict = nq.predict();
    nqubits = nnqubits;
    poly_param = 1.5;
}

void Verifier :: work(){
    poly = Polygon(q, nqubits, c, poly_param);
    vector<bool> veri_res = poly.verify(predict);
    bool not_verified = 0;
    for (int i = 0;i < veri_res.size();i++) if (veri_res[i] == 0)   not_verified = 1;
    while(not_verified){
        poly_param -= 0.05;
        poly = Polygon(q, nqubits, c, poly_param);
        vector<bool> veri_res = poly.verify(predict);
        not_verified = 0;
        for (int i = 0;i < veri_res.size();i++) if (veri_res[i] == 0)   not_verified = 1;
    }
    robust_bound = poly.robust_bound();
}

double Verifier :: get_robust_bound() const{
    return robust_bound;
}

bool Verifier :: random_sampling_check(int samples) const{
    srand((int) time (NULL));
    PureState nq = q;
    
    printf("Robust bound: %.4lf\n", robust_bound);
    if (robust_bound <= 0)  return 1;
    for (int t = 0;t < samples;t++){

        double phi = (double)rand() / (double)RAND_MAX * 7;
        int tg = rand() % nqubits;
        int gate = rand() % 3;
        double distance;
        Gate g = gate == 0 ? RX : (gate == 1 ? RY : RZ);
        nq.apply_operator(Operator(g, tg, vector<int>{}, phi));
        distance = 1 - q.fidelity(nq);

        while(1 - q.fidelity(nq) > robust_bound || distance < (robust_bound - 0.01)){

            phi = (double)rand() / (double)RAND_MAX * 7;
            tg = rand() % nqubits;
            gate = rand() % 3;
            g = gate == 0 ? RX : (gate == 1 ? RY : RZ);
            nq = PureState(q);
            nq.apply_operator(Operator(g, tg, vector<int>{}, phi));
            distance = 1 - q.fidelity(nq);
        }
        nq.apply_circuit(c);
        if (predict != nq.predict())
            return 0;
            //printf("sample %d: Distance = %.4lf CENTER = %d\n SAMPLE = %d\n", t, distance, predict, nq.predict());
        //else printf("sample %d: Distance = %.4lf CENTER = SAMPLE = %d\n", t, distance, predict);
    }
    return 1;
}