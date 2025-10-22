#include <iostream>

using namespace std;

struct user {
    long long saldo;
    string nama;
    string alamat;
};

int main() {
    int numUser;

    cout << "Masukkan Jumlah nasabah : ";
    cin >> numUser;
    cin.ignore();
    system("cls");

    user nasabah[numUser];

// mengisi user
    for (int i = 0; i < numUser; i++) {
        cout << "Masukkan nama nasabah : ";
        getline(cin, nasabah[i].nama); 

        cout << "\nMasukkan saldo : ";
        cin >> nasabah[i].saldo;

        cout << "Masukkan alamat nasabah : ";
        cin.ignore();
        getline(cin, nasabah[i].alamat);

        cout << endl;
    }

// menampilkan data dari nasabah
    for(int i = 0; i < numUser; i++) {
        cout << "Nama : " << nasabah[i].nama << endl;
        cout << "Jumlah Saldo : " << nasabah[i].saldo << endl;
        cout << "Alamat nasabah : " << nasabah[i].alamat << endl;

        cout << endl;
    }
}