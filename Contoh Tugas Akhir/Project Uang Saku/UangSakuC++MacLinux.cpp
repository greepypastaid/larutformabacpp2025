#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <cstdlib>

using namespace std;

struct transaction {
    string name;
    string notes;
    long long amount;
};

// Portable clear screen helper
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// renamed to avoid confusion with label
void showMainMenu(){
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
    // consume leftover newline (if any) then read full line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, data.name);
    cout << "Masukkan Nominal : ";
    cin >> data.amount;
    cout << "Keterangan (Isi - Jika Kosong!) : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, data.notes);
}

long long pemasukkanTotal(const vector<transaction>& tabungan, const vector<transaction>& masaDepan, const vector<transaction>& kebutuhan, const vector<transaction>& halLain) {
    long long total = 0;

    for (size_t i = 0; i < tabungan.size(); i++) total += tabungan[i].amount;
    for (size_t i = 0; i < masaDepan.size(); i++) total += masaDepan[i].amount;
    for (size_t i = 0; i < kebutuhan.size(); i++) total += kebutuhan[i].amount;
    for (size_t i = 0; i < halLain.size(); i++) total += halLain[i].amount;

    return total;
}

long long pengeluaranTotal(const vector<transaction>& harian, const vector<transaction>& makanan, const vector<transaction>& pembayaran, const vector<transaction>& lainnya) {
    long long total = 0;

    for (size_t i = 0; i < harian.size(); i++) total += harian[i].amount;
    for (size_t i = 0; i < makanan.size(); i++) total += makanan[i].amount;
    for (size_t i = 0; i < pembayaran.size(); i++) total += pembayaran[i].amount;
    for (size_t i = 0; i < lainnya.size(); i++) total += lainnya[i].amount;

    return total;
}

void editData(vector<transaction>& data) {
    int edit;
    
    // menampilkan data
    cout << "Menampilkan Seluruh Data" << endl;
    for (size_t i = 0; i < data.size(); i++) {
        cout << i + 1 << ". " << data[i].name << " - Rp." << data[i].amount << " - " << data[i].notes << endl;
    }

    int index;
    cout << "Masukkan Index yang ingin dirubah : ";
    cin >> index;

    cout << "Edit Atau Hapus? (1 Edit | 0 Hapus) ";
    cin >> edit;

    if (edit == 1) {
        if (index >= 1 && index <= static_cast<int>(data.size())) {
            // Editing data
            cout << "\nMerubah Index " << index << ":" << endl;
            insertData(data[index - 1]);
            cout << "Transaksi berhasil dirubah!" << endl;
        } else {
            cout << "Index yang dimasukkan salah!" << endl;
        }

    } else if (edit == 0) {
        if (index >= 1 && index <= static_cast<int>(data.size())) {
            // Deleting data
            data.erase(data.begin() + index - 1);
            cout << "Transaksi berhasil dihapus" << endl;
        } else {
            cout << "Index yang dimasukkan salah!" << endl;
        }
    }

    cout << "\nTekan Enter untuk lanjut!" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Fungsi menyimpan di TXT
void saveData(const vector<transaction>& data, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& entry : data) {
            file << entry.name << "," << entry.amount << "," << entry.notes << endl;
        }
        file.close();
    } else {
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
            ss.ignore(1); // Ignore the comma
            getline(ss, entry.notes);

            data.push_back(entry);
        }

        file.close();
    }
    // if file not present, that's ok (start empty)
}

