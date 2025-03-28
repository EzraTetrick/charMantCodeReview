#include <iostream>
#include <cstring>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

//helper functions
void convert_to_char(int c, int n, int d, char result[], int len);
int count_digits(int c);
void clear_answers(char a[], char b[], int len);
void test_addition(char test[], char expected[], int len);
void test_subtraction(char test[], char expected[], int len);
void test_function(bool (*func)(int, int, int, int, int, int, char*, int),
    int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len,
    string test_name, char expected[]);
void reduce_fraction(int reduced[], int n, int d);
int gcd(int a, int b);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "-1.0456"; 
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
    c1 = 11;
    n1 = 13;
    d1 = 24;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    int len = 10;
    char test[len] = {'0'};
    char expected[len] = {'0'};

    //addition tests
    test_addition(test, expected, len);

    //subtraction tests
    test_subtraction(test, expected, len);


    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        //cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        //cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //create reference variables so the characteristic knows when to end the loop
    const char period[] = ".";
    const char zero[] = "0";
    const char endLine[] = "\0";
    int endOfNonSignificantIntegers = 0;
    bool significantIntFound = false;
    int i = 0;
    //helper variables to get c
    char charCArray[12];
    int arrayIterator = 0;

    //iterate through numString until the '.' is found
    while (numString[i] != period[0])
    {
        //if the numString array does not find the '.' by this point, either the characteristic is too long or the number is not a float
        if (i == 9 && numString[9] != period[0])
        {
            cout << "Using a non-floating point variable or characteristic is too long!!" << endl;
            return false;
        }

        //if the first significant integer is found, add it to the character array
        if (numString[i] != zero[0] && !significantIntFound)
        {
            significantIntFound = true;
            charCArray[arrayIterator] = numString[i];
            arrayIterator++;
        }
        //if the first significant is already found, add to the character array
        else if (significantIntFound)
        {
            i++;
            charCArray[arrayIterator] = numString[i];
            arrayIterator++;
        }
        //iterate
        else
        {
            endOfNonSignificantIntegers++;
            i++;
        }
    }

    //set endline of the charArray
    charCArray[i + 1] = endLine[0];
    //set an int to the value of charCArray
    c = atoi(charCArray);
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    bool isMantissa = false;
    //helper variables to find the end of the significant numbers
    const char period[] = ".";
    const char zero[] = "0";
    const char endLine[] = "\0";
    int i = 0;
    //iterate through numString until we get to the mantissa
    while (!isMantissa)
    {
        //if the end of the characteristic is found, move to the mantissa
        if (numString[i] == period[0])
        {
            isMantissa = true;
        }
        i++;
    }

    //find the end of the significant variables
    bool significantIntFound = false;
    bool atEnd = false;
    int endOfSigInts = i;
    while (!significantIntFound)
    {
        if (endOfSigInts > 18)
        {
            cout << "Matissa is too long!" << endl;
            return false;
        }

        //find the end of the numString
        if (!atEnd)
        {
            if (numString[endOfSigInts] == endLine[0])
            {
                atEnd = true;
            }
            else
            {
                endOfSigInts++;
            }
        }

        //if the end of the numString is found, find the end of the significant integers
        if (atEnd)
        {
            if (numString[endOfSigInts] != zero[0] && numString[endOfSigInts] != endLine[0])
            {
                significantIntFound = true;
            }
            else
            {
                endOfSigInts--;
            }
        }
    }

    //helper variables to get c
    char charNumeratorArray[10];
    int arrayIterator = 0;
    denominator = 10;
    //iterate through i until the last significant integer
    while (i != endOfSigInts)
    {
        charNumeratorArray[arrayIterator] = numString[i];
        denominator *= 10;
        arrayIterator++;
        i++;
    }
    //finish creation of the numerator array and set the numerator to the value of said array
    charNumeratorArray[arrayIterator] = numString[i];
    charNumeratorArray[arrayIterator + 1] = endLine[0];
    numerator = atoi(charNumeratorArray);
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{   
    // check if the array is greater than 0
    if (len <= 0){
        return false;
    }

    // check that denoms are greater than 0 so we dont divide by 0
    if(d1 < 0 || d2 < 0){
        return false;
    }

    // if the charateristic is negative, make the numerator negative too
    if(c1 < 0 && n1 >= 0){
        n1 = -n1;
    }
    if (c2 < 0 && n2 >= 0){
        n2 = -n2;
    }
    
    // convert to improper fractions
    int num1 = c1 * d1 + n1;
    int num2 = c2 * d2 + n2;
    
    // common denominator
    int common_denom = d1 * d2;
    int sum_num = num1 * d2 + num2 * d1;
    
    // convert back to characteristic and fraction
    int result_char = sum_num / common_denom;
    int result_num = sum_num % common_denom;

    // reduce the fraction
    int reduced [2] = {0};
    reduce_fraction(reduced, result_num, common_denom);
    result_num = reduced[0];
    common_denom = reduced[1];

    //cout << "C: " << characteristic << "\tN: " << result_num << "\tD: " << common_denom <<endl;

    // characteristic won't fit in result array
    if (count_digits(result_char) > len - 1){
        return false;
    }

    convert_to_char(result_char, result_num, common_denom, result, len);

    return true;
}

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    // subtraction is the same as adding a negative number so we can
    // just flip the sign on the second number reuse the add function
    c2 = -c2;
    n2 = -n2;
    return add(c1, n1, d1, c2, n2, d2, result, len);
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //convert all numbers into full fractions -> removing c and n and just having n

    int finalNumerator = (c1*d1+n1) * (c2*d2+n2);
    int finalDenom = d1*d2;

    // make it negative if its negative
    bool negative = false;
    if (finalNumerator < 0) { negative = true; finalNumerator = -finalNumerator; }
    if (finalDenom < 0)   { negative = true; finalDenom   = -finalDenom; }

    // Obtain the integer part and remainder.
    int integerPart = finalNumerator / finalDenom;
    int remainder   = finalNumerator % finalDenom;

    //uses convert char to convert the answer
    convert_to_char( integerPart, remainder,1, result, len);

    return true;
}

