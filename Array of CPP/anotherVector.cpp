#include <iostream>
#include <vector> // manggil fungsi vector

using namespace std;

int main() {
    // Contoh: daftar belanja sederhana menggunakan vector<string>
    vector<string> daftar;

    // Menambahkan elemen ke paling belakang konsep queue
    daftar.push_back("Susu");
    daftar.push_back("Roti");
    daftar.push_back("Telur");

    // Menampilkan jumlah dan isi (range-for)
    cout << "Jumlah item: " << daftar.size() << "\n";
    for (size_t i = 0; i < daftar.size(); ++i) {
        cout << "- " << daftar[i] << "\n";
    }

    
    // Sisipkan item di index 1
    daftar.insert(daftar.begin() + 1, "Gula");
    
    // Ubah elemen (misalnya index 2)
    if (daftar.size() > 2) {
        daftar[2] = "Roti Tawar";
    }
    
    daftar[1] = "KACANG";
    
    // Hapus elemen terakhir
    daftar.pop_back();
    
    // Urutkan secara alfabet
    sort(daftar.begin(), daftar.end());

    cout << "\nSetelah modifikasi dan pengurutan:\n";
    for (size_t i = 0; i < daftar.size(); ++i) {
        cout << i << ": " << daftar[i] << "\n";
    }

    return 0;
}