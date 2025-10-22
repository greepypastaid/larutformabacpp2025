#include <iostream>

using namespace std;

int main() {
    // Variabel biasa
    int x = 5;

    // Deklarasi pointer: p dapat menyimpan alamat variabel int
    int *p = &x; // &x = alamat x

    // Cetak nilai & alamat
    cout << "Nilai x        : " << x << "\n";
    cout << "Alamat x (&x)  : " << &x << "\n";
    cout << "Pointer p      : " << p << " (menyimpan alamat)\n";
    cout << "Dereference *p : " << *p << " (nilai di alamat yang ditunjuk)\n\n";

    // Ubah nilai lewat pointer -> mempengaruhi x
    *p = 10; // set nilai pada alamat p menunjuk menjadi 10
    cout << "Setelah *p = 10; x = " << x << "\n\n";

    // Pointer bisa diarahkan ke variabel lain
    int y = 42;
    p = &y;
    cout << "Sekarang p menunjuk ke y\n";
    cout << "Pointer p      : " << p << "\n";
    cout << "Dereference *p : " << *p << "\n";
    cout << "x tetap = " << x << "\n\n";

    // Null pointer: aman untuk dicek sebelum dereference
    p = nullptr;
    if (p == nullptr) {
        cout << "p adalah nullptr — jangan dereference\n";
    }

    return 0;
}

// Cara bacanya?
// Baris 6: int x = 5;
// Buat variabel integer bernama x dengan nilai 5.

// Baris 9: int *p = &x;
// Deklarasi pointer p yang menyimpan alamat variabel x. Operator & berarti "alamat dari".

// Baris 12–15: Cetak nilai dan alamat

// x → nilai biasa.
// &x → alamat memori tempat x disimpan.
// p → sama dengan &x (nilai p adalah alamat).
// *p → dereference; baca nilai yang ada di alamat yang disimpan p (seharusnya 5).
// Baris 18: *p = 10;
// Ubah nilai di alamat yang ditunjuk p menjadi 10. Ini mengubah x juga karena p menunjuk ke x.

// Baris 19: Cetak x lagi → sekarang nilai x = 10.

// Baris 22–26: Arahkan pointer ke variabel lain

// int y = 42; buat variabel baru y.
// p = &y; sekarang p menunjuk ke y (bukan lagi x).
// *p sekarang membaca/menulis nilai y (42). x tetap 10.
// Baris 30–33: Null pointer check

// p = nullptr; set pointer menjadi null (tidak menunjuk ke mana-mana).
// Cek if (p == nullptr) untuk mencegah dereference pada pointer yang tidak valid.