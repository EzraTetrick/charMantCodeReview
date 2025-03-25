
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

void convert_to_char(int c, int n, int d, char result[], int len);
int count_digits(int c);
void clear_answers(string test_name, char a[], char b[], int len);
void test_addition(char test[], char expected[], int len);
void test_subtraction(char test[], char expected[], int len);
void test_function(bool (*func)(int, int, int, int, int, int, char*, int),
    int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len,
    string test_name, char expected[]);

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
    //check if the array is grater than 0
    if (len <= 0){
        return false;
    }

    //check that denoms are greater than 0
    if(d1 <= 0 || d2 <=0){
        return false;
    }

    //add the two characteristics together
    int characteristic = c1 + c2;
    cout << "C: " << characteristic << endl;
    cout << "c1: " << c1 << "\tn1: " << n1 << "\nc2: " << c2 << "\tn2: " << n2 << endl;

    //make the numerator negative if the characteristic is negative
    if(c1 < 0 && n1 >= 0){
        n1 = -n1;
    }
    if (c2 < 0 && n2 >= 0){
        n2 = -n2;
    }

    //find common denom and add
    int denominator = d1 * d2;
    int numerator_1 = (n1 * d2);
    int numerator_2 = (n2 * d1);

    //check if we need to borrow 1 from characteristic
    if (numerator_2 < 0 && numerator_1 > 0 && characteristic < 0){
        characteristic += 1;
    }

    cout << "new_num_1: " << numerator_1 << "\tnew_num_2: " << numerator_2 << endl;

    int new_numerator = 0;
    if (numerator_2 < 0){
        new_numerator = numerator_1 + numerator_2;
    }
    else{
        new_numerator = numerator_1 - numerator_2;
    }

    cout << "C: " << characteristic << "\tN: " << new_numerator << endl;

    //characteristic won't fit in result array
    if (count_digits(characteristic) > len - 1){
        return false;
    }

    // cout << "C: " << characteristic << "\tN: " << numerator << endl;

    //numerator %= denominator;

    //cout << characteristic << "\t" << numerator << "\t" << denominator << endl;

    convert_to_char(characteristic, new_numerator, denominator, result, len);

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
    // expected[0] = '-';
    // expected[1] = '2';
    // expected[2] = '.';
    // expected[3] = '7';
    // expected[3] = '5';
    // test_function(subtract, -1, 5, 10, 1, 25, 100, test, len, "(-1.5) - 1.25", expected);

    expected[0] = '0';
    test_function(subtract, 1, 0, 10, 1, 0, 10, test, len, "1 - 1", expected);

}