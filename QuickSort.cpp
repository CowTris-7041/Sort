#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

int partition(vector<double> &arr, int low, int high){
	double pivot = arr[high];
	
	int i = low - 1;
	
	for(int j = low; j < high; j++){
		if(arr[j] < pivot){
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i+1], arr[high]);
	return i+1;
}

void QuickSort(vector<double> &arr, int low, int high){
	if(low < high){
		int pi = partition(arr, low, high);
		QuickSort(arr, low, pi-1);
		QuickSort(arr, pi+1, high);
	}
}

int main() {
ofstream result("QuickSort_result.csv");

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

    QuickSort(arr, 0, (int)arr.size() - 1);

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

cout << "\nDa ghi ket qua vao QuickSort_result.csv\n";

return 0;

}
