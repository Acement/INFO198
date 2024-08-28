#include "func_math.h"

int summation(vector<int> numbers){
    int sum = 0;
    for(int i : numbers){
        sum += i;
    }
    return sum;
}

float average(vector<int> numbers){
    float sum = summation(numbers);
    return sum/numbers.size();
}

float calc_func(float n){
    if(n == 0){
        cout << "No se pudo realizar la operacion (Division por cero)" << endl;
        return 0;
    }
    else return ((5*n)*n) + 1/n;
}