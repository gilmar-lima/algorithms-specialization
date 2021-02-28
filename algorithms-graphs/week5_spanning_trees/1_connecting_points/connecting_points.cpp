#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>

using namespace std;

struct point{
  int value;
  int x,y;
  int prev;
  double cost;

  point(int x, int y) : x(x), y(y) {
    prev = -1;
    cost = INFINITY;
  }

  point(){
    prev = -1;
    cost = INFINITY;
  }
};

double distance(point a, point b){
  double result = (double) sqrt (pow (a.x - b.x, 2) + pow (a.y - b.y, 2));
  return result;
}

double total_length(const vector<point> &V){
  double result = 0.0;
  for (auto &&i : V)
  {
    result += i.cost;
  }
  return result;  
}

void fill_coordinates(vector<int> &x, vector<int> &y, vector<point> &V){
  for (size_t i = 0; i < x.size(); i++)
  {
    V[i].value = i;
    V[i].x = x[i];
    V[i].y = y[i];
  }  
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.0;
  
  auto comparison = [](point a, point b){
    return a.cost > b.cost;          
  };
  priority_queue<point, vector<point>, decltype(comparison)> H (comparison);
  unordered_set<int> R;
  vector<point> V (x.size());
  fill_coordinates(x,y,V);

  V[0].cost = 0.0;
  H.push(V[0]);
  R.insert(0);
  
  while(H.size() > 0){
    point v = H.top();
    H.pop();
    R.insert(v.value);   

    for (size_t i = 0; i < V.size() ; i++)
    {
      point* z = &V[i];
      //vertex already explored
      unordered_set<int>::const_iterator item = R.find(z->value);
      if(item != R.end()) continue;

      //skip reference to self vertex
      if( i == v.value) continue;

      double weight_v_z = distance(v,*z);

      if (z->cost > weight_v_z){
        z->cost = weight_v_z;
        z->prev = v.value;
        H.push(*z);
      }
    }
  }

  return total_length(V);
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
