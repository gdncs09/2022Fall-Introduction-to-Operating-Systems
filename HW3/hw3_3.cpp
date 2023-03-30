#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct process
{
          int id = 0;
          int arrival = 0;
          int burst = 0;
          int priority = 0;
          int waiting_time = 0;
          int turnaround_time = 0;
          bool finished = false;
};

void RR(process &P, int &time, int time_quantum)
{
          if (P.burst <= time_quantum)
          {
                    time += P.burst;
                    P.finished = true;
          }
          else
          {
                    time += time_quantum;
                    P.arrival  = time;
                    P.burst -= time_quantum;
                    P.priority = 1;
          }
}

int main()
{
          int N, time_quantum;
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
          cin >> time_quantum;

          vector <process> process_tmp = process_list;
          queue <int> low_priority;
          int process_finished = 0; //count finished process
          int time = 0;
          int index = -1;
          while (process_finished < N)
          {
                    for (int i  = 0; i < N; i++)
                    {
                              if (process_tmp[i].arrival <= time && process_tmp[i].priority == 0 && !process_tmp[i].finished) //high priority queue
                              {

                                        if (index != -1 && !process_tmp[index].finished)
                                        {
                                                  low_priority.push(index);
                                                  index = -1;
                                        }
                                        process_list[i].waiting_time += time - process_tmp[i].arrival;
                                        RR(process_tmp[i], time, time_quantum);
                                        if (!process_tmp[i].finished)
                                                  low_priority.push(i);
                                        else
                                        {
                                                  process_finished += 1;
                                                  process_list[i].turnaround_time = time - process_list[i].arrival;
                                        }

                                        continue;
                              }
                    }

                    if (!low_priority.empty() && index == -1)
                    {
                              index = low_priority.front();
                              process_list[index].waiting_time += time - process_tmp[index].arrival;
                              low_priority.pop();
                    }
                    time += 1;
                    if (index != -1)
                    {
                              process_tmp[index].burst -= 1;

                              if (process_tmp[index].burst == 0)
                              {
                                        process_list[index].turnaround_time = time - process_list[index].arrival;
                                        process_tmp[index].finished = true;
                                        process_finished += 1;
                                        index = -1;
                              }
                              else
                              {
                                        process_tmp[index].arrival = time;
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


