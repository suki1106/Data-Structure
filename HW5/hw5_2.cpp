#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node{
    int index;
    int weight;
    vector<node>n; // neighbor
    bool findShortest = false;
    node(int i ,int w):index(i),weight(w){}
    node(){findShortest = false;}
};

int main(){
    int m,n,start;
    while(cin >> m >> n){
        node* nodes = new node[m+1];
        int*table = new int [m+1];
        for(int i = 1,f,d,w;i<=n;i++){
            cin >> f >> d >> w;
            nodes[f].n.push_back(node(d,w));
        }
        for(int i = 1;i<=m;i++)table[i]=0x7fffffff;


        cin >> start;

        table[start]=0;
 
        while(1){
            bool flag = false;
            int min=0x7fffffff,loc=1;
            for(int i =1;i<=m;i++){
                if(!nodes[i].findShortest&&table[i] < min){
                    min = table[i];
                    loc = i;
                    flag = true;
                }
            }
            if(!flag) break;
            nodes[loc].findShortest = true;
            cout << loc << ' ' << table[loc] << endl;
            for(auto neighbor : nodes[loc].n)
                if(table[neighbor.index] > table[loc]+neighbor.weight)table[neighbor.index]=table[loc]+neighbor.weight;
        
            
        }

    }
    
    return 0;
}