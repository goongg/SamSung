#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<string, int> element_cnt1;
map<string, int> element_cnt2;


int solution(string str1, string str2) {
    int answer = 0;

vector<string> all_element1; // 1의 다중집합 원소들
vector<string> all_element2; // 2의 다중집합 원소들


for(int i=0; i< str1.size()-1; i++)
{
    string s = "";
    s.resize(0);

    if(str1[i] >= 'A' && str1[i] <= 'Z')
        s+=str1[i];
    else if(str1[i] >= 'a' && str1[i] <= 'z')
        s+= (str1[i] + ('A'-'a'));
    else
        continue;

    if(str1[i+1] >= 'A' && str1[i+1] <= 'Z')
        s+=str1[i+1];
    else if(str1[i+1] >= 'a' && str1[i+1] <= 'z')
        s+= (str1[i+1] + ('A'-'a'));
    else
        continue;
    
    all_element1.push_back(s);
    if(element_cnt1.find(s)==element_cnt1.end())
        element_cnt1[s] =1;
    else
        element_cnt1[s]++;
}
for(int i=0; i< str2.size()-1; i++)
{
    string s = "";
    s.resize(0);

    if(str2[i] >= 'A' && str2[i] <= 'Z')
        s+=str2[i];
    else if(str2[i] >= 'a' && str2[i] <= 'z')
        s+= (str2[i] + ('A'-'a'));
    else
        continue;

    if(str2[i+1] >= 'A' && str2[i+1] <= 'Z')
        s+=str2[i+1];
    else if(str2[i+1] >= 'a' && str2[i+1] <= 'z')
        s+= (str2[i+1] + ('A'-'a'));
    else
        continue;
    
    all_element2.push_back(s);
    //cout<<s<<endl;
    if(element_cnt2.find(s)==element_cnt2.end())
        element_cnt2[s]=1;
    else
    element_cnt2[s]++;
}

    vector<string> G; //교집합
    vector<string> H; //합집합
    
    int num=0;
    int init=0;

    sort(all_element1.begin(), all_element1.end());
    all_element1.erase( unique(all_element1.begin(), all_element1.end()),all_element1.end());
/* 1에만 있거나 둘다 있는거 넣기 */
    for(string ss : all_element1)
    {
        if(element_cnt2.find(ss)== element_cnt2.end())
        {
            for(int i =0; i< element_cnt1[ss]; i++)
                H.push_back(ss);
        }
        else if( element_cnt2[ss] >= element_cnt1[ss])
        {
            for(int i =0; i< element_cnt2[ss]; i++)
                H.push_back(ss);
            for(int i =0; i< element_cnt1[ss]; i++)
                G.push_back(ss);
        }
        else if(element_cnt2[ss] < element_cnt1[ss])
        {
            for(int i =0; i< element_cnt1[ss]; i++)
                H.push_back(ss);
            for(int i =0; i< element_cnt2[ss]; i++)
                G.push_back(ss);
        }
    }

  
/* 2에만 있는거 넣기 넣기 */
    sort(all_element2.begin(), all_element2.end());
    all_element2.erase( unique(all_element2.begin(), all_element2.end()),all_element2.end());

    for(string ss : all_element2)
    {
        if( element_cnt1.find(ss)== element_cnt1.end())
        {
            for(int i =0; i< element_cnt2[ss]; i++)
                H.push_back(ss);
        }
    }
//         cout<<"G:\n";
//     for(string ssss: G) cout<<ssss<<endl;
    
//     cout<<"\n H:\n";
//     for(string ssss: H) cout<<ssss<<endl;

    if( H.size()==0 )
    {
        return 65536;
    }
    
    else
    {
        return (G.size() * 65536)/(H.size());
    }
    
    
    return answer;
}