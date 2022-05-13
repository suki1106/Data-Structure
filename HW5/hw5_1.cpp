#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
map<int,int>mp; // treeset
struct edge{
    int from;
    int des;
    int weight;
    edge(int f ,int d ,int w):from(f),des(d),weight(w){}
    edge(){}
};

struct cmp{
    bool operator()(edge&a,edge&b){
        if(a.weight != b.weight)return a.weight>b.weight;
        if(a.from != b.from) return a.from>b.from;
        if(a.des!=b.des)return a.des>b.des;
    }
};
void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}
int findRoot(int index){
    int root = index;
    while(mp[root]>0){
        root = mp[root];
    }
    return root;
}
int main(){
    int m,n;
    priority_queue<edge,vector<edge>,cmp>pq;
    priority_queue<edge,vector<edge>,cmp>pq2;
    while(cin >> m >> n){
        for(int i =0,f,s,w;i<n;i++){
            cin >> f >> s >> w;
            mp[f]=-1,mp[s]=-1;
            pq.push(edge(f,s,w));
        }

        while(!pq.empty()){
            edge e = pq.top();
            pq.pop();

            // verify
            int r1 = findRoot(e.from);
            int r2 = findRoot(e.des);

            if(r1!=r2){ // different trees, we can combine them

                if(mp[r1] <mp[r2]){
                    mp[r1]+=mp[r2];
                    mp[r2]  = r1;
                }else{
                    mp[r2]+=mp[r1];
                    mp[r1]  = r2;
                }
                if(e.from>e.des)swap(e.from,e.des);
                pq2.push(edge(e.from,e.des,e.weight));
            }

        }
        while(!pq2.empty()){
            edge e = pq2.top();
            pq2.pop();
            cout << e.from << ' ' << e.des << ' ' << e.weight << endl;
        }
        mp.clear();
    }
    return 0;
}