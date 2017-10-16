#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int gap = 1;

int main()
{
   int a=0, b=0, x=0, intRating=0;
   vector<int>::iterator tempIndex;
   vector<int> v;
   //get input
   cin >> a;
   cin >> b;
   //loop through each line of input
   for(int i = 0; i < a; i++)
   {
       //store input into vector 
       v.clear();
       for(int j=0; j<b; j++)
       {
           cin >> x;
           v.push_back(x);
       }
       //calculate Interger Rating
       intRating = 0;
       for(int j=0; j<b; j++)
       {
           tempIndex = find(v.begin()+j,v.end(),v.at(j)-gap);
           if(tempIndex != v.end()){intRating += distance((v.begin()+j) ,tempIndex);}
           tempIndex = find(v.begin()+j,v.end(),v.at(j)+gap);
           if(tempIndex != v.end()){intRating += distance((v.begin()+j) ,tempIndex);}
       }
       cout << intRating << endl;
   }
   return 0;
}
