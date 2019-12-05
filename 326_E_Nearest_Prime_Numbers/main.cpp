#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;
const long long lowValue = 2;
const long long highValue = LLONG_MAX;
//const long long highValue = 10000000;
//const long long highValue = 100;

long long main()
{
    std::set<long long> s;
    std::string line;
    std::set<long long>::iterator it; 
    long long j = 0, upperPrime = 0, lowerPrime = 0;
    for(long long i = lowValue; i<=highValue; i++)
    {
        s.insert(i);
    }
    cout << "Size of set is:" << s.size() << endl;
    long long sqRootOfMax = (long long)(sqrt(highValue)+1);
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
