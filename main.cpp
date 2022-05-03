//
//  main.cpp
//  Bagpack
//
//  Created by Сергей Пиденко on 03.05.2022.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int solve(int n, vector<int> Val_s, vector<int> Weight, int W) {
    vector<int> memo1(W+1, 0);
    vector<int> memo2(W+1, 0);
    for (int i = 1; i <= n; i++)
    
    {
        vector<int> Tmp = memo1;
        memo1 = memo2;
        memo2 = Tmp;
        for (int k = 0; k <= W; k++)
        {
            memo2[k] = memo1[k];
            if (k - Weight[i - 1] >= 0)
            {
                memo2[k] = max(memo2[k], memo1[k - Weight[i-1]] + Val_s[i-1]);
            }
        }
    }
    int Res_t = 0;
    for (int i = W; i >= 0; i--)
    {
        if(memo2[i] != 0) {
            Res_t = memo2[i];
            break;
        }
    }
    return Res_t;
}

int main() {
    string path = "/Users/Sergej/data2";
       auto it = fs::directory_iterator(path);
       vector<fs::path> array_path;
       copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
           [](const auto& entry)
               {
               return fs::is_regular_file(entry);
       });
    for (auto& p : array_path)
    {
        ifstream fin;
        fin.open(p.string());
        cout << p.string() << endl;
        int n, W;
        fin >> n >> W;
        vector<int> Val_s;
        vector<int> Weight;
        int i=0;
        while(i<n)
        {
            int Val_, Weight_;
            fin >> Val_ >> Weight_;
            Val_s.push_back(Val_);
            Weight.push_back(Weight_);
            i++;
        }
        int Max_Val = solve(n, Val_s, Weight, W);
        cout << Max_Val << endl;
    }
    return 0;
}
