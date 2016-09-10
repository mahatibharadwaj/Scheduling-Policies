#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
using namespace std;
std::ifstream infile("sample.txt");

class RR
{
public:
    int p[5], at[5], st[5], tat[5], wt[5], rst[5], ft[5], twt, ttat, total, mean_wt, ini_wt, inter_wt, mean_tat;
    int n;
    void readInputFile();
    void computeRR();
    void Initialize();
    void dispTime();
}

void RR::readInputFile()
{
    int i;
    n = 5;
    ifstream infile;
    infile.open("sample.txt");
    for (i = 0; i<n; i++)
    {
        infile >> p[i];
        infile >> at[i];
        infile >> st[i];
    }
    infile.close();
}

void RR::Initialize()
{
    total = 0;
    twt = 0;
    ttat = 0;
    n = 5;
    for (int i = 0; i<n; i++)
    {
        rst[i] = st[i];
        ft[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
        total = total + st[i];
    }
}

void RR::computeRR()
{
    readInputFile();
    Initialize();
    int time, j, q, i, dec = 0;
    cout << "Enter the time quantum: \n";
    cin >> q;
    cout << "Gantt chart \n";
    for (time = 0; time<total; time++)
    {
        for (i = 0; i<n; i++)
        {
            if (at[i] <= time && finish[i] == 0)
            {
                cout << "(" << time << ")|==P" << (i + 1) << "==|";
                if (rt[i]<q)
                {

                    dec = rt[i];
                }
                else { dec = q; }

                rt[i] = rt[i] - dec;
                if (rt[i] == 0)
                    finish[i] = 1;
                for (j = 0; j<n; j++)
                    if (j != i && finish[j] == 0 && at[j] <= time)
                        wt[j] = wt[j] + dec;
                time = time + dec;
            }
        }
    }
    cout << "(" << total << ")" << endl;
    dispTime();
}


void RR::dispTime()
{
    for (int i = 0; i<n; i++)
    {
        twt = twt + wt[i];
        tat[i] = wt[i] + st[i];
        ttat += tat[i];
        cout << "Waiting time for P" << (i + 1) << "=" << wt[i] << ",Turnaround time =" << tat[i] << endl;
    }
    cout << "Avg Waiting time = " << (double)twt / n << " and Avg Turnaround time = " << (double)ttat / n << endl;
    cout << "Scheduling complete\n";
}
void main()
{

    RR rr;
    rr.computeRR
}
