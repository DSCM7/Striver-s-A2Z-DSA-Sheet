// An armstrong number is a number that is equal to the sum of its own digits each raised to the power of the number of digits.
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int temp = n;
    int s = 0;
    int c = 0;
    while (temp > 0)
    {
        c++;
        temp = temp / 10;
    }
    temp = n;
    while (temp > 0)
    {
        int d = temp % 10;
        s += pow(d, c);
        temp = temp / 10;
    }
    if (s == n)
    {
        cout << "Armstrong Number" << endl;
    }
    else
    {
        cout << "Not an Armstrong Number" << endl;
    }
}
