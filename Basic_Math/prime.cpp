#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int limit = sqrt(n);
    int c = 0;
    for (int i = 2; i <= limit; i++)
    {
        if (n % i == 0)
        {
            c++;
        }
    }
    if (c > 0)
    {
        cout << "Not Prime";
    }
    else
    {
        cout << "Prime";
    }
}