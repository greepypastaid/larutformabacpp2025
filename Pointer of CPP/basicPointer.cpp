#include <iostream>

using namespace std;

int main() {
    // Notess : gunakan ponter sesuai yang ingin ditunjuk
    // Contoh : untuk menunjuk int maka gunakan pointer dgn tipe data int, menunjuk char gunakan tipe data char

    // Contoh bentuk bentuk deklarasi pointer
    // int* pi;
    // pi = &i;

    // Atau bisa
    // int *pi = &i; 

    // check ukuran daripada pointer
    // gunakan fungsi sizeof()


    int x = 10;
    
    // mengisi address daripada alamat
    int *alamat = &x;
    
    // menampilkan address daripada x
    cout << &x << endl;

    // menampilkan isi dari x
    cout << x << endl;

    // showing isi dari address daripada alamat dari address x
    cout << alamat << endl;

    // showing address dari alamat
    cout << &alamat << endl;

    // showing alamat daripada x + reference
    cout << x + &alamat;

    // showing x + isi drpd alamat yaitu x sehingga menghasilkan 20
    cout << x + *alamat;

    // // membuat pointer yang tidak menunjuk siapa-siapa
    // int *z = NULL;
    // z = &x; 

    // // Showing alamat daripada x
    // cout << z << endl;

    // // showing alamat isi dari z yaitu isi dari x
    // cout << *z << endl;


}