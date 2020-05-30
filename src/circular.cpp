#include "circular.h"

/* A circular buffer with fixed capacity
 * This data structure turns out to be a perfect fit for our use-case:
 * in both graphs, we need a moving constant-length range of states displayed,
 * and we care little about the order.
 */

Circular::Circular (int capacity) {
    capa = capacity ;
    tab = new QVector<double> ;
    len = 0 ;
    idx = -1 ;
}

Circular::~Circular () {
    delete tab ;
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
        dir[i] = (*tab)[(idx+i+capa-len+1) % capa] ;
    }
    return dir ;
}
