#include <iostream>

using namespace std;

// int itu jenis tipe data fungsinya
int luasPersegi(int sisi) { // int sisi itu parameter
    return sisi * sisi; // nilai dikembalikan ke pemanggil
}

int main() {
    int sisi = 5; // ukuran sisi persegi

    // Memanggil fungsi dan menyimpan hasilnya cari luas
    int area = luasPersegi(sisi); // kita memanggil sebuah hitungan diluar program utama

    cout << "Sisi: " << sisi << "\n";
    cout << "Luas persegi: " << area << "\n";

    return 0;
}