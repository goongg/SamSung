#include <string>
#include <vector>
#include <queue>
using namespace std;

class QQQ
{
    public:
    queue<int> q1;
    queue<int> q2;
    int cnt;
    int TargetNum;
    int Sumq1;
};

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -2;
    int maxsize=0;;
QQQ Q;
queue<QQQ> V;


    for(int i: queue1)
    {
        Q.q1.push(i);
        Q.TargetNum+=i;
        Q.Sumq1+=i;
        maxsize++;
    }
    for(int i: queue2)
    {
        Q.q2.push(i);
        Q.TargetNum+=i;
    }
    if(Q.TargetNum%2 ==1) return -1;

    Q.TargetNum/=2;
    Q.cnt=0;
    
    if(Q.TargetNum == Q.Sumq1) return 0;
    V.push(Q);
    while(!V.empty())
    {
        QQQ cur = V.front();
        QQQ ex = cur;
        V.pop();

/* q1 -> q2 */
        if(!cur.q1.empty() && cur.Sumq1 > cur.TargetNum)
        {
            cur.q2.push(cur.q1.front());
            cur.Sumq1-= cur.q1.front();
            cur.q1.pop();
            cur.cnt++;

            if(cur.cnt > maxsize*3) return -1;

            if(cur.Sumq1 == cur.TargetNum)
                return cur.cnt;
            else
            {
                V.push(cur);
            }
        }
        cur=ex;
/* q2 -> q1 */
        if(!cur.q2.empty() && cur.Sumq1< cur.TargetNum)
        {
            cur.q1.push(cur.q2.front());
            cur.Sumq1+= cur.q2.front();
            cur.q2.pop();
            cur.cnt++;
            
            if(cur.cnt > maxsize*3) return -1;

            if(cur.Sumq1 == cur.TargetNum)
                return cur.cnt;

            else
            {
                V.push(cur);
            }
        }
    }

    return -1;
}