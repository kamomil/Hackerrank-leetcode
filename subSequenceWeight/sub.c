#include <bits/stdc++.h>
#include <map>

using namespace std;

vector<string> split_string(string);

// Complete the solve function below.
unsigned long long solve(vector<int> a, vector<int> w) {

    map<int, unsigned long long> maxi;
    unsigned long long final_max = 0;
    for(int i = 0;i<a.size();i++){
        int key = a[i];
        std::map<int, unsigned long long>::iterator itlow = maxi.lower_bound(key);
        unsigned long long max = 0;
        for (std::map<int, unsigned long long>::iterator it=maxi.begin(); it!=itlow; ++it){

            int k = it->first;
            unsigned long long v = it->second;
            if(v>max)
                max = v;
            if(w[i] == 50 || w[i] == 30)
                cout << k <<"," << v << "\n";
        }
        unsigned long long m = maxi[key];
        if(m < max + w[i])
            maxi[key] = max + w[i];
        if(max + w[i] > final_max){
            final_max = max + w[i];
            //cout << i <<","<<final_max << "\n";
        }
    }

        //cout << value << "bla\n";
    return final_max;

}

int main()
{
  ofstream fout(getenv("OUTPUT_PATH"));

  int t;
  cin >> t;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int t_itr = 0; t_itr < t; t_itr++) {
    int n;
    cin >> n;



    vector<int> a(n);
    vector<int> w(n);

    for(int i =0;i<n;i++)
      scanf("%d",&a[i]);
    for(int i =0;i<n;i++)
      scanf("%d",&w[i]);



    unsigned long result = solve(a, w);

    cout << result << "\n";
  }
  return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
