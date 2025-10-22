#include <iostream>

using namespace std; 

int main () {
    // Buat variabel array nilai mahasiswa
    float nilaiMHS [5]; // buat dulu data nilai mahasiswa yang isinya 5 orang
    float total = 0.0; // totalnya nilai semua berapa?

    // Input nilai mahasiswa
    for (int i = 0; i < 5; ++i) {
        cout << "Masukkan nilai mahasiswa ke-" << (i + 1) << ": ";
        cin >> nilaiMHS[i];
        total += nilaiMHS[i]; // Tambah nilai ke total mungkin alternatif total = total + nilaiMHS[i];
        cout << total << endl;
    }

    // Hitung rata-rata
    float rataRata = total / 5; // alternative lainnya pakai sizeof array kalo ga salah
    cout << "Rata-rata nilai mahasiswa: " << rataRata << "\n";

    return 0;
}
