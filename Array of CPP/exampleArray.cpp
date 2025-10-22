#include <iostream>

using namespace std; 

int main () {
    // Buat variabel array nilai mahasiswa
    float nilaiMHS [5];
    float total = 0.0;

    // Input nilai mahasiswa
    for (size_t i = 0; i < 5; ++i) {
        cout << "Masukkan nilai mahasiswa ke-" << (i + 1) << ": ";
        cin >> nilaiMHS[i];
        total += nilaiMHS[i]; // Tambah nilai ke total
    }

    // Hitung rata-rata
    float rataRata = total / 5;
    cout << "Rata-rata nilai mahasiswa: " << rataRata << "\n";

    return 0;
}
