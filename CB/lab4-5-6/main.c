#include <stdio.h>
#include <stdlib.h>

void sortare(int *p,int len)
{
    for(int i=0;i<len-1;i++){
        int minn=*(p+i), poz=i;
        for(int j=i+1;j<len;j++){
            if(*(p+j)<minn){
                minn=*(p+j);
                poz=j;
            }
        }

        int aux=*(p+i);
        *(p+i)=*(p+poz);
        *(p+poz)=aux;
    }
}

void afisare(int *p,int n){
    printf("\n");
    for (int i=0;i<n;i++){
        printf("%d ",*(p+i));
    }
    printf("\n");
}

void interclasare(int *p1,int *p2,int n,int m, int *p3,int *len){
    int l=-1;

    int i,j;
    i=j=0;
    while(i<n && j<m){
        if(*(p1+i)<=*(p2+j)){
            l++;
            *(p3+l)=*(p1+i);
            i++;
        }
        else{
            l++;
            *(p3+l)=*(p2+j);
            j++;
        }
    }

    while(i<n){
        l++;
        *(p3+l)=*(p1+i);
        i++;
    }
    while(j<m){
        l++;
        *(p3+l)=*(p2+j);
        j++;
    }

    *(len)=l+1;
}
int main()
{
    int a[1001],b[1001],n,m;
    int *p1,*p2;
    p1=&a[0]; p2=&b[0];

    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        //int x;
        scanf("%d",p1+i);
        //*(p2+i)=x;
    }

    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        //int x;
        scanf("%d",p2+i);
        //*(p2+i)=x;
    }

    sortare(p1,n);
   // afisare(p1,n);

    sortare(p2,m);
   // afisare(p2,m);

    int c[2002]={0,1},l, *p3;

    p3=c;



   interclasare(p1,p2,n,m,p3,&l);
   afisare(p3,l);
  /*

    for (int i=0;i<m;i++){
        printf("%d ",*(p2+i));
    }*/


    return 0;
}
