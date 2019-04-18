// Simion Cristian

#include <iostream>
#include <functional>
#pragma once
using namespace std;

template <typename T, typename Compare = greater<T>>
class arn: public arbore<T, Compare> {
private:
    nod_rn<T> *rad;

public:
    arn(): arbore<T, Compare>() { rad = NULL; };

    bool cautare(T data, Compare comp = Compare());
    void inserare(T data, Compare comp = Compare());

    friend ostream& operator<<(ostream& os, arn<T, Compare>& arb) {
        arb.rad -> inordine(os);
        return os;
    }
};

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