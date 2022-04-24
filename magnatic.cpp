#include <iostream>
#include <vector>
using namespace std;

class Mag 
{
    public:
        int pol[8];
};

class Rotate
{
    public:
    int m_num;    
    int direct;
};

class Magnatic {
    public:

        bool is_rotate[5];
        int K;
        vector<Mag> mags;
        vector<Rotate> rotate_info;
        void input()
        {
            cin>>K;
            mags.resize(5);
            for(int i=1; i<=4; i++)
                for(int j=0; j<8; j++)
                    cin>>mags[i].pol[j];

            rotate_info.resize(K+1);
            for(int i=1; i<= K; i++)
                cin>> rotate_info[i].m_num>>rotate_info[i].direct;
            
        }
        void rotate(int m_idx, int d) //d ==1 : 시계 d ==-1 반시계
        {
            Mag m;
            if(d== 1) // 시계방향이면
            {
                m.pol[0]= mags[m_idx].pol[7];    
                for(int i=1; i<=7; i++)
                {    
                    m.pol[i]= mags[m_idx].pol[i-1];
                }
            }
            else
            {
               m.pol[7]= mags[m_idx].pol[0];    
                for(int i=0; i<7; i++)
                {
                    m.pol[i]= mags[m_idx].pol[i+1];
                }
            }
            mags[m_idx] =m;


        }

        void print()
        {
            cout<<"\ndebug\n";
            for(int i=1; i<=4; i++){
                cout<<i<<"번 자석:";
                for(int j=0; j<8; j++)
                    cout<<mags[i].pol[j]<<" ";
                cout<<endl;
            }
            cout<<"\n";
        }
        bool check(int a, int b) // 두 자석의 닿은면이 같은극인지 조사, 입력시 작은쪽 먼저 입력
        {
            
            if(mags[a].pol[2] != mags[b].pol[6]) return 1;
            else return 0;
        }

        int solve()
        {
            input();
            for(int i=1; i<= K ; i++)
            {

                int j=rotate_info[i].m_num;
                int d= rotate_info[i].direct;

                is_rotate[1] =0 ;
                is_rotate[2] =0 ;
                is_rotate[3] =0 ;
                is_rotate[4] =0 ;
                is_rotate[j]= 1;
                // cout<<i<<"번째 이동"<<j<<"자석을 "<<d<<"회전\n";
                while(j+1 <=4)
                {
                    if(check(j, j+1) )
                        is_rotate[j+1]=1;
                    else
                        break;
                    j++;
                }

                j = rotate_info[i].m_num;
                d= rotate_info[i].direct;
                
                while(j-1 >=1)
                {
                    if(check(j-1, j) )
                        is_rotate[j-1]=1;
                    else
                        break;
                    j--;

                }

//실재회전
            j = rotate_info[i].m_num;
            d= rotate_info[i].direct;

            rotate(j, d);
                while(j+1 <=4)
                {
                    d*=-1;

                    if(is_rotate[j+1])
                        rotate(j+1, d);
                    else
                        break;

                    j++;
                }
                j = rotate_info[i].m_num;
                d= rotate_info[i].direct;
                
                while(j-1 >=1)
                {
                    d*=-1;

                     if(is_rotate[j-1])
                        rotate(j-1, d);
                    else
                        break;
                    j--;
                }

            // print();
            }

            return calc();
        }

        int calc()
        {
            int result=0;
            int point= 1;

            for(int i=1; i<=4; i++)
            {
                result+= mags[i].pol[0] * point;

                point*=2;
            }

            return result;
        }
};

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
	for(test_case = 1; test_case <= T; ++test_case)
	{
	Magnatic M;
        cout<<"#"<<test_case<<" "<<M.solve() <<'\n';
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}