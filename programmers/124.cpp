#include <string>
#include <vector>

using namespace std;

string solution(int n) {
    string answer = "";
    string buf;
    while(n>0)
    {
        switch((n-1)%3)
        {
            case 0: answer.push_back('1'); break;
            case 1: answer.push_back('2'); break;
            case 2: answer.push_back('4'); break;
        }
        n= (n-1)/3;
    }
    
    while(!answer.empty())
    {
        buf.push_back(answer.back());
        answer.pop_back();
    }
    return buf;
}