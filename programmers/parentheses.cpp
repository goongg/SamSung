#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    vector<int> finish_Day;
    int remain;
    for(int idx=0; idx< progresses.size(); idx++)
    {
        if((100- progresses[idx])%speeds[idx] ==0)
            remain=(100- progresses[idx])/speeds[idx];           
        else  
            remain=(100- progresses[idx])/speeds[idx] + 1;           
        if(finish_Day.size()==0) finish_Day.push_back(remain);
        
        else
        {
            if(finish_Day.back() > remain)
            {
                finish_Day.push_back(finish_Day.back()) ;
            }
            else
                finish_Day.push_back(remain) ;       
        }
        
//        cout<<finish_Day.back()<<" ";            
    }
    
    
    int ans_idx=0;
    for(int idx=0; idx< finish_Day.size() ; idx++)
    {
        if(answer.size()==0)
        {
            answer.push_back(1);
            ans_idx++;
            continue;
        }
        
        if( finish_Day[idx-1] == finish_Day[idx] )
        {
            answer[ans_idx-1]++;
        }
        else
        {
            answer.push_back(1);
            ans_idx++;
            continue;            
        }
        
        
        
    }
    
    
    return answer;
}