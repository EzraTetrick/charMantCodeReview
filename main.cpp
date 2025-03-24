
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
void check_answer(char output[], char expected[]);
void clear_answers(char a[], char b[], int len);

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
    cout << "=====Addition Tests=====" << endl;
    //1 + 1
    expected[0] = '2';
    add(1, 0, 100, 1, 0, 100, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //1 + 0.5
    expected[0] = '2';
    expected[1] = '.';
    expected[2] = '5';
    add(1, 5, 10, 1, 0, 10, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //2 + -1
    expected[0] = '1';
    add(2, 0, 10, -1, 0, 10, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //1 + -5.5
    expected[0] = '-';
    expected[1] = '4';
    expected[2] = '.';
    expected[3] = '5';
    add(1, 0, 10, -5, 5, 10, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //check for characteristic too large
    if(!add(999999999, 0, 10, 999999999, 0, 10, test, len)){
        cout << "Test passed" << endl;
        cout << "Characteristic is too large" << endl << endl;
    }
    
    //check for division by zero
    if(!add(1, 0, 0, 1, 0, 0, test, len)){
        cout << "Test passed" << endl;
        cout << "Division by 0" << endl << endl;
    }

    //subtraction tests
    cout << "=====Subtraction Tests=====" << endl;
    //2 - 1
    expected[0] = '1';
    subtract(2, 0, 100, 1, 0, 100, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //0 - 2.75
    expected[0] = '-';
    expected[1] = '2';
    expected[2] = '.';
    expected[3] = '7';
    expected[4] = '5';
    subtract(0, 0, 100, 2, 75, 100, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

    //-5 - (-10)
    expected[0] = '5';
    subtract(-5, 0, 100, -10, 0, 100, test, len);
    check_answer(test, expected);
    clear_answers(test, expected, len);

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
    if (len <= 0){
        return false;
    }

    //add the two characteristics together
    int characteristic = c1 + c2;

    //find common denom and add
    int numerator = n1 * d2 + n2 * d1;
    int denominator = d1 * d2;

    //check that denom is greater than 0
    if(denominator <= 0){
        return false;
    }

    //add the carry from the fractional part to characteristic
    characteristic += numerator / denominator;


    //characteristic won't fit in result array
    if (count_digits(characteristic) > len - 1){
        return false;
    }

    // Handle negative numerator by borrowing from characteristic
    if (numerator < 0) {
        characteristic -= 1;
        numerator += denominator;
    }

    numerator %= denominator;

    //std::cout << characteristic << "\t" << numerator << "\t" << denominator << endl;

    convert_to_char(characteristic, numerator, denominator, result, len);

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    if (len <= 0){
        return false;
    }

    // Subtract the two characteristics
    int characteristic = c1 - c2;

    // Find common denominator and calculate new numerator
    int numerator = (n1 * d2) - (n2 * d1);
    int denominator = d1 * d2;

    //check that denom is greater than 0
    if(denominator <= 0){
        return false;
    }

    convert_to_char(characteristic, numerator, denominator, result, len);

    return true;
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

void convert_to_char(int c, int n, int d, char result[], int len){
    int num_digit = count_digits(c);
    int index = 0;
    //check if characteristic is negative
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
    //TODO handle number longer than len
    //characteristic is not zero and is positive now
    else{
        //iterate over the digits in c from right to left
        for (int i = num_digit - 1; i >= 0; i--) {
            //convert the first digit to a char
            result[index + i] = '0' + (c % 10);
            //integer division by 10 to get rid of first digit (the rightmost one)
            c = c / 10;
        }
        //move index to correct position in result [] after adding digits in the charateristics
        index += num_digit;
    }

    //TODO comments
    if (n < 0){
        n = -n;
    }

    if (n > 0){
        if (index < len - 1){
            result[index++] = '.';
    
            //add values from the matissa until end of array
            for (index; index < len - 1 && n > 0; index++) {
                n *= 10;
                result[index] = '0' + (n / d);
                n %= d;
            }
        }
    }
    
    
    
    //cout << "length: " << strlen(result) << endl;

    result[index] = '\0';

    //cout << "result: " << (result) << endl;
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

void check_answer(char output[], char expected[]){
    if (strcmp(output, expected) == 0){
        cout << "Test passed" << endl;
    }
    else if (strcmp(output, expected) != 0){
        cout << "Test failed" << endl;
    }
    cout << "Answer: " << output << "\tExpected: " << expected << endl << endl;
}

void clear_answers(char a[], char b[], int len){
    for (int i = 0; i < len - 1; i++){
        a[i] = 0;
        b[i] = 0;
    }
}