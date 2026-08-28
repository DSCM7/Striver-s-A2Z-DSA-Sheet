#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        // Spaces before stars
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }

        // Stars
        for (int j = 0; j < 2 * i + 1; j++)
        {
            cout << "*";
        }

        // Spaces after stars
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }

        cout << endl;
    }

    return 0;
}