#include <bits/stdc++.h>
using namespace std;

void sum(int n, int c, int &s)
{
    if (c > n)
    {
        return;
    }
    s += c;
    sum(n, c + 1, s);
}

void sum(int n, int &s)
{
    s = n * (n + 1) / 2;
}

int main()
{
    int n;
    cin >> n;

    int s = 0;
    sum(n, 1, s);
    cout << s << endl;

    sum(n, s);
    cout << s << endl;

    return 0;
}