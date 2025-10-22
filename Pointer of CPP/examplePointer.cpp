#include <iostream>

using namespace std;

int main() {
    // Contoh 1: pointer ke variabel
    int x = 10;        // variabel biasa
    int *p = &x;       // p menyimpan alamat x

    cout << "Nilai x: " << x << "\n";
    cout << "Alamat x: " << &x << "\n";
    cout << "Pointer p (alamat): " << p << "\n";
    cout << "Nilai via *p: " << *p << "\n\n";

    // Ubah nilai lewat pointer -> mempengaruhi x
    *p = 20;
    cout << "Setelah *p = 20; x = " << x << "\n\n";

    // Contoh 2: pointer dan array
    int arr[] = { 1, 2, 3 }; // arr adalah alamat elemen pertama
    int *pa = arr;           // pa menunjuk ke arr[0]
    cout << "arr[0]: " << arr[0] << ", via pa[0]: " << pa[0] << "\n";
    cout << "arr[1]: " << arr[1] << ", via pa[1]: " << pa[1] << "\n\n";

    // Contoh 3: null pointer (aman untuk dicek sebelum dereference)
    int *pn = nullptr;
    if (pn == nullptr) {
        cout << "pn adalah nullptr — jangan dereference\n";
    }

    return 0;
}