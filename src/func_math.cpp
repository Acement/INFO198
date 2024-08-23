#include "func_math.h"

float calc_func(float n){
    if(n == 0){
        cout << "No se pudo realizar la operacion (Division por cero)" << endl;
        return 0;
    }
    else return ((5*n)*n) + 1/n;
}