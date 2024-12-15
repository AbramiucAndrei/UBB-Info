#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

bool viz[100001];
int nrviz;
vector<int> muchie[101000];
stack <int> ciclu;

void dfs(int nod){
    viz[nod]=1;
    nrviz++;

    for(int urm: muchie[nod]){
        if(!viz[urm]){
            dfs(urm);
        }
    }

}

void euler(int nod){
    while(!muchie[nod].empty()){
        int urm=muchie[nod][0];

        //sterge muchia nod-urm
        muchie[nod].erase(muchie[nod].begin());
        vector<int>::iterator it =find(muchie[urm].begin(),muchie[urm].end(),nod);
        muchie[urm].erase(it);
        //
        euler(urm);
    }
    ciclu.push(nod);
}
int main()
{
    int v,e;
    fin>>v>>e;
    for(int i=1;i<=e;i++){
        int x,y;
        fin>>x>>y;
        muchie[x].push_back(y);
        muchie[y].push_back(x);
    }


    //verif daca e conex;
    dfs(0);
    if(nrviz!=v){
        fout<<-1;
        return 0;
    }

    //verfi daca toate nodurile au grad par
    for(int i=0;i<v;i++)
       if(muchie[i].size()%2==1){
            fout<<-1<<' '<<i;
            return 0;
        }

    euler(0);
    while(ciclu.empty()==0){
        fout<<ciclu.top()<<' ';
        ciclu.pop();
    }
    return 0;
}
