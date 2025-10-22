#include <iostream>
#include <vector> 

using namespace std;

struct makanan {
    string nama;
    int harga;
    int level;
};

int main() {
    vector <makanan> menu;

    makanan nasgor;
    nasgor.nama = "Nasi Goreng Seafood";
    nasgor.harga = 200000;
    nasgor.level = 5;
    menu.push_back(nasgor);

    makanan ayamgeprek;
    ayamgeprek.nama = "Ayam Geprek";
    ayamgeprek.harga = 180000;
    ayamgeprek.level = 4;
    menu.push_back(ayamgeprek);

    // Menampilkan hasil insert ke vector
    for (int i = 0; i < menu.size(); i++) {
        cout << menu[i].nama << " harganya " << menu[i].harga << endl;
    }
}