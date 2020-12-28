#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int Parent(int i){
    return floor((i-1)/2);
  }

  int LeftChild(int i){
    return 2*i + 1;
  }

  int RightChild(int i){
    return 2*i + 2;
  }

  void SiftDown(int i){
    
    int maxIndex = i;
    int l = LeftChild(i);

    if (l <= (data_.size()-1) && data_[l] < data_[maxIndex]){
      maxIndex = l;      
    }
    int r = RightChild(i);
    if(r <= (data_.size()-1) && data_[r] < data_[maxIndex]){
      maxIndex = r;
    }

    if(i != maxIndex){
      swap(data_[i], data_[maxIndex]);
      swaps_.push_back(make_pair(i, maxIndex));
      SiftDown(maxIndex);      
    }
  }
  
  void GenerateSwaps() {
    swaps_.clear();

    for(int i = floor((data_.size() -1)/2); i >= 0; i--){
      SiftDown(i);
    }
    
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
