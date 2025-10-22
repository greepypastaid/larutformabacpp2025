#include <iostream>

using namespace std;

int main() {
    // buatlah do while yang menjumlahkan angka sesuai dari batas input kita? 
    
    // Deklarasi angka yang bakalan dimasukkin
    int angka;

    // input angka kita
    cout << "Masukkan angka: ";
    cin >> angka;

    // aku btuh bantuan nih buat iterasinya, pakailah i = 0
    int i = 0;

    // aku deklarasiin itungan kosong atau tempat buat ngitung jumlahnya
    int sum = 0;

    do {
        i++; // loop 4 i = 4
        sum = sum + i; // sum = 6 + 4 = 10
    } while (i < angka); // apakah i masih kurang dari angka?

    cout << "Hasilnya ialah: " << sum; // output sum = 10

    return 0;
}