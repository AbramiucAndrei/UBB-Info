#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

int mat[50001][3],v,e;
int main()
{
    fin>>v>>e;
    for(int i=0;i<e;i++){
        int x,y,val;
        fin>>x>>y>>val;
        mat[i][0]=x;
        mat[i][1]=y;
        mat[i][2]=val;
    }

    for(int i=0;i<e-1;i++)
        for(int j=i+1;j<e;j++)
            if(mat[i][2]>mat[j][2])
                swap(mat[i],mat[j]);

    int t[5001];
    for(int i=0;i<v;i++)
        t[i]=i;

    int muchii=0,i=0,cost=0;
    int ind_muchie[50001];

    while(muchii!=v-1 and i<e){
        if(t[mat[i][0]]!=t[mat[i][1]]){
            //buna
            cost+=mat[i][2];
            ind_muchie[++muchii]=i;

            t[mat[i][0]]=t[mat[i][1]];
        }
        i++;
    }

    fout<<cost<<endl;
    fout<<muchii<<endl;
    for(i=1;i<=muchii;i++)
        fout<<mat[ind_muchie[i]][0]<<' '<<mat[ind_muchie[i]][1]<<endl;
    return 0;
}
