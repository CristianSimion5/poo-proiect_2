// Simion Cristian

#include <iostream>
#include <fstream>
#include <algorithm>

#include "interface.hpp"
#include "abc.hpp"
#include "arn.hpp"

using namespace std;

int main() {
    abc<int> a;
    a.inserare(10);
    a.inserare(20);
    a.inserare(0);
    a.inserare(5);
    a.inserare(-3);
    abc<int> b;
    b.inserare(30);
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
    cout << c << ' ' << c.size() << '\n';
    cout << a.inaltime() << ' ' << b.inaltime() << ' ' << c.inaltime() << '\n';
    abc<int> v[3] = {a, b, c};
    sort(v, v + 3);
    for (int i = 0; i < 3; i++) {
        cout << v[i].size() << '\n';
    }
    if (c == c)
        cout << "ok" << '\n' << '\n';
    arn<int> A;
    A.inserare(10);
    A.inserare(5);
    A.inserare(-10);
    A.inserare(60);
    A.inserare(30);
    A.inserare(20);
    A.inserare(100);
    A.inserare(35);
    A.inserare(27);
    A.inserare(200);
    A.inserare(300);
    A.inserare(400);
    cout << A.size() << '\n';
    arn<int> B(A);
    cin >> B;
    cout << B << '\n';
    B = A;
    cout << B << '\n' << A.inaltime() << '\n';
    return 0;
}
