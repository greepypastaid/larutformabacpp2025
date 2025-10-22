#include <iostream>

using namespace std;

// Masukkan Kumpulan Fungsi dibawah ini wak!

void menu() {
    cout << "=== Menu ===" << endl;
    cout << "1. Option 1" << endl;
    cout << "2. Option 2" << endl;
    cout << "3. Exit" << endl;
}

int main() {
   menu(); // Panggil fungsi menu untuk menampilkan menu
    
   cout << "Pilih opsi: ";
   int choice;
   cin >> choice;

   while (choice != 3) {
       cout << "Kamu memilih opsi " << choice << endl;
       menu(); // Tampilkan menu lagi
       cout << "Pilih opsi: ";
       cin >> choice;
   }

   return 0;
}