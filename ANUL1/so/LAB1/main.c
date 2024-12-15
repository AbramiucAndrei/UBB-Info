#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
    int m,n;
    FILE* f=fopen(argv[1],"r");

    fscanf(f,"%d%d",&m,&n);

    int** mat=(int**)malloc(m*sizeof(int*));

    for(int i=0;i<m;i++){
        mat[i]=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            fscanf(f,"%d",&mat[i][j]);
        }
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }

    for(int i=0;i<m;i++)
        free(mat[i]);
    free(mat);

    fclose(f);
    return 0;
}
