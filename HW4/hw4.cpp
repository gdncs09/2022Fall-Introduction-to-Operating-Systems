#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int FIFO(int pages[], int N_PAGES, int N_FRAMES)
{
          vector<int>  frames;
          int page_fault = 0;
          for (int i = 0; i < N_PAGES; i++)
          {
                    if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) //not present
                    {
                              page_fault++;
                              if  (frames.size() == N_FRAMES)
                                        frames.erase(frames.begin());
                              frames.push_back(pages[i]);
                    }
          }
          return page_fault;
}

int LRU(int pages[], int N_PAGES, int N_FRAMES)
{
          vector<int> frames;
          int page_fault = 0;
          for (int i = 0; i < N_PAGES; i++)
          {
                    auto id = find(frames.begin(), frames.end(), pages[i]);
                    if (id == frames.end()) //not present
                    {
                              page_fault++;
                              if (frames.size() == N_FRAMES)
                                        frames.erase(frames.begin());
                              frames.push_back(pages[i]);
                    }
                    else //present
                    {
                              frames.erase(id);
                              frames.push_back(pages[i]);
                    }
          }
          return page_fault;
}

int LFU(int pages[], int N_PAGES, int N_FRAMES)
{
          vector<int> frames;
          unordered_map<int, int> freq, time;
          int page_fault = 0;
          for (int i = 0; i < N_PAGES; i++)
          {
                    auto id = find(frames.begin(), frames.end(), pages[i]);
                    if(id == frames.end()) //not present
                    {
                              page_fault++;
                              if (frames.size() == N_FRAMES) //full
                              {
                                        freq[frames[0]]=0;
                                        frames.erase(frames.begin());
                              }
                              frames.push_back(pages[i]);
                              time[pages[i]] = i+1;
                              freq[pages[i]]++;
                    }
                    else //present
                    {
                              frames.erase(id);
                              frames.push_back(pages[i]);
                              freq[pages[i]]++;
                    }
                    for (int i = frames.size()-2; i >= 0; i--) //sort
                    {
                              if (freq[frames[i]] > freq[frames[i+1]]) //frequency
                                        swap(frames[i], frames[i+1]);
                              if (freq[frames[i]] == freq[frames[i+1]] && time[frames[i]] > time[frames[i+1]]) //time
                                        swap(frames[i], frames[i+1]);
                    }
          }
          return page_fault;
}

int main()
{
          int N_FRAMES, N_PAGES;
          cin >> N_FRAMES;
          cin >> N_PAGES;
          int pages[N_PAGES];
          for (int i = 0; i < N_PAGES; i++)
          {
                    cin >> pages[i];
          }
          cout << FIFO(pages, N_PAGES, N_FRAMES) << endl;
          cout << LRU(pages, N_PAGES, N_FRAMES) << endl;
          cout << LFU(pages, N_PAGES, N_FRAMES);
          return 0;
}
