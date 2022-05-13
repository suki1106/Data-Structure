#include <iostream>

using namespace std;
/*
void swap(int &a,int &b){
    int temp = a;
    a = b;
    b =temp;
}
int Partition(int b,int e ,int * ptr){
    int pivot = ptr[e];
    int l =  b-1; // record last index which less than pivot
    for(int i = b ; i<e;i++){
        if(ptr[i] <= pivot){
            ++l;
            swap(ptr[l],ptr[i]);
        }
    }
    ++l;
    swap(ptr[e],ptr[l]);
    return l;
}
void QuickSort(int b ,int e ,int*ptr){
    if(b<e){
        int d  = Partition(b,e,ptr);

        QuickSort(b,d-1,ptr);
        QuickSort(d+1,e,ptr);    
    }
}*/
void Merge(int b,int e ,int * ptr){
    int m = (b+e)/2;
    int* t1 = new int [m-b+1];
    int* t2 = new int [e-m];
    for(int i = b ; i <=m;i++)
        t1[i-b] = ptr[i];
    for(int i = m+1;i <= e;i++)
        t2[i-m-1] = ptr[i];
    int l = 0 ,r=0,index = b;
    while(l < m-b+1 && r < e-m){
        if(t1[l] > t2[r]){
            ptr[index] = t2[r];
            ++r;
        }else{
            ptr[index] = t1[l];
            ++l;
        }
        ++index;
    }
    while(l<m-b+1){
        ptr[index] = t1[l];
        ++index,++l;
    }
    while(r<e-m){
        ptr[index] = t2[r];
        ++r,++index;
    }
    delete t1;
    delete t2;
}
void MergeSort(int b,int e ,int * ptr){
    if(b<e){
        int m = (b+e)/2;
        MergeSort(b,m,ptr);
        MergeSort(m+1,e,ptr);
        Merge(b,e,ptr);
    }
}
int main(){
    int n,size;
    int*ptr;
    cin >> n;
    while(n--){
        cin >> size;
        ptr = new int [size];
        for(int i = 0 ; i<size;i++)
            cin >> ptr[i];
        MergeSort(0,size-1,ptr);
        for(int i = 0 ; i<size-1;i++)
            cout << ptr[i] << " ";
        cout << ptr[size-1] << endl;
        delete ptr;
    }
    return 0;
}