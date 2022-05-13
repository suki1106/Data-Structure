#include <iostream>

using namespace std;

int Search(int begin, int end, int* arr,int target) {
	int mid = -1;
	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target == arr[mid])
			return mid;
		else if (target > arr[mid])
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

int main() {
	int n,m,num,p,target;
	int* arr;
	while (cin >> n) {
		p = 0;
		arr = new int [n] ;
		for (int i = 0; i < n; i++) {
			cin >> num;
			arr[i] = num;
			if (i != 0 && p == 0 && arr[i - 1] > arr[i])p = i;
		}
		cin >> m; // queries
		while (m--) {
			cin >> target;	
			if (target >= arr[0]) {//0~p-1
				cout << Search(0, p - 1, arr, target) << '\n';
			}
			else { // p~n-1
				cout << Search(p, n - 1, arr, target) << '\n';
			}
		}
		delete arr;
	}
}