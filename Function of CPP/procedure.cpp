#include <iostream>

using namespace std;

// Procedure: void (tidak mengembalikan nilai)
// tapi hanya melakukan aksi (mencetak)
void cetakLuasPersegi(int sisi) {
    int luas = sisi * sisi;
    cout << "Sisi: " << sisi << " -> Luas: " << luas << "\n";
}

int main() {
    // Panggil procedure beberapa kali dengan input berbeda
    cetakLuasPersegi(4);
    cetakLuasPersegi(7);
    cetakLuasPersegi(10);

    return 0;
}