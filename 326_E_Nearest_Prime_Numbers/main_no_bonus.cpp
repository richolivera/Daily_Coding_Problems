#include <set>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;
const int lowValue = 2;
const int highValue = 10000000;
//const int highValue = 100;

int main()
{
    std::set<int> s;
    std::string line;
    std::set<int>::iterator it; 
    int j = 0, upperPrime = 0, lowerPrime = 0;
    for(int i = lowValue; i<=highValue; i++)
    {
        s.insert(i);
    }
    cout << "Size of set is:" << s.size() << endl;
    int sqRootOfMax = (int)(sqrt(highValue)+1);
    //Construct the sieve
    for(it = s.begin(); *it <= sqRootOfMax; it++) 
    {
        j = (*it) * (*it);
        while(j < highValue )
        {
            if(s.find(j) != s.end()) {s.erase(j);}
            j = j + *it;
        }
    }
    while(getline(cin, line))
    {
        stringstream ss(line);
        ss >> j;
        if(s.find(j) != s.end())
        {
            cout << j << " is prime." << endl;
        }
        else
        {
            it = s.upper_bound(j);
            upperPrime = *it;
            it--;
            lowerPrime = *it;
            cout << lowerPrime << " < " << j << " < " << upperPrime << endl;
        }
    }
    return 0;
}
