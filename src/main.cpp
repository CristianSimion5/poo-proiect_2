// Simion Cristian

#include <iostream>
#include <fstream>
#include <set>
#include "interface.hpp"

using namespace std;

int main() {
    abc<int> a;
    for (int i = 0; i < 10; i++) {
        a.inserare(i * i - 5 * i);
        cout << a.nr_noduri << '\n';
    }
    cout << a << '\n';
    return 0;
}