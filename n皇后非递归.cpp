#include <iostream>
#include <math.h>
#define N 5
#define initial -100   //数字大一点，保证在判断某一个位置能否放置皇后时，不会出现巧合而导致错误

using namespace std;

int q[N];
void init()    //初始化
{
    for(int i=0;i<N;i++)
    {
        q[i]=initial;
    }
}

int valid(int row,int col)   //探测row行col列的位置能否放置皇后
{
    for(int i=0;i<row;i++)   //只需要比较前面row行即可
    {
        if(q[i]==col||abs(i-row)==abs(q[i]-col))    //某一列的位置是否有冲突，以及主对角线和次对角线上的位置是否有冲突
            return 0;
    }
    return 1;
}


void print()    //打印输出N皇后的一组解
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (q[i] != j)      //a[i]为初始值
				cout<<"o ";
			else                //a[i]表示在第i行的第a[i]列可以放置皇后
				cout<<"1 ";
		}
		cout<<endl;
	}
	for (i = 0; i < N; i++)
		cout<<q[i];
	cout<<endl;
	cout<<"--------------------------------"<<endl;

}

void queen()
{
    int answer_num=1;
    int i=0,j=0;
    while(i<N)
    {
        while(j<N)    //试探每一列的位置
        {
            if(valid(i,j))   //找到一个合适位置，就去试探下一行
            {
                q[i]=j;
                j=0;       //探测下一行的位置时，j从0开始，要注意，这里就算是最后一行的最后一个位置，j
                break;
            }
            else
            {
                j++;
            }
        }
        if(j==N)   //如果一整行都没有合适的位置，就回退到上一行，将上一行的皇后位置前移，再去试探
        {
            if(i==0)    //如果已经回退到第一行还没有合适的位置，说明已经没有更多的解了
                break;
            else
            {
                i--;
                j=q[i]+1;
                q[i]=initial;
                continue;
            }

        }
        if(i==N-1)   //已经在最后一行也找到了合适位置，可以输出一个答案了
        {
            cout<<"answer "<<answer_num<<endl;
            answer_num++;
            print();
            j=q[i]+1;
        //要注意，这里不能是j++，因为某一行如果探测到一个合适位置安放皇后以后，会把j设置为0，最后一行也是如此，
        //如果是j++，就又会从1开始探测，探测到合适位置后j又设为0，这样j在最后一行的时候永远不会到N，也就无法进入上一条if语句中去回溯，
        //陷入死循环，导致一直输出第一个答案
            q[i]=initial;
            continue;
        }
        i++;
    }
}



int main()
{
    init();
    queen();
    system("pause");
    return 0;
}
