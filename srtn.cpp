#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
using namespace std;
std::ifstream infile( "insrt.txt" );
 
class SRTN
	{
	public:
    	int p[5],st[5],at[5],tat[5],wt[5],rt[5],ft[5],twt,ttat,total,meanwt,initwt,interwt,meantat;
		int n;
    	void readInputFile();
    	void computeSRTN();
    	void Initialize();
    	void Output();
    	int getNextProcess(int);
    	};
 
void SRTN::readInputFile()
	{
	int i;
	n=5;
	ifstream infile;
	infile.open("insrt.txt");
	for(i=0;i<n;i++)
			{
			infile >> p[i];
			infile >> at[i];
			infile >> st[i];
			}
	infile.close();
	} 
 
void SRTN::Initialize()
    {
    total=0;
    twt=0;
    ttat=0;
    n=5;
    for(int i=0; i<n; i++){
        rt[i]=st[i];
        ft[i]=0;
        wt[i]=0;
        tat[i]=0;
        total+=st[i];
        }
    }
 
void SRTN::computeSRTN(){
    readInputFile();
    Initialize();
    int time,next=0,old,i;
    cout<<"Gantt Chart or process schedule\n ";
    for(time=0;time<total;time++)
    	{
        old=next;
        next=getNextProcess(time);
        if(old!=next || time==0) cout<<"("<<time<<")|==P"<<next+1<<"==|";
        rt[next]=rt[next]-1;
        if(rt[next]==0) ft[next]=1;
        for(i=0;i<n;i++)
            if(i!=next && ft[i]==0 && at[i]<=time)
                wt[i]++;
     	}
    	cout << "(" << total << ")" <<endl;
    	Output();
	}
 
void SRTN::Output()
	{
   	for(int i=0;i<n;i++)
    		{
		twt+=wt[i];
		tat[i]=wt[i]+st[i];
		ttat+=tat[i];
		cout << " Total waiting time for P" << (i+1) << " = " << wt[i] << ", Total turnaround time = " << tat[i] << endl;
     		}
    	cout << "Mean Waiting time = "<<(double)twt/n<<" and Mean Turnaround time = "<<(double)ttat/n<<endl;
    	}
 
int SRTN::getNextProcess(int time)
	{
        int i,low;
        for(i=0;i<n;i++)
            if(ft[i]==0)
		{
		low=i; 
		break; 
		}
        for(i=0;i<n;i++)
            if(ft[i]!=1)
                if(rt[i]<rt[low] && at[i]<=time)
                        low=i;
        return low;
	}
 

int main()
	{
	SRTN s;
   	s.computeSRTN();
	}
