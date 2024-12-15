#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define inf 1000000
using namespace std;
ifstream fin("date.txt");
ofstream fout("bellmanford.out");
int main()
{
    int v,e,s;
    fin>>v>>e;
    s=1;

    vector<pair<int,int>> m[50001];

    for(int i=1;i<=e;i++){
        int x,y,val;
        fin>>x>>y>>val;
        m[x].push_back({val,y});
    }

    int d[50001],t[50001];
    set<int> relaxed_vertices;
    for(int i=1;i<=v;i++)
        d[i]=inf, relaxed_vertices.emplace(i), t[i]=inf;
    d[s]=0;
    t[s]=s;


    for(int relaxari=1;relaxari<v;relaxari++){
        set<int> temp_relaxed;
        for(int vf:relaxed_vertices){
            if(d[vf]==inf) continue;

            for(auto val_m:m[vf]){
                int urm=val_m.second;
                int val=val_m.first;

                if(d[urm]>d[vf]+val){
                    d[urm]=d[vf]+val;
                    temp_relaxed.emplace(urm);
                    t[urm]=vf;
                }
            }
        }
        relaxed_vertices=temp_relaxed;
    }

    for(int vf=1;vf<=v;vf++){
            for(auto val_m:m[vf]){
                int urm=val_m.second;
                int val=val_m.first;

                if(d[urm]>d[vf]+val){
                    //ciclu negativ
                    fout<<"Ciclu negativ!";
                    cout<<"Ciclu negativ!\n";

                    deque<int>ciclul;

                    t[urm]=vf;
                    //cout<<urm<<' ';
                    ciclul.push_front(urm);

                    bool viz[10001]={};
                    viz[urm]=1;
                    while(!viz[vf]){
                        //cout<<vf<<' ';
                        ciclul.push_front(vf);
                        viz[vf]=1;
                        vf=t[vf];
                    }
                    for(auto x:ciclul)
                        cout<<x<<' ';
                    return 0;
                }
            }
        }

    for(int i=2;i<=v;i++)
        cout<<d[i]<<' ';
    return 0;
}
