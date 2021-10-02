//5시 35분

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define debug 0

int dx[4] ={-1, 0, 1, 0};
int dy[4] ={0, 1, 0, -1};

class bbq{

    vector<int> t;
    vector<int> chik;
    vector<int> house;
    int n, m;
public:
    void input()
    {
        cin>>n>>m;
        t=vector<int>(n*n);
        for(int i=0; i< n*n; i++)
        {
            cin>>t[i];
            if(t[i]==1) house.push_back(i);
            if(t[i]==2) chik.push_back(i);
        }

    }
    int distance(int a, int b)
    {
        return abs(a%n -  b%n) + abs(a/n - b/n); 
    }        

    int clac( vector<int> c)    //
    {
        int ret = 0;
        for(int i :house)   //각 집에서 가장 가까운 치킨집을 찾음
        {
            int dis_min = 999999999;
            for(int j : c)
            {
                if( distance(i, j) <dis_min) dis_min = distance(i, j) ;
            }
            ret += dis_min;
        }
        return ret;
    }

    int sol()
    {
        input();
        int min_ret=9999999;
        vector<bool> combination;

        for(int i=0; i<m; i++) combination.push_back(1);
        while( combination.size() < chik.size() ) combination.push_back(0);
        sort( combination.begin(),combination.end()); 
        
        do{
            vector<int> buf;
            int ret_buf;
            for(int i=0; i< combination.size(); i++)
            {
                if(combination[i])
                {
                    buf.push_back(chik[i]);
                    #if debug
                    cout << i<<" ";
                    #endif
                }
                     #if debug
                    cout <<'\n';
                    #endif

            }

        ret_buf= clac(buf);
        if( ret_buf < min_ret) min_ret = ret_buf;
        buf.clear();
        }while( next_permutation(combination.begin(), combination.end()));

        return min_ret;
    }

};


int main()
{

bbq q;
cout<<q.sol();

    return 0;
}