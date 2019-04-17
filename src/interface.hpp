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

    nod(T data = T()): info(data), st(NULL), dr(NULL), pr(NULL) {};
    void inordine(ostream& os) {
        if (this == NULL)
            return;
        st -> inordine(os);
        os << info << ' ';
        dr -> inordine(os);
    };
    void copie_recursiv(nod<T>* copie) {
        info = copie -> info;
        if (copie -> st != NULL) {
            st = new nod<T>;
            st -> copie_recursiv(copie -> st);
            st -> pr = this;
        }
        if (copie -> dr != NULL) {
            dr = new nod<T>;
            dr -> copie_recursiv(copie -> dr);
            dr -> pr = this;
        }
    }
};

template <typename T>
class nod_rn: public nod<T> {
public:
    char culoare;

    nod_rn(T data = 0, char c = 'r'): nod<T>(data), culoare(c) {};
};

template <typename T, typename Compare = greater<T>>
class arbore {
protected:
    int nr_noduri;
public:
    arbore(): nr_noduri(0) {};
    virtual ~arbore() {};
    virtual bool cautare(T data, Compare comp) = 0;
    virtual void inserare(T data, Compare comp) = 0;
    virtual void stergere(T data, Compare comp) = 0;
    virtual T get_rad() = 0;
    virtual int inaltime() = 0;

    int size() { return nr_noduri; };
    bool empty() { if (nr_noduri > 0) return false; return true; };
};

