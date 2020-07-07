#include <iostream>
#include<math.h>

#define initial -100    //默认的初始值，表示某一行还没有放置皇后
using namespace std;

static int N;
long answer_num = 1, upperlim = 1;     //answer_num是答案,upperlim是bit位的有效位数，比如5皇后对应的应该是011111
int *q;    //存储答案的数组
void init()       //初始化
{
    q=new int[N];
    for(int i=0;i<N;i++)
        q[i]=initial;
}

int which_row=0;    //全局变量来记录探测到哪一行
void print()                    //输出一个答案
{
    int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (q[i] != j)      //q[i]为初始值
				cout<<"o ";
			else                //q[i]表示在第i行的第q[i]列可以放置皇后
				cout<<"1 ";
		}
		cout<<endl;
	}
	for (i = 0; i < N; i++)
    cout<<q[i];
	cout<<endl;
	cout<<"--------------------------------"<<endl;
}

// 试探算法从最右边的列开始。
//row代表一行里哪些列不能放置棋子,left_diagonal代表左对角线的限制，right_diagonal代表右对角线的限制
void queen_by_bit(long row, long left_diagonal, long right_diagonal)
{
	if (row != upperlim)      //如果row不等于upperlim，说明还有行没有放置皇后
	{
		// row，ld，rd进行“或”运算，求得所有可以放置皇后的列,对应位为0，
		// 然后再取反后“与”上全1的数，来求得当前所有可以放置皇后的位置，对应列改为1
		// 也就是求取当前哪些列可以放置皇后
		//和upperlim进行与运算保证不会因为移位导致超出有效位数

		long pos = upperlim & ~(row | left_diagonal | right_diagonal);
		while (pos)    // 如果pos为0 ，则表明皇后没有地方可放，应该向上一行回溯
		{
			// 获取pos最右边为1的bit，其余bit置0
			// 也就是取得可以放皇后的最右边的列
			//pos和负的pos进行与运算，相当于pos&(~pos+1)，因为补码里面一个数的负数就是“取反加1”，所以相当于和负的pos进行与运算

			long p = pos & -pos;

			// 将pos最右边为1的bit清零
			// 也就是为获取下一次的最右可用列使用做准备，
			// 程序将来会回溯到这个位置继续试探

			pos -= p;
            int location=N-1-log(p)/log(2);  //location记录这一行的皇后放在哪个位置，注意列标的方向是从左至右0,1,2,3
            q[which_row]=location;    //在数组内记录答案
            which_row++;            //探测下一行

			// row + p，将当前列置1，表示记录这次皇后放置的列。
			// (left_diagonal + p) << 1，标记当前皇后左边相邻的列不允许下一个皇后放置。
			// (right_diagonal + p) >> 1，标记当前皇后右边相邻的列不允许下一个皇后放置。
			// 此处的移位操作实际上是记录对角线上的限制，只是因为问题都化归到一行网格上来解决，所以表示为列的限制就可以了。

			queen_by_bit(row + p, (left_diagonal + p) << 1, (right_diagonal + p) >> 1);
			which_row--;    //如果下一行没有合适的位置，就回溯到上一行，从下一个可行位置开始探测
			q[which_row]=initial;

		}
	}
	else
	{
		// row的所有位都为1，即找到了一个成功的布局，回溯
		cout<<"answer "<<answer_num<<endl;
		print();
		answer_num++;
	}
}

int main()
{


	// 因为long数据类型的限制，最大只能32位，
	// 如果想处理N大于32的皇后问题，需要
	// 用bitset数据结构进行存储
	cout<<"输入皇后数量:"<<endl;
	cin>>N;
	if ((N < 1) || (N > 20))
	{
		printf(" 皇后的数量建议在1-20之间\n");
		exit(-1);
	}
	cout<<N<<"皇后问题："<<endl;
	// N个皇后只需N位存储，N列中某列有皇后则对应bit置1。
	upperlim = (upperlim << N) - 1;   //控制bit的有效位数
    init();
	queen_by_bit(0, 0, 0);  //从棋盘为空开始探测
	delete []q;   //释放空间
	system("pause");
	return 0;
}


