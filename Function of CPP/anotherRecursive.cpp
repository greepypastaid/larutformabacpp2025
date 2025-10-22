#include <iostream>

using namespace std;

unsigned long long fib(unsigned int n) {
    if (n == 0) return 0;           // base case 0
    if (n == 1) return 1;           // base case 1
    return fib(n - 1) + fib(n - 2); // recursive case
}

int main() {
    unsigned int n;
    cout << "Masukkan n (>=0, disarankan <=40 untuk kecepatan): ";
    if (!(cin >> n)) return 0;

    cout << n << "th Fibonacci = " << fib(n) << "\n";

    cout << "Deret Fibonacci 0.." << n << " : ";
    for (unsigned int i = 0; i <= n; ++i) {
        cout << fib(i) << (i == n ? "\n" : " ");
    }

    return 0;
}