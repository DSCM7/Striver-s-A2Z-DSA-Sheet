#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int original = n;
    int reversed = 0;

    while (n != 0)
    {
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n = n / 10;
    }

    cout << reversed << endl;

    if (reversed == original)
    {
        cout << "Palindrome";
    }
    else
    {
        cout << "Not Palindrome";
    }
}