/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:05:41
 * @LastEditTime: 2022-03-05 10:20:26
 * @FilePath: \QCNN\src\circuit.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/circuit.h"

string toString(Gate G){
    switch(G){
        case H:
            return "H";
        case I:
            return "I";
        case X:
            return "X";
        case Y:
            return "Y";
        case Z:
            return "Z";
        case RX:
            return "RX";
        case RY:
            return "RY";
        case RZ:
            return "RZ";
    }
    return "";
}

Circuit :: Circuit(int nnqubits){
    nqubits = nnqubits;
    freopen("ansatz_circuit.txt", "r", stdin);
    int ngates, nparams;
    cin >> nparams;
    map<string, double> params;
    for (int i = 0;i < nparams;i++){
        double num; cin >> num;
        params["beta" + to_string(i)] = num;
    }
    cin >> ngates;
    while(ngates--){
        int op;
        string name, param = "-1";
        cin >> op >> name;
        if (name != "X")    cin >> param;
        int tar, con;
        cin >> tar;
        if (op == 2)    cin >> con;
        vector<int> g;
        if (op == 2)    g.push_back(con);
        Gate G;
        if (name == "X")    G = X;
        if (name == "RX")   G = RX;
        if (name == "RY")   G = RY;
        if (name == "RZ")   G = RZ;
        operators.push_back(Operator(G, tar, g, param == "-1" ? 0 : params[param]));
    }
} 

ostream & operator << (ostream &os, const Circuit &A){
    os << "Number of Gates: " << A.operators.size() << endl;
    for (int i = 0;i < A.operators.size();i++){
        os << toString(A.operators[i].G) << " " <<A.operators[i].alpha << " " << A.operators[i].target_qubit<<" ";
        for (int j = 0;j < A.operators[i].controll_qubits.size();j++) os << A.operators[i].controll_qubits[j] << " ";
        os << endl;
    }
    return os;
}

vector<Operator> Circuit :: get_operators() const{
    return operators;
}