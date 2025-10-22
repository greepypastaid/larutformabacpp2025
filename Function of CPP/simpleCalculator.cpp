#include <iostream>

using namespace std;

// Fungsi: mengembalikan hasil operasi
int tambah(int budi, int adi) { // fungsi untuk menghitung penjumlahan
    return budi + adi; 
}
int kurang(int a, int b) { // fungsi untuk menghitung pengurangan
     return a - b; 
}
int kali(int a, int b)   {  // fungsi untuk menghitung perkalian
    return a * b; 
}

// Prosedur: hanya mencetak hasil
void cetakHasil(int hasil, string namaOrang) {
    cout << "Hasil: " << hasil << "\n";
    cout << "Hitungan barusan dibuat oleh: " << namaOrang << "\n";
}

int main() {
    int x, y; // deklarasiin variable x dan y
    char op; // deklarasiin variable op untuk operator untuk milih menu

    cout << "Masukkan dua bilangan (mis: 4 5): ";
    if (!(cin >> x >> y)) {
        cout << "Input tidak valid\n";
        return 0;
    } 

    cout << "Pilih operasi (+ - *): ";
    cin >> op;

    // kunci pengambilan fungsi ada diabwah ini!
    int hasil; // deklarasiin hasil
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

    string nama = "Reka";

    cetakHasil(hasil, nama);
    return 0;
}