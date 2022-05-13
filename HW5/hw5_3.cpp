#include <iostream>
#include <map>
using namespace std;

int main() {
    int n, tar;
    int* arr;
    map<int, int> mp;
    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++)cin >> arr[i];
    while (cin >> tar) {
        for (int i = 0; i < n; i++) {
            if (mp.find(arr[i]) != mp.end()) {
                cout << mp[arr[i]] << ' ' << arr[i] << '\n';
                break;
            }
            else {
                if (tar - arr[i] > 0)mp[tar - arr[i]] = arr[i];
            }
        }
        mp.clear();
    }
    delete arr;
    return 0;
}