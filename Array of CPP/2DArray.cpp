#include <iostream>
#include <string>

using namespace std;

int main() {
    string arr[3][4] = { // aku bikin semua matriks ukuran 3x4
        { "Arr[0][0]", "Arr[0][1]", "Arr[0][2]", "Arr[0][3]" },
        { "Arr[1][0]", "Arr[1][1]", "Arr[1][2]", "Arr[1][3]" },
        { "Arr[2][0]", "Arr[2][1]", "Arr[2][2]", "Arr[2][3]" }
    };

    int rows = 3;
    int cols = 4;

    cout << "Rows: " << rows << ", Cols: " << cols << "\n\n";

    // Tampilkan setiap elemen dengan indeksnya
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << "arr[" << r << "][" << c << "] = " << arr[r][c] << "\n";
        }
    }

    return 0;
}