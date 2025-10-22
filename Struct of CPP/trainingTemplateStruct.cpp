#include <iostream>
#include <vector>

using namespace std;

// Buatkan struct mengenai data laptop
struct Laptop {
    string merk;
    string model;
    int ram;
    int storage;
};

int main() {
    // buatin vector buat nyimpen data laptop
    vector<Laptop> jenisLaptop;

    // buatin objek laptop pake looping seperti exampleStruct2.cpp
    cout << "Masukkan data laptop." << endl;

    for (int i = 0; i < 3; i++) {
        Laptop list;

        cout << "Merk: ";
        getline(cin, list.merk);
        cin.ignore();

        cout << "Models: ";
        getline(cin, list.model);
        cin.ignore();

        cout << "RAM (GB): ";
        cin >> list.ram;
        cin.ignore();

        cout << "Storage (GB): ";
        cin >> list.storage;
        cin.ignore();

        jenisLaptop.push_back(list);
    }

    // buatin tampilannya!
    cout << "\n\n\n-------------------------" << endl;

    for (size_t i = 0; i < jenisLaptop.size(); i++) {
        cout << "Merk: " << jenisLaptop[i].merk << endl;
        cout << "Model: " << jenisLaptop[i].model << endl;
        cout << "RAM: " << jenisLaptop[i].ram << " GB" << endl;
        cout << "Storage: " << jenisLaptop[i].storage << " GB" << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}