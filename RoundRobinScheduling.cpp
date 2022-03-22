#include<iostream>
using namespace std;

// finding the waiting time for all

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum)
{
	int rem_bt[n];
	for (int i = 0 ; i < n ; i++)
    {
        rem_bt[i] = bt[i];
    }

	int t = 0; // Current time
	while (1)
	{
		bool done = true;
		for (int i = 0 ; i < n; i++)
		{
			if (rem_bt[i] > 0)
			{
				done = false;

				if (rem_bt[i] > quantum)
				{
					t += quantum;

					rem_bt[i] -= quantum;
				}
				else
				{
					t = t + rem_bt[i];
					wt[i] = t - bt[i];
					rem_bt[i] = 0;
				}
			}
		}
		if (done == true)
		break;
	}
}

//calculating turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
	for (int i = 0; i < n ; i++)
	{
        tat[i] = bt[i] + wt[i];
    }
}

//calculating average time
void findavgTime(int processes[], int n, int bt[], int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	// finding waiting time of all processes
	findWaitingTime(processes, n, bt, wt, quantum);

	// finding turn around time for all processes
	findTurnAroundTime(processes, n, bt, wt, tat);

	// Display processes along with all details
	cout << "Processes "<< " Burst time "
		<< " Waiting time " << " Turn around time\n";

	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< wt[i] <<"\t\t " << tat[i] <<endl;
	}

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

int main()
{
	// Taking no of process from the user...
    int nop;
    cout<<endl<<"Enter number of process: ";
    cin>>nop;
	int processes[nop];
    for (int i = 0; i < nop; i++)
    {
        processes[i] = i+1;
    }
    
	int n = sizeof processes / sizeof processes[0];

	// taking Burst Time from the user
	int burst_time[nop];
    for (int i = 0; i < nop; i++)
    {
        cout<<endl<<"Enter the Burst Time for process "<<i+1<<" is: ";
        cin>>burst_time[i];
    }
    cout<<endl;
	// Time quantum
	int quantum = 2;
	findavgTime(processes, n, burst_time, quantum);
	return 0;
}