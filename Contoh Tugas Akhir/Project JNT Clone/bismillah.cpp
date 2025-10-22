#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <map>
#include <set>
#include <limits>

using namespace std;

struct Edge {
    string to;
    float jarakKota;
};

struct Node {
    string resi;
    string namaKirim, alamatKirim, hpKirim, namaTujuan, alamatTujuan, kotaTujuan, hpTujuan, namaBarang, jenisBarang, jenisJasa, statusKirim;
    float beratBarang, biayaKirim; 
    int itemID;
    time_t waktuKirim;
    float estimasiKirim;
    Node* next;
};

class Graph {
    map<string, vector<Edge>> adjList;

public:
    void addEdge(const string& from, const string& to, float jarakKota) {
        adjList[from].push_back(Edge{to, jarakKota});
        adjList[to].push_back(Edge{from, jarakKota}); // For bidirectional graph
    }

    void loadGraphFromFile(const string& filename) {
        ifstream inFile(filename);
        string line;

        if (!inFile.is_open()) {
            cerr << "Gagal Membuka File" << filename << endl;
            return;
        }

        while (getline(inFile, line)) {
            stringstream ss(line);
            string from, to, dist;
            getline(ss, from, ',');
            getline(ss, to, ',');
            getline(ss, dist);
            float jarakKota = stof(dist);
            addEdge(from, to, jarakKota);
        }
        inFile.close();
    }

    float dijkstra(const string& source, const string& tujuan) {
        if (adjList.find(source) == adjList.end() || adjList.find(tujuan) == adjList.end()) {
            cout << "Kota tidak ditemukan!" << endl;
            return -1; // Indicating an error or non-existence of path
        }

        map<string, float> distances;
        map<string, string> predecessors;
        set<pair<float, string>> queue;

        for (const auto& node : adjList) {
            distances[node.first] = numeric_limits<float>::max();
        }

        distances[source] = 0;
        queue.insert({0, source});

        while (!queue.empty()) {
            string current = queue.begin()->second;
            queue.erase(queue.begin());

            for (const auto& edge : adjList[current]) {
                float dist = distances[current] + edge.jarakKota;
                if (dist < distances[edge.to]) {
                    queue.erase({distances[edge.to], edge.to});
                    distances[edge.to] = dist;
                    predecessors[edge.to] = current;
                    queue.insert({dist, edge.to});
                }
            }
        }

        printRoute(predecessors, tujuan); // Optionally print the route
        return distances[tujuan]; // Return the total jarakKota to the tujuan
    }

    void printRoute(const map<string, string>& predecessors, const string& tujuan) {
        stack<string> path;
        string langkah = tujuan;
 
        if (predecessors.find(langkah) == predecessors.end()) {
            cout << "Tidak ditemukan rute!" << endl;
            return;
        }

        path.push(langkah);
        while (predecessors.find(langkah) != predecessors.end()) {
            langkah = predecessors.at(langkah);
            path.push(langkah);
        }

        cout << "Rute yang akan ditempuh" << tujuan << ": ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
    }
};

struct singleLinkedlist {
    Node* head = NULL;
    Node* tail = NULL;

    Graph kota;

    void add(string nKirim, string alKirim, string newhpKirim, string nTuju, string alTuju, string kTuju, string hpTuju, string nBarang, string jenBarang, float brtBarang, string jenJasa, float jarak) {
        auto now = chrono::system_clock::now();

        Node* tmp = new Node();
        tmp->waktuKirim = chrono::system_clock::to_time_t(now);
        tmp->itemID = count();
        tmp->resi = resiRandom(6);
        tmp->namaKirim = nKirim;
        tmp->alamatKirim = alKirim;
        tmp->hpKirim = newhpKirim;
        tmp->namaTujuan = nTuju;
        tmp->alamatTujuan = alTuju;
        tmp->kotaTujuan = kTuju;
        tmp->hpTujuan = hpTuju;
        tmp->namaBarang = nBarang;
        tmp->jenisBarang = jenBarang;
        tmp->beratBarang = brtBarang;
        tmp->jenisJasa = jenJasa;
        tmp->biayaKirim = hargaKirim(jenJasa, brtBarang, jarak);
        tmp->estimasiKirim = estiKirim(jenJasa, jarak);
        tmp->next = NULL;

        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }

