#pragma once

#include <QVector>

class Circular {
public:
    Circular (int) ;
    ~Circular () ;
    void insert (double) ;
    int length () ;
    QVector<double> extract () ;


private:
    QVector<double> * tab ;
    int idx ;
    int capa ;
    int len ;
};
