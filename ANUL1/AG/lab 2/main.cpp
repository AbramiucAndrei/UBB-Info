#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define inf 1000000000
using namespace std;


void matricea_tranzitiva(){
    ifstream fin("tranzi.txt");
    bool tr[101][101]={};
    int v,e;
    fin>>v>>e;
    for(int i=0;i<v;i++)
        tr[i][i]=1;
    for (int i=1;i<=e;i++)
    {
        int x,y;
        fin>>x>>y;
        tr[x][y]=1;
    }

    for(int k=0;k<v;k++)
        for(int i=0;i<v;i++)
            for(int j=0;j<v;j++)
                    if(!tr[i][j])
                        if(tr[i][k] and tr[k][j])
                            tr[i][j]=1;

    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
            cout<<tr[i][j]<<' ';
        cout<<endl;
    }
}

void cerinta_4(){
    int v,e,sursa;
    bool mat[101][101]={};
    ifstream fin("bfs.txt");
    fin>>v>>e>>sursa;
    for(int i=1;i<=e;i++)
    {
        int x,y;
        fin>>x>>y;
        mat[x][y]=mat[y][x]=1;
    }

    int coada[10001],fata,spate,t[10001],dist[10001];
    fata=spate=0;
    coada[fata]=sursa;
    for(int i=0;i<v;i++)
        t[i]=-1, dist[i]=inf;
    t[sursa]=sursa;
    dist[sursa]=0;

    while(fata<=spate) // !q.empty
    {
        int c=coada[fata];
        fata++;

        for(int j=0;j<v;j++)
        {
            if(mat[c][j] and c!=j)
            {
                if(t[j]==-1){
                    coada[++spate]=j;
                    dist[j]=dist[c]+1;
                    t[j]=c;
                }
            }
        }
    }
    for(int i=0;i<v;i++)
        cout<<i<<' '<<dist[i]<<endl;

    cout<<endl;
    for(int i=0; i<v;i++)
        cout<<"tatal lui "<<i<<':'<<t[i]<<endl;
}

void dfs(int lista[][101],int nod,bool viz[]){
    viz[nod]=1;
    cout<<nod<<' ';
    for(int j=1;j<=lista[nod][0];j++)
    {
        int urm=lista[nod][j];
        if(!viz[urm])
            dfs(lista,urm,viz);
    }

}
void cerinta_5(){
    ifstream fin("dfs.txt");
    int v,e,lista[101][101]={};
    fin>>v>>e;
    for(int i=1;i<=e;i++)
    {
        int x,y;
        fin>>x>>y;
        lista[x][0]++;
        lista[x][lista[x][0]]=y;

        lista[y][0]++;
        lista[y][lista[y][0]]=x;


    }

    bool viz[101]={};
    for(int i=0;i<v;i++)
    {
        if(!viz[i])
            dfs(lista,i,viz), cout<<endl;

    }
}

void moore_bfs(){
    ifstream fin("graf.txt");

    int nrn;
    fin>>nrn;
    vector<int> lst[nrn+1];
    queue<int> q;


    int x,y;
    while(fin>>x>>y){
        lst[x].push_back(y);
    }

    int t[nrn+1],dist[nrn+1];
    for(int i=1;i<=nrn;i++)
        t[i]=-1, dist[i]=inf;

    int src,dest;
    printf("Introduceti nodul sursa: ");
    cin>>src;
    printf("Introduceti nodul destinatie: ");
    cin>>dest;

    t[src]=0; dist[src]=0;
    q.push(src);
    while(!q.empty()){
        int nc=q.front();
        q.pop();
        for(int it:lst[nc]){
            if(t[it]==-1)//neviz
            {
                t[it]=nc;
                dist[it]=dist[nc]+1;
                q.push(it);
            }
        }
    }
    for(int i=1;i<=nrn;i++){
        cout<<i<<' '<<t[i]<<' '<<dist[i]<<endl;
    }

    cout<<"Lungime pana la "<<dest<<':'<<dist[dest]<<endl;

    int lant[nrn-1];
    int i=0, nc=dest;
    while(t[nc]!=0){
        lant[i++]=nc;
        nc=t[nc];
    }
    lant[i]=nc;

    for(int i=dist[dest];i>=0;i--)
        cout<<lant[i]<<' ';
}
int main()
{
    //moore_bfs();
    //matricea_tranzitiva();

    //cerinta_4();
    //cerinta_5();
    return 0;
}
