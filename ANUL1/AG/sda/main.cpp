#include <iostream>

using namespace std;

class integer{
    int num;
public:
    integer(){
        num=0;
        cout<<"1";
    }
    integer(int arg){
        cout<<"2";
        num=arg;
    }
    int getv(){
        cout<<"3";
        return num;
    }
};

int main()
{

    integer i;
    i=10;
    cout<<i.getv();
    return 0;
}
