#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

class File
{
    public:
    string h;
    int n;
    string t;
    string origin;
    int idx;
    File(string _origin, int _idx)
    {
        origin = _origin;        
        idx= _idx;
        int numstart=0;
        int numend=origin.size()-1;
  
        for(int i=0; i<origin.size(); i++)
        {
            if(origin[i]>='0' && origin[i]<='9' && numstart==0)
               numstart=i;
              
            else if(numstart!=0 && numend ==origin.size()-1 )         
                numend=i;
        }
        string hh= origin.substr(0, numstart);

        for(char c: hh)
        {
            if(c >='a'&& c >='a') h.push_back(c+'A'-'a');
            else h.push_back(c);
        }        
        n =stoi(origin.substr(numstart, numend-numstart+1));
        t= origin.substr(numend+1, origin.size()); 
        
        // cout<< h<<" "<<n <<" ";
    }
};

bool comph(File a, File b)
{
    if(a.h > b.h) return 0;
    else if (a.h < b.h) return 1;
        
    else
    {
        if(a.n > b.n) return 0;
        else if(a.n < b.n) return 1;
            
        else
        {
            if(a.idx>b.idx) return 0;
            else return 1;
        }
    }

}
vector<string> solution(vector<string> files) {
    vector<string> answer;
    
    vector<File> v;
    int idx=0;
    for(string s : files)
    {
        File a(s,idx++);
        v.push_back(a);
    }

    stable_sort(v.begin(),v.end(), comp);
    
    for(File f: v)
        // answer.push_back(f.origin);
    
    
    return answer;
}

