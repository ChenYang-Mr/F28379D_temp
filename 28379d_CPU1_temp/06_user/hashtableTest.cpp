#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

Solution dd;
int main()
{
   // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

   // for (const string& word : msg)
   // {
   //    cout << word << " ";
   // }
   // cout << endl;
   std::vector<int> ss= {1,2,4};
   std::vector<int> ff;
   int y = 6;
   ff = dd.twoSum(ss,y);
   while(1);
}