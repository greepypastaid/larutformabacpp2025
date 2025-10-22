#include <iostream>

using namespace std;

// Masukkan Kumpulan Fungsi dibawah ini wak!

void menu() {
    cout << "=== Menu ===" << endl;
    cout << "1. Nasi Goreng (13000)" << endl;
    cout << "2. Mie Ayam (10000)" << endl;
    cout << "3. Exit" << endl;
}

int hargaMakanan(int choice, int satuan)
{
    if (choice == 1)
        return 13000*satuan;
    else if (choice == 2) {
        return 10000*satuan;
    }   
}

int main() {
   menu(); // Panggil fungsi menu untuk menampilkan menu
    
   cout << "Pilih opsi: ";
   int choice;
   cin >> choice; // aku pilih nasgor = 1

   cout << "Masukkan jumlah porsi: ";
   int porsi;
   cin >> porsi; // masukkin poorsi 4

   // aku masukkin sebuah nasgor dengan 4 porsi ke fungsi hargaMakanan
   int total=hargaMakanan(choice, porsi);

   cout << total;

   return 0;
}