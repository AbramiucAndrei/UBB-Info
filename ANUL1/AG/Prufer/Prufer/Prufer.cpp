// Prufer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;
ifstream fin("prufer.in");


bool a_devenit_frunza(int nod, int t[],int n) {
    for (int i = 0; i < n; i++)
        if (t[i] == nod)
            return false;
    return true;
}
void codare_prufer(int n, int t[], int rad) {
    set<int,less<int>> frunze;

    for (int i = 0; i < n; i++)
        frunze.insert(i);
    for (int i = 0; i < n; i++)
        frunze.erase(t[i]);

    vector<int> codare;
    //raman doar frunzele in set
    while(*frunze.begin()!=rad) {
        //minimul dintre frunze
        int get_min = *frunze.begin();
        //adaug tatal minimului in codare
        codare.push_back(t[get_min]);
        //salvez tatal
        int tata = t[get_min];
        //sterg legatura tata->get_min
        t[get_min] = -1;
        frunze.erase(get_min);

        //daca a devenit frunza tatal
        if (a_devenit_frunza(tata, t, n) ){
            frunze.insert(tata);
        } 
    }
    cout << codare.size() << endl;
    for (auto& it : codare)
        cout << it << ' ';
}

void codare_prufer2(int n, int t[], int rad,int nrcopii[]) {
    set<int, less<int>> frunze;

    for (int i = 0; i < n; i++)
        if (nrcopii[i] == 0)
            frunze.insert(i);
    vector<int>codare;
    while (*frunze.begin() != rad) {
        int get_min = *frunze.begin();
        //sterg frunza cu indicele cel mai mic
        frunze.erase(get_min);
        //adaug in codare tatal frunzei
        codare.push_back(t[get_min]);

        //verific daca tatal a devenit frunza
        //si il adaug daca a devenit
        nrcopii[t[get_min]]--;
        if (nrcopii[t[get_min]] == 0)
            frunze.insert(t[get_min]);
    }

    cout << codare.size() << endl;
    for (auto& it : codare)
        cout << it << ' ';
}

int cod[200000];
int tati[100000];
int frecv[100001];
void decodare_prufer(int nrvalori) {
    //cod : 1->nrvalori
    
    int st = 1, dr = nrvalori;
    for (int i = st; i <= dr; i++)
        frecv[cod[i]]++;

    for (int i = 1; i <= nrvalori; i++) {
        int x, y;
        //x ia prima valoare din cod-actuala
        x = cod[st];

        y = -1;
        //y ia valoarea cea mai mica ce NU apare in cod
        for(int i=0;i<=nrvalori and y==-1;i++)
            if (frecv[i] == 0) {
                y = i;
                frecv[x]--;
                frecv[y]=1;
            }
        //tatal lui y ce nu apare in cod devine x-prima valoare din cod
        tati[y] = x;

        //se sterge prima valoare din cod-x
        st++;
        //se adauga la sfarsit valoarea ce nu apare-y
        dr++;
        cod[dr] = y;
        //la sfarsit,setez tatal al radacinii arborelui la -1
        if (i == nrvalori)
            tati[x] = -1;
    }
    cout << nrvalori + 1 << endl;
    for (int i = 0; i <= nrvalori; i++)
        cout << tati[i] << ' ';
}

int main()
{
    int t[100000], n, rad, nrcopii[100000] = {};
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> t[i];
        
        if (t[i] == -1)
            rad = i;
        else
            nrcopii[t[i]]++;
    }

    codare_prufer2(n, t, rad,nrcopii);
    cout << endl;

    int m;
    fin >> m;
    for (int i = 1; i <= m; i++) {
        fin >> cod[i];
    }
    decodare_prufer(m);
    return 0;
}

