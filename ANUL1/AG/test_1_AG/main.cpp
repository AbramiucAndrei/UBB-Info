#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define inf 1000000
using namespace std;
ifstream fin("date.txt");

struct pint{
    int val,nod;
};
bool viz[10001];

void afisare_drum(int s,int curr,int t[]){
    if(curr==s)
        cout<<s<<' ';
    else{
       afisare_drum(s,t[curr],t);
        cout<<curr<<" ";
    }
}
int main()
{

    int V,E,S,x,y;

    vector<pint> m[10002];
    fin>>V>>E>>S;

    int s,dst,val;
    for(int i=1;i<=E;i++){

        fin>>s>>dst>>val;
        m[s].push_back({val,dst});
    }
    for(int i=0;i<V;i++){
        cout<<i<<':';
        for(auto it:m[i]){
            cout<<"("<<it.nod<<','<<it.val<<") ";
        }
        cout<<endl;
    }

    int d[10001],t[10001];
    for(int i=0;i<V;i++)
        d[i]=inf, viz[i]=0, t[i]=i;
    d[S]=0;


    priority_queue<pair<int,int>> q;
    q.push({0,S});
    while(!q.empty()){
        pair<int,int> top=q.top();

        int curr,dist_curr;
        curr=top.second; dist_curr=d[curr];
        viz[curr]=1;

        for(auto it:m[curr]){
            int urm=it.nod;

            if(!viz[urm] && d[urm]>dist_curr+it.val){
                d[urm]=dist_curr+it.val;
                q.push({-d[urm],urm});
                t[urm]=curr;
            }
        }
        q.pop();

    }

    for(int i=0;i<V;i++){
        if(d[i]==inf)
            cout<<"INF ";
        else
            cout<<d[i]<<' ';
    }
    return 0;
}
