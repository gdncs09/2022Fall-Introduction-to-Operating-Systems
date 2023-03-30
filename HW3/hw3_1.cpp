#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process
{
          int id = 0;
          int arrival = 0;
          int burst = 0;
          int waiting_time = 0;
          int turnaround_time = 0;
          bool finished = false;
};

bool compare_burst_time(const process &a, const process &b)
{
          return (a.burst < b.burst) || (a.burst == b.burst && a.id < b.id);
}

int main()
{
          int N;
          cin >> N;
          vector <process> process_list(N);
          for (int i = 0; i < N; i++)
          {
                    process_list[i].id = i;
                    cin >> process_list[i].arrival;
          }
          for (int i = 0; i < N; i++)
          {
                    cin >> process_list[i].burst;
          }
          vector <process> process_queue = process_list;
          int process_finished = 0;
          int time= 0;
          int index = 0;
          while (process_finished< N)
          {
                    sort(process_queue.begin(), process_queue.end(), compare_burst_time);
                    int index = -1;
                    int i = 0;
                    for (i = 0; i < N; i++)
                    {
                              if (process_queue[i].arrival <= time && !process_queue[i].finished)
                              {
                                        for (int j = 0; j < N; j++)
                                        {
                                                  if (process_list[j].id == process_queue[i].id)
                                                  {
                                                            index  = j;
                                                            break;
                                                  }
                                        }
                                        process_queue[i].burst -= 1;
                                        process_list[index].waiting_time += time - process_queue[i].arrival;
                                        break;
                              }
                    }
                    time += 1;
                    if (index != -1)
                    {
                              process_queue[i].arrival = time; //update
                              if (process_queue[i].burst == 0)
                              {
                                        process_finished += 1;
                                        process_list[index].turnaround_time = time - process_list[index].arrival;
                                        process_queue[i].finished = true;
                              }
                    }
          }
          int total_waiting_time = 0;
          int total_turnaround_time = 0;
          for (int i = 0; i < N; i++)
          {
                    total_waiting_time += process_list[i].waiting_time;
                    total_turnaround_time += process_list[i].turnaround_time;
                    cout << process_list[i].waiting_time << " " << process_list[i].turnaround_time << endl;
          }
          cout << total_waiting_time << endl;
          cout << total_turnaround_time << endl;
          return 0;
}
