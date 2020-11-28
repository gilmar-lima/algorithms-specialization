#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int before(int point, vector<int> &starts){

    int count = starts.size();

    for(int s : starts){
	if(point < s){
	    break;
	}else{
	    count--;
	}    
    }

    return count;  
}

int after(int point, vector<int> &ends){

    int count = 0;

    for(int e : ends){
	if(point > e)
	{
	    count++;
	}else{
	    break;
	}    
    }

    return count;  
}



vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());

    sort(starts.begin(),starts.end());
    sort(ends.begin(), ends.end());

    for(int i = 0; i < points.size(); i++){
	cnt[i] = starts.size() - before(points[i], starts) - after(points[i], ends);
    }
  
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
	std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
	std::cin >> points[i];
    }
  
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
	std::cout << cnt[i] << ' ';
    }
}
