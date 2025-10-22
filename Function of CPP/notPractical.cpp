#include <iostream>
using namespace std;

int main() {
    double r1 = 3.5;
    double area1 = 3.14159 * r1 * r1; 
    cout << "Luas lingkaran 1: " << area1 << endl;

    double r2 = 5.0;
    double area2 = 3.14159 * r2 * r2; 
    // kode penghitungan diulang wak jadi ga reusable
    cout << "Luas lingkaran 2: " << area2 << endl;

    return 0;
}