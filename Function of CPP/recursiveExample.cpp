#include <iostream>

using namespace std;

// Menghitung n! (faktorial n) secara rekursif
unsigned long long factorial(unsigned int n) {
    // Base case: 0! = 1
    if (n == 0) {
        return 1;
    }
    // Recursive case: n! = n * (n-1)!
    return n * factorial(n - 1);
}

int main() {
    unsigned int n;
    cout << "Masukkan n (>=0) untuk menghitung n!: ";
    if (!(cin >> n)) return 0;

    unsigned long long result = factorial(n);
    cout << n << "! = " << result << "\n";

    return 0;
}