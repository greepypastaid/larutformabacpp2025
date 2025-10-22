#include <iostream>
#include <vector> // PENTING: Harus menyertakan library <vector>

int main() {
    // 1. Mendeklarasikan sebuah Vector
    std::vector<int> nilaiMahasiswa;

    // 2. Menambahkan elemen ke Vector (Ukuran Dinamis)
    // Gunakan push_back() untuk menambahkan elemen di akhir
    nilaiMahasiswa.push_back(85);
    nilaiMahasiswa.push_back(92);
    nilaiMahasiswa.push_back(78);
    nilaiMahasiswa.push_back(95);

    // 3. Mengakses elemen
    std::cout << "Nilai pertama (indeks 0): " << nilaiMahasiswa[0] << std::endl;
    std::cout << "Jumlah nilai saat ini (ukuran): " << nilaiMahasiswa.size() << std::endl;

    // 4. Mengubah elemen (sama seperti Array)
    nilaiMahasiswa[2] = 80;
    std::cout << "Nilai indeks 2 setelah diubah: " << nilaiMahasiswa[2] << std::endl;

    // 5. Iterasi (Mengulang) semua elemen menggunakan for loop
    std::cout << "\n--- Daftar Semua Nilai Mahasiswa ---" << std::endl;
    // Menggunakan .size() untuk mengetahui batas loop secara dinamis
    for (int i = 0; i < nilaiMahasiswa.size(); i++) {
        std::cout << "Nilai ke-" << i + 1 << ": " << nilaiMahasiswa[i] << std::endl;
    }

    // 6. Menghapus elemen (Opsional: Contoh penghapusan elemen terakhir)
    nilaiMahasiswa.pop_back();

    return 0;
}