void chart(long long pemasukkan, long long pengeluaran) {
    const int panjangChart = 35;
    int panjang = 0;

    long long total = pemasukkan + pengeluaran;
    double persenPemasukkan = 0.0;
    double persenPengeluaran = 0.0;
    if (total > 0) {
        persenPemasukkan = (pemasukkan * 100.0 / total);
        persenPengeluaran = (pengeluaran * 100.0 / total);
    }

    // Determine which bar to emphasize
    if (persenPemasukkan >= persenPengeluaran) {
        panjang = static_cast<int>((persenPengeluaran / 100.0) * panjangChart);
        cout << "\n\tProgress Pemasukkan : " << endl;
    } else {
        panjang = static_cast<int>((persenPemasukkan / 100.0) * panjangChart);
        cout << "\n\tProgress Pengeluaran : " << endl;
    }

    // draw simple bar (two lines for visual)
    cout << "[ ";
    for (int i = 0; i < (panjangChart - panjang); i++) cout << "=";
    for (int i = 0; i < panjang; i++) cout << " ";
    cout << " ]" << endl;

    cout << "[ ";
    for (int i = 0; i < (panjangChart - panjang); i++) cout << "=";
    for (int i = 0; i < panjang; i++) cout << " ";
    cout << " ]" << endl;
    cout << endl;

    if (persenPemasukkan >= persenPengeluaran) {
        cout << "Pemasukan : " << persenPemasukkan << "% ";
        cout << "\tPengeluaran : " << persenPengeluaran << "% ";
    } else {
        cout << "Pengeluaran : " << persenPengeluaran << "% ";
        cout << "\tPemasukkan : " << persenPemasukkan << "% ";
    }

    cout << "\n\n\t~ Intisari ~" << endl;
    cout << "Jumlah Pemasukkan : Rp." << pemasukkan << endl;
    cout << "Jumlah Pengeluaran : Rp." << pengeluaran << endl;
    cout << "\nSisa Uangmu : Rp." << pemasukkan - pengeluaran << endl;
      
    // catatan
    cout << "\nCatatan Untuk kamu : ";

    if (persenPemasukkan > 75) {
        cout << "Tingkatkan Hematmu, Mari Menabung!" << endl;
    } else if (persenPemasukkan > 50 && persenPemasukkan <= 75) {
        cout << "Tetaplah semangat berhemat :D" << endl;
    } else if (persenPemasukkan > 35 && persenPemasukkan <= 50) {
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
    vector<transaction> tabungan, masaDepan, kebutuhan, halLain;
    vector<transaction> harian, makanan, pembayaran, lainnya;

    // load data from the txt file (if files missing, vectors stay empty)
    loadData(tabungan, "tabungan.txt");
    loadData(masaDepan, "masaDepan.txt");
    loadData(kebutuhan, "kebutuhan.txt");
    loadData(halLain, "halLain.txt");
    loadData(harian, "harian.txt");
    loadData(makanan, "makanan.txt");
    loadData(pembayaran, "pembayaran.txt");
    loadData(lainnya, "lainnya.txt");

    // MENU UTAMA
    main_menu:
    clearScreen();
    
    cout << "==================  Rekap Pengelolaan Uang   ==================" << endl;
    long long masuk = pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain);
    long long keluar = pengeluaranTotal(harian, makanan, pembayaran, lainnya);

    chart(masuk, keluar);

    // Main Menu
    showMainMenu();
    cout << "Input : ";
    cin >> inputMenu;

    switch (inputMenu) {
        case 1: {
            int inputPemasukkan; 
            loopPemasukkan:

            clearScreen();
            cout << "================== Tambah Pemasukkan ==================" << endl;
            cout << "Masukkan Jenis Pemasukkan" << endl;
            cout << "1. Tabungan" << endl;
            cout << "2. Masa Depan" << endl;
            cout << "3. Kebutuhan Sehari-hari" << endl;
            cout << "4. Hal Lain" << endl;
            cout << "Input : ";
            cin >> inputPemasukkan;

            clearScreen();
            if (inputPemasukkan == 1) {
                cout << "================== Tambah Tabungan ==================" << endl;
                insertData(data);
                tabungan.push_back(data);
                saveData(tabungan, "tabungan.txt");
            } else if (inputPemasukkan == 2) {
                cout << "================== Tambah Masa Depan ==================" << endl;
                insertData(data);
                masaDepan.push_back(data);
                saveData(masaDepan, "masaDepan.txt");
            } else if (inputPemasukkan == 3) {
                cout << "================== Tambah Kebutuhan Sehari-hari ==================" << endl;
                insertData(data);
                kebutuhan.push_back(data);
                saveData(kebutuhan, "kebutuhan.txt");
            } else if (inputPemasukkan == 4) {
                cout << "================== Tambah Hal Lain ==================" << endl;
                insertData(data);
                halLain.push_back(data);
                saveData(halLain, "halLain.txt");
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                cout << "Tekan Enter untuk melanjutkan..." << endl;
                cin.get();
                goto loopPemasukkan;
            }

            cout << "Tambah Transaksi Pemasukkan lagi Y/N?  ";
            cin >>  loop;
            if (loop == 'y' || loop == 'Y') goto loopPemasukkan;
            break;
        }

        case 2: {
            int inputPengeluaran;
            loopPengeluaran:

            clearScreen();
            cout << "================== Tambah Pengeluaran ==================" << endl;
            cout << "Masukkan Jenis Pengeluaran" << endl;
            cout << "1. Kebutuhan Sehari-hari" << endl;
            cout << "2. Makanan" << endl;
            cout << "3. Pembayaran" << endl;
            cout << "4. Hal Lain" << endl;
            cout << "Input : ";
            cin >> inputPengeluaran;

            clearScreen();
            if (inputPengeluaran == 1) {
                cout << "================== Tambah Kebutuhan sehari-hari ==================" << endl;
                insertData(data);
                harian.push_back(data);
                saveData(harian, "harian.txt");
            } else if (inputPengeluaran == 2) {
                cout << "================== Tambah Makanan ==================" << endl;
                insertData(data);
                makanan.push_back(data);
                saveData(makanan, "makanan.txt");
            } else if (inputPengeluaran == 3) {
                cout << "================== Tambah Pembayaran ==================" << endl;
                insertData(data);
                pembayaran.push_back(data);
                saveData(pembayaran, "pembayaran.txt");
            } else if (inputPengeluaran == 4) {
                cout << "================== Tambah Hal Lain ==================" << endl;
                insertData(data);
                lainnya.push_back(data);
                saveData(lainnya, "lainnya.txt");
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                cout << "Tekan Enter untuk melanjutkan..." << endl;
                cin.get();
                goto loopPengeluaran;
            }

            cout << "Tambah Transaksi Pengeluaran lagi Y/N?  ";
            cin >>  loop;
            if (loop == 'y' || loop == 'Y') goto loopPengeluaran;
            break;
        }

        case 3: {
            int inputEdit;
            loopEdit:

            clearScreen();
            cout << "================== Edit Pemasukkan / Pengeluaran ==================" << endl;
            cout << "Jenis Pengelolaan : " << endl;
            cout << "1. Pemasukkan" << endl;
            cout << "2. Pengeluaran" << endl;
            cout << "Input : ";
            cin >> inputEdit;

            if (inputEdit == 1) {
                int inputPemasukkan;
                loopEditPemasukkan:
                clearScreen();
                cout << "================== Edit Pemasukkan ==================" << endl;
                cout << "Masukkan Jenis Pemasukkan" << endl;
                cout << "1. Tabungan" << endl;
                cout << "2. Masa Depan" << endl;
                cout << "3. Kebutuhan Sehari-hari" << endl;
                cout << "4. Hal Lain" << endl;
                cout << "Input : ";
                cin >> inputPemasukkan;

                if (inputPemasukkan == 1) {
                    editData(tabungan);
                    saveData(tabungan, "tabungan.txt");
                } else if (inputPemasukkan == 2) {
                    editData(masaDepan);
                    saveData(masaDepan, "masaDepan.txt");
                } else if (inputPemasukkan == 3) {
                    editData(kebutuhan);
                    saveData(kebutuhan, "kebutuhan.txt");
                } else if (inputPemasukkan == 4) {
                    editData(halLain);
                    saveData(halLain, "halLain.txt");
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan Enter untuk melanjutkan..." << endl;
                    cin.get();
                    goto loopEditPemasukkan;
                }
            } else if (inputEdit == 2) {
                int inputPengeluaran;
                loopEditPengeluaran:
                clearScreen();
                cout << "================== Edit Pengeluaran ==================" << endl;
                cout << "Masukkan Jenis Pengeluaran" << endl;
                cout << "1. Kebutuhan Sehari-hari" << endl;
                cout << "2. Makanan" << endl;
                cout << "3. Pembayaran" << endl;
                cout << "4. Hal Lain" << endl;
                cout << "Input : ";
                cin >> inputPengeluaran;

                if (inputPengeluaran == 1) {
                    editData(harian);
                    saveData(harian, "harian.txt");
                } else if (inputPengeluaran == 2) {
                    editData(makanan);
                    saveData(makanan, "makanan.txt");
                } else if (inputPengeluaran == 3) {
                    editData(pembayaran);
                    saveData(pembayaran, "pembayaran.txt");
                } else if (inputPengeluaran == 4) {
                    editData(lainnya);
                    saveData(lainnya, "lainnya.txt");
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Maaf input Anda salah, silahkan coba lagi!" << endl;
                    cout << "Tekan Enter untuk melanjutkan..." << endl;
                    cin.get();
                    goto loopEditPengeluaran;
                }
            }
            cout << "Ingin Mengedit lagi Y/N?  ";
            cin >>  loop;
            if (loop == 'y' || loop == 'Y') goto loopEdit;
            break;
        }

        case 4: {
            clearScreen();
            long long totalTabungan = 0, totalmasaDepan = 0, totalKebutuhan = 0, totalHalLain = 0;

            cout << "================== Menampilkan Pemasukkan ==================" << endl;
            cout << "Pemasukkan Total : Rp." << pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain) << endl;

            for (size_t i = 0; i < tabungan.size(); i++) {
                totalTabungan += tabungan[i].amount;
                if (tabungan[i].amount >= 1) {
                    cout << "\nNama : " << tabungan[i].name << endl;
                    cout << "Nominal: " << tabungan[i].amount << endl;
                    cout << "Keterangan : " << tabungan[i].notes << endl;
                } 
            }
            if (totalTabungan >= 1) cout << "\n\nTotal Tabungan : Rp." << totalTabungan << endl;

            for (size_t i = 0; i < masaDepan.size(); i++) {
                totalmasaDepan += masaDepan[i].amount;
                if (masaDepan[i].amount >= 1) {
                    cout << "\nNama : " << masaDepan[i].name << endl;
                    cout << "Nominal: " << masaDepan[i].amount << endl;
                    cout << "Keterangan : " << masaDepan[i].notes << endl;
                }
            }
            if (totalmasaDepan >= 1) cout << "\n\nTotal Masa Depan : Rp." << totalmasaDepan << endl;

            for (size_t i = 0; i < kebutuhan.size(); i++) {
                totalKebutuhan += kebutuhan[i].amount;
                if (kebutuhan[i].amount >= 1) {
                    cout << "\nNama : " << kebutuhan[i].name << endl;
                    cout << "Nominal: " << kebutuhan[i].amount << endl;
                    cout << "Keterangan : " << kebutuhan[i].notes << endl;
                }
            }
            if (totalKebutuhan >= 1) cout << "\n\nTotal Kebutuhan : Rp." << totalKebutuhan << endl;

            for (size_t i = 0; i < halLain.size(); i++) {
                totalHalLain += halLain[i].amount;
                if (halLain[i].amount >= 1) {
                    cout << "\nNama : " << halLain[i].name << endl;
                    cout << "Nominal: " << halLain[i].amount << endl;
                    cout << "Keterangan : " << halLain[i].notes << endl;
                }
            }
            if (totalHalLain >= 1) cout << "\n\nTotal Hal Lain : Rp." << totalHalLain << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk kembali ke menu.";
            cin.get();
            break;
        }

        case 5: {
            clearScreen();
            long long totalHarian = 0, totalMakanan = 0, totalPembayaran = 0, totalLainnya = 0;

            cout << "================== Menampilkan Pengeluaran ==================" << endl;
            cout << "Pengeluaran Total : Rp." << pengeluaranTotal(harian, makanan, pembayaran, lainnya) << endl;

            for (size_t i = 0; i < harian.size(); i++) {
                totalHarian += harian[i].amount;
                if (harian[i].amount >= 1) {
                    cout << "\nNama : " << harian[i].name << endl;
                    cout << "Nominal: " << harian[i].amount << endl;
                    cout << "Keterangan : " << harian[i].notes << endl;
                }
            }
            if (totalHarian >= 1) cout << "Total harian : Rp." << totalHarian << endl;

            for (size_t i = 0; i < makanan.size(); i++) {
                totalMakanan += makanan[i].amount;
                if (makanan[i].amount >= 1) {
                    cout << "\nNama : " << makanan[i].name << endl;
                    cout << "Nominal: " << makanan[i].amount << endl;
                    cout << "Keterangan : " << makanan[i].notes << endl;
                } 
            }
            if (totalMakanan >= 1) cout << "Total Makanan : Rp." << totalMakanan << endl;

            for (size_t i = 0; i < pembayaran.size(); i++) {
                totalPembayaran += pembayaran[i].amount;
                if (pembayaran[i].amount >= 1) {
                    cout << "\nNama : " << pembayaran[i].name << endl;
                    cout << "Nominal: " << pembayaran[i].amount << endl;
                    cout << "Keterangan : " << pembayaran[i].notes << endl;
                }
            }
            if (totalPembayaran >= 1) cout << "Total Pembayaran : Rp." << totalPembayaran << endl;

            for (size_t i = 0; i < lainnya.size(); i++) {
                totalLainnya += lainnya[i].amount;
                if (lainnya[i].amount >= 1) {
                    cout << "\nNama : " << lainnya[i].name << endl;
                    cout << "Nominal: " << lainnya[i].amount << endl;
                    cout << "Keterangan : " << lainnya[i].notes << endl;
                }
            }
            if (totalLainnya >= 1) cout << "Total Hal Lain : Rp." << totalLainnya << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk kembali ke menu.";
            cin.get();
            break;
        }

        case 6: {
            clearScreen();
            cout << "================== Rekap Total ==================" << endl;
            chart(masuk, keluar);

            cout << "\n~ Pemasukkan ~" << endl;
            int totalMasuk = static_cast<int>(tabungan.size() + masaDepan.size() + kebutuhan.size() + halLain.size());
            cout << "Jumlah Transaksi Pemasukanmu : " << totalMasuk << endl;
            cout << "Nominalnya : " << pemasukkanTotal(tabungan, masaDepan, kebutuhan, halLain) << endl;

            cout << "\n~ Pengeluaran ~" << endl;
            int totalKeluar = static_cast<int>(harian.size() + makanan.size() + pembayaran.size() + lainnya.size());
            cout << "Jumlah Transaksi Pengeluaranmu : " << totalKeluar << endl;
            cout << "Nominalnya : " << pengeluaranTotal(harian, makanan, pembayaran, lainnya) << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk kembali ke menu.";
            cin.get();
            break;
        }

        case 0:
            return 0;
    }

    goto main_menu;   
}