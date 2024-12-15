#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
        int day;
        int month;
        int year;
}_date;

 typedef struct{
    _date date;

    char description[50];
    double amount;
    char _type[20];//income or outcome
}Transaction;

bool valid_type(char type[]){
    //verify if the type of transaction is either "income" or "outcome"
    return ((strcmp(type,"income")==0) || (strcmp(type,"outcome")==0));
}

bool valid_amount(double amount)
{
    //verify if the amount is strictly positive
    return (amount>0);
}

bool valid_date(int day,int month,int year){
    /*verifies if the date is a real date*/
    if(day<1 || month<1 || year<1) return 0;

    if(month==2){
        if(day<=28) return 1;
        return 0;
    }
    if(month>=1 && month<=7){
        if(month%2==0){
            if(day<=30) return 1;
            return 0;
        }
        else{
            if(day<=31) return 1;
            return 0;
        }
    }
    if (month>7 && month<=12){
        if(month%2==0){
            if(day<=31) return 1;
            return 0;
        }
        else{
            if(day<=30) return 1;
            return 0;
        }
    }
    return 0;
}

Transaction create_trans(int d,int m,int y,char Desc[],
                         double money, char __type[]){
    //recieves through parameters the values representing a transaction
    //and returns a transaction with the transmitted parameters
    Transaction t;
    t.date.day=d;
    t.date.month=m;
    t.date.year=y;
    strcpy(t.description,Desc);
    t.amount=(int)(money*100);
    t.amount/=(100.0);
    strcpy(t._type,__type);
    return t;
}

Transaction read_trans(){
    /* reads from the console the values needed for a transaction
        ,verifies if the input is valid and then returns a transaction
        that has the entered values*/
    int d,m,y;
    do{
        printf("Enter date (day:month:year): ");
        scanf("%d%d%d",&d,&m,&y);
    }while(valid_date(d,m,y)==0);
    //READS THE DATE


    char buffer[20];
    gets(buffer);
    //buffer clear

    char desc[50];
    printf("Enter description:");
    gets(desc);
    //READS THE DESCRIPTION OF THE TRANSACTION


    double _amount;
    do{
        printf("Enter amount: ");
        scanf("%lf",&_amount);
    }while(!valid_amount(_amount));
    //READS THE AMOUNT

    char __type[20];
    do{
        printf("Enter type (income or outcome): ");
        scanf("%s",&__type);
    }while(!valid_type(__type));
    //READS THE TYPE

    return create_trans(d,m,y,desc,_amount,__type);
}

void print_trans(Transaction t){
    //prints the transaction transmited through parameter
    printf("Day:%02d\nMonth:%02d\nYear:%d\n",t.date.day,t.date.month,t.date.year);
    printf("Desc:%s\nAmount:%.2f\nType:%s\n\n",t.description,t.amount,t._type);
}
void print_past_trans(Transaction v[], int len){
    //prints ALL the transactions made until the function was called
    for(int i=0;i<len;i++){
        print_trans(v[i]);
    }
}
void add_trans(Transaction v[],int *len,Transaction t){
    //adds to the array 'v' the transaction transmitted through
    //the parameter t
    //and updates the lenght of 'v'
    v[*(len)]=t;
    *(len)+=1;
}
void record_new_trans(Transaction v[],int *len){
    //reads a transaction from the user in 't'
    //and adds it to 'v'
    Transaction t=read_trans();
    add_trans(v,len,t);
}
double calculate_balance(Transaction v[],int len){
    //calculates the balance,according to ALL the made transactions
    double balance=0;
    for(int i=0;i<len;i++){
        if(strcmp(v[i]._type,"income")==0)
            balance+=v[i].amount;
        else
            balance-=v[i].amount;
    }
    return balance;
}

bool inversed_dates(_date d1,_date d2){
    //tells if d1 is cronologically after d2
    if(d1.year>d2.year)
        return 1;
    if(d1.year<d2.year)
        return 0;
    //else
    if(d1.month>d2.month)
        return 1;
    if(d1.month<d2.month)
        return 0;
    //else
    if(d1.day>d2.day)
        return 1;
    if(d1.day<d2.day)
        return 0;
    //else
    return 0;
}

bool x_between_dates(_date l,_date r,_date x){
    //verifies if the date 'x' is cronologically between
    //date 'l' and 'r'
    //in case of 'l' and 'r' beeing reversed cronologically,
    //they are swapped AND ONLY AFTER THAT THE CONDITION IS VERIFIED
    if(inversed_dates(l,r)==1){
        _date aux=l;
        l=r;
        r=aux;
    }

    if(x.year< l.year || x.year>r.year) return 0;
    if(x.year>l.year && x.year<r.year) return 1;
    if(x.year==l.year && x.year==r.year){
        if(x.month<l.month || x.month>r.month) return 0;
        if(x.month>l.month && x.month<r.month) return 1;
        if(x.month==l.month && x.month==r.month){
            if(x.day>=l.day && x.day<=r.day) return 1;
            else return 0;
        }
        else if(x.month==l.month){
            if(x.day>=l.day) return 1;
            else return 0;
        }
        else//x.month==r.month
        {
            if(x.day<=r.day) return 1;
            else return 0;
        }
    }
    else if(x.year==l.year){
        if(x.month>l.month) return 1;
        else if(x.month==l.month) {
            if(x.day>=l.day) return 1;
            else return 0;
        }
        else return 0;
    }
    else//x.year==r.year
    {
        if(x.month<r.month) return 1;
        else if(x.month==r.month){
            if(x.day<=r.day) return 1;
            else return 0;
        }
        else return 0;
    }

}
double income_summary_between(Transaction v[],int len,_date d1,_date d2){
    //calculates the income between dates 'd1' and 'd2'
    double total=0;
    for(int i=0;i<len;i++)
        if(strcmp(v[i]._type,"income")==0)
            if(x_between_dates(d1,d2,v[i].date))
                total+=v[i].amount;
    return total;

}

