#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

vector<string> combi;
void combination( string all_orders, string s, int depth, int idx)
{
    if(s.size() == depth)
    {
        combi.push_back(s);
        return;
    }
    
    if(idx >= all_orders.size()) return;
    for(int i =idx; i<all_orders.size(); i++)
    {
        s.push_back(all_orders[i]);
        combination(all_orders, s, depth ,i+1);
        s.pop_back();
    }
    
};
    

/* 특정 사람의 order에 new_coures가 포함되어있는지를 체크*/
/* string에서 특정 원소 찾는 STL 필요 */
int check(vector<string> orders, string new_coures)
{
    int ret=0;
    
    for(string s : orders)
    {
        bool no_found=0;
        for(char c :new_coures )
        {
            if (s.find(c) == (size_t)(-1) )
            {    
                no_found=1;
                break;
            }
        }
        if(!no_found) ret++;
    }
    return ret;
    
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    string all_orders;
    
    for(string s: orders)
        for(char c : s)
            all_orders.push_back(c);
    
    sort(all_orders.begin(), all_orders.end()); 
    all_orders.erase(unique(all_orders.begin(), all_orders.end()),all_orders.end() );
    
    for(int i : course)
    {
        combi.resize(0);
        string s ="";
        combination(all_orders, s, i, 0);
        int max=0;
        for(string ss: combi)
        {
            int ret = check( orders, ss);
            if(ret >max) max = ret;
        }

        // cout<<endl;
        for(string ss: combi)
        {
            int ret = check( orders, ss);
            if(ret == max && ret >=2) 
            {
                // cout<<ss<<" "<<ret;
                answer.push_back(ss);
            }
        }
    }

    sort(answer.begin(), answer.end());
    
    
    return answer;
}