#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Alumno
{
  char codigo [5];
  char nombre [11];
  char apellidos [20];
  char carrera [15];

  int ciclo;
  float mensualidad;
};

// Escribir un registro
ofstream& operator <<(ofstream& stream, Alumno& al){
  int index = 0;
  stream.write((char*) &al, sizeof(al));
  stream.write((char*) &index, sizeof(int));
  stream << flush;
  return stream;
}

// Leer un  Registro
ifstream& operator >>(ifstream& stream, Alumno& al){
  stream.read((char*) &al, sizeof(al) + sizeof(int));
  return stream;
}

enum Type {free_list};

class FixedRecordFile {
  private:
    Type strategy;
    string filename;
    int head;
  public:
    // Constructor
    FixedRecordFile(string filename, Type strategy){
      this->filename = filename;
      this->strategy = strategy;
      head = -1;
    }

  vector<Alumno> load(){
    ifstream file(filename, ios::in | ios::binary);
    
    if(!file.is_open()) throw ("No se pudo abrir el archivo");

    vector<Alumno> alumnos;
    Alumno al;

    while(file >> al){
      alumnos.push_back(al);
    }

    file.close();
    return alumnos;
  }

  void add(Alumno al){
    ofstream file(filename, ios::app | ios::binary);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");

    file << al;

    file.close();
  }

  Alumno readRecord(int pos){

  }

  int size(){
    ifstream file(filename, ios::in | ios::binary);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");
    
    file.seekg(0, ios::end);
    long total_bytes = file.tellg();
    file.close();
    return total_bytes / sizeof(Alumno);
  }
};

int main(){
  Alumno al1 {"2022", "Jeffrey", "Monja", "CS", 5, 2.6};

  FixedRecordFile file("data.dat", free_list);
  file.add(al1);

  vector<Alumno> alumnos = file.load();

  cout << alumnos.size() << endl;


  return 0;
}