#include <iostream>
using namespace std;

int main()
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