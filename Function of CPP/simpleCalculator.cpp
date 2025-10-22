#include <iostream>

using namespace std;

// Fungsi: mengembalikan hasil operasi
int tambah(int a, int b) { 
    return a + b; 
}
int kurang(int a, int b) {
     return a - b; 
}
int kali(int a, int b)   { 
    return a * b; 
}

// Prosedur: hanya mencetak hasil
void cetakHasil(int hasil) {
    cout << "Hasil: " << hasil << "\n";
}

int main() {
    int x, y;
    char op;

    cout << "Masukkan dua bilangan (mis: 4 5): ";
    if (!(cin >> x >> y)) return 0;

    cout << "Pilih operasi (+ - *): ";
    cin >> op;

    int hasil;
    if (op == '+') {
        hasil = tambah(x, y);
    } else if (op == '-') {
        hasil = kurang(x, y);
    } else if (op == '*' || op == 'x' || op == 'X') {
        hasil = kali(x, y);
    } else {
        cout << "Operator tidak valid\n";
        return 0;
    }

    cetakHasil(hasil);
    return 0;
}