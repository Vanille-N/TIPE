#include "circular.h"

Circular::Circular (int capacity) {
    capa = capacity ;
    tab = new QVector<double> ;
    len = 0 ;
    idx = -1 ;
}

Circular::~Circular () {
    delete[] tab ;
}

int Circular::length () {
    return len ;
}

void Circular::insert (double item) {
    if (len < capa) {
        ++len ;
        tab->push_back(item) ;
        idx++ ;
    } else {
        idx = (idx+1) % capa ;
        (*tab)[idx] = item ;
    }
}

QVector<double> Circular::extract () {
    QVector<double> dir (len) ;
    for (int i = 0; i < len; i++) {
        //printf("%d\n", (idx+i-len) % capa) ;
        dir[i] = (*tab)[(idx+i+capa-len+1) % capa] ;
        //printf("i:%d  (*dir)[i]:%f  idx:%d  capa:%d  (*tab)[...]:%f\n", i, (*dir)[i]*1e10, idx, capa, (*tab)[(idx+i) % capa]*1e10) ;
    }
    return dir ;
}
