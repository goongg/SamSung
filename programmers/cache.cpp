#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    queue<string> q;
    queue<string> nq;

    if(cacheSize == 0)
        return cities.size() *5;
    
    for(string sss : cities)
    {
        string s;
        s.resize(0);
        for(char c : sss)
        {
            if(c>='A' && c<='Z')
                c-=('A' - 'a');
            s.push_back(c);
        }
        
        if(q.empty())
        {
            q.push(s);
            answer+=5;
            continue;
        }

        string hit_city;
        bool hit=0;
        string cur;
        while(!q.empty())
        {
            cur= q.front();
            q.pop();
            if( cur== s)
            {
                hit=1;
                hit_city=s;
            }
            else
                nq.push(cur);
        }
        
        if(hit)
        {
            nq.push(hit_city);
            answer+=1;
        }
        else
        {
            nq.push(s);
            answer+=5;            
        }
        if(nq.size() > cacheSize)
            nq.pop();
        
        q=nq;
        while(!nq.empty())
            nq.pop();        
    }
    
    return answer;
}