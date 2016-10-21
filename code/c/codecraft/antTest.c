#include<stdio.h>
#include<iostream>  
#include<math.h>  
#include<time.h>  
#include<stdlib.h>
using namespace std; 


double abs(double a)
{
	if(a<0)return -a;
	return a;
}

#define N 75  //number of city
double C[N][2]={  
{6,25},  {7, 43}, {9,56},  {10,70}, {11,28},  
{12,17}, {12,38}, {15,5},  {15,14}, {15,56},  
{16,19}, {17,64}, {20,30}, {21,48}, {21,45},  
{21,36}, {22,53}, {22,22}, {26,29}, {26,13},  
{26,59}, {27,24}, {29,39}, {30,50}, {30,20},  
{30,60}, {31,76}, {33,34}, {33,44}, {35,51},  
{35,16}, {35,60}, {36, 6}, {36,26}, {38,33},  
{40,37}, {40,66}, {40,60}, {40,20}, {41,46},  
{43,26}, {44,13}, {45,42}, {45,35}, {47,66},  
{48,21}, {50,30}, {50,40}, {50,50}, {50,70},  
{50, 4}, {50,15}, {51,42}, {52,26}, {54,38},  
{54,10}, {55,34}, {55,45}, {55,50}, {55,65},  
{55,57}, {55,20}, {57,72}, {59, 5}, {60,15},  
{62,57}, {62,48}, {62,35}, {62,24}, {64, 4},  
{65,27}, {66,14}, {66,8},  {67,41}, {70,64}  
};

/**********上面参数是固定的，下面的参数是可变的*********/
int NcMax = 100;
#define M 50  //number of ant 
double  alpha = 1; 	//信息启发因子，
double 	 beta = 5;  	//期望启发式因子  
double 	  rou = 0.2;   //全局信息素挥发参数    
double alpha1 = 0.1;//局部信息素挥发参数
double  qzero = 0.1; //状态转移公式中的q0 
/**********问题三结束*********/


//局部更新时候使用的的常量，它是由最近邻方法得到的一个长度  
//什么是最近邻方法?:)就是从源节点出发，每次选择一个距离最短的点来遍历所有的节点得到的路径  
//每个节点都可能作为源节点来遍历 
double Lnn = 0;

double allDistance[N][N];

//计算两个城市之间的距离 
double calculateDistance(int i, int j)
{
	return sqrt( pow((C[i][0]-C[j][0]),2.0) + pow((C[i][1]-C[j][1]),2.0) );
}

//由矩阵表示两两城市之间的距离  
void calculateAllDistance()  
{  
    for(int i = 0; i < N; i++)  
    {  
        for(int j = 0; j < N; j++)  
        {  
            if (i != j)  
            {  
                allDistance[i][j] = calculateDistance(i, j);  
                allDistance[j][i] = allDistance[i][j];  
            }  
        }  
    }  
}

double calculateSumOfDistance(int* tour)  
{  
    double sum = 0;  
    for(int i = 0; i< N ;i++)  
    {  
        int row = *(tour + 2 * i);  
        int col = *(tour + 2* i + 1);  
        sum += allDistance[row][col];  
    }  
    return sum;  
}  
  

class ACSAnt;

class AntColonySystem
{
private:
	double info[N][N],visible[N][N];
public:
	AntColonySystem()
	{
	}
	void InitParameter(double value);

	double Transition(int i, int j);

	void UpdateLocalPathRule(int i, int j);

	void UpdateGlobalPathRule(int* bestTour, int globalBestLength);
};

void AntColonySystem::InitParameter(double value)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			info[i][j] = value;
			info[j][i] = value;
			if( i != j)
			{
				visible[i][j] = 1.0/allDistance[i][j];
				visible[j][i] = visible[i][j];
			}
		}
	}
}


double AntColonySystem::Transition(int i, int j)
{
	if(i != j)
	{
		return pow(info[i][j],alpha) * pow(visible[i][j],beta);
	}
	else {return 0.0;}
}

void AntColonySystem::UpdateLocalPathRule( int i, int j)
{
    info[i][j] = (1.0 - alpha1) * info[i][j] + alpha1 * (1.0 / (N * Lnn));  //what the mean of the second???????
	info[j][i] = info[i][j];
}

void AntColonySystem::UpdateGlobalPathRule(int* bestTour, int globalBestLength)
{
	for(int i=0;i<N;i++)
	{
		int row = *(bestTour + 2*i);
		int col = *(bestTour + 2*i + 1);
		info[row][col] = (1.0 - rou) * info[row][col] + rou * (1.0/globalBestLength);
		info[col][row] = info[row][col];
	}
}





