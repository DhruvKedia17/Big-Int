/*conventions used
    ->the sign is 0 when the number is positive an it is 1 when the number is negative 
    ->the sign is required when the number is being passed as input for better representation and operations 
    ->if sign is not provided in the input then the program would not execute further
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//the maximum size of a number will be 309, so the length of the string would be 311
#define SIZE 311

typedef enum{FAILURE, SUCCESS} status_code;

int max(int a, int b){
    int retVal = b;
    if(a >= b){
        retVal = a;
    }

    return retVal;
}

typedef struct BIG_INT_TAG{
    int sign;
    int* arr;
    int length;
}bigInt;


//function to convert the given string into bigInt
status_code convertIntoNum(char* ch, bigInt* b){
    status_code retVal = SUCCESS;
    int strLength = strlen(ch);
    int numLength = strLength - 1;

    if(ch[0] == '+'){
        b -> sign = 0;
    }
    else if(ch[0] == '-'){
        b -> sign = 1;
    }
    else{
        retVal = FAILURE;
    }

    if(retVal == SUCCESS){
        b -> length = numLength;
        b -> arr = (int*)malloc(sizeof(int) * (b -> length));

        for(int i=1; i<strLength; i++){
            char temp = ch[i];
            int ascii = temp;
            ascii -= 48;

            b -> arr[numLength - i] = ascii;
        }
    }

    return retVal;
}


//function to print the number 
void printNum(bigInt* b){
    int length = b -> length;
    if(b -> sign == 0){
        printf("+");
    }
    else{
        printf("-");
    }

    for(int i=length-1; i>=0; i--){
        printf("%d", b -> arr[i]);
    }

    printf("\n");
}


//declaration of the functions 
bigInt addition(bigInt* b1, bigInt* b2);
bigInt substraction(bigInt* b1, bigInt* b2);
bigInt multiply(bigInt* b1, bigInt* b2);





int main(){
    char* str1 = (char*)malloc(sizeof(char) * SIZE);
    char* str2 = (char*)malloc(sizeof(char) * SIZE);
    status_code s1, s2;
    bigInt b1, b2;
    bigInt ans;
    int operation;

    printf("Enter the first number \n");
    scanf("%s", str1);

    printf("Enter the second number \n");
    scanf("%s", str2);

    s1 = convertIntoNum(str1, &b1);
    s2 = convertIntoNum(str2, &b2);

    if(s1 == SUCCESS && s2 == SUCCESS){
        printf("Enter the number to perform the specific operation\n");
        printf("1. Addition     2. Subtraction     3. Multiplication \n");
        scanf("%d", &operation);

        if(operation == 1){
            ans = addition(&b1, &b2);
        }
        else if(operation == 2){
            ans = substraction(&b1, &b2);
        }
        else if(operation == 3){
            ans = multiply(&b1, &b2);
        }
        else{
            printf("Please specify the operation clearly \n");
        }

        if(operation == 1 || operation == 2 || operation == 3){
            printNum(&ans);
        }
    }
    else{
        printf("The number entered incorrectly, please enter the number again \n");
    }
    return 0;
}







bigInt addition(bigInt* b1, bigInt* b2){
    bigInt temp, ans;
    int carry = 0, sum, i = 0;
    int length1 = b1 -> length, length2 = b2 -> length;

    if(b1 -> sign == b2 -> sign){
        ans.sign = b1 -> sign;
        ans.length = max(b1 -> length, b2 -> length) + 1;
        ans.arr = (int*)malloc(sizeof(int) * (ans.length));

        while(i < length1 && i < length2){
            sum = carry + b1 -> arr[i] + b2 -> arr[i];
            ans.arr[i] = sum%10;
            carry = sum / 10;
            i++;
        }
        while(i < length1){
            sum = carry + b1 -> arr[i];
            ans.arr[i] = sum % 10;
            carry = sum / 10;
            i++;
        }
        while(i < length2){
            sum = carry + b2 -> arr[i];
            ans.arr[i] = sum % 10;
            carry = sum / 10;
            i++;
        }

        ans.arr[i] = carry;
    }
    else if(b1 -> sign == 1){
        temp = *b1;
        temp.sign = 0;
        ans = substraction(b2, &temp);
    }
    else if(b2 -> sign == 1){
        temp = *b2;
        temp.sign = 0;
        ans = substraction(b1, &temp);
    }

    return ans;
}

bigInt substraction(bigInt* b1, bigInt* b2){
    bigInt temp, ans;
    int diff, borrow = 0, carry = 0, i = 0, sum;
    int length1 = b1 -> length, length2 = b2 -> length;

    if(b1 -> sign == b2 -> sign){
        ans.sign = b1 -> sign;
        ans.length = max(b1 -> length, b2 -> length) + 1;
        ans.arr = (int*)malloc(sizeof(int)*(ans.length));

        while(i < length1 && i < length2){
            diff = b1 -> arr[i] - borrow - b2 -> arr[i];
            if(diff < 0){
                diff += 10;
                borrow = 1;
            }
            else{
                borrow = 0;
            }
            ans.arr[i] = diff;
            i++;
        }
        while(i < length1){
            diff = b1 -> arr[i] - borrow;
            if(diff < 0){
                borrow = 1;
                diff += 10;
            }
            else{
                borrow = 0;
            }
            ans.arr[i] = diff;
            i++;
        }
        while(i < length2){
            borrow = 1;
            diff = -(borrow + b2 -> arr[i]);
            diff += 10;
            ans.arr[i] = diff % 10;
            i++;
        }

        if(borrow == 1){
            ans.arr[ans.length - 1] = 9;
            for(int i=0; i<ans.length; i++){
                ans.arr[i] = 9 - ans.arr[i];
            }
            ans.arr[0] += 1;
            carry = ans.arr[0] / 10;
            ans.arr[0] = ans.arr[0] % 10;

            i = 1;
            while(carry != 0){
                sum = carry + ans.arr[i];
                ans.arr[i] = sum % 10;
                carry = sum / 10;
                i++;
            }
            ans.sign = !(ans.sign);
        }
        else{
            ans.arr[ans.length-1] = 0;
        }
    }

    else{
        temp = *b2;
        temp.sign = !(temp.sign);
        ans = addition(b1, &temp);
    }

    return ans;
}

bigInt multiply(bigInt* b1, bigInt* b2){
    int length1 = b1 -> length;
    int length2 = b2 -> length;
    int i, j, sum, carry;
    bigInt m;

    m.length = (length1 + length2);
    m.arr = (int*)malloc(sizeof(int) * (m.length));
    if(b1 -> sign == b2 -> sign){
        m.sign = 0;
    }
    else{
        m.sign = 1;
    }

    //initializing all the values of arr m to 0
    for(int i=0; i<m.length; i++){
        m.arr[i] = 0;
    }

    for(int i=0; i<length1; i++){
        carry = 0;
        for(int j=0; j<length2; j++){
            sum = carry + (m.arr[i+j]) + ((b1 -> arr[i]) * (b2 -> arr[j]));
            m.arr[i+j] = sum % 10;
            carry = sum / 10;
        }
        if(carry != 0){
            m.arr[i+length2] = carry;
        }
    }

    return m;
}