#include <iostream>
#include <conio.h>
using namespace std;

int fcfs()
{
    int n;
    cout << "enter number of process : ";
    cin >> n;
    int burst[n];
    for (int i = 0; i < n; i++)
    {
        cout << "enter burst time of process : ";
        cin >> burst[i];
    }
    int wait[n];
    wait[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wait[i] = burst[i - 1] + wait[i - 1];
    }
    int turn_arount_time[n];
    for (int j = 0; j < n; j++)
    {
        turn_arount_time[j] = wait[j] + burst[j];
    }
    int avarage_wait = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + wait[i];
    }
    avarage_wait = sum / n;
    cout << "average waiting time is " << avarage_wait << endl;

    int average_turn;
    int sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum2 = sum2 + turn_arount_time[i];
    }
    average_turn = sum2 / n;
    cout << "average turnaround time is " << average_turn << endl;
    return 0;
}

int sjf()
{
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;
    cout<<"Enter number of process:";
    cin>>n;

    cout<<"\nEnter Burst Time:\n";
    for (i = 0; i < n; i++)
    {
        cout<<"p"<<i+1<<": ";
        cin>>bt[i];
        p[i] = i + 1;
    }

    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (bt[j] < bt[pos])
                pos = j;
        }

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0;

    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];

        total += wt[i];
    }

    avg_wt = (float)total / n;
    total = 0;

    cout<<"\nProcesst    Burst Time    \tWaiting Time\tTurnaround Time";
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        cout<<endl<<p[i]<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
    }

    avg_tat = (float)total / n;
    cout<<"\n\nAverage Waiting Time = "<<avg_wt;
    cout<<"\nAverage Turnaround Time = "<<avg_tat;
    getch();
    return 0;
}

int prio_Sch()
{
    int bt[20], p[20], wt[20], tat[20], pr[20], i, j, n, pos, temp;
    float total = 0 , avg_wt, avg_tat;
    cout << "Enter Total Number of Process:";
    cin >> n;

    cout << "\nEnter Burst Time and Priority\n";
    for (i = 0; i < n; i++)
    {
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Burst_Time:";
        cin >> bt[i];
        cout << "Priority:";
        cin >> pr[i];
        p[i] = i + 1;
    }

    //sorting
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (pr[j] < pr[pos])
                pos = j;
        }

        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0;

    //calculate waiting time
    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];

        total += wt[i];
    }
    //average waiting time
    avg_wt = total / n;
    total = 0;

    cout << "\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i]; 
        total += tat[i];
        cout << "\nP" << p[i] << "\t\t  " << bt[i] << "\t\t    " << wt[i] << "\t\t\t" << tat[i];
    }

    avg_tat = total / n; 
    cout << "\n\nAverage Waiting Time=" << avg_wt;
    cout << "\nAverage Turnaround Time=" << avg_tat;
    return 0;
}

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

int Round_robin()
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

int main()
{
    int user_choice;

Menu:
    cout<<endl<<"Press 1 for FCFS"<<endl;
    cout<<"Press 2 for SJF"<<endl;
    cout<<"Press 3 for Priority Scheduling"<<endl;
    cout<<"Press 4 for Round Robin Scheduling"<<endl;
    cout<<"Press 0 to go back to MENU"<<endl;
    cout<<"Your Input: ";
    cin>>user_choice;
    
    if (user_choice == 1)
    {
        fcfs();
        int Block_choice;
        cout<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    else if (user_choice == 2)
    {
        sjf();
        int Block_choice;
        cout<<endl<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    else if (user_choice == 3)
    {
        prio_Sch();
        int Block_choice;
        cout<<endl<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    else if (user_choice == 4)
    {
        Round_robin();
        int Block_choice;
        cout<<endl<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    else if (user_choice == 0)
    {
        goto Menu;
        int Block_choice;
        cout<<endl<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    else{
        cout<<"Invalid User Input :-( "<<endl;
        int Block_choice;
        cout<<endl<<"Press 0 to go back to MENU"<<endl;
        cout<<"Press any other key to Exit"<<endl;
        cin>>Block_choice;
        if (Block_choice == 0)
        {
            goto Menu;
        }
        else{
            return 0;
        }
    }
    
    getch();
    return 0;
}