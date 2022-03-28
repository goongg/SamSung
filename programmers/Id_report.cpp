#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    answer=vector<int>(id_list.size());
    map<string, int> ID;
    vector<vector<int>> form;
    form= vector<vector<int> > (id_list.size());
    
    int idx=0;
    for(string s: id_list)
        ID[s]=idx++;

    for(string s: report)
    {
        string to;
        string from_buf;
        to.clear();
        from_buf.clear();
        int space_idx=0;
        for(char c: s)
        {
            if(c==' ' )
            {
               to = s.substr(space_idx+1, s.size() -space_idx-1 );
               from_buf =  s.substr(0, space_idx);
                // cout<<to<<" is baned "<< from_buf<<endl;


               form[ID[to]].push_back(ID[from_buf]);
               break;
            }      
            space_idx++;
        }
    }
int iii=0;
    for(vector<int> v : form)
    {
        sort(v.begin(), v.end());
        v.erase( unique(v.begin(), v.end()), v.end());
        if(v.size()>=k)
        {
            for(int i : v)
                answer[i]++;                
        }
    }

 
        return answer;
}