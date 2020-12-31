#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;
  struct worker{
    int worker_id;
    long long time;
  };

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
   
  void AssignJobs() {

    //Lambda function for comparison
    auto comparison = [](worker a, worker b){

      if(a.time == b.time){
        return a.worker_id > b.worker_id;
      }
        return a.time > b.time;    
    };
    
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    priority_queue<worker, vector<worker>, decltype(comparison)> next_free_worker (comparison);

    for(int i = 0; i < num_workers_; i++){
      worker w {i,0};
      next_free_worker.push(w);
    }        

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      worker next_worker = next_free_worker.top();
      next_free_worker.pop();
           
      assigned_workers_[i] = next_worker.worker_id;
      start_times_[i] = next_worker.time;
      next_worker.time += duration;

      next_free_worker.push(next_worker);
    }
    
    
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
