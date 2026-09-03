#include <iostream>
#include <string>
using namespace std;

bool palindrome(string s, int i)
{
    if (i >= s.length() / 2)
    {
        return true;
    }

    if (s[i] != s[s.length() - i - 1])
    {
        return false;
    }

    return palindrome(s, i + 1);
}

int main()
{
    string s;
    cin >> s;

    if (palindrome(s, 0))
    {
        cout << "Palindrome";
    }
    else
    {
        cout << "Not Palindrome";
    }

    return 0;
}