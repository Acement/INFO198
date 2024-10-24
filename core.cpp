#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

void calcular(const string& operacion) {
    ofstream resultados(getenv("RESULTADOS"), ios::app);
    int id;
    string op;
    double num1, num2;

    stringstream ss(operacion);
    string temp;
    
    getline(ss, temp, ';'); // ID
    id = stoi(temp);
    getline(ss, op, ';'); // Operación
    getline(ss, temp); // Números

    // Parsear números
    size_t comma_pos = temp.find(',');
    num1 = stod(temp.substr(0, comma_pos));
    num2 = stod(temp.substr(comma_pos + 1));

    double resultado = 0;
    if (op == "suma") {
        resultado = num1 + num2;
    } 
    else if (op == "resta") {
        resultado = num1 - num2;
    } 
    else if (op == "division") {
        resultado = num2 != 0 ? num1 / num2 : 0;
    } 
    else if (op == "multiplicacion") {
        resultado = num1 * num2;
    }

    resultados << "(" << id<< ":" << operacion << ")=>" << resultado << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        string operacion = argv[1];
        calcular(operacion);
    }
    return 0;
}
