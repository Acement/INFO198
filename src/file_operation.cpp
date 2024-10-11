#include "file_operation.h"

//guarda los path de todos los archivos dentro de una carpeta
vector<string> get_files_path(string folderPath){
    vector<string> filePathList = {};

    for(const auto & entry : fs::directory_iterator(folderPath)){
        filePathList.push_back(entry.path());
    }


    return filePathList;
}

//Abre el archivo y guarda cada linea en un vector
vector<string> read_file(string fileName){
    vector<string> parseFile = {};
    string temp;
    fstream myFile(fileName);

    while(getline(myFile,temp)) parseFile.push_back(temp);

    myFile.close();
    return parseFile;
}

//Agrega linea a archivo (line tiene que tener un "\n" al final)
void add_line_to_file(string fileName, string line){
    fstream myFile;
    myFile.open(fileName,ios::app);
    myFile << line;
    myFile.close();
}

//Agrega un usuario a la carpeta usuario
void add_user_to_file(string fileName, string line){
    fstream myFile;
    myFile.open(fileName,ios::app);
    
    myFile << "\n" + line;
    myFile.close();
}

//Borra lineas (Lento ya que escencialmente copia todas las lineas excepto la que se esta borrando)
void erase_lines(string fileName, vector<string> fileIn){
    ofstream myFile;
    myFile.open(fileName,ofstream::out | ofstream::trunc);
    myFile.close();
    int j = 1;

    for(string i : fileIn){
        if(j == fileIn.size()) add_line_to_file(fileName,i);
        else add_line_to_file(fileName,i + "\n");
        j++;
    }

}

//Chekea si el archivo de entrada tiene la misma cantidad de archivos que el de salida
bool input_output_file_check(string input, string output){
    vector<string> inputVector = get_files_path(input);
    vector<string> outputVector =get_files_path(output);

    if(inputVector.size() != outputVector.size()) return false;
    else return true;
}