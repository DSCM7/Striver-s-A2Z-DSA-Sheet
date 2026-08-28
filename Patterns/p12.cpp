#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int s = (2 * n) - 2;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << j;
        }
        for (int i = 1; i <= s; i++)
        {
            cout << " ";
        }
        s = s - 2;
        for (int j = i; j > 0; j--)
        {
            cout << j;
        }
        cout << endl;
    }
}