class ACSAnt
{
private:
	AntColonySystem* antColony;
protected:
	int startCity,currentCity;
	int allowed[N];
	int Tour[N][2];
	int currentTourIndex;
public:
	ACSAnt(AntColonySystem* acs, int start)
	{
		antColony = acs;
		startCity = start;
	}
	int* Search();
	int Choose();
	void MoveToNextCity(int nextCity);
};

int* ACSAnt::Search()
{
	currentCity = startCity;
	int toCity;
	currentTourIndex = 0;
	for(int i=0;i<N;i++)
	{
		allowed[i] = 1;
	}
	allowed[currentCity] = 0;
	int endCity = 0;
	int count = 0;
	do
	{
		count++;
		endCity = currentCity;
		toCity = Choose();
		if(toCity >= 0)
		{
			MoveToNextCity(toCity);
			antColony->UpdateLocalPathRule(endCity,toCity);
		}
	}while(toCity >= 0);
	MoveToNextCity(startCity);
	antColony->UpdateLocalPathRule(endCity,startCity);

	return *Tour;
}


int ACSAnt::Choose()
{
	int nextCity = -1;
	double q = rand()/(double)RAND_MAX;
	if(q <= qzero)
	{
		double probability = -1.0;
		for(int i=0;i<N;i++)
		{
			if(allowed[i] == 1)
			{
				double prob_temp = antColony->Transition(currentCity,i);
				if( prob_temp > probability)
				{
					nextCity = i;
					probability = prob_temp;
				}
			}
		}
	}
	else
	{
		double     		  p = rand()/(double)RAND_MAX;
		double 		    sum = 0.0;
		double  probability = 0.0;
		for(int i=0;i<N;i++)
		{
			if(allowed[i] == 1)
			{
				sum += antColony->Transition(currentCity,i);
			}
		}
		for(int j=0;j<N;j++)
		{
			if(allowed[j] == 1  &&  sum > 0 )
			{
				probability += 	antColony->Transition(currentCity,j)/sum;
				if(probability >= p || (p > 0.9999 && probability >0.9999))
				{
					nextCity = j;
					break;
				}
			}
		}
	}
	return nextCity;
}

void ACSAnt::MoveToNextCity(int nextCity)
{
	allowed[nextCity] = 0;
	Tour[currentTourIndex][0] = currentCity;
	Tour[currentTourIndex][1] = nextCity;
	currentTourIndex ++;
	currentCity = nextCity;
}

int ChooseNextNode(int currentNode, int visitedNode[])
{
	int nextNode = -1;
	double shortDistance = 0.0;
	for(int i=0;i<N;i++)
	{
		if(visitedNode[i] == 1)
		{
			if(shortDistance == 0.0)
			{
				shortDistance = allDistance[currentNode][i];
				nextNode = i;
			}
			if(allDistance[currentNode][i] < shortDistance)
			{
				shortDistance = allDistance[currentNode][i];
				nextNode = i;

			}
		}
	}
	return nextNode;
}

// int ChooseNextNode(int currentNode, int visitedNode[])  
// {  
//     int nextNode = -1;        
//     double shortDistance = 0.0;  
//     for(int i = 0; i < N; i++)  
//     {  
//         //去掉已走过的节点,从剩下节点中选择距离最近的节点  
//         if (1 == visitedNode[i])  
//         {             
//             if (shortDistance == 0.0)  
//             {  
//                 shortDistance = allDistance[currentNode][i];  
//                 nextNode = i;  
//             }  ////////////////////////////////////////[nextNode]???
//             if(shortDistance < allDistance[currentNode][i])  
//             {  
//                 nextNode = i;  
//             }  
//         }  
//     }  
//     return nextNode;  
// } 

double CalAdjacentDistance(int node)
{
	double sum = 0.0;
	int visitedNode[N];
	for(int j=0;j<N;j++)
	{
		visitedNode[j] = 1;
	}
	visitedNode[node] = 0;
	int currentNode = node;
	int nextNode;
	do
	{
		nextNode = ChooseNextNode(currentNode,visitedNode);
		if(nextNode >= 0)
		{
			sum += allDistance[currentNode][nextNode];
			currentNode = nextNode;
			visitedNode[nextNode] = 0;
		}
	}while(nextNode >=0);
	sum += allDistance[currentNode][node];
	return sum;
}


