#include<iostream>
using namespace std;

bool flag[2] = {false,false};
int turn;

void process0(){
    flag[0] = true;
    turn = 1;

    while(flag[1] && turn ==1);

    cout<<"Process 0 is in critical section"<<endl;
    flag[0] = false;
}

void process1(){
    flag[1] = true;
    turn =0;

    while(flag[0] && turn==0);
    cout<<"Process 1 is in critical section"<<endl;
    flag[1] = false;
}

int main(){
    process0();
    process1();

    return 0;
}