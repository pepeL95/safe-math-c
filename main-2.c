#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "safe-math.h"

void produceOutput(long A, long B, int checks) {
    /* This function produces the correct output to
       the assignment depending to the checks variable.
       checks is defined as...
       1 => chars
       2 => ints
       3 => longs
    */
    
    char C; int I; long L;
    if (psnip_safe_char_mul(&C, A, B) && checks == 1) // only check when A and B are chars
        printf("%ld and %ld can be successfully multiplied as chars, producing product %hhd.", A, B, C);

    else if (psnip_safe_int_mul(&I, A, B) && checks <= 2) // check when A and B are ints or chars
        printf("%ld and %ld can be successfully multiplied as ints, producing product %d.", A, B, I);
    
    else if (psnip_safe_long_mul(&L, A, B) && checks) // fallthrogh case...
        printf("%ld and %ld can be successfully multiplied as longs, producing product %ld.", A, B, L);
    
    else // none of the cases above worked...
        printf("%ld and %ld cannot be multiplied as longs.", A, B);
}

int main(void){
    long A, B;
    char input1[128], input2[128];

    //Read A and B
    if(fgets(input1, 128, stdin) == NULL) {
        A = 0; 
    }
    if(fgets(input2, 128, stdin) == NULL) {
        B = 0; 
    }
    
    A = strtol(input1, NULL, 10);
    if(errno) { // if conversion is unsuccessful, set A to zero
        input1[strcspn(input1, "\n")] = 0; // Trim new line character from string
        input2[strcspn(input2, "\n")] = 0; // Trim new line character from string
        A = 0; 
    }
    
    errno = 0; // resetting error number...
    
    B = strtol(input2, NULL, 10);
    if(errno) { // if conversion is unsuccessful, set B to zero
        input2[strcspn(input2, "\n")] = 0; // Trim new line character from string
        B = 0;
    }
    
    if ((CHAR_MIN <= A && A <= CHAR_MAX) && (CHAR_MIN <= B && B <= CHAR_MAX))
        produceOutput(A, B, 1);

    else if ((INT_MIN <= A && A <= INT_MAX) && (INT_MIN <= B && B <= INT_MAX))
        produceOutput(A, B, 2);

    else if ((LONG_MIN <= A && A <= LONG_MAX) && (LONG_MIN <= B && B <= LONG_MAX))
        produceOutput(A, B, 3);
    
    return 0;
}