double outcome_summary_between(Transaction v[],int len,_date d1,_date d2){
    //calculates the outcome between dates 'd1' and 'd2'
    double total=0;
    for(int i=0;i<len;i++)
        if(strcmp(v[i]._type,"outcome")==0)
            if(x_between_dates(d1,d2,v[i].date))
                total+=v[i].amount;
    return total;

}




void summary(Transaction v[],int len){
    /* prints  the total income and outcome for a specifi period of time
        entered by the user in the console*/

    //READS FIRST AND SECOND DATA
    int d1,m1,y1;
    int d2,m2,y2;

        do{
            printf("Enter first date (day:month:year): ");
            scanf("%d%d%d",&d1,&m1,&y1);
        }while(valid_date(d1,m1,y1)==0);


        do{
            printf("Enter second date (day:month:year): ");
            scanf("%d%d%d",&d2,&m2,&y2);
        }while(valid_date(d2,m2,y2)==0);

    _date date1,date2;
    date1=(_date){d1,m1,y1};
    date2=(_date){d2,m2,y2};

    //VERIFIES THE DATA 1 AND DATA 2 ARE PLACED CRONOLOGICALLY
    if(inversed_dates((_date){d1,m1,y1},(_date){d2,m2,y2})==1){
        _date aux=date1;
        date1=date2;
        date2=aux;
    }



    double in,out;
    in=income_summary_between(v,len,(_date){d1,m1,y1},(_date){d2,m2,y2});
    out=outcome_summary_between(v,len,(_date){d1,m1,y1},(_date){d2,m2,y2});

    printf("Income between the 2 dates entered above:%.2f\n",in);
    printf("Outcome between the 2 dates entered above:%.2f\n",out);
}

void show_menu(){
    //prints the commands menu
    printf("\n1.Add a new transaction\n");
    printf("2.Show past transactions\n");
    printf("3.Calculate balance\n");
    printf("4.Show the summary of transactions made between 2 dates\n");
    printf("5.Exit\n\n");

}

void ui(Transaction v[],int *n){
    /* this funtion shows the menu and interracts with the user
        through the console
        here we have all the funtionalities of the program,
        also including the exit
    */

    bool execute=true;

    while(execute==true){
            show_menu();
            int command;
            do{
                printf("Enter the command:");
                scanf("%d",&command);
                printf("\n");
            }while(!(command>=1 && command<=5));
            //READS ONE OF THE 5 COMMANDS AVALIBLE

            switch(command){
                case 1:
                    //RECORD NEW TRANSACTION
                    record_new_trans(v,n);
                    break;
                case 2:
                    //PRINT PAST TRANSACTIONS
                    print_past_trans(v,*(n));
                    break;
                case 3:
                    //PRINTS BALANCE
                    printf("%.2lf\n",calculate_balance(v,*(n)));
                    break;
                case 4:
                    //PRINTS THE INCOME AND OUTCOME SUMMARY FOR A
                    //SPECIFIC PERIOD OF TIME , ENTERED BY THE USER
                    summary(v,*(n));
                    break;
                case 5:
                    //EXIT
                    execute=false;
                    printf("BYE!");
                    break;
            }
    }
}

void save_data(Transaction v[],int last,int n,FILE *f){
    //saves the data in file "data.txt"

   // if(last<n) fprintf(f,"\n");
    for(int i=last;i<n;i++){
        fprintf(f,"%02d\n%02d\n%d\n",v[i].date.day,v[i].date.month,v[i].date.year);
        fprintf(f,"%s\n%.2f\n%s\n",v[i].description,v[i].amount,v[i]._type);
    }
}
void import_data(Transaction v[],int *n,FILE *f){
    //imports the data in file "data.txt"
    int d,m,y;
    char descr[50],typee[20];
    double money;

    while(!feof(f)){

        fscanf(f,"%d%d%d\n",&d,&m,&y);

        fgets(descr,49,f);
        strtok(descr,"\n");
        //ELIMINATE \N

        fscanf(f,"%lf\n",&money);

        fgets(typee,19,f);
        strtok(typee,"\n");
        //ELIMINATE THE \N FROM THE END

        char buffer[50];
        fgets(buffer,49,f);
        //CLEAR THE BUFFER//

        Transaction t=create_trans(d,m,y,descr,money,typee);
        add_trans(v,n,t);
    }
}

