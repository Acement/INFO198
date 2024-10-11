#include <iostream>
#include "thread_operation.h"
#include "env_setter.h"

using namespace std;

int main(int argc, char** argv) {
    cout<<"PID: "<<getpid()<<endl;
    crearIndiceInvertido();
}
