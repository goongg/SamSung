
#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = "";

    for(char c: new_id)
    {
        /* 대문자면 */
        if(c >= 'A' && c<= 'Z')
        {    answer.push_back( c- ('A' -'a') );}
        /* 소문자면*/
        else if (c >= 'a' && c<='z')
            answer.push_back(c);
        
        /*숫자면*/ 
        else if (c >='0' && c <='9')
            answer.push_back(c);
        
        else if (c =='-' || c =='_')
            answer.push_back(c);
        
        /* 마침표면 */
        else if (c =='.')
        {
            /*처음이면 안넣기*/
            if(answer.size()==0)
            {}
            /*중복이면 안넣기*/
            else if(answer.back()==c)
            {}
            else
            answer.push_back(c);
        }
    }
    if(answer.size()==0)
        answer.push_back('a');

    while (answer.size()>=16 || answer.back() == '.')
    {
        answer.pop_back();
    }
    
    while(answer.size() <=2)
        answer.push_back(answer.back());
    
    return answer;
}