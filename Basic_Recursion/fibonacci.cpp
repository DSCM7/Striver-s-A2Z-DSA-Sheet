#include <bits/stdc++.h>
using namespace std;

int fibonacci(int N)
{
    // Base case
    if (N <= 1)
    {
        return N;
    }

    // Recursive case
    int last = fibonacci(N - 1);
    int slast = fibonacci(N - 2);

    return last + slast;
}

int main()
{
    int N;
    cin >> N;
    cout << fibonacci(N) << endl;

    return 0;
}