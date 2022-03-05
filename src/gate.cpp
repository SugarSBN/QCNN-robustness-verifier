/*
 * @Author: SuBonan
 * @Date: 2022-03-05 09:41:42
 * @LastEditTime: 2022-03-05 09:45:00
 * @FilePath: \QCNN\src\gate.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
#include"../headers/gate.h"

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