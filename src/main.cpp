// Simion Cristian

#include <iostream>
#include <fstream>

#include "interface.hpp"
#include "abc.hpp"

using namespace std;

int main() {
    abc<int> a;
    a.inserare(10);
    a.inserare(20);
    a.inserare(0);
    a.inserare(5);
    a.inserare(-3);
    abc<int> b;
    a.inserare(30);
    b.inserare(-123);
    b.inserare(100);
    b.inserare(15);
    b.inserare(13);
    b.inserare(2);
    b.inserare(-42124);
    b.inserare(10);
    b.inserare(0);
    b.inserare(5);
    cout << a << "\n" << b << '\n';
    cout << a.size() << " " << b.size() << '\n';
    abc<int> c = a * b;
    cout << c << ' ' << c.size();
    return 0;
}
