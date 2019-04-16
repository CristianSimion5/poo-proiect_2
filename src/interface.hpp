// Simion Cristian

#include <iostream>
#include <functional>
#pragma once
using namespace std;


template <typename T>
class nod {
public:
    T info;
    nod<T> *st, *dr, *pr;

    nod(T data = T()): info(data) {st = NULL, dr = NULL, pr = NULL;};
};

template <typename T>
class nod_rn: public nod<T> {
public:
    char culoare;

    nod_rn(T data = 0, char c = 'r'): nod<T>(data), culoare(c) {};
};

template <typename T, typename Compare = greater<T>>
class arbore {
public:
    int nr_noduri;

    arbore(): nr_noduri(0) {};
    virtual bool cautare(T data, Compare comp) = 0;
    virtual void inserare(T data, Compare comp) = 0;
   // virtual void stergere(T data, Compare comp) = 0;
    //virtual int inaltime() = 0;
};

template <typename T, typename Compare = greater<T>>
class abc: public arbore<T, Compare> {
private:
    nod<T> *rad;

public:
    abc(): arbore<T, Compare>() { rad = NULL; };
    bool cautare(T data, Compare comp = Compare());
    void inserare(T data, Compare comp = Compare());

    friend ostream& operator<<(ostream& os, abc<T, Compare> &arb) {
        abc<T, Compare> sub;
        sub.rad = arb.rad -> st;
        if (sub.rad != NULL)
            os << sub;
        os << arb.rad -> info << ' ';
        sub.rad = arb.rad -> dr;
        if (sub.rad != NULL)
            os << sub;
        return os;
    }
};

template <typename T, typename Compare>
bool abc<T, Compare>::cautare(T data, Compare comp) {
    nod<T>* p = rad;
    while (p != NULL && p->info != data) {
        if (comp(p -> info, data))
            p = p -> st;
        else
            p = p -> dr;
    }
    if (p == NULL)
        return false;
    return true;
}

template <typename T, typename Compare>
void abc<T, Compare>::inserare(T data, Compare comp) {
    if (rad == NULL) {
        rad = new nod<T>(data);
        return;
    }
    if (cautare(data))
        return;
    nod<T>* p = rad, *q = new nod<T>(data);
    this -> nr_noduri++;
    while (p->info != data) {
        if (comp(p -> info, data))
            if (p -> st == NULL) {
                p -> st = q;
                q -> pr = p;
                break;
            }
            else
                p = p -> st;
        else
            if (p -> dr == NULL) {
                p -> dr = q;
                q -> pr = p;
                break;
            }
            else
             p = p -> dr;
    }
}
