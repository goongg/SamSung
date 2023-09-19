#include <string>
#include <vector>
#include <iostream>
#include <math>
using namespace std;

bool check_prime(int n)
{
    // cout<<'\n'<<n;
    if(n==0) return 0;
    if(n==1) return 0;
    if(n==2) return 1;

    for(int i =2; i<sqrt(n); i++)
    {
        if(n%i ==0 ) return 0;
    }
    
    // cout<<"is prime\n";
    return 1;
}
int solution(int n, int k) {
    int answer = 0;
    
    string s;
    while(n>0)
    {
        s+=to_string(n%k);        
        n/=k;
    }
    
    // cout<<s<<endl;
    int num=0;
    int exp=1;
    int idx=0;
    for(char c : s)
    {        
        if(c=='0' )
        {         
            if(check_prime(num)) answer++;
            
            num=0;
            exp=1;
        }
            
        else if(c>='1' && c<='9')
        {
            num+= exp*(c-'0');
            exp*=10;
        }
        
        idx++;
        if(idx==s.size()){
            if(check_prime(num)) answer++;
                 // cout<<num<<endl;
        }
    }
    return answer;
}