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

template <typename T>
class nod_rn {
public:
    T info;
    char culoare;
    nod_rn<T> *st, *dr, *pr;

    nod_rn(T data = 0, char c = 'r'): info(data), culoare(c), st(NULL), dr(NULL), pr(NULL) {};
    void inordine(ostream& os) {
        if (this == NULL)
            return;
        st -> inordine(os);
        os << culoare << ' ';
        dr -> inordine(os);
    };


    nod_rn<T>* unchi() {
        nod_rn<T>* p = this -> pr, *g = p -> pr;
        if (g == NULL)
            return NULL;
        if (g -> st == p)
            return g -> dr;
        return g -> st;
    }

    char get_culoare() { return culoare; };
    void rotatie_st() {
        nod_rn<T>* nou = this -> dr, *p = this -> pr;
        if (nou == NULL)
            return;
        this -> dr = nou -> st;
        nou -> st = this;
        this -> pr = nou;

        if (this -> dr != NULL)
            this -> dr -> pr = this;
        if (p != NULL) {
            if (this == p -> st)
                p -> st = nou;
            else if (this == p -> dr)
                p -> dr = nou;
        }
        nou -> pr = p;
    };
    void rotatie_dr() {
        nod_rn<T>* nou = this -> st, *p = this -> pr;
        if (nou == NULL)
            return;
        this -> st = nou -> dr;
        nou -> dr = this;
        this -> pr = nou;

        if (this -> st != NULL)
            this -> st -> pr = this;
        if (p != NULL) {
            if (this == p -> st)
                p -> st = nou;
            else if (this == p -> dr)
                p -> dr = nou;
        }
        nou -> pr = p;
    }

    void reparare_arbore(nod_rn<T>* current) {
        // reparam arborele
        if (current -> pr == NULL) {
            current -> culoare = 'n';
            return;
        }
        if (current -> pr -> culoare == 'n')
            return;
        nod_rn<T>* u = current -> unchi(); 
        if (u != NULL && u -> culoare == 'r') {
            current -> pr -> culoare = 'n';
            u -> culoare = 'n';
            current -> pr -> pr -> culoare = 'r';
            this -> reparare_arbore(current -> pr -> pr);
        }
        else {
            nod_rn<T>* p = current -> pr, *g = current -> pr -> pr;
            if (current == p -> dr && p == g -> st) {
                p -> rotatie_st();
                current = current -> st;
            }
            else if (current == p -> st && p == g -> dr) {
                p -> rotatie_dr();
                current = current -> dr;
            }

            p = current -> pr;
            g = p -> pr;
            // nodul curent este in exteriorul subarborelui
            if (current == p -> st)
                g -> rotatie_dr();
            else
                g -> rotatie_st();
            p -> culoare = 'n';
            g -> culoare = 'r';
        }
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
    //virtual void stergere(T data, Compare comp) = 0;
    //virtual T get_rad() = 0;
    //virtual int inaltime() = 0;
    //virtual void afis_frunze(ostream& os) = 0;

    int size() { return nr_noduri; };
    bool empty() { if (nr_noduri > 0) return false; return true; };
};

