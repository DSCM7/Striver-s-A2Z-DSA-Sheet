#include <iostream>
using namespace std;
int main()
{
    int a, b;
    cin >> a >> b;
    int small;
    if (a < b)
    {
        small = a;
    }
    else
    {
        small = b;
    }
    int gcd = 1;
    for (int i = 1; i <= small; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcd = i;
        }
    }
    cout << gcd << endl;
}

// method 2, euclidean algorithm
int main()
{
    int a, b;
    cin >> a >> b;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    cout << a << endl;
}