#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    
    stops.push_back(dist);
    stops.push_back(0);
    sort(stops.begin(), stops.end());
   
    int num_refils = 0;
    int current_refil = 0;
    int last_refil = 0;
    int num_stops = stops.size();
    
    while (current_refil < num_stops - 1) {
	last_refil = current_refil;

	while ((current_refil + 1 < num_stops) &&
	       (stops[current_refil + 1] - stops[last_refil] <= tank)) {
	    current_refil++;	    
	}

	if(current_refil == last_refil)
	    return -1;

	if(current_refil < num_stops - 1)
	    num_refils++;
    }
    return num_refils;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
