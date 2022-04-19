#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    map<string, int> uid_idx;
    map<string, string> uid_name;
    int idx=0;
    
    for(string s : record)
    {
        int first=0;
        int second=0;
     
        string uid="NULL";
        string name="NULL";
        int blank_Cnt=0;
        for(int i=0; i< s.size(); i++)
        {
            if(s[i] == ' ')
            {
                blank_Cnt++;

                if(first==0)
                    first=i;
                else
                    second=i;
            }
        }
        
        if(blank_Cnt==2){
            uid = s.substr(first+1, second -first -1);
            name = s.substr(second+1, s.size() - second+1 );

            uid_name[uid]= name;
            // cout<<"id 등록:" << uid<<" "<< uid_name[uid]<<endl;
        }

    }
    
 

    for(string s : record)
    {
        int first=0;
        int second=0;
        for(int i=0; i< s.size(); i++)
        {
            if(s[i] == ' ')
            {   
                if(first==0)
                    first=i;
                else
                    second=i;
            }
        }
        string uid = s.substr(first+1, second -first -1);
        if(s[0]=='E') answer.push_back(uid_name[uid] +"님이 들어왔습니다.");
        else if(s[0]=='L') answer.push_back(uid_name[uid] +"님이 나갔습니다.");

    }
    return answer;
}