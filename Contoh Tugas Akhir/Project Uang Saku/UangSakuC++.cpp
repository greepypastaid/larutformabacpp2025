#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct transaction {
    string name;
    string notes;
    long long amount;
};

void mainMenu(){
    cout << "\n\tMenu Utama" << endl;
    cout << "1. Tambah Pemasukkan" << endl;
    cout << "2. Tambah Pengeluaran" << endl;
    cout << "3. Edit Pengeluaran / Pemasukkan" << endl;
    cout << "4. Tampilkan Pemasukkan" << endl;
    cout << "5. Tampilkan Pengeluaran" << endl;
    cout << "6. Rekap Total" << endl;
    cout << "0. Exit" << endl;
}

void insertData(transaction& data) {
    cout << "Masukkan nama : ";
    cin.ignore();
    getline(cin, data.name);
    cout << "Masukkan Nominal : ";
    cin >> data.amount;
    cout << "Keterangan (Isi - Jika Kosong!) : ";
    cin.ignore();
    getline(cin, data.notes);
}

long long pemasukkanTotal(vector <transaction>& tabungan, vector <transaction>& masaDepan, vector <transaction>& kebutuhan, vector <transaction>& halLain) {
    long long total = 0;

    for (int i = 0; i < tabungan.size(); i++) {
        total += tabungan[i].amount;
    }

    for (int i = 0; i < masaDepan.size(); i++) {
        total += masaDepan[i].amount;
    }

    for (int i = 0; i < kebutuhan.size(); i++) {
        total += kebutuhan[i].amount;
    }

    for (int i = 0; i < halLain.size(); i++) {
        total += halLain[i].amount;
    }

    return total;
}

long long pengeluaranTotal(vector <transaction>& harian, vector <transaction>& makanan, vector <transaction>& pembayaran, vector <transaction>& lainnya) {
    long long total = 0;

    for (int i = 0; i < harian.size(); i++) {
        total += harian[i].amount;
    }

    for (int i = 0; i < makanan.size(); i++) {
        total += makanan[i].amount;
    }

    for (int i = 0; i < pembayaran.size(); i++) {
        total += pembayaran[i].amount;
    }

    for (int i = 0; i < lainnya.size(); i++) {
        total += lainnya[i].amount;
    }

    return total;
}

void editData(vector <transaction>& data) {
    int edit;
    
    // menampilkan data
    cout << "Menampilkan Seluruh Data" << endl;
    for (int i = 0; i < data.size(); i++) {
        cout << i + 1 << ". " << data[i].name << " - Rp." << data[i].amount << " - " << data[i].notes << endl;
    }

    int index;
    cout << "Masukkan Index yang ingin dirubah : ";
    cin >> index;

    cout << "Edit Atau Hapus? (1 Edit | 0 Hapus) ";
    cin >> edit;

    if (edit == 1) {
        if (index >= 1 && index <= data.size()) {
            // Editing data
            cout << "\nMerubah Index" << index << ":" << endl;
            insertData(data[index - 1]);
            cout << "Transaksi berhasil dirubah!" << endl;
        } else {
            cout << "Index yang dimasukkan salah!" << endl;
        }

    } else if (edit == 0) {
        if (index >= 1 && index <= data.size()) {
        // Deleting data
        data.erase(data.begin() + index - 1);
        cout << "Transaksi berhasil dihapus" << endl;
        } else {
        cout << "Index yang dimasukkan salah!" << endl;
    }
    }

    cout << "\nTekan apapun untuk lanjut!" << endl;
    cin.ignore();
}

// Fungsi menyimpan di TXT
void saveData(const vector<transaction>& data, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& entry : data) {
            file << entry.name << "," << entry.amount << "," << entry.notes << endl;
        }

        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Fungsi load data dr txt
