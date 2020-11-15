#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    int size = values.size();
    int max_element_index = 0;
    int weight;
    vector<double> relative_values(size);
  
    for(int i = 0; i < size; i++){
	relative_values[i] = (double) values[i]/weights[i];    
    }

    for(int i = 0; i < size; i++){
	if(capacity == 0)
	    return value;

	max_element_index =
	    max_element(relative_values.begin(), relative_values.end())
	    - relative_values.begin();

	weight = min(weights[max_element_index], capacity);
	value = value + (double) weight*relative_values[max_element_index];
	capacity = capacity - weight;
	relative_values[max_element_index] = 0.0;
	
    }
    
    return value;
}

int main() {
    int n;
    int capacity;
    cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
	cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    cout.precision(10);
    cout << optimal_value << endl;
    return 0;
}
