#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
using namespace std;
int main(){
    int power,node,num;
    cin>>node>>power>>num;
    char generator[100];
    char correct[10],your[10],testcase[10000],buffer[100];
    ifstream corr,you,test;
    sprintf(generator,"generator %d %d > test.in",node,power);
    for(int i=0;i<num;i++){
        system(generator);
        system("corr < test.in > answer_correct.out");
        system("a < test.in > answer_your.out");
        corr.open("answer_correct.out", ios::in );
        you.open("answer_your.out", ios::in );
        corr>>correct;
        you>>your;
        corr.close();
        you.close();
        int len=strlen(correct)>strlen(your)?strlen(correct):strlen(your);
        for(int i=0;i<len;i++){
            if(correct[i]!=your[i]){
                cout<<"wrong testcase:"<<endl;
                cout<<"---------------------------------------"<<endl;
                cout<<testcase<<endl;
                test.open("test.in", ios::in );
                while (!test.eof() )  {  
                    test.getline (buffer,100);  
                    cout << buffer << endl;  
                }  
                test.close();
                cout<<"---------------------------------------"<<endl;
                cout<<"correct:"<<correct<<endl;
                cout<<"your:"<<your<<endl;
                system("pause");
                return 0;
            }
        }
    }
    cout<<"OK, you have passed "<<num<<" testcases."<<endl;
    system("pause");
    return 0;
}
