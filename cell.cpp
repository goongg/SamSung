#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define zero 800

struct cell { 
    public:
        int x; 
        int y;
};

int dx[4] ={-1, 0, 1, 0};
int dy[4] ={0, 1, 0, -1};


class board{
    public: 
    int N, M, K;
    vector<int> init;
    vector<cell> cells;
    bool visit[2*zero +1][2*zero +1];

int power[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
int state[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
int max[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
    void input()
    {
        cin>>N>>M>>K;
        init.resize(N*M);

        for(int i=0; i< N*M; i++)
        {
            cin>>init[i];
            cell c;
            c.x =  i%M+zero;
            c.y =  i/M+zero;
            if(init[i]!=0)
                cells.push_back(c);
            power[ c.x ][c.y ] =  init[i];  
            state[ c.x ][c.y ] =  init[i] * (-1);
        
        
        }
    }

    void TimeGo()
    {
        K--;
        vector<cell> new_cells;
        vector<cell> live_cells;

        vector<int> new_power;
        int cell_idx=0;
        for(int i=0; i< cells.size(); i++)
        {
            int x = cells[i].x;
            int y = cells[i].y;
            if( state[x][y]<0 ) // 비 활성화 된 세포라면,
            {
                state[x][y]++; //상태하나 늘림
                if( state[x][y] != power[x][y]);
                live_cells.push_back(cells[i]);
            }

            else if( state[x][y] >=0 && state[x][y] < power[x][y]) //활성화 된 세포라면
            {
                state[x][y]++; //상태하나 늘림
                if(state[x][y] != power[x][y])
                    live_cells.push_back(cells[i]);
                for(int d=0; d<4; d++) //네방향으로 퍼트림
                {
                    int nx= x + dx[d];
                    int ny= y + dy[d];

                    if(power[nx][ny] == 0) // 아직 안퍼진 곳이면?
                    {
                        cell cc;
                        cc.x= nx;
                        cc.y= ny;
                        if(!visit[nx][ny])
                        {
                            new_cells.push_back(cc);
                            new_power.push_back(power[x][y]);
                            visit[nx][ny]=1;
                        }
                        else 
                        {
                            for(int ii=0; ii<new_cells.size(); ii++)
                            {
                                if(nx== new_cells[ii].x && ny==new_cells[ii].y)
                                {
                                    if(new_power[ii] < power[x][y])
                                        new_power[ii] = power[x][y];
                                }
                            }
                        }
                    }
                }
            }
            else    //아무것도 안함
            {
                // cout<<"dead:"<<x -zero <<" " << y -zero<<endl;

                continue;
            }
        }
        cells.resize(0);
      //  cout<<K<<"-------------------\n";
        int iiii=0;
        for(cell ccc: new_cells)
        {

            cells.push_back(ccc);
            power[ccc.x][ccc.y] = new_power[iiii++];
            state[ccc.x][ccc.y] = power[ccc.x][ccc.y] * (-1);

       //     cout<<"new: ("<<ccc.x -zero <<"," << ccc.y -zero <<") "<< power[ccc.x][ccc.y]<<" "<<state[ccc.x][ccc.y]<< endl;
        }
        for(cell ccc: live_cells)
        {
            cells.push_back(ccc);
        //    cout<<"alive: ("<<ccc.x -zero <<"," << ccc.y -zero <<") "<< power[ccc.x][ccc.y]<<" "<<state[ccc.x][ccc.y]<< endl;
        }
        
    }

    int solve()
    {
        input();
        while(K!=0)
        {
            TimeGo();
//    cout<<"남은수:"<<cells.size()<<"\n";
            if(K==0) break;
        }
        return cells.size();
    }

}  ;
int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
    vector<board> b;
    b.resize(T);
	for(test_case = 1; test_case <= T; ++test_case)
	{
	cout<<"#"<<test_case<<" "<<b[test_case-1].solve()<<endl;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}