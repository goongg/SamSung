#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector< vector<int> > list; 
vector<int> solution(string s) {
    vector<int> answer;
    
    vector<int> e;
    string num;
    bool init=1;
    for(char c : s)
    {
        if(init)
        {
            init=0;
            continue;
        }
        if(c=='{')
        {
            e.resize(0);
        }
        else if (c >='0' && c <='9')        
            num.push_back(c);

        else if (c ==',')
        {
            e.push_back(stoi(num));
            num.resize(0);
        }
        else if (c =='}')
        {
            if(!num.empty())
            {
                e.push_back(stoi(num));
                // num.resize(0);
            }
             list.push_back(e);
        }
    }
    list.pop_back();
    int find_length=1;
    while(1)
    {
        for(vector<int> cur : list)
        {
            if(find_length==1 && cur.size()==1)
            {
                answer.push_back(cur[0]);
                find_length++;
                break;
            }
            if(cur.size() == find_length)
            {
                int x;
                bool find;
                for(int i : cur)
                {
                    find=0;
                    for(int ii: answer)
                    {
                        if(i==ii) 
                            find=1;
                    }
                    if(!find)
                    {
                    answer.push_back(i);
                    find_length++;
                    break;
                    }
                }
                if(!find) break;
            }
        }
        if(find_length == list.size()+1)
        break;
    }
    
    return answer;
}