        cout << "\t\t\t============ Rangkuman Pengiriman ============" << endl;
        cout << "\n==========================================================" << endl;
        cout << "Item ID : " << tmp->itemID << endl;
        cout << "Nomor Resi : " << tmp->resi << endl;
        cout << "==========================================================" << endl;
        cout << "Nama Pengirim : " << tmp->namaKirim << endl;
        cout << "Alamat Pengirim : " << tmp->alamatKirim << endl;
        cout << "Nomor HP Pengirim : " << tmp->hpKirim << endl;
        cout << "==========================================================" << endl;
        cout << "Nama Tujuan : " << tmp->namaTujuan << endl;
        cout << "Kota Tujuan : " << tmp->kotaTujuan << endl;
        cout << "Nomor HP Tujuan : " << tmp->hpTujuan << endl;
        cout << "==========================================================" << endl;
        cout << "Nama Barang : " << tmp->namaBarang << endl;
        cout << "Berat Barang : " << tmp->beratBarang << endl;
        cout << "Jenis Jasa : " << tmp->jenisJasa << "\n";
        cout << "==========================================================" << endl;
        cout << "\n================== Rangkuman Pengiriman ==================" << endl;
        cout << "Biaya Pengiriman : " << tmp->biayaKirim << endl;
        cout << "Estimasi lama Kirim : " << tmp->estimasiKirim <<"-"<<tmp->estimasiKirim+1 <<" Hari" << endl;
        cout << "==========================================================\n" << endl;
    }

    int estiKirim(string jenisJasa, float jarak){
        int esti;
        if (jarak < 100){
            if(jenisJasa == "Hemart"){
                esti=2;}
            else if(jenisJasa == "Kentjang"){
                esti=1;}
            else if(jenisJasa == "Cebrut"){
                esti=0;}
        }
        else if (jarak < 500){
            if(jenisJasa == "Hemart"){
                esti=3;}
            else if(jenisJasa == "Kentjang"){
                esti=2;}
            else if(jenisJasa == "Cebrut"){
                esti=1;}
        }
        else if (jarak > 500){
            if(jenisJasa == "Hemart"){
                esti=5;}
            else if(jenisJasa == "Kentjang"){
                esti=3;}
            else if(jenisJasa == "Cebrut"){
                esti=1;}
        }
        return esti;
    }

    string statusPengiriman(const string& jenisJasa, const time_t waktuKirim) {
    auto now = chrono::system_clock::now();
    auto selisihWaktu = chrono::duration_cast<chrono::hours>(now - chrono::system_clock::from_time_t(waktuKirim)).count();

        if (jenisJasa == "Hemart") {
            if (selisihWaktu < 5) return "Barang sedang disiapkan";
            else if (selisihWaktu < 18) return "Barang sampai di Gudang Pusat";
            else if (selisihWaktu < 48) return "Barang sedang dikirim ke Gudang Kota Tujuan";
            else if (selisihWaktu < 72) return "Barang sudah sampai di Gudang Terdekat Tujuan";
            else if (selisihWaktu < 87) return "Barang sedang dikirim ke alamat";
            else if (selisihWaktu > 92) return "Barang telah sampai tujuan";
        } else if (jenisJasa == "Kentjang") {
            if (selisihWaktu < 5) return "Barang sedang disiapkan";
            else if (selisihWaktu < 10) return "Barang sampai di Gudang Pusat";
            else if (selisihWaktu < 48) return "Barang sedang dikirim ke Gudang Kota Tujuan";
            else if (selisihWaktu < 60) return "Barang sudah sampai di Gudang Terdekat Tujuan";
            else if (selisihWaktu < 70) return "Barang sedang dikirim ke alamat";
            else if (selisihWaktu > 72) return "Barang telah sampai tujuan";
        } else if (jenisJasa == "Cebrut (Cepat Brutal)") {
            if (selisihWaktu < 5) return "Barang sedang disiapkan";
            else if (selisihWaktu < 20) return "Barang sampai di Gudang Pusat";
            else if (selisihWaktu < 21) return "Barang sedang dikirim ke Gudang Kota Tujuan";
            else if (selisihWaktu < 24) return "Barang sudah sampai di Gudang Terdekat Tujuan";
            else if (selisihWaktu < 25) return "Barang sedang dikirim ke alamat";
            else if (selisihWaktu > 26) return "Barang telah sampai tujuan";
        } 
    return "Status pengiriman tidak diketahui";
    }

    int count() {
        Node* temp = head;
        int count = 0;
        while (temp != nullptr) {
            if (temp->itemID > count) 
            count = temp->itemID;
            temp = temp->next;
        }
        return count+1;
    }

    string resiRandom(int panjangResi) {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        string resi;
        srand(time(0));
        resi = "SL";
        for (int i = 0; i < panjangResi; i++) {
            resi += chars[rand() % chars.length()];
        }
        return resi;
    }

    double hargaKirim(string jenisJasa, float beratBarang, float jarak) {
        double hargaKirim;
        if (beratBarang < 1) {
            if (jenisJasa == "Hemart") {
                hargaKirim = 100 * jarak * (110 / 100);
            } else if (jenisJasa == "Kentjang") {
                hargaKirim = 105 * jarak * (120 / 100);
            } else if (jenisJasa == "Cebrut (Cepat Brutal)") {
                hargaKirim = 110 * jarak * (160 / 100);
            }
        } else if (beratBarang >= 1 && beratBarang <= 3) {
            if (jenisJasa == "Hemart") {
                hargaKirim = 105 * jarak * (130 / 100);
            } else if (jenisJasa == "Kentjang") {
                hargaKirim = 110 * jarak * (150 / 100);
            } else if (jenisJasa == "Cebrut (Cepat Brutal)") {
                hargaKirim = 115 * jarak * (170 / 100);
            }
        } else if (beratBarang > 5) {
            if (jenisJasa == "Hemart") {
                hargaKirim = 110 * jarak * (110 / 100);
            } else if (jenisJasa == "Kentjang") {
                hargaKirim = 125 * jarak * (120 / 100);
            } else if (jenisJasa == "Cebrut (Cepat Brutal)") {
                hargaKirim = 125 * jarak * (160 / 100);
            }
        }
        return hargaKirim;
    }

    void insertionSort(string sortBy) {
        if (head == NULL || head->next == NULL) return;
        Node* sorted = NULL;
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            if (sorted == NULL || isLessThan(current, sorted, sortBy)) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* sortedCurrent = sorted;
                while (sortedCurrent->next != NULL && !isLessThan(current, sortedCurrent->next, sortBy)) {
                    sortedCurrent = sortedCurrent->next;
                }
                current->next = sortedCurrent->next;
                sortedCurrent->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    bool isLessThan(Node* a, Node* b, string sortBy) {
        if (sortBy == "kotaTujuan") {
            if (a->kotaTujuan == b->kotaTujuan) return a->waktuKirim > b->waktuKirim;
            return a->kotaTujuan < b->kotaTujuan;
        } else if (sortBy == "jenisJasa") {
            if (a->jenisJasa == b->jenisJasa) return a->waktuKirim > b->waktuKirim;
            return a->jenisJasa > b->jenisJasa;
        } else if (sortBy == "jenisBarang") {
            if (a->jenisBarang == b->jenisBarang) return a->waktuKirim > b->waktuKirim;
            return a->jenisBarang < b->jenisBarang;
        } else if (sortBy == "itemID") {
            if (a->itemID == b->itemID) return a->waktuKirim > b->waktuKirim;
            return a->itemID < b->itemID;
        }
        return false;
    }

    void editData(const string& mark, const string& nKirim, const string& alKirim, const string& newhpKirim, const string& nTuju, const string& alTuju, const string& kTuju, const string& hpTuju, const string& nBarang, const string& jenBarang, float brtBarang, const string& jenJasa, float jarak) {
        Node* current = head;
        bool found = false;
        while (current != NULL) {
            if (current->resi == mark) {
                current->namaKirim = nKirim;
                current->alamatKirim = alKirim;
                current->hpKirim = newhpKirim;
                current->namaTujuan = nTuju;
                current->alamatTujuan = alTuju;
                current->kotaTujuan = kTuju;
                current->hpTujuan = hpTuju;
                current->namaBarang = nBarang;
                current->jenisBarang = jenBarang;
                current->beratBarang = brtBarang;
                current->jenisJasa = jenJasa;
                current->biayaKirim = hargaKirim(jenJasa, brtBarang, jarak);
                current->estimasiKirim = estiKirim(jenJasa, jarak);
                found = true;

                system("cls");
                cout << "\t\t\t============ Rangkuman Pengiriman ============" << endl;
                cout << "\n==========================================================" << endl;
                cout << "Item ID : " << current->itemID << endl;
                cout << "Nomor Resi : " << current->resi << endl;
                cout << "==========================================================" << endl;
                cout << "Nama Pengirim : " << current->namaKirim << endl;
                cout << "Alamat Pengirim : " << current->alamatKirim << endl;
                cout << "Nomor HP Pengirim : " << current->hpKirim << endl;
                cout << "==========================================================" << endl;
                cout << "Nama Tujuan : " << current->namaTujuan << endl;
                cout << "Kota Tujuan : " << current->kotaTujuan << endl;
                cout << "Nomor HP Tujuan : " << current->hpTujuan << endl;
                cout << "==========================================================" << endl;
                cout << "Nama Barang : " << current->namaBarang << endl;
                cout << "Berat Barang : " << current->beratBarang << endl;
                cout << "Jenis Jasa : " << current->jenisJasa << "\n";
                cout << "==========================================================" << endl;
                cout << "\n================== Rangkuman Pengiriman ==================" << endl;
                cout << "Biaya Pengiriman : " << current->biayaKirim << endl;
                cout << "Estimasi lama Kirim : " << current->estimasiKirim <<"-"<<current->estimasiKirim+1 <<" Hari" << endl;
                cout << "==========================================================\n" << endl;
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Data tidak ditemukan dari resi yang diberikan." << endl;
        }
    }

    void DeleteSpecified(string mark) {
        if (head == NULL) {
            cout << "List Masih Kosong" << endl;
            return;
        }

        Node* current = head;
        Node* prev = NULL;

        while (current != NULL && current->resi != mark) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << "Data Resi Tidak Ditemukan" << endl;
        } else {
            if (prev == NULL) {
                head = head->next;
                if (head == NULL) {
                    tail = NULL; 
                }
            } else {
                prev->next = current->next;
                if (prev->next == NULL) {
                    tail = prev;
                }
            }
            delete current; 
            cout << "Data berhasil dihapus!" << endl;
        }
    }

    void search(string searchKey, string searchValue) {
        Node* current = head;
        bool found = false;

        // Panggil statusKirim

        cout << "\nHasil Pencarianmu :" << endl;
        while (current != nullptr) {
            bool matchFound = false;
            if (searchKey == "resi" && current->resi == searchValue) {
                matchFound = true;
            } else if (searchKey == "itemID" && to_string(current->itemID) == searchValue) {
                matchFound = true;
            } else if (searchKey == "namaKirim" && current->namaKirim == searchValue) {
                matchFound = true;
            } else if (searchKey == "namaTujuan" && current->namaTujuan == searchValue) {
                matchFound = true;
            } else if (searchKey == "kotaTujuan" && current->kotaTujuan == searchValue) {
                matchFound = true;
            } else if (searchKey == "namaBarang" && current->namaBarang == searchValue) {
                matchFound = true;
            }

            // Cari status
            string status = statusPengiriman(current->jenisJasa, current->waktuKirim);

            if (matchFound) {
                found = true;
                cout << "==========================================================" << endl;
                cout << "Item ID : " << current->itemID << "\n";
                cout << "Nomor Resi : " << current->resi << "\n";
                cout << "Waktu Kirim : " << ctime(&(current->waktuKirim));
                cout << "\n==========================================================" << endl;
                cout << "Nama Pengirim : " << current->namaKirim << "\n";
                cout << "Alamat Pengirim : " << current->alamatKirim << "\n";
                cout << "Nomor HP Pengirim : " << current->hpKirim << "\n";
                cout << "==========================================================" << endl;
                cout << "Nama Tujuan : " << current->namaTujuan << "\n";
                cout << "Alamat Tujuan : " << current->alamatTujuan << "\n";
                cout << "Kota Tujuan : " << current->kotaTujuan << "\n";
                cout << "Nomor HP Tujuan : " << current->hpTujuan << "\n";
                cout << "==========================================================" << endl;
                cout << "Nama Barang : " << current->namaBarang << "\n";
                cout << "Jenis Barang : " << current->jenisBarang << "\n";
                cout << "Berat Barang : " << current->beratBarang << " kg\n";
                cout << "Jenis Jasa : " << current->jenisJasa << "\n";
                cout << "================== Rangkuman Pengiriman ==================" << endl;
                cout << "Biaya Pengiriman : " << current->biayaKirim << endl;
                cout << "Estimasi lama Kirim : " << current->estimasiKirim <<"-"<<current->estimasiKirim+1 <<" Hari" << endl;
                cout << "Status Pengiriman : " << status << endl;
                cout << "==========================================================\n" << endl;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Data tidak ditemukan!" << endl;
        }
    }

    void print() {
        Node* current = head;
    
        cout << "\t\t\t============ Data Pengiriman ============" << endl;
        while (current != NULL) {
            // Cari status
            string status = statusPengiriman(current->jenisJasa, current->waktuKirim);

            cout << "\n==========================================================" << endl;
            cout << "Item ID : " << current->itemID << endl;
            cout << "Nomor Resi : " << current->resi << endl;
            cout << "Waktu Kirim : " << ctime(&(current->waktuKirim));
            cout << "==========================================================" << endl;
            cout << "Nama Pengirim : " << current->namaKirim << endl;
            cout << "Alamat Pengirim : " << current->alamatKirim << endl;
            cout << "Nomor HP Pengirim : " << current->hpKirim << endl;
            cout << "==========================================================" << endl;
            cout << "Nama Tujuan : " << current->namaTujuan << endl;
            cout << "Alamat Tujuan : " << current->alamatTujuan << endl;
            cout << "Kota Tujuan : " << current->kotaTujuan << endl;
            cout << "Nomor HP Tujuan : " << current->hpTujuan << endl;
            cout << "==========================================================" << endl;
            cout << "Nama Barang : " << current->namaBarang << endl;
            cout << "Jenis Barang : " << current->jenisBarang << endl;
            cout << "Berat Barang : " << current->beratBarang << endl;
            cout << "Jenis Jasa : " << current->jenisJasa << "\n";
            cout << "==========================================================" << endl;
            cout << "\n================== Rangkuman Pengiriman ==================" << endl;
            cout << "Biaya Pengiriman : " << current->biayaKirim << endl;
            cout << "Estimasi lama Kirim : " << current->estimasiKirim <<"-"<<current->estimasiKirim+1 <<" Hari" << endl;
            cout << "Status Pengiriman : " << status << endl;
            cout << "==========================================================" << endl;
            current = current->next;
        }
        cout << endl;
    }

    void saveToFile() {
        ofstream outFile("database.txt", ios::out | ios::trunc);
        if (!outFile.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            outFile << fixed << setprecision(2); // Ensure correct precision for float values
            outFile << current->itemID << ","
                    << current->resi << ","
                    << current->namaKirim << ","
                    << current->alamatKirim << ","
                    << current->hpKirim << ","
                    << current->namaTujuan << ","
                    << current->alamatTujuan << ","
                    << current->kotaTujuan << ","
                    << current->hpTujuan << ","
                    << current->namaBarang << ","
                    << current->jenisBarang << ","
                    << current->beratBarang << ","
                    << current->jenisJasa << ","
                    << current->biayaKirim << ","                
                    << current->estimasiKirim << ","
                    << current->waktuKirim << endl;
            if (outFile.fail()) {
                cerr << "Error writing to file." << endl;
                break;
            }
            current = current->next;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("database.txt");
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string itemID, resi, namaKirim, alamatKirim, hpKirim, namaTujuan, alamatTujuan, kotaTujuan, hpTujuan, namaBarang, jenisBarang, beratBarang, jenisJasa, biayaKirim, estimasiKirim, waktuKirimStr;
            getline(ss, itemID, ',');
            getline(ss, resi, ',');
            getline(ss, namaKirim, ',');
            getline(ss, alamatKirim, ',');
            getline(ss, hpKirim, ',');
            getline(ss, namaTujuan, ',');
            getline(ss, alamatTujuan, ',');
            getline(ss, kotaTujuan, ',');
            getline(ss, hpTujuan, ',');
            getline(ss, namaBarang, ',');
            getline(ss, jenisBarang, ',');
            getline(ss, beratBarang, ',');
            getline(ss, jenisJasa, ',');
            getline(ss, biayaKirim, ',');
            getline(ss, estimasiKirim, ',');
            getline(ss, waktuKirimStr);

            if (head == nullptr) {
                head = new Node();
                tail = head;
            } else {
                tail->next = new Node();
                tail = tail->next;
            }
            tail->itemID = stof(itemID);
            tail->resi = resi;
            tail->namaKirim = namaKirim;
            tail->alamatKirim = alamatKirim;
            tail->hpKirim = hpKirim;
            tail->namaTujuan = namaTujuan;
            tail->alamatTujuan = alamatTujuan;
            tail->kotaTujuan = kotaTujuan;
            tail->hpTujuan = hpTujuan;
            tail->namaBarang = namaBarang;
            tail->jenisBarang = jenisBarang;
            tail->beratBarang = stof(beratBarang);
            tail->jenisJasa = jenisJasa;
            tail->biayaKirim = stof(biayaKirim);
            tail->estimasiKirim = stoi(estimasiKirim);
            tail->waktuKirim = static_cast<time_t>(stoll(waktuKirimStr));
            tail->next = nullptr;
        }
        inFile.close();
    }
};

int main() {
    singleLinkedlist ls;
    Graph kota;

    // Defining item
    string namaKirim, alamatKirim, hpKirim, namaTujuan, alamatTujuan, kotaTujuan, hpTujuan, namaBarang, jenisBarang, jenisJasa, ID;
    float beratBarang, jarak;

    vector<string> menu_app = {
        "\t\t1. Login Admin",
        "\t\t2. Lihat Data",
        "\t\t3. Cari Data",
        "\t\t4. Keluar"
    };

    vector<string> menu_ADM = {
        "\t\tHalo Admin, silahkan pilih Menu !",
        "\t\t1. Tambah Data",
        "\t\t2. Lihat Data",
        "\t\t3. Cari Data",
        "\t\t4. Ubah Data",
        "\t\t5. Hapus Data",
        "\t\t6. Keluar"
    };

    vector<string> menu_tambah = {
        "1. Tambah lagi",
        "2. Exit"
    };

    vector<string> menu_jasa = {
        "\t\t1. Hemart",
        "\t\t2. Kentjang",
        "\t\t3. Cebrut (Cepat Brutal)"
    };

    bool app_run = true;
    bool ADM_run = false;
    bool jasa_run = false;
    string username = "admin", password = "admin", in_user, in_pass;
    int i, pilih_app, pilih_admin, pilih_jasa;

    // Load Data from txt file
    ls.loadFromFile();
    kota.loadGraphFromFile("databaseKota.txt");

    while (app_run) {
        system("cls");
        cout << "\n\n\t\t\tSI LAMBAT LOGISTICS" << endl;
        cout << "\t\tHalo, Silahkan pilih menu dibawah ini!" << endl;

        for (i = 0; i < menu_app.size(); i++) { //okeh
            cout << menu_app[i] << endl;
        }
        cout << "\t\tOpsi Kamu : ";
        cin >> pilih_app;

        system("cls");
        switch (pilih_app) {
            case 1: {
                cout << "\n\n\t\t\tLogin Admin" << endl;
                cout << "\t\tMasukan Username: ";
                cin >> in_user;
                cout << "\n\t\tMasukan Password: ";
                cin >> in_pass;
                if (in_user == username && in_pass == password) {
                    app_run = false;
                    ADM_run = true;

                    while (ADM_run) {
                    system("cls");
                        for (i = 0; i < menu_ADM.size(); i++) {
                            cout << menu_ADM[i] << endl;
                        }
                        cout << "\t\tInput : ";
                        cin >> pilih_admin;

                        system("cls");
                        switch (pilih_admin) {
                        case 1: {
                            bool run_tambah = true;

                            while (run_tambah == true) {
                                system("cls");
                                cout << "=========== PENGISIAN DATA PENGIRIM ===========" << endl;
                                cout << "Masukan Nama Pengirim : ";
                                cin.ignore();
                                getline(cin, namaKirim);
                                cout << "Masukan Nomor HP Pengirim : ";
                                cin >> hpKirim;
                                cout << "Masukan Alamat Pengirim (Opsional) : ";
                                cin.ignore();
                                getline(cin, alamatKirim);

                                cout << "\n=========== PENGISIAN DATA TUJUAN ===========" << endl;
                                cout << "Masukan Nama Tujuan : ";
                                getline(cin, namaTujuan);
                                cout << "Masukan Nomor HP Tujuan : ";
                                cin >> hpTujuan;
                                cout << "Masukan Alamat Tujuan : ";
                                cin.ignore();
                                getline(cin, alamatTujuan);
                                cout << "Masukan Kota Tujuan : ";
                                getline(cin, kotaTujuan);

                                // Hitung Jarak Kota dari Gudang Semarang
                                jarak = kota.dijkstra("Semarang", kotaTujuan);

                                cout << "\n=========== PENGISIAN DATA BARANG ===========" << endl;
                                cout << "Masukan Nama Barang : ";
                                getline(cin, namaBarang);
                                cout << "Masukan Jenis Barang (1. Pecah Belah; 2. Biasa) : ";
                                cin >> jenisBarang;

                                if (jenisBarang == "1") {
                                    jenisBarang = "Pecah Belah";
                                } else if (jenisBarang == "2") {
                                    jenisBarang = "Biasa";
                                }
                                cout << "Masukan Berat Barang : ";
                                cin >> beratBarang;

                                cout << "Pilih Jenis Jasa : " << endl;
                                cout << "A. Hemart (Estimasi 4 Hari) " << endl;
                                cout << "B. Kentjang (Estimasi 2-3 Hari)" << endl;
                                cout << "C. Cebrut (Cepat Brutal) (Estimasi 1-2 Hari)" << endl;
                                cout << "Input : ";
                                cin >> jenisJasa;

                                if (jenisJasa == "A") {
                                    jenisJasa = "Hemart";
                                } else if (jenisJasa == "B") {
                                    jenisJasa = "Kentjang";
                                } else if (jenisJasa == "C") {
                                    jenisJasa = "Cebrut (Cepat Brutal)";
                                } else {
                                    cout << "Input Salah" << endl;
                                }

                                ls.add(namaKirim, alamatKirim, hpKirim, namaTujuan, alamatTujuan, kotaTujuan, hpTujuan, namaBarang, jenisBarang, beratBarang, jenisJasa, jarak);
                                ls.saveToFile();
                                run_tambah = false;

                                bool tambah_run = true;
                                int pilih_tambah;
                                cout << "Tambah data lagi??" << endl;
                                while (tambah_run) {
                                    for (int j = 0; j < menu_tambah.size(); j++) {
                                        cout << menu_tambah[j] << endl;
                                    }
                                    cout << "Input : ";
                                    cin >> pilih_tambah;

                                    if (pilih_tambah == 1) {
                                        tambah_run = false;
                                        run_tambah = true;
                                    } else if (pilih_tambah == 2) {
                                        tambah_run = false;
                                        run_tambah = false;
                                        system("cls");
                                        ADM_run = true;
                                    }
                                }
                            }
                        break;
                        }

                        case 2: {
                            int count = 2;
                            char next;

                            system("cls");
                            cin.ignore();
                            ls.insertionSort("ID");
                            ls.print();

                            do {
                                cout << "Ketik O untuk Sorting data dari Jenis Jasa, Item ID, Kota Tujuan, Jenis Barang" << endl;
                                next = getch();

                                if (count == 1) {
                                    system("cls");
                                    cout << "\t\t\t\t   Sort By ItemID " << endl;
                                    ls.insertionSort("ID");
                                    ls.print();
                                } else if (count == 2) {
                                    system("cls");
                                    cout << "\t\t\t\t   Sort By Jenis Jasa" << endl;
                                    ls.insertionSort("jenisJasa");
                                    ls.print();
                                } else if (count == 3) {
                                    system("cls");
                                    cout << "\t\t\t\t   Sort By Kota Tujuan" << endl;
                                    ls.insertionSort("kotaTujuan");
                                    ls.print();
                                } else if (count == 4) {
                                    count = 1;
                                    system("cls");
                                    cout << "\t\t\t\t   Sort By Jenis Barang" << endl;
                                    ls.insertionSort("jenisBarang");
                                    ls.print();
                                }
                                count++;
                            } while (next == 'O' || next == 'o');
                        break;
                        }

                        case 3: {
                            int inKey;
                            string searchKey, searchValue;
                            cout << "Cari data berdasarkan\n";
                            cout << "1. Resi\n";
                            cout << "2. ItemID\n";
                            cout << "3. Nama Pengirim\n";
                            cout << "4. Nama Tujuan\n";
                            cout << "5. Kota Tujuan\n";
                            cout << "6. Nama Barang\n";
                            cout << "Masukan Variabel Yang Ingin Anda Cari: ";
                            cin >> inKey;

                            if (inKey == 1) {
                                searchKey = "resi";
                            } else if (inKey == 2) {
                                searchKey = "itemID";
                            } else if (inKey == 3) {
                                searchKey = "namaKirim";
                            } else if (inKey == 4) {
                                searchKey = "namaTujuan";
                            } else if (inKey == 5) {
                                searchKey = "kotaTujuan";
                            } else if (inKey == 6) {
                                searchKey = "namaBarang";
                            }
                            cout << "Masukan Kata Kunci Yang Ingin Anda Cari: " << endl;
                            cout << "Masukkan " << searchKey << ": ";
                            cin.ignore();
                            getline(cin, searchValue);
                            system("cls");
                            cout << "Kamu mencari : " << searchValue << endl;
                            ls.search(searchKey, searchValue);
                            cout << "Ketik Apapun Untuk Kembali ke Menu";
                            cin.ignore();
                        }
                        break;

                        case 4: {
                            bool run_ganti = true;
                            string mark;
                            cout << "Masukan Resi Dari Data Yang Ingin Diedit : ";
                            cin >> mark;

                            while (run_ganti == true) {
                                system("cls");
                                cout << "=========== PENGISIAN DATA PENGIRIM ===========" << endl;
                                cout << "Masukan Nama Pengirim : ";
                                cin.ignore();
                                getline(cin, namaKirim);
                                cout << "Masukan Nomor HP Pengirim : ";
                                cin >> hpKirim;
                                cout << "Masukan Alamat Pengirim (Opsional) : ";
                                cin.ignore();
                                getline(cin, alamatKirim);

                                cout << "\n=========== PENGISIAN DATA TUJUAN ===========" << endl;
                                cout << "Masukan Nama Tujuan : ";
                                getline(cin, namaTujuan);
                                cout << "Masukan Nomor HP Tujuan : ";
                                cin >> hpTujuan;
                                cout << "Masukan Alamat Tujuan : ";
                                cin.ignore();
                                getline(cin, alamatTujuan);
                                cout << "Masukan Kota Tujuan : ";
                                getline(cin, kotaTujuan);

                                // Hitung Jarak Kota dari Gudang Semarang
                                jarak = kota.dijkstra("Semarang", kotaTujuan);

                                cout << "\n=========== PENGISIAN DATA BARANG ===========" << endl;
                                cout << "Masukan Nama Barang : ";
                                getline(cin, namaBarang);
                                cout << "Masukan Jenis Barang (1. Pecah Belah; 2. Biasa) : ";
                                cin >> jenisBarang;

                                if (jenisBarang == "1") {
                                    jenisBarang = "Pecah Belah";
                                } else if (jenisBarang == "2") {
                                    jenisBarang = "Biasa";
                                }
                                cout << "Masukan Berat Barang : ";
                                cin >> beratBarang;

                                cout << "Pilih Jenis Jasa : " << endl;
                                cout << "A. Hemart (Estimasi 4 Hari) " << endl;
                                cout << "B. Kentjang (Estimasi 2-3 Hari)" << endl;
                                cout << "C. Cebrut (Cepat Brutal) (Estimasi 1-2 Hari)" << endl;
                                cout << "Input : ";
                                cin >> jenisJasa;

                                if (jenisJasa == "A") {
                                    jenisJasa = "Hemart";
                                } else if (jenisJasa == "B") {
                                    jenisJasa = "Kentjang";
                                } else if (jenisJasa == "C") {
                                    jenisJasa = "Cebrut (Cepat Brutal)";
                                } else {
                                    cout << "Input Salah" << endl;
                                }
                                
                                ls.editData(mark, namaKirim, alamatKirim, hpKirim, namaTujuan, alamatTujuan, kotaTujuan, hpTujuan, namaBarang, jenisBarang, beratBarang, jenisJasa, jarak);
                                cin.ignore();
                                ls.saveToFile();

                                run_ganti = false;
                            }
                        break;
                        }

                        case 5: {
                            string mark;
                            cout << "Masukan Resi Dari Data Yang Ingin Dihapus: ";
                            cin >> mark;
                            ls.DeleteSpecified(mark);
                            ls.saveToFile();
                            cin.ignore();

                            cout << "Tekan apapun untuk kembali ke menu awal!" << endl;
                            cin.ignore();
                        }
                        break;

                        case 6: {
                            ADM_run = false;
                            app_run = true;
                        
                        break;
                        }
                        }
                    }
                }
            }
            break;

            case 2:{
                system("cls");
                cin.ignore();
                ls.print();
                cout << "Ketik Apapun Untuk Kembali ke Menu! ";
                cin.ignore();
            }
            break;

            case 3:{
                system("cls");
                string searchKey = "resi";
                string searchValue;
                cout << "Masukan Resi Barang Yang Ingin Anda Cari: ";
                cin >> searchValue;
                ls.search(searchKey, searchValue);
                cout << "Ketik Apapun Untuk Kembali ke Menu";
                cin.ignore();
                cin.ignore();
            }
            break;

            case 4:{
                app_run = false;
            }
        
        }
    }
    return 0;
}