//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //flip the denominator and numerator then multiply
    int finalNumerator = (c2*d2+n2);
    // denominator is the numerator and the numerator is denominator
    multiply(c1,n1,d1,d2,0,finalNumerator,result,len);
    
    return true;
}

//this function takes the result from one of the math function and converts it to a char array
void convert_to_char(int c, int n, int d, char result[], int len){
    int num_digit = count_digits(c);
    int index = 0;

    //check if characteristic or numerator is negative
    if (c < 0 || n < 0){
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

    //characteristic is not zero
    else{
        //iterate over the digits in c from right to left
        for (int i = num_digit - 1; i >= 0; i--) {
            //convert the first digit to a char
            result[index + i] = '0' + (c % 10);
            //get rid of first digit (the right-most one)
            c = c / 10;
        }
        //move index to correct position
        index += num_digit;
    }

    //we have already written the negative sign above so if numerator 
    //is negative then we need to make it positive
    if (n < 0){
        n = -n;
    }

    if (n > 0){
        //check if there is room left in result for the deicimal point and at least 1 more digit
        if (index < len - 2){
            result[index++] = '.';
    
            //add values from the numerator from left to right
            //ignore trailing zeros
            for (index; index < len - 1 && n > 0; index++) {
                n *= 10;
                result[index] = '0' + (n / d);
                n %= d;
            }
        }
    }

    //finally, add null terminator at the end
    result[index] = '\0';

}

int count_digits(int c){
    //count number of digits in characteristic
    int num_digit = 0;

    //if neg, make pos
    if (c < 0){ 
        c = -c;
    }
    while (c > 0){
        c = c / 10;
        num_digit++;
    }

    return num_digit;
}

void clear_answers(char a[], char b[], int len){
    for (int i = 0; i < len - 1; i++){
        a[i] = 0;
        b[i] = 0;
    }
}

//takes a function pointer as an argument and outputs where the function
//result matched the expected result
void test_function(bool (*func)(int, int, int, int, int, int, char*, int),
int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len,
string test_name, char expected[]){
    func(c1, n1, d1, c2, n2, d2, result, len);
    cout << "Test: " << test_name << endl;
    cout << "Expected: " << expected << "\tAnswer: " << result << endl;
    
    if (strcmp(result, expected) == 0){
        cout << "PASSED" << endl;
    }
    else if (strcmp(result, expected) != 0){
        cout << "FAILED" << endl;
    }
    cout << endl;

    clear_answers(result, expected, len);
}

//function to find the greatest common denominator
int gcd(int n, int d) {
    while (d != 0) {
        int temp = d;
        d = n % d;
        n = temp;
    }
    //cout << "gcd: " << n << endl;
    return n;
}

void reduce_fraction(int reduced[], int n, int d) {
    //find absolute if n is negative
    int abs_n = n;
    if (n < 0){
        abs_n = -n;
    } 
    //find greatest common denominator
    int divisor = gcd(abs_n, d);
    
    //divide by gcd to reduce fraction
    n /= divisor;
    d /= divisor;

    reduced[0] = n;
    reduced[1] = d;
}

void test_addition(char test[], char expected[], int len){
    cout << "=====Addition Tests=====" << endl;
    //1 + 1
    expected[0] = '2';
    test_function(add, 1, 0, 10, 1, 0, 10, test, len, "1 + 1", expected);

    //1 + 0.5
    expected[0] = '2';
    expected[1] = '.';
    expected[2] = '5';
    test_function(add, 1, 5, 10, 1, 0, 10, test, len, "1 + 0.5", expected);

    //2 + -1
    expected[0] = '1';
    test_function(add, 2, 0, 10, -1, 0, 10, test, len, "2 + (-1)", expected);
    
    //1 + -5.5
    expected[0] = '-';
    expected[1] = '4';
    expected[2] = '.';
    expected[3] = '5';
    test_function(add, 1, 0, 10, -5, 5, 10, test, len, "1 + -(5.5)", expected);

    //1 + (-1.5)
    expected[0] = '-';
    expected[1] = '0';
    expected[2] = '.';
    expected[3] = '5';
    test_function(add, 1, 0, 10, -1, 5, 10, test, len, "1 + (-1.5)", expected);

    //1 + (-1.(-5)) with both the characteristic and numerator being passed as negative
    expected[0] = '-';
    expected[1] = '0';
    expected[2] = '.';
    expected[3] = '5';
    test_function(add, 1, 0, 10, -1, -5, 10, test, len, "1 + (-1.(-5))", expected);

    //1.9 + 1.1
    expected[0] = '3';

    test_function(add, 1, 9, 10, 1, 1, 10, test, len, "1.1+ 1.9", expected);

    //check for characteristic too large
    if(!add(999999999, 0, 10, 999999999, 0, 10, test, len)){
        cout << "PASSED" << endl;
        cout << "Characteristic is too large" << endl << endl;
    }
    
    //check for division by zero
    if(!add(1, 0, 0, 1, 0, 0, test, len)){
        cout << "PASSED" << endl;
        cout << "Division by 0" << endl << endl;
    }
}

void test_subtraction(char test[], char expected[], int len){
    cout << "=====Subtraction Tests=====" << endl;
    //2 - 1
    expected[0] = '1';
    test_function(subtract, 2, 0, 100, 1, 0, 100, test, len, "2 - 1", expected);

    //0 - 2.75
    expected[0] = '-';
    expected[1] = '2';
    expected[2] = '.';
    expected[3] = '7';
    expected[4] = '5';
    test_function(subtract, 0, 0, 100, 2, 75, 100, test, len, "0 - 2.75", expected);

    //-5 - (-10)
    expected[0] = '5';
    test_function(subtract, -5, 0, 100, -10, 0, 100, test, len, "-5 - (-10)", expected);

    //1.75 - 3.25
    expected[0] = '-';
    expected[1] = '1';
    expected[2] = '.';
    expected[3] = '5';
    test_function(subtract, 1, 75, 100, 3, 25, 100, test, len, "1.75 - 3.25", expected);

    //3.25 - 1.75
    expected[0] = '-';
    expected[1] = '1';
    expected[2] = '.';
    expected[3] = '5';
    test_function(subtract, 1, 75, 100, 3, 25, 100, test, len, "3.25 - 1.75", expected);

    //(-1.5) - 1.25
    expected[0] = '-';
    expected[1] = '2';
    expected[2] = '.';
    expected[3] = '7';
    expected[4] = '5';
    test_function(subtract, -1, 5, 10, 1, 25, 100, test, len, "(-1.5) - 1.25", expected);

    //20.33333 - 10.11111
    test_function(subtract, 20, 33333, 100000, 10, 111111, 1000000, 
        test, len, "20.3333 - 10.1111", expected);

}
