#include <string>
#include <vector>
#include <iostream>

using namespace std;


bool IsSame(string s, int idx, int unit)
{
    if(idx + unit >= s.size() || idx-unit+1 <0 )
        return 0;
    if(s.substr(idx-unit+1, unit) == s.substr(idx+1, unit))
        return 1;
    else
        return 0;
}


int solution(string s) {
    int answer = 0;

    int zip_unit_num=2;
    int cnt=0;
    int idx=0;
    int iidx=0;
    int unit=2;

    int same_cnt=0;

    string ziped;
    for(idx=0; idx<s.size();)
    {
        if(IsSame(s, idx, unit))
        {   
            same_cnt=2;
            for(iidx= idx+unit; iidx < s.size(); iidx+= unit)
            {
                if(IsSame(s,iidx,unit))
                    same_cnt++;
                else
                    break;
            }
            ziped+= to_string(same_cnt)+s.substr(idx-unit+1, unit);
            same_cnt=0;
            idx=iidx+1;
        }
        else
          idx++; 
    }

    cout<< 
    return answer;
}