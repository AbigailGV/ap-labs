#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    int r = values[0];
    for(int i = 1; i < nValues; i++){
        switch (operator){
            case 1:
                r = r + values[i];     
                break;
            case 2:
                r = r - values[i];     
                break;
            case 3:
                r = r * (values[i]);     
                break;
            } 
    }
}

int main(int argc, char **argv) {
    int ope;
    int result;
    int size = argc -2;
    int nums[size];
    for (int i = 0; i < size; i++) {
        nums[i] = atoi(argv[i+2]);
    }

    if(strcmp(argv[1],"add") == 0){
        ope = 1;
        result = calc(ope, size, nums);
        printf("%d\n", result);
    }
    else if(strcmp(argv[1],"sub") == 0){
        ope = 2;
        result = calc(ope, size, nums);
        printf("%d\n", result);
    }
    else if(strcmp(argv[1],"mult") == 0){
        ope = 3;
        result = calc(ope, size, nums);
        printf("%d\n", result);
    }else{
        printf("Operator not available!\n");
    }
    return -1;
}
