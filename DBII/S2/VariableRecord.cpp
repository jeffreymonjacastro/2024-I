#include <iostream>
#include <fstream>

using namespace std;

struct Alumno {
  string nombre;
  string carrera;
  int edad;
  float talla;

  void writeString(ofstream &file, string &cadena){
    int size = cadena.size();
    file.write((char*) &size, sizeof(int));
    file.write(cadena.c_str(), size);
  }

  void write(ofstream &file){
    file.write((char*) &edad, sizeof(edad));
    file.write((char*) &talla, sizeof(talla));
    writeString(file, nombre);
    writeString(file, carrera);
  }

  void readString(ifstream &file, string &cadena){
    int size = 0;
    file.read((char*) &size, sizeof(int));

    // Se necesita un buffer de tamaño size
    char* buffer = new char[size];
    file.read(buffer, size);
    cadena = buffer;
  }

  void read(ifstream &file){
    file.read((char*) &edad, sizeof(edad));
    file.read((char*) &talla, sizeof(talla));
    readString(file, nombre);
    readString(file, carrera);
  }

  int size_of(){
    return sizeof(edad) + sizeof(talla) + nombre.size() + carrera.size();
  }
};

int main(){

  return 0;
}