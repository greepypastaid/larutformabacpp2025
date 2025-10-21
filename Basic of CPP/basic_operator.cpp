#include <iostream>

using namespace std;

int main() {
	int a = 10;            // penugasan
	int b = 3;

	int sum = a + b;       // penjumlahan
	int diff = a - b;      // pengurangan
	int prod = a * b;      // perkalian
	int quot = a / b;      // pembagian (integer)
	int mod = a % b;       // modulus

	a += 2;                // penugasan kompleks (a = a + 2)
	b++;                   // increment
    a--;                   // decrement

	bool gt = a > b;       // perbandingan

	cout << "sum: " << sum << "\n";
	cout << "diff: " << diff << "\n";
	cout << "prod: " << prod << "\n";
	cout << "quot: " << quot << "\n";
	cout << "mod: " << mod << "\n";
    cout << "gt: " << gt << "\n";
	return 0;
}