void test_create_trans(){
    Transaction t=create_trans(13,12,2000,"new transfer ",150,"income");
    //print_trans(t);
    assert(t.date.day==13 && t.date.month==12
            && t.date.year==2000);
    assert(t.amount==150);

    assert(strcmp(t.description,"new transfer ")==0);
    assert(strcmp(t._type,"income")==0);
}

void test_valid_date(){
    assert(valid_date(28,2,2004)==1);
    assert(valid_date(29,2,2004)==0);
    assert(valid_date(0,2,2000)==0);
    assert(valid_date(13,13,2000)==0);
}

void test_valid_amount(){
    assert(valid_amount(0.1)==1);
    assert(valid_amount(0)==0);
    assert(valid_amount(-10.15)==0);
    assert(valid_amount(125512.231)==1);
}

void test_valid_type(){
    assert(valid_type("income")==1);
    assert(valid_type("outcome")==1);
    assert(valid_type("ncome")==0);
}
void test_inversed_dates(){
    assert(inversed_dates((_date){15,12,2008},(_date){16,12,2008})==0);
    assert(inversed_dates((_date){16,12,2008},(_date){15,12,2008})==1);
    assert(inversed_dates((_date){16,12,2007},(_date){15,12,2008})==0);
    assert(inversed_dates((_date){16,12,2007},(_date){16,12,2007})==0);
}
void test_x_between_dates(){
    assert(x_between_dates((_date){15,12,2004},(_date){02,05,2005},(_date){01,02,2005})==1);
    assert(x_between_dates((_date){15,02,2004},(_date){02,05,2004},(_date){01,02,2005})==0);
    assert(x_between_dates((_date){15,02,2004},(_date){02,05,2004},(_date){16,02,2004})==1);
    assert(x_between_dates((_date){15,02,2004},(_date){02,05,2004},(_date){15,02,2004})==1);
    assert(x_between_dates((_date){15,02,2004},(_date){02,05,2004},(_date){02,05,2004})==1);
    assert(x_between_dates((_date){15,02,2004},(_date){02,05,2006},(_date){02,05,2005})==1);
    assert(x_between_dates((_date){28,02,2004},(_date){28,02,2004},(_date){28,02,2004})==1);
}

void test_calculate_balance(Transaction v[],int n){
   // printf("%f",calculate_balance(v,n));

    double eps=0.001;
    assert(calculate_balance(v,n)-111.25<eps);//==
    assert(calculate_balance(v,n)-111.24>=eps);//!=
    assert(calculate_balance(v,n)-111.26<=-eps);//!=
}

void test_income_summary_between(Transaction v[],int n){
    double eps=0.01;
    double result;

    result=income_summary_between(v,n,(_date){10,12,2005},(_date){12,12,2005});
    assert(result-137.45<eps && result-137.45>-eps);
    result=income_summary_between(v,n,(_date){10,12,2005},(_date){03,06,2006});
    assert(result-137.45<eps && result-137.45>-eps);
    result=income_summary_between(v,n,(_date){10,12,2005},(_date){10,12,2005});
    assert(result-12.20<eps && result-12.20>-eps);
    result=income_summary_between(v,n,(_date){03,02,2006},(_date){03,02,2006});
    assert(result==0);
}

void test_outcome_summary_between(Transaction v[],int n){
    double eps=0.1;
    double result;

    result=outcome_summary_between(v,n,(_date){02,06,2006},(_date){03,06,2006});
    assert(result-26.20<=eps && result-26.20>=-eps);
    result=outcome_summary_between(v,n,(_date){02,06,2006},(_date){02,06,2006});
    assert(result-14.00<=eps && result-14.00>=-eps);
    result=outcome_summary_between(v,n,(_date){10,12,2005},(_date){02,06,2006});
    assert(result-14.00<=eps && result-14.00>=-eps);
    result=outcome_summary_between(v,n,(_date){04,06,2006},(_date){03,02,2023});
    assert(result==0);
}

void tests(){
    test_create_trans();
    test_valid_date();
    test_valid_amount();
    test_valid_type();
    test_inversed_dates();
    test_x_between_dates();

    Transaction v[101], t;
    int n=0;

    t=create_trans(12,12,2005,"transfer",125.25,"income" );
    add_trans(v,&n,t);
    t=create_trans(10,12,2005,"trans",12.20,"income" );
    add_trans(v,&n,t);
    t=create_trans(02,06,2006,"donation",14,"outcome" );
    add_trans(v,&n,t);
    t=create_trans(03,06,2006,"transaction",12.20,"outcome" );
    add_trans(v,&n,t);
   // print_past_trans(v,n);

    test_calculate_balance(v,n);
    test_income_summary_between(v,n);
    test_outcome_summary_between(v,n);

}
int main()
{
    tests();
    FILE *f=fopen("data.txt","r+");
    if(f==NULL) assert(false);


    //trans is the main list of transactions
    //n is its lenght
    Transaction trans[150]={};
    int n=0;
    import_data(trans,&n,f);
    int last=n;

    ui(trans,&n);

    save_data(trans,last,n,f);
    fclose(f);
    return 0;
}

