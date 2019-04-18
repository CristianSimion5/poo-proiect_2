// Simion Cristian

#include <iostream>
#include <functional>
#pragma once
using namespace std;

template <typename T, typename Compare = greater<T>>
class abc: public arbore<T, Compare> {
private:
    nod<T> *rad;

public:
    abc(): arbore<T, Compare>() { rad = NULL; };
    abc(const abc& arb);
    ~abc() {
        delete_recursiv(rad);
    };

    void delete_recursiv(nod<T>* node);
    bool cautare(T data, Compare comp = Compare());
    void inserare(T data, Compare comp = Compare());
    void stergere(T data, Compare comp = Compare());
    T get_rad() { return rad -> info; };
    int inaltime() { if (rad == NULL) return 0; return rad -> height_max(); };
    void afis_frunze(ostream& os) {
        rad -> afis_recursiv(os);
    }

    abc<T, Compare>& operator=(const abc<T, Compare>& arb);
    abc<T, Compare> operator+(abc<T, Compare> arbdel);
    abc<T, Compare> operator-(abc<T, Compare> arbdel);
    abc<T, Compare> operator*(abc<T, Compare> arbdel);

    bool operator==(abc<T, Compare>& arb);
    bool operator!=(abc<T, Compare>& arb);
    bool operator<(abc<T, Compare>& arb);


    friend ostream& operator<<(ostream& os, abc<T, Compare>& arb) {
        arb.rad -> inordine(os);
        return os;
    }

    friend istream& operator>>(istream& is, abc<T, Compare>& arb) {
        T x;
        is >> x;
        arb.inserare(x);
        return is;
    }
};

template <typename T, typename Compare>
abc<T, Compare>::abc(const abc<T, Compare>& arb): arbore<T, Compare>(arb) {
    rad = new nod<T>;
    rad -> copie_recursiv(arb.rad);
}

template <typename T, typename Compare>
void abc<T, Compare>::delete_recursiv(nod<T>* node) {
    if (node != NULL) {
            delete_recursiv(node -> st);
            delete_recursiv(node -> dr);
            delete node;
        }
}

template <typename T, typename Compare>
abc<T, Compare>& abc<T, Compare>::operator=(const abc<T, Compare>& arb) {
    if (this == &arb)
        return *this;
    delete_recursiv(rad);
    this -> nr_noduri = arb.nr_noduri;
    rad = new nod<T>;
    rad -> copie_recursiv(arb.rad);
    return *this;
}

template <typename T, typename Compare>
abc<T, Compare> abc<T, Compare>::operator+(abc<T, Compare> arbdel) {
    abc<T, Compare> suma = *this;
    while (!arbdel.empty()) {
        suma.inserare(arbdel.get_rad());
        arbdel.stergere(arbdel.get_rad());
    }
    return suma;
}

template <typename T, typename Compare>
abc<T, Compare> abc<T, Compare>::operator-(abc<T, Compare> arbdel) {
    abc<T, Compare> dif = *this;
    while (!arbdel.empty()) {
        dif.stergere(arbdel.get_rad());
        arbdel.stergere(arbdel.get_rad());
    }
    return dif;
}

template <typename T, typename Compare>
abc<T, Compare> abc<T, Compare>::operator*(abc<T, Compare> arbdel) {
    abc<T, Compare> inters, de_sters;
    if (this -> size() > arbdel.size()) {
        de_sters = arbdel;
        arbdel = *this;
    } 
    else
        de_sters = *this;
    T x;
    while (!de_sters.empty()) {
        x = de_sters.get_rad();
        if (de_sters.cautare(x) && arbdel.cautare(x))
            inters.inserare(x);
        de_sters.stergere(x);
    }
    return inters;
}

template <typename T, typename Compare>
bool abc<T, Compare>::operator==(abc<T, Compare>& arb) {
    return rad -> compara_recursiv(arb.rad);
}

template <typename T, typename Compare>
bool abc<T, Compare>::operator!=(abc<T, Compare>& arb) {
    return !(*this == arb);
}

template <typename T, typename Compare>
bool abc<T, Compare>::operator<(abc<T, Compare>& arb) {
    return this -> size() < arb.size();
}

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
        this -> nr_noduri++;
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

template <typename T, typename Compare>
void abc<T, Compare>::stergere(T data, Compare comp) {
    if (!cautare(data))
        return;
    this -> nr_noduri--;
    nod<T>* p = rad;
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
            delete p;
            rad = NULL;
            return;
        }
        if (stanga)
            p -> pr -> st = NULL;
        else
            p -> pr -> dr = NULL;
        delete p;
        return;
    }
    if (p -> st == NULL) {
        if (data != rad -> info) {
            if (stanga)
                p -> pr -> st = p -> dr;
            else
                p -> pr -> dr = p -> dr;
        }
        else 
            rad = p -> dr;
        p -> dr -> pr = p -> pr;
        delete p;
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
        delete p;
    }
    else {
        nod<T>* q = p -> st;
        if (q -> dr == NULL) {
            q -> dr = p -> dr;
            q -> pr = p -> pr;
            if (q -> dr != NULL)
                q -> dr -> pr = q;
            if (data == rad -> info) {
                rad = q;
                delete p;
                return;
            }
            else if (stanga)
                q -> pr -> st = q;
            else
                q -> pr -> dr = q;
            return;
        }
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
            delete p;
            return;
        }
        else if (stanga)
            q -> pr -> st = q;
        else
            q -> pr -> dr = q;
        delete p;
    }
}
