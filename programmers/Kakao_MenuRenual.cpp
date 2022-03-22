#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;


vector<string> all_combi; //각 손님들의 조합을 찾아서 저장

void search_comination(vector<string> orders, int course)
{
    vector<bool> sel;

    int idx=0; // 사람의 인덱스
    for(string s : orders)
    {
        if( course > s.size()){
            idx++;   
            continue;
        }

        int i=0;
        //sel : 조합의 재료로 쓸 bool
        sel.clear();
        for(char c : s)
        {
            if(course > i)    //선택해야하는 코스 갯수만큼 1
                sel.push_back(1);
            else
                sel.push_back(0);
            i++;
        }
        sort(sel.begin(), sel.end());

        cout<< idx <<"의 조합: ";
        do
        {
            string buf;
            buf.clear();
            for(int j=0; j< s.size(); j++)
            {
                if(sel[j])
                    buf.push_back(s[j]);
            }
            all_combi.push_back(buf);
            cout << all_combi.back()<<" ";
        } while (next_permutation(sel.begin(), sel.end()));
        idx++;
        cout<<endl;
    }
};


vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    
    vector<string> odrers_sorted;
    for(string s: orders)
    {
        sort(s.begin(), s.end());
        odrers_sorted.push_back(s);
    }
    map <string, int> m;
    vector<string> buf;    
    
    for(int i : course)
        search_comination(odrers_sorted,i);
    
int MaxOder[1000]; //각 코스별 최대 사이즈
memset(MaxOder, -1, 1000);

    for (string s :all_combi)
    {
        if(m.find(s) == m.end())
            m[s]=1;
        else
            m[s]= m[s]+1;

        if(MaxOder[s.size()]< m[s]) MaxOder[s.size()] =m[s];
    }

    for (string s :all_combi)
    {
        if(m[s]>=2 && MaxOder[s.size()] == m[s])
        {
            answer.push_back(s);
        }
    }
    
    sort(answer.begin(), answer.end());
    answer.erase( unique(answer.begin(), answer.end()), answer.end()) ;
return answer;

}


