#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void print(int n, string s, int c)
    {
        if (c > n)
        {
            return;
        }

        cout << s << endl;
        print(n, s, c + 1);
    }
};

int main()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    Solution obj;
    obj.print(n, s, 1);

    return 0;
}