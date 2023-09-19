#include <string>
#include <vector>
#include <iostream>
using namespace std;
int answer = 0;


string rotate(string s)
{
    string ret;
    ret.resize(0);
    int openCnt[3] = {0,0,0}; 
    int clsCnt[3] ={0,0,0};
    bool check=1;
    for(int i =1; i<= s.size(); i++)
    {
        if(i == s.size()) ret.push_back(s[0]);
        else ret.push_back(s[i]);
        switch(ret.back())
        {
            case '(':
                openCnt[0]++;
                break;
            case '{':
                openCnt[1]++;
                break;
            case '[':
                openCnt[2]++;
                break;
            case ')':
                openCnt[0]--;
                break;
            case '}':
                openCnt[1]--;
                break;
            case ']':
                openCnt[2]--;
                break;
        }
        if(openCnt[0] <0 || openCnt[1] <0 || openCnt[2] <0 )
            check=0;
    }
    
    if(check && openCnt[0] ==0 && openCnt[1] ==0 && openCnt[2] ==0 ) 
        answer++;     
    
    return ret;
}

int solution(string s) {
    
    if(s.size()==0 || s.size()%2 ==1) return 0;

    for(int i =0; i< s.size(); i++)
        s=rotate(s);
       
    return answer;
}