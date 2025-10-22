#include <iostream>

using namespace std;

// Dijadiin satu tempat nih buat kerangka!
struct Mahasiswa {
    int nim;
    string nama;
    float ipk;
};

int main() {
    // 1. Buatin kosongan dari blueprint Mahasiswa
    Mahasiswa budi;

    // 2. Isi data Budi
    budi.nim = 12345;               
    budi.nama = "Budi Santoso";
    budi.ipk = 3.75;

    // 3. Tampilkan data Budi
    cout << "NIM  : " << budi.nim << "\n";
    cout << "Nama : " << budi.nama << "\n";
    cout << "IPK  : " << budi.ipk << "\n";

    return 0;
}