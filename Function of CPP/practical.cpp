#include <iostream>
using namespace std;

double hitungLuasLingkaran(double r) {
    return 3.14159 * r * r;
}

int main() {
    double r1 = 3.5;
    // tinggal panggil deh fungsinya!
    cout << "Luas lingkaran 1: " << hitungLuasLingkaran(r1) << endl;

    // Tinggal panggil lagi buat lingkaran kedua
    double r2 = 5.0;
    cout << "Luas lingkaran 2: " << hitungLuasLingkaran(r2) << endl;

    return 0;
}