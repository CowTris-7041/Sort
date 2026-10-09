#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
ofstream result("StdSort_result.csv");

if (!result.is_open()) {
    cout << "Khong tao duoc file ket qua!\n";
    return 1;
}

result << "Test,Loai du lieu,So phan tu,Thoi gian (giay)\n";

for (int test = 1; test <= 10; test++) {
    string filename = "input/input";

    if (test < 10) filename += "0";
    filename += to_string(test) + ".txt";

    ifstream fin(filename.c_str());

    if (!fin.is_open()) {
        cout << "Khong mo duoc file: "
             << filename << '\n';
        continue;
    }

    vector<double> arr;
    double x;

    while (fin >> x) {
        arr.push_back(x);
    }

    fin.close();

    if (arr.empty()) {
        cout << "File rong: " << filename << '\n';
        continue;
    }

    string type;

    if (test == 1)
        type = "Tang dan";
    else if (test == 2)
        type = "Giam dan";
    else
        type = "Ngau nhien";

    auto start = chrono::steady_clock::now();

    sort(arr.begin(), arr.end());

    auto end = chrono::steady_clock::now();

    double elapsed =
        chrono::duration<double>(end - start).count();

    result << test << ","
           << type << ","
           << arr.size() << ","
           << fixed << setprecision(6)
           << elapsed << '\n';

    cout << "Test " << test
         << " (" << type << "): "
         << arr.size() << " phan tu, "
         << elapsed << " giay\n";
}

result.close();

cout << "\nDa ghi ket qua vao StdSort_result.csv\n";

return 0;

}

