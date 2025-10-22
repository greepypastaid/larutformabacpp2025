#include <iostream>

using namespace std;

// int itu jenis tipe data fungsinya
int luasPersegi(int sisi) { // int sisi itu parameter
    return sisi * sisi; // nilai dikembalikan ke pemanggil
}

int main() {
    int s = 5;

    // Memanggil fungsi dan menyimpan hasilnya
    int area = luasPersegi(s);

    cout << "Sisi: " << s << "\n";
    cout << "Luas persegi: " << area << "\n";

    return 0;
}