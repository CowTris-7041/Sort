#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

void merge(vector<double> &arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> L(n1), R(n2);

    for(int i = 0; i < n1; i++){
        L[i] = arr[left+i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = arr[mid + j + 1];
    }

    int i =0, j = 0;
    int k = left;

    while(i < n1 && j < n2){
        if(L[i] < R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<double> &arr, int left, int right){
    if(left >= right) return;

    int mid  = left + (right - left)/2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

int main() {
ofstream result("result.csv");

if (!result.is_open()) {
    cout << "Khong tao duoc file result.csv!\n";
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

    MergeSort(arr, 0, (int)arr.size() - 1);

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

cout << "\nDa ghi ket qua vao result.csv\n";

return 0;


}