void loadData(vector<transaction>& data, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        data.clear(); // Clear existing data before loading

        string line;
        while (getline(file, line)) {
            transaction entry;
            stringstream ss(line);
            
            getline(ss, entry.name, ',');
            ss >> entry.amount;
            ss.ignore(); // Ignore the comma
            getline(ss, entry.notes);

            data.push_back(entry);
        }

        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void chart(long long pemasukkan, long long pengeluaran) {
    const int panjangChart = 35;
    int panjang;

    // Menghitung persenan
    double persenPemasukkan = (pemasukkan * 100.0 / (pemasukkan + pengeluaran));
    double persenPengeluaran = (pengeluaran * 100.0 / (pemasukkan + pengeluaran));

    // Main chart
        if (persenPemasukkan > persenPengeluaran ) {
        panjang = (persenPengeluaran / 100) * panjangChart;

        cout << "\n\tProgress Pemasukkan : " << endl;
        cout << "[ ";
        } else if (persenPengeluaran > persenPemasukkan) {
            panjang = (persenPemasukkan / 100) * panjangChart;

            cout << "\n\tProgress Pengeluaran : " << endl;
            cout << "[ ";
        }
        
            // print bar pengeluaran
            for (int i = 0; i < (panjangChart - panjang); i++) {
                cout << "="; 
            }

            // print bar pemasukkan
            for (int i = 0; i < panjang; i++) {
                cout << " ";
            }
            cout << " ]" << endl;

            cout << "[ ";
            
            // print bar pengeluaran
            for (int i = 0; i < (panjangChart - panjang); i++) {
                cout << "="; 
            }

            // print bar pemasukkan
            for (int i = 0; i < panjang; i++) {
                cout << " ";
            }
            cout << " ]" << endl;
            cout << endl;

        if (persenPemasukkan > persenPengeluaran) {
            cout << "Pemasukan : " << persenPemasukkan << "% ";
            cout << "\tPengeluaran : " << persenPengeluaran << "% ";
        } else if (persenPengeluaran > persenPemasukkan) {
            cout << "Pengeluaran : " << persenPengeluaran << "% ";

            cout << "\tPemasukkan : " << persenPemasukkan << "% ";
        }

        cout << "\n\n\t~ Intisari ~" << endl;
        cout << "Jumlah Pemasukkan : Rp." << pemasukkan << endl;
        cout << "Jumlah Pengeluaran : Rp." << pengeluaran << endl;
        cout << "\nSisa Uangmu : Rp." << pemasukkan - pengeluaran << endl;
          
        // logic cataatan 
        cout << "\nCatatan Untuk kamu : "; 

        if (persenPemasukkan > 75) {
            cout << "Tingkatkan Hematmu, Mari Menabung!" << endl;
        } else if (persenPemasukkan < 75 || persenPemasukkan > 50) {
            cout << "Tetaplah semangat berhemat :D" << endl;
        } else if (persenPemasukkan < 50 || persenPemasukkan > 35) {
            cout << "Jangan lupa menabung :v" << endl;
        } else {
            cout << "Nabung Cok!!" << endl;
        }
}

int main() {
    // declaring main variables
    int inputMenu;
    char loop; 

    // declaring struct
    transaction data;

    // declaring vector of pemasukkan & Pengeluaran
    vector <transaction> tabungan, masaDepan, kebutuhan, halLain;
    vector <transaction> harian, makanan, pembayaran, lainnya;

    // load data from the txt file
    loadData(tabungan, "tabungan.txt");
    loadData(masaDepan, "masaDepan.txt");
    loadData(kebutuhan, "kebutuhan.txt");
    loadData(halLain, "halLain.txt");
    loadData(harian, "harian.txt");
    loadData(makanan, "makanan.txt");
    loadData(pembayaran, "pembayaran.txt");
    loadData(lainnya, "lainnya.txt");

    // MENU UTAMA
    mainMenu:
    system("cls");
    
    cout << "==================  Rekap Pengelolaan Uang   ==================" << endl;
    // hitung total data for chart
    long long masuk = pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain);
    long long keluar =  pengeluaranTotal(harian, makanan, pembayaran, lainnya);

    chart(masuk, keluar);

    // Main Menu
    mainMenu();
    cout << "Input : ";
    cin >> inputMenu;

    switch (inputMenu) {
        case 1:
            int inputPemasukkan; 
            loopPemasukkan:

            system ("cls");
            cout << "================== Tambah Pemasukkan ==================" << endl;
            cout << "Masukkan Jenis Pemasukkan" << endl;
            cout << "1. Tabungan" << endl;
            cout << "2. Masa Depan" << endl;
            cout << "3. Kebutuhan Sehari-hari" << endl;
            cout << "4. Hal Lain" << endl;
            cout << "Input : ";
            cin >> inputPemasukkan;

            system ("cls");
                // logic pemasukkan
                if (inputPemasukkan == 1) {
                    cout << "================== Tambah Tabungan ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    tabungan.push_back(data);

                    // saving into txt file
                    saveData(tabungan, "tabungan.txt");
                } else if (inputPemasukkan == 2) {
                    cout << "================== Tambah Masa Depan ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    masaDepan.push_back(data);

                    // saving into txt file
                    saveData(masaDepan, "masaDepan.txt");
                } else if (inputPemasukkan == 3) {
                    cout << "================== Tambah Kebutuhan Sehari-hari ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    kebutuhan.push_back(data);

                    // saving into txt file
                    saveData(kebutuhan, "kebutuhan.txt");
                } else if (inputPemasukkan == 4) {
                    cout << "================== Tambah Hal Lain ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    halLain.push_back(data);

                    // saving into txt file
                    saveData(halLain, "halLain.txt");
                } else {
                    cin.ignore();
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan apapun untuk melanjutkan :) " << endl;
                    cin.ignore();
            
                    goto loopPemasukkan;
                }

            cout << "Tambah Transaksi Pemasukkan lagi Y/N?  ";
            cin >>  loop;

            if (loop == 'y' || loop == 'Y') {
                goto loopPemasukkan;
            }
        break;
        
        case 2:
            int inputPengeluaran;
            loopPengeluaran:

            system ("cls");
            cout << "================== Tambah Pengeluaran ==================" << endl;
            cout << "Masukkan Jenis Pemasukkan" << endl;
            cout << "1. Kebutuhan Sehari-hari" << endl;
            cout << "2. Makanan" << endl;
            cout << "3. Pembayaran" << endl;
            cout << "4. Hal Lain" << endl;
            cout << "Input : ";
            cin >> inputPengeluaran;

            system ("cls");
                // logic pemasukkan
                if (inputPengeluaran == 1) {
                    cout << "================== Tambah Kebutuhan sehari-hari ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    harian.push_back(data);

                    // saving into txt file
                    saveData(harian, "harian.txt");
                } else if (inputPengeluaran == 2) {
                    cout << "================== Tambah Makanan ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    makanan.push_back(data);

                    // saving into txt file
                    saveData(makanan, "makanan.txt");
                } else if (inputPengeluaran == 3) {
                    cout << "================== Tambah Pembayaran ======= ===========" << endl;
                    insertData(data);

                    // inserting into vector
                    pembayaran.push_back(data);

                    // saving into txt file
                    saveData(pembayaran, "pembayaran.txt");
                } else if (inputPengeluaran == 4) {
                    cout << "================== Tambah Hal Lain ==================" << endl;
                    insertData(data);

                    // inserting into vector
                    lainnya.push_back(data);

                    // saving into txt file
                    saveData(lainnya, "lainnya.txt");
                } else {
                    cin.ignore();
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan apapun untuk melanjutkan :) " << endl;
                    cin.ignore();
            
                    goto loopPengeluaran;
                }

            cout << "Tambah Transaksi Pemasukkan lagi Y/N?  ";
            cin >>  loop;

            if (loop == 'y' || loop == 'Y') {
                goto loopPengeluaran;
            }
        break;

        case 3:
            int inputEdit;
            loopEdit:

            system("cls");
            cout << "================== Edit Pemasukkan / Pengeluaran ==================" << endl;
            cout << "Jenis Pengelolaan : " << endl;
            cout << "1. Pemasukkan" << endl;
            cout << "2. Pengeluaran" << endl;
            cout << "Input : ";
            cin >> inputEdit;

            if (inputEdit == 1) {
                loopEditPemasukkan:
                
                system("cls");

                cout << "================== Edit Pemasukkan ==================" << endl;
                cout << "Masukkan Jenis Pemasukkan" << endl;
                cout << "1. Tabungan" << endl;
                cout << "2. Masa Depan" << endl;
                cout << "3. Kebutuhan Sehari-hari" << endl;
                cout << "4. Hal Lain" << endl;
                cout << "Input : ";
                cin >> inputPemasukkan;

                if (inputPemasukkan == 1) {
                    cout << "================== Edit Tabungan ==================" << endl;
                    editData(tabungan);

                    // saving into txt file
                    saveData(tabungan, "tabungan.txt");
                } else if (inputPemasukkan == 2) {
                    cout << "================== Edit Masa Depan ==================" << endl;
                    editData(masaDepan);

                    // saving into txt file
                    saveData(masaDepan, "masaDepan.txt");
                } else if (inputPemasukkan == 3) {
                    cout << "================== Edit Kebutuhan Sehari-hari ======= ===========" << endl;
                    editData(kebutuhan);

                    // saving into txt file
                    saveData(kebutuhan, "kebutuhan.txt");
                } else if (inputPemasukkan == 4) {
                    cout << "================== Edit Hal Lain ==================" << endl;
                    editData(halLain);

                    // saving into txt file
                    saveData(halLain, "halLain.txt");
                } else {
                    cin.ignore();
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan apapun untuk melanjutkan :) " << endl;
                    cin.ignore();
            
                    goto loopEditPemasukkan;
                }

            } else if (inputEdit == 2) {
                loopEditPengeluaran:
                
                system("cls");

                cout << "================== Edit Pengeluaran ==================" << endl;
                cout << "Masukkan Jenis Pengeluaran" << endl;
                cout << "1. Kebutuhan Sehari-hari" << endl;
                cout << "2. Makanan" << endl;
                cout << "3. Pembayaran" << endl;
                cout << "4. Hal Lain" << endl;
                cout << "Input : ";
                cin >> inputPengeluaran;

                if (inputPengeluaran == 1) {
                    cout << "================== Kebutuhan sehari-hari ==================" << endl;
                    editData(harian);

                    // saving into txt file
                    saveData(harian, "harian.txt");
                } else if (inputPengeluaran == 2) {
                    cout << "================== Edit Makanan ==================" << endl;
                    editData(makanan);

                    // saving into txt file
                    saveData(makanan, "makanan.txt");
                } else if (inputPengeluaran == 3) {
                    cout << "================== Edit Pembayaran ======= ===========" << endl;
                    editData(pembayaran);

                    // inserting into vector
                    pembayaran.push_back(data);

                    // saving into txt file
                    saveData(pembayaran, "pembayaran.txt");
                } else if (inputPengeluaran == 4) {
                    cout << "================== Edit Hal Lain ==================" << endl;
                    editData(lainnya);

                    // saving into txt file
                    saveData(lainnya, "lainnya.txt");
                } else {
                    cin.ignore();
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan apapun untuk melanjutkan :) " << endl;
                    cin.ignore();
            
                    goto loopEditPengeluaran;
                }
            }
            cout << "Ingin Mengedit lagi Y/N?  ";
            cin >>  loop;

            if (loop == 'y' || loop == 'Y') {
                goto loopEdit;
            }
        break;

        case 4:
        {
            system("cls");

            // declaration
            long long totalTabungan = 0, totalmasaDepan = 0, totalKebutuhan = 0, totalHalLain = 0;

            cout << "================== Menampilkan Pemasukkan ==================" << endl;
            cout << "Pemasukkan Total : Rp." << pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain) << endl;

            // Untuk tabungan
            for (int i = 0; i < tabungan.size(); i++) {
                totalTabungan += tabungan[i].amount;

                if (totalTabungan >= 1) {
                    cout << "\nNama : " << tabungan[i].name << endl;
                    cout << "Nominal: " << tabungan[i].amount << endl;
                    cout << "Keterangan : " << tabungan[i].notes << endl;
                } 
            }
            if (totalTabungan >= 1) {
                cout << "\n\nTotal Tabungan : Rp." << totalTabungan << endl;
            }

            // untuk masadepan
            for (int i = 0; i < masaDepan.size(); i++) {
                totalmasaDepan += masaDepan[i].amount;

                if (totalmasaDepan >= 1) {
                    cout << "\nNama : " << masaDepan[i].name << endl;
                    cout << "Nominal: " << masaDepan[i].amount << endl;
                    cout << "Keterangan : " << masaDepan[i].notes << endl;
                }
            }
            if (totalmasaDepan >= 1) {
                cout << "\n\nTotal Masa Depan : Rp." << totalmasaDepan << endl;
            }

            // untuk kebutuhan
            for (int i = 0; i < kebutuhan.size(); i++) {
                totalKebutuhan += kebutuhan[i].amount;

                if (totalKebutuhan >= 1) {
                    cout << "\nNama : " << kebutuhan[i].name << endl;
                    cout << "Nominal: " << kebutuhan[i].amount << endl;
                    cout << "Keterangan : " << kebutuhan[i].notes << endl;
                }
            }
            if (totalKebutuhan >= 1) {
                cout << "\n\nTotal Kebutuhan : Rp." << totalKebutuhan << endl;
            }

            // untuk halLain
            for (int i = 0; i < halLain.size(); i++) {
                totalHalLain += halLain[i].amount;

                if (totalHalLain >= 1) {
                    cout << "\nNama : " << halLain[i].name << endl;
                    cout << "Nominal: " << halLain[i].amount << endl;
                    cout << "Keterangan : " << halLain[i].notes << endl;
                }
            }
            if (totalHalLain >= 1) {
                cout << "\n\nTotal Hal Lain : Rp." << totalHalLain << endl;
            }

            cin.ignore();
            cout << "\nTekan Apapun untuk kembali ke menu.";
            cin.ignore();

        break;
        }

        case 5:
        {
            system("cls");

            // declaration
            long long totalHarian = 0, totalMakanan = 0, totalPembayaran = 0, totalLainnya = 0;

            cout << "================== Menampilkan Pengeluaran ==================" << endl;
            cout << "Pengeluaran Total : Rp." << pengeluaranTotal(harian, makanan, pembayaran, lainnya) << endl;

            // untuk harian
            for (int i = 0; i < harian.size(); i++) {
                totalHarian += harian[i].amount;

                if (totalHarian >= 1) {
                    cout << "\nNama : " << harian[i].name << endl;
                    cout << "Nominal: " << harian[i].amount << endl;
                    cout << "Keterangan : " << harian[i].notes << endl;
                }
            }
            if (totalHarian >= 1) {
                cout << "Total harian : Rp." << totalHarian << endl;
            }

            // Untuk makanan
            for (int i = 0; i < makanan.size(); i++) {
                totalMakanan += makanan[i].amount;

                if (totalMakanan >= 1) {
                    cout << "\nNama : " << makanan[i].name << endl;
                    cout << "Nominal: " << makanan[i].amount << endl;
                    cout << "Keterangan : " << makanan[i].notes << endl;
                } 
            }
            if (totalMakanan >= 1) {
                cout << "Total Makanan : Rp." << totalMakanan << endl;
            }

            // untuk pembayaran
            for (int i = 0; i < pembayaran.size(); i++) {
                totalPembayaran += pembayaran[i].amount;

                if (totalPembayaran >= 1) {
                    cout << "\nNama : " << pembayaran[i].name << endl;
                    cout << "Nominal: " << pembayaran[i].amount << endl;
                    cout << "Keterangan : " << pembayaran[i].notes << endl;
                }
            }
            if (totalPembayaran >= 1) {
                cout << "Total Pembayaran : Rp." << totalPembayaran << endl;
            }

            // untuk lainnya
            for (int i = 0; i < lainnya.size(); i++) {
                totalLainnya += lainnya[i].amount;

                if (totalLainnya >= 1) {
                    cout << "\nNama : " << lainnya[i].name << endl;
                    cout << "Nominal: " << lainnya[i].amount << endl;
                    cout << "Keterangan : " << lainnya[i].notes << endl;
                }
            }
                if (totalLainnya >= 1) {
                    cout << "Total Hal Lain : Rp." << totalLainnya << endl;
                }
            
            cin.ignore();
            cout << "\nTekan Apapun untuk kembali ke menu.";
            cin.ignore();

        break;
        }

        case 6:
        {
            system("cls");
            cout << "================== Rekap Total ==================" << endl;
            chart(masuk, keluar);

            cout << "\n~ Pemasukkan ~" << endl;

            // count jumlah pemasukkan
            int totalMasuk = tabungan.size() + masaDepan.size( ) + kebutuhan.size() + halLain.size();
            cout << "Jumlah Transaksi Pemasukanmu : " << totalMasuk << endl;
            cout << "Nominalnya : " << pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain) << endl;

            cout << "\n~ Pengeluaran ~" << endl;

            int totalKeluar = harian.size() + makanan.size() + pembayaran.size() + lainnya.size();
            cout << "Jumlah Transaksi Pengeluaranmu : " << totalKeluar << endl;
            cout << "Nominalnya : " << pengeluaranTotal(harian, makanan, pembayaran, lainnya) << endl;

            cin.ignore();
            cout << "\nTekan Apapun untuk kembali ke menu.";
            cin.ignore(); 

        break;
        }
        case 0:
            return 0;
    }

    goto mainMenu;   
}