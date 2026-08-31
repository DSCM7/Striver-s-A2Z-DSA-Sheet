#include <bits/stdc++.h>
using namespace std;

void print(int n, int c)
{
    if (c > n)
    {
        return;
    }
    cout << c << endl;
    print(n, c + 1);
}

int main()
{
    int n;
    cin >> n;

    print(n, 1);

    return 0;
}