#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

void heapify(vector<double> &arr, int n, int i){
	int largest = i;
	int l = i*2+1;
	int r = i*2+2;
	
	if(l < n && arr[l] > arr[largest]) largest = l;
	if(r < n && arr[r] > arr[largest]) largest = r;
	if(largest != i){
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void HeapSort(vector<double> &arr){
	int n = arr.size();
	
	for(int i = n/2 - 1; i >= 0; i--){
		heapify(arr, n, i);
	}
	
	for(int i = n-1; i >= 0; i--){
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main() {
ofstream result("HeapSort_result.csv");

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

    HeapSort(arr);

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

cout << "\nDa ghi ket qua vao HeapSort_result.csv\n";

return 0;

}

