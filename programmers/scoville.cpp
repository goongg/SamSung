#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int> > pq;
    
    for(int i : scoville) pq.push(i);
    
    if(scoville.size() ==1 && scoville[0] <K) return -1;
    if(scoville.size() ==1 && scoville[0] >K) return 0;
    
    while(!pq.empty())
    {
        if(pq.top() >=K) return answer;
        int min= pq.top();
        pq.pop();
        pq.push(pq.top()*2 + min);
        pq.pop();
        answer++;
    }
    
    return -1;
}