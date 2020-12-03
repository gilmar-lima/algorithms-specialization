#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int edit_distance(const string &str1, const string &str2) {

    int E [str1.length()+1][str2.length()+1];
    int insertion, deletion, match, mismatch;

    for(int i = 0; i <= str1.length(); i++) E[i][0] = i;
    for(int j = 0; j <= str2.length(); j++) E[0][j] = j;

    for(int i = 1; i <= str1.length(); i++){
	for(int j = 1; j <= str2.length(); j++){

	    insertion = E[i][j-1] + 1;
	    deletion = E[i-1][j] + 1;
	    match = E[i-1][j-1];
	    mismatch = E[i-1][j-1] + 1;

	    if(str1[i-1] == str2[j-1]){
		E[i][j] = min(insertion, min(deletion, match));
	    }else{
		E[i][j] = min(insertion, min(deletion, mismatch));
	    }
	    
	}
    }
    
    
    
    return E [str1.length()][str2.length()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
