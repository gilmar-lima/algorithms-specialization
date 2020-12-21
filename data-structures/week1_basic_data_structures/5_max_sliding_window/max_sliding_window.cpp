#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void max_sliding_window(vector<int> const & A, unsigned int w) {
    
    queue<int> window ;
    
    for(int element : A){
	
	window.push(element);
	if(window.size() == w){
	    cout << *max_element(&window.front(),&window.back() + 1) << " ";
	}else if(window.size() > w){
	    window.pop();
	    cout << *max_element(&window.front(),&window.back() + 1) << " ";
	}
	
    }

}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}
