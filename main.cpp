
#include <iostream>
#include <cstring> // for testing, remove later
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

bool convert_to_char(int c, int n, int d, char result[], int len);
int count_digits(int c);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        //cout<<"c: "<<c<<endl;
        //cout<<"n: "<<n<<endl;
        //cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;

    d2 = 3; 

    //if the c-string can hold at least the characteristic
    // if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    // {
    //     //display string with answer 4.1666666 (cout stops printing at the null terminating character)
    //     cout<<"Answer: "<<answer<<endl;
    // }
    // else
    // {
    //     //display error message
    //     cout<<"Error on add"<<endl;
    // }
    char answer_2[10] = {'0'};
    if(subtract(c1, n1, d1, c2, n2, d2, answer_2, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer_2<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }


    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    c1 = 10;
    c2 = 100;
    n1 = 500;
    n2 = 250;
    d1 = 1000;
    d2 = 1000;

    //add the two characteristics together
    int characteristic = c1 + c2;

    //characteristic won't fit in result array
    if (count_digits(characteristic) > len - 1){
        return false;
    }

    //cross multiply the numerator and denominators to find common denom and add
    int numerator = n1 * d2 + n2 * d1;
    int denominator = d1 * d2;

    //add the carry from the fractional part to characteristic
    characteristic += numerator / denominator;
    //remove the carry from the denominator
    numerator %= denominator;

    //std::cout << c << "\t" << n << "\t" << d << endl;

    return convert_to_char(characteristic, numerator, denominator, result, len);
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    c1 = -10;
    c2 = 0;
    n1 = 0;
    n2 = 10;
    d1 = 10;
    d2 = 10;

    // Subtract the two characteristics
    int characteristic = c1 - c2;

    // Find common denominator and calculate new numerator
    int numerator = (n1 * d2) - (n2 * d1);
    int denominator = d1 * d2;

    // Adjust characteristic if numerator is negative
    if (numerator < 0) {
        characteristic -= 1;   // Borrow from characteristic
        numerator += denominator;  //add borrowed value to mantissa
    }

    //cout << "c: " << characteristic << "\tm: " << numerator << endl;

    return convert_to_char(characteristic, numerator, denominator, result, len);
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}

bool convert_to_char(int c, int n, int d, char result[], int len){
    int num_digit = count_digits(c);
    int index = 0;
    //check if characteristic is negative
    if (c < 0){
        result[index] = '-';
        //make charateristic positive
        c *= -1;
        index++;
    }

    //characteristic is 0
    if (c == 0){
        result[index] = '0';
        index++;
    }

    //TODO handle number longer than 10 digits
    //characteristic is not zero and is positive now    
    else{
        //cout << "num digit in c: " << num_digit << endl;

        //iterate over the digits in c from right to left
        for (int i = num_digit - 1; i >= 0; --i) {
            //convert the first digit to a char
            result[index + i] = '0' + (c % 10);
            //cout << result[index + i] << endl;
            //integer division by 10 to get rid of first digit (the rightmost one)
            c = c / 10;
        }
        //move index to correct position in result [] after adding digits in the charateristics
        index += num_digit;
    }

    //TODO comments
    if (n > 0) {
        if (index < len - 1){
            result[index] = '.';
            index++;

            //add values from the matissa until 
            for (index; index < len - 1; index++) {
                n *= 10;
                result[index] = '0' + (n / d);
                n %= d;
            }
        }
    }
    //cout << "length: " << strlen(result) << endl;

    result[index] = '\0';

    //cout << "result: " << (result) << endl;

    return true;
}

int count_digits(int c){
    //count number of digits in characteristic
    int num_digit = 0;
    while (c > 0){
        c = c / 10;
        num_digit++;
    }

    return num_digit;
}
