#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end());
    vector<int> new_people;
    
    while(!people.empty())
    {
        int big = people.back();
        people.pop_back();    
        int small_idx=-1;
   
        if(people[0] + big <= limit)
            people.erase(people.begin()+i);
        answer++;        
    }
    return answer;
}

/*
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    sort(people.begi(), people.end());
    reverse(people.begin(), people.end());
    int N = (int)people.size();
    int res = 0;
    for (int i = 0, j = N - 1; i <= j; i++) {
        if (people[i] + people[j] <= limit) {
            j--;
        }
        res++;
    }
    return res;
}
*/