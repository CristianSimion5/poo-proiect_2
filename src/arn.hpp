// Simion Cristian

#include <iostream>
#include <functional>
#pragma once
using namespace std;

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
        os << info << ' ' << culoare << '\n';
        dr -> inordine(os);
    };
    void copie_recursiv(nod_rn<T>* copie) {
        info = copie -> info;
        culoare = copie -> culoare;
        if (copie -> st != NULL) {
            st = new nod_rn<T>;
            st -> copie_recursiv(copie -> st);
            st -> pr = this;
        }
        if (copie -> dr != NULL) {
            dr = new nod_rn<T>;
            dr -> copie_recursiv(copie -> dr);
            dr -> pr = this;
        }
    }


    nod_rn<T>* frate() {
        nod_rn<T> *p = this -> pr;
        if (p == NULL)
            return NULL;
        if (p -> st == this)
            return p -> dr;
        return p -> st;
    }
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
    };
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
    };
};

template <typename T, typename Compare = greater<T>>
class arn: public arbore<T, Compare> {
private:
    nod_rn<T> *rad;

public:
    arn(): arbore<T, Compare>() { rad = NULL; };
    arn(const arn& arb);
    ~arn() {
        delete_recursiv(rad);
    };

    void delete_recursiv(nod_rn<T>* node);
    bool cautare(T data, Compare comp = Compare());
    void inserare(T data, Compare comp = Compare());
    void stergere(T data, Compare comp = Compare());
    T get_rad() { return rad -> info; };
    int inaltime() { 
        if (rad == NULL)
            return 0;
        nod_rn<T> *p = rad;
        int negre = 0;
        if (p -> culoare == 'n')
            negre++;
        while (p -> st != NULL) {
            p = p -> st;
            if (p -> culoare == 'n')
                negre++;
        }
        return negre;
    }

    arn<T, Compare>& operator=(const arn<T, Compare>& arb);

    friend ostream& operator<<(ostream& os, arn<T, Compare>& arb) {
        arb.rad -> inordine(os);
        return os;
    }
    friend istream& operator>>(istream& is, arn<T, Compare>& arb) {
        T x;
        is >> x;
        arb.inserare(x);
        return is;
    }
};

// constructor de copiere
template <typename T, typename Compare>
arn<T, Compare>::arn(const arn<T, Compare>& arb): arbore<T, Compare>(arb) {
    rad = new nod_rn<T>;
    rad -> copie_recursiv(arb.rad);
}

// destructor
template <typename T, typename Compare>
void arn<T, Compare>::delete_recursiv(nod_rn<T>* node) {
    if (node != NULL) {
            delete_recursiv(node -> st);
            delete_recursiv(node -> dr);
            delete node;
        }
}

template <typename T, typename Compare>
arn<T, Compare>& arn<T, Compare>::operator=(const arn<T, Compare>& arb) {
    if (this == &arb)
        return *this;
    delete_recursiv(rad);
    this -> nr_noduri = arb.nr_noduri;
    rad = new nod_rn<T>;
    rad -> copie_recursiv(arb.rad);
    return *this;
}

template <typename T, typename Compare>
bool arn<T, Compare>::cautare(T data, Compare comp) {
    nod_rn<T>* p = rad;
    while (p != NULL && p->info != data) {
        if (comp(p -> info, data))
            p = p -> st;
        else
            p = p -> dr;
    }
    if (p == NULL)
        return false;
    cout << p -> culoare << '\n';
    return true;
}

template <typename T, typename Compare>
void arn<T, Compare>::inserare(T data, Compare comp) {
    if (rad == NULL) {
        rad = new nod_rn<T>(data);
        this -> nr_noduri++;
        rad -> culoare = 'n';
        return;
    }
    if (cautare(data))
        return;
    nod_rn<T>* p = rad, *q = new nod_rn<T>(data);
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
    q -> reparare_arbore(q);
    rad = q;
    while (rad -> pr != NULL)
        rad = rad -> pr;
}

template <typename T, typename Compare>
void arn<T, Compare>::stergere(T data, Compare comp) {
    /*if (!cautare(data))
        return;
    this -> nr_noduri--;
    nod_rn<T>* p = rad, *u;
    bool stanga = false;
    while (p->info != data) {
        if (comp(p -> info, data)) {
            p = p -> st;
            stanga = true;
        }
        else {
            p = p -> dr;
            stanga = false;
        }
    }
    if (p -> st == NULL && p -> dr == NULL) {
        if (data == rad -> info) {
            rad = NULL;
        }
        else if (stanga)
            p -> pr -> st = NULL;
        else
            p -> pr -> dr = NULL;
        u = NULL;
    }
    else if (p -> st == NULL) {
        if (data != rad -> info) {
            if (stanga)
                p -> pr -> st = p -> dr;
            else
                p -> pr -> dr = p -> dr;
        }
        else 
            rad = p -> dr;
        p -> dr -> pr = p -> pr;
        u = p -> dr;
    }
    else if (p -> dr == NULL) {
        if (data != rad -> info) {
            if (stanga)
                p -> pr -> st = p -> st;
            else
                p -> pr -> dr = p -> st;
        }
        else
            rad = p -> st;
        p -> st -> pr = p -> pr;
        u = p -> st;
    }
    else {
        nod_rn<T>* q = p -> st;
        if (q -> dr == NULL) {
            q -> dr = p -> dr;
            q -> pr = p -> pr;
            if (q -> dr != NULL)
                q -> dr -> pr = q;
            if (data == rad -> info) {
                rad = q;
            }
            else if (stanga)
                q -> pr -> st = q;
            else
                q -> pr -> dr = q;
            u = q;
        }
        else {
            while (q -> dr != NULL) {
                q = q -> dr;
            }

            // daca fiul stang exista, ii facem parintele tatal lui q
            if (q -> st != NULL)
                q -> st -> pr = q -> pr;
            // noul fiu drept(stang) al tatalui lui q este fiul stang al lui q
            q -> pr -> dr = q -> st;
            // il inlocuim pe p cu q si il eliminam pe p
            q -> dr = p -> dr;
            if (q -> dr != NULL)
                q -> dr -> pr = q;
            q -> st = p -> st;
            q -> st -> pr = q;
            q -> pr = p -> pr;
            if (data == rad -> info) {
                rad = q;
            }
            else if (stanga)
                q -> pr -> st = q;
            else
                q -> pr -> dr = q;
            u = q;
        }
    }
    if (u == NULL)
        u -> culoare = 'n';
    if (p -> culoare == 'r' || u -> culoare == 'r')
        u -> culoare = 'n';
    if (p -> culoare == 'n' && u -> culoare == 'n')
        u -> culoare = 'd';
    while (u -> culoare == 'd' && u -> pr != NULL) {
        nod_rn<T>* s = u -> frate(), *r = NULL;
        if (s -> st != NULL && s -> st -> culoare == 'r')
            r = s -> st;
        else if (s -> dr != NULL && s -> dr -> culoare == 'r')
            r = s -> dr;
        if (s -> culoare == 'n' && r != NULL)
    }
    delete p;*/
    cout << "TODO";
}