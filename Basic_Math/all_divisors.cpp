#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int lim = sqrt(n);
    for (int i = 1; i <= lim; i++)
    {
        if (n % i == 0)
        {
            cout << i << " ";
            if (i != n / i)
            {
                cout << n / i << " ";
            }
        }
    }
}
// if d is a divisor of n then n/d is also a divisor of n. This property is symmetric about the square root of N.
// Thus, by traversing just the first half we can avoid redundant iteration and computations improving the efficiency of the algorithm.