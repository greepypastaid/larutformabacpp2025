#include <iostream>
#include <vector>

using namespace std;

struct makanan {
    string nama;
    int harga;
    int level;
};

int main() {
    vector<makanan> menu;

    cout << "Masukkan data makanan. Ketik 'q' sebagai nama untuk selesai.\n";
    while (true) {
        makanan m;
        cout << "Nama: ";
        getline(cin, m.nama);
        if (m.nama == "q") break;

        cout << "Harga: ";
        if (!(cin >> m.harga)) break;

        cout << "Level: ";
        if (!(cin >> m.level)) break;

        menu.push_back(m);
    }

    // Menampilkan hasil insert ke vector
    for (size_t i = 0; i < menu.size(); i++) {
        cout << menu[i].nama << " harganya " << menu[i].harga << " level " << menu[i].level << endl;
    }
}