int main()  
{  
    time_t timer,timerl;  
  
    time(&timer);  
    unsigned long seed = timer;  
    seed %= 56000;  
    srand((unsigned int)seed);//init of rand()  
  
    //由矩阵表示两两城市之间的距离  
    calculateAllDistance();  
    //蚁群系统对象  
    AntColonySystem* acs = new AntColonySystem();  
    ACSAnt* ants[M];  
    //蚂蚁均匀分布在城市上  
    for(int k = 0; k < M; k++)  
    {  
        ants[k] = new ACSAnt(acs, (int)(k%N));  
    }  
   // calculateAllDistance();  
    //随机选择一个节点计算由最近邻方法得到的一个长度  
    int node = rand() % N;  
    Lnn = CalAdjacentDistance(node);  
      
    //各条路径上初始化的信息素强度  
    double initInfo = 1 / (N * Lnn);  
    acs->InitParameter(initInfo);      
      
    //全局最优路径  
    int globalTour[N][2];  
    //全局最优长度  
    double globalBestLength = 0.0;    
    for(int i = 0; i < NcMax; i++)  
    {  
        //局部最优路径  
        int localTour[N][2];  
        //局部最优长度  
        double localBestLength = 0.0;  
        //当前路径长度  
        double tourLength;  
        for(int j = 0; j < M; j++)  
        {  
            int* tourPath = ants[j]->Search();  
            tourLength = calculateSumOfDistance(tourPath);                
            //局部比较，并记录路径和长度  
            if(tourLength < localBestLength || abs(localBestLength - 0.0) < 0.000001)  
            {                 
                for(int m = 0; m< N; m++)  
                {  
                    int row = *(tourPath + 2 * m);  
                    int col = *(tourPath + 2* m + 1);  
                    localTour[m][0] = row;  
                    localTour[m][1] = col;  
                }  
                localBestLength = tourLength;             
            }  
        }  
        //全局比较，并记录路径和长度  
        if(localBestLength < globalBestLength || abs(globalBestLength - 0.0) < 0.000001)  
        {                 
            for(int m = 0; m< N; m++)  
            {  
                globalTour[m][0] = localTour[m][0];  
                globalTour[m][1] = localTour[m][1];  
            }  
            globalBestLength = localBestLength;   
        }  
        acs->UpdateGlobalPathRule(*globalTour, globalBestLength);  
        //输出所有蚂蚁循环一次后的迭代最优路径 
         if(i%1 == 0) 
         {
          cout<<"第 "<<i + 1<<" 迭代最优路径:"<<localBestLength<<"."<<endl;  
             // for(int m = 0; m< N; m++)  
             // {  
             //     cout<<localTour[m][0]<<".";  
             // }  
             cout<<endl;  
         }       
    }     
    //输出全局最优路径  
    cout<<"全局最优路径长度:"<<globalBestLength<<endl;      
    cout<<"全局最优路径:";  
    for(int m = 0; m< N; m++)  
    {  
        cout<<globalTour[m][0]<<".";  
    }  
    cout<<endl;  
    time(&timerl);  
    int t = timerl - timer;  
    cout<<Lnn<<endl;  
    return 0;  
}  









// int main()
// {
// 	time_t timer,timerl;
// 	time(&timer);
// 	unsigned long seed = timer;
// 	seed %= 56000;
// 	srand((unsigned int)seed);

// 	calculateAllDistance();

// 	AntColonySystem* acs = new AntColonySystem();
// 	ACSAnt*          ants[M];
// 	for(int k=0;k<M;k++)
// 	{
// 		ants[k] = new ACSAnt(acs, (int)(k%N));
// 	}

// 	int node = rand() % N;
// 	Lnn = CalAdjacentDistance(node);

// 	double initInfo = 1/(N * Lnn);
// 	acs->InitParameter(initInfo);

// 	int globalTour[N][2];
// 	double globalBestLength = 0.0;
// 	for(int i=0;i<NcMAX;i++)
// 	{
// 		int 	localTour[N][2];
// 		double  localBestLength = 0.0;
// 		double  tourLength;
// 		for(int j=0;j<M;j++)
// 		{
// 			int* tourPath = ants[j]->Search();
// 			tourLength = calculateSumOfDistance(tourPath);
// 			if(tourLength < localBestLength || abs(localBestLength -0.0) < 0.00001)
// 			{
// 				for(int m=0;m<N;m++)
// 				{
// 					int row = *(tourPath + 2*m);
// 					int col = *(tourPath + 2*m + 1);
// 					localTour[m][0] = row;
// 					localTour[m][1] = col;
// 				}
// 				localBestLength = tourLength;
// 			}
// 		}
// 		if(localBestLength < globalBestLength || abs(globalBestLength - 0.0) < 0.000001)  
//         {                 
//             for(int m = 0; m< N; m++)  
//             {  
//                 globalTour[m][0] = localTour[m][0];  
//                 globalTour[m][1] = localTour[m][1];  
//             }  
//             globalBestLength = localBestLength;   
//         }  
//         acs->UpdateGlobalPathRule(*globalTour,globalBestLength);

//         cout<<"第 "<<i + 1<<" 迭代最优路径:"<<localBestLength<<"."<<endl;  
// 	}
// 	 cout<<"全局最优路径长度:"<<globalBestLength<<endl;
// 	 time(&timerl);
// 	 int t = timerl - timer;
// 	 cout<<"total time:"<<t<<endl;
// 	 return 0;
// }

