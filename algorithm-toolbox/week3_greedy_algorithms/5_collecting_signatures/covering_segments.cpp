#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment {
  int start, end;
};

bool compare(Segment a, Segment b){
    return a.start < b.start;
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  vector<int> segments_index;
  int  temp_start, temp_end = 0;

  sort(segments.begin(), segments.end(), compare);
  
  while(segments.size() > 0){
      
      segments_index.push_back(0);
      temp_start = segments[0].start;
      temp_end = segments[0].end;
      
      for (size_t i = 1; i < segments.size(); ++i) {
	  if(segments[i].start <= temp_end && segments[i].end >= temp_start){

	      segments_index.push_back(i);

	      if(segments[i].start > temp_start) temp_start = segments[i].start;
	      if(segments[i].end < temp_end) temp_end = segments[i].end;	      
	  }
      }

      points.push_back(temp_start);
      segments.erase(segments.begin(), segments.begin() + segments_index.size());
      segments_index.clear();
  }

  return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
	std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
	cout << points[i] << " ";
    }
}
