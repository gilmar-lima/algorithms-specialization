#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <climits>
#include <queue>

using namespace std;


class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

  private:
    vector<vector<int> > adj;
    vector<vector<int>> capacity;
    vector<vector<int>> flows;

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  void fill_source_connections(const vector<vector<bool>>& adj_matrix){
    int num_flights = adj_matrix.size();

    for (int flight = 1; flight <= num_flights; ++flight) {
      adj[0].push_back(flight);
      capacity[0][flight] = 1;
      adj[flight].push_back(0);      
    }
  }

  void fill_sink_connections(const vector<vector<bool>>& adj_matrix){
    int num_flights = adj_matrix.size();
    int num_crews = adj_matrix[0].size();
    int sink = adj_matrix.size() + adj_matrix[0].size() + 1;    

    for (int crew = num_flights + 1; crew <= num_crews + num_flights; ++crew) {
      adj[crew].push_back(sink);
      capacity[crew][sink] = 1;
      adj[sink].push_back(crew);
    }
  }

  void fill_flight_to_crew_connections(const vector<vector<bool>>& adj_matrix){
    int num_flights = adj_matrix.size();
    int num_crews = adj_matrix[0].size();

    for (int flight = 1; flight <= num_flights; ++flight) {
      for (int crew = num_flights + 1; crew <= num_flights + num_crews; ++crew) {

        if(!adj_matrix[flight -1][crew -1 -num_flights]) continue;        

        adj[flight].push_back(crew);
        capacity[flight][crew] = 1;
        adj[crew].push_back(flight);
      }      
    }
  }

  void create_data_structures(const vector<vector<bool>>& adj_matrix){
    int num_nodes = adj_matrix.size() + adj_matrix[0].size() + 2;
    int num_crews = adj_matrix[0].size();


    vector<vector<int> > adj_input(num_nodes, vector<int>());
	  vector<vector<int> > capacity_input(num_nodes, vector<int>(num_nodes,0));

    adj = adj_input;
		capacity = capacity_input;
		flows = capacity_input;

    fill_source_connections(adj_matrix);
    fill_sink_connections(adj_matrix);
    fill_flight_to_crew_connections(adj_matrix);

  }

  int bfs(int s, int t, vector<int>& parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;
		queue<pair<int, int>> q;
		q.push({s, INT_MAX});

		while (!q.empty()) {
		  int cur = q.front().first;
			int flow = q.front().second;
			q.pop();

			for (int next : adj[cur]) {
				if (parent[next] == -1 && capacity[cur][next]) {
					parent[next] = cur;
					int new_flow = min(flow, capacity[cur][next]);
					if (next == t) return new_flow;
					q.push({next, new_flow});
				}
			}
		}

	  return 0;
  }

  int max_flow(int s, int t) {
		int flow = 0;
		vector<int> parent(adj.size());
		int new_flow;

		while (new_flow = bfs(s, t, parent)) {
			flow += new_flow;
			int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= new_flow;
				flows[prev][cur] += new_flow;
				capacity[cur][prev] += new_flow;
				cur = prev;
			}
		}

		return flow;
  }

  vector<int> build_matching(const vector<vector<bool>>& adj_matrix){
    int num_flights = adj_matrix.size();
    int num_crews = adj_matrix[0].size();
    vector<int> matching(num_flights, -1);

    for (int flight = 1; flight <= num_flights; ++flight) {
      for (int crew = num_flights + 1; crew <= num_flights + num_crews; ++crew) {
        if(!(flows[flight][crew] == 1)) continue;
        matching[flight -1] = crew - num_flights -1;        
      }      
    }

    return matching;
  }


  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
   
    int num_flights = adj_matrix.size();
    int num_crews = adj_matrix[0].size();
    int t = adj_matrix.size() + adj_matrix[0].size() + 1;

    create_data_structures(adj_matrix);
    max_flow(0,t);
    return build_matching(adj_matrix);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
