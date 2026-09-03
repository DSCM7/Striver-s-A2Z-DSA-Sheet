#include <bits/stdc++.h>
using namespace std;

void print(int c)
{
    if (c == 0)
    {
        return;
    }
    cout << c << endl;
    print(c - 1);
}

int main()
{
    int c;
    cin >> c;
    print(c);
}
