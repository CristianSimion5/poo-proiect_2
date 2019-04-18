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
    int height_max() {
        if (st == NULL && dr == NULL)
            return 0;
        if (st == NULL)
            return 1 + dr -> height_max();
        if (dr == NULL)
            return 1 + st -> height_max();
        int a = st -> height_max(), b = dr -> height_max();
        if (a < b)
            a = b;
        return 1 + a;
    }
    void afis_recursiv(ostream &os) {
        if (st == NULL && dr == NULL) {
            os << info << ' ';
            return;
        }
        if (st != NULL)
            st -> afis_recursiv(os);
        if (dr != NULL)
            dr -> afis_recursiv(os);
    }
    bool compara_recursiv(nod<T>* node) {
        if (this == NULL && node == NULL)
            return true;
        if ((this == NULL && node != NULL) || (this != NULL && node == NULL))
            return false;
        if (this -> info == node -> info)
            return (st -> compara_recursiv(node -> st) && dr -> compara_recursiv(node -> dr));
        return false;
    }
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
    virtual void afis_frunze(ostream& os) {};

    int size() { return nr_noduri; };
    bool empty() { if (nr_noduri > 0) return false; return true; };
};

