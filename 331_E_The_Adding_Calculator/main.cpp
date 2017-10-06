#include <cstdint>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;
const int8_t negOne= 0xFF;
const int success = 0;
const int generalFailure = 1;
const int nonIntegralResult = 2;
const int notDefined = 3;
const int invalidOperatorChar = 4;

class Calculator
{
    public:
        int firstOperand;
        int secondOperand;
        char operatorChar;
        Calculator() : firstOperand(0), secondOperand(0), operatorChar('\0'), retVal(0)  {}
        int processInput() // checks division by zero, varies call depending on negative values, prints output
        {
            switch(operatorChar)
            {
                case '+': 
                    retVal = add(firstOperand, secondOperand); break;
                case '-':
                    if(secondOperand>=0){retVal = subtract(firstOperand, secondOperand);}
                    else{add(firstOperand, flipNegToPos(secondOperand));}
                    break;
                case '*':
                    retVal = multiply(firstOperand, secondOperand); break;
                case '/':
                    retVal = divide(firstOperand, secondOperand); break;
                case '^':
                    retVal = exponent(firstOperand, secondOperand); break;
                default:
                    retVal = invalidOperatorChar;
            }
            switch(retVal)
            {
                case success: 
                    cout << initResult << endl; break;
                case generalFailure:
                    cout << "general Failure"<<endl; break;
                case nonIntegralResult:
                    cout << "Non-Integral answer" <<endl; break;
                case notDefined:
                    cout << "Not-defined"<<endl; break;

            }
            return 0;
        }

    private:
        int retVal;
        int initResult;
        int flipNegToPos(int x)
        {
            int j=0;
            for(int i=x;i<0;i++){j++;}
            return j;
        }
        int flipPosToNeg(int x)
        {
            int j=0;
            for(int i=0;i<x;i++){j = j+negOne;}
            return j;
        }
        int add(int x, int y) { initResult = x + y; return 0;}
        int subtract(int x, int y)
        {
            for(int i=0; i<y; i++)
            {
                x = x + negOne;
            }
            initResult=x;
            return 0;
        }
        int multiply(int x, int y)
        {
            int negCount = 0, tempVal = 0;
            if(y==0 || x==0) {initResult = 0; return 0;}
            if(x<0) {negCount++; x=flipNegToPos(x);}
            if(y<0) {negCount++; y=flipNegToPos(y);}
            for(int i = 0; i<y; i++) 
            {
                tempVal=tempVal+x;
            }
            if(1==negCount) {tempVal=flipPosToNeg(tempVal);}
            initResult = tempVal; 
            return 0;
        }
        int divide(int x, int y)
        {
            if(y==0){return notDefined;}
            int tempVal = 0, i=0, negCount = 0;
            if(x<0) {negCount++; x=flipNegToPos(x);}
            if(y<0) {negCount++; y=flipNegToPos(y);}
            while(tempVal<=x)
            {
                if(tempVal==x)
                {
                    if(1==negCount) {i=flipPosToNeg(i);}
                    initResult = i; 
                    return 0;
                }
                else{tempVal = tempVal+y; i++;}
            }

            return nonIntegralResult;
        }
        int exponent(int x, int y)
        {
            if(y==0) {initResult = 1; return 0;}
            if(y<0) {return nonIntegralResult;}
            int tempVal = x;
            for(int i = 1; i<y; i++) 
            {
                multiply(x,tempVal);
                tempVal=initResult;
            }
            initResult = tempVal; 
            return 0;
        }
};


int main()
{   
    std::string line;
    Calculator calc;
    while(getline(cin, line))
    {
        std::stringstream ss(line);
        ss >> calc.firstOperand >> calc.operatorChar >> calc.secondOperand; 
        calc.processInput();
    }
   return 0;
}
