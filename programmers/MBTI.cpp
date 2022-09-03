#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";

    
    map <char, int > point;    
    int index=0;
    for(string s: survey)
    {
        if(choices[index] >= 5) /* 동의 할때 */
        {
            point[s[1]] += choices[index]-4;            
        }
        else    /* 비동의 할때*/
        {
            point[s[0]] += 4 -choices[index];                   
        }            
        index++;
    }
    /*높은 점수를 찾아 성경유형에 추가*/
    if(point['R'] >= point['T']) 
        answer.push_back('R');
    else 
        answer.push_back('T');

    if(point['C'] >= point['F']) 
        answer.push_back('C');
    else 
        answer.push_back('F');

    if(point['J'] >= point['M']) 
        answer.push_back('J');
    else 
        answer.push_back('M');

    if(point['A'] >= point['N']) 
        answer.push_back('A');
    else 
        answer.push_back('N');

return answer;
}