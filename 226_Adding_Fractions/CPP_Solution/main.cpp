#include <iostream>
#include <stdint.h>
#include <string>

class Fraction
{
private:
    int64_t numerator;
    int64_t denominator;

public:
    int64_t getNumerator()
    {
        return numerator;
    }

    int64_t getDenominator()
    {
        return denominator;
    }

    void setNumerator(int64_t num)
    {
        numerator = num;
    }

    void setDenominator(int64_t denom)
    {
        denominator = denom;
    }
    
};

class FractionArray
{

private:
    int size;
    int population;
    Fraction * p_arr;

    //Lowest Common Multiple function
   int64_t LowestCommonMultiple( int64_t n1, int64_t  n2)
   {
       int64_t minMultiple, retVal, lowerBaseMultiple;

       //Prevent division by 0
       n1 = (n1 == 0) ? 1 : n1;
       n2 = (n2 == 0) ? 1 : n2;

       // maximum number between n1 and n2 is stored in minMultiple
       lowerBaseMultiple = (n1>n2) ? n1 : n2;
       minMultiple = lowerBaseMultiple;

       // Always true
       while(1)
       {
           if( minMultiple%n1==0 && minMultiple%n2==0 )
           {
               retVal = minMultiple;
               break;
           }
           minMultiple += lowerBaseMultiple;
       }
       return retVal;
   }


   //Greatest Common Devisor Function
   int64_t GreatestCommonFactor(int64_t a, int64_t b)
   {
       // Everything divides 0 
       if (a == 0 || b == 0)
           return 0;

        // base case
        if (a == b)
            return a;

        // a is greater
        if (a > b)
            return GreatestCommonFactor(a-b, b);
        return GreatestCommonFactor(a, b-a);
    }


public:
    //constructor
    FractionArray(int arraySize)
    {
        size = ( arraySize > 0 ? arraySize : 10); //validate arraySize
        p_arr = new Fraction[size];
        population = 0;
    }

    //Destructor
    ~FractionArray()
    {
        delete [] p_arr;
    }
    
    //getCommonDenominator - 
    int64_t getCommonDenominator()
    { 
        int64_t lcm = 1;
        //loop through each object in array
        for(int i = 0; i < population; i++)
        {
            lcm = LowestCommonMultiple(lcm, p_arr[i].getDenominator());
        }
        return lcm;
    }
    

    //pushFraction method - Place fraction at end of array
    void pushFraction(int64_t numer, int64_t denom)
    {
        p_arr[population].setNumerator(numer);
        p_arr[population].setDenominator(denom);
        population++;
    }

    //AddFractions method - add all fractions and reduce result 
    void AddFractions(Fraction * fract)
    {  
        int64_t comDenom = getCommonDenominator();
        int64_t tempNum = 0;
        int64_t gcf = 0;
        //loop to get total numerator
        for(int i =0; i<population; i++)
        {
            tempNum = tempNum + (p_arr[i].getNumerator() * (comDenom / p_arr[i].getDenominator())) ;
        }
        //reduce fraction
        gcf = GreatestCommonFactor(comDenom, tempNum);
        fract->setNumerator(tempNum/gcf);
        fract->setDenominator(comDenom/gcf);
    }

};

int main(int argc, char* argv[])
{
    int numFractions;
    std::string tempInput;
    int strPosition;
    Fraction output;
    FractionArray fractArr(20);

    std::cout << "Enter number of fractions to add:" << std::endl;
    std::cin >> numFractions;
    std::cout << "Enter Fractions:" << std::endl;
    for(int i = 0; i < numFractions; i++)
    {
        std::cin >> tempInput;
        strPosition = tempInput.find("/");
        fractArr.pushFraction(std::stol(tempInput.substr(0,strPosition)), std::stol(tempInput.substr(strPosition+1)));
    }
    fractArr.AddFractions(&output);
    std::cout << "answer: " << output.getNumerator() << "/" << output.getDenominator() << std::endl;
}
