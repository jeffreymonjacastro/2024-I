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

  void print(){
    cout << "Nombre: " << nombre << endl;
  }
};

// Escribir un registro
//ofstream& operator <<(ofstream& stream, Alumno& al){
//  int index = 0;
//  stream.write((char*) &al, sizeof(al));
//  stream.write((char*) &index, sizeof(int));
//  stream << flush;
//  return stream;
//}
//
//// Leer un  Registro
//ifstream& operator >>(ifstream& stream, Alumno& al){
//  stream.read((char*) &al, sizeof(al) + sizeof(int));
//  return stream;
//}

enum Type {FREE_LIST, MOVE_TO_LAST};

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
      genHead();
    }

  void genHead(){
    if (strategy == FREE_LIST)
      head = -1;
    else if (strategy == MOVE_TO_LAST)
      head = size();
  }

  vector<Alumno> load(){
    ifstream file(filename, ios::in | ios::binary);
    
    if(!file.is_open()) throw ("No se pudo abrir el archivo");

    vector<Alumno> alumnos;
    Alumno al;

    while(file.read((char*) &al, sizeof(al))){
      alumnos.push_back(al);
    }

    file.close();
    return alumnos;
  }

  Alumno readRecord(int pos){
    ifstream inFile(filename, ios::in | ios::binary);

    if (!inFile.is_open()) throw ("No se pudo abrir el archivo");

    Alumno al;

    inFile.seekg(pos * (sizeof(al) + sizeof(int)), ios::beg);

    inFile.read((char *) &al, sizeof(al));

    inFile.close();

    return al;
  }

  int size(){
    ifstream file(filename, ios::in | ios::binary);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");
    
    file.seekg(0, ios::end);
    long total_bytes = file.tellg();
    file.close();
    return total_bytes / sizeof(Alumno);
  }

  void add(Alumno al){
    fstream file(filename, ios::in | ios::app | ios::binary);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");

    if (strategy == FREE_LIST){
      int temp, index;

      file.seekp(0, ios::beg);
      file.seekp(head * (sizeof(al) + sizeof(int)));
      file.seekg(head * (sizeof(al) + sizeof(int)));
      file.seekg(sizeof(al));
      file.read((char*) &temp, sizeof(int));
      file.write((char*) &al, sizeof(al));
      file.write((char*) &index, sizeof(int));
      head = temp;

    } else if (strategy == MOVE_TO_LAST){
      file.seekp(head * sizeof(al));
      file.write((char*) &al, sizeof(al));
      head++;
    }

    file.close();
  }

  void del(int pos){
    fstream file(filename, ios::in | ios::out | ios::binary);

    if (!file.is_open()) throw ("No se puede abrir el archivo");

    Alumno al;

    if (strategy == FREE_LIST){

    } else if (strategy == MOVE_TO_LAST){
      file.seekg(head * sizeof(al));
      file.seekp(pos * sizeof(al));
      file.read((char*) &al, sizeof(al));
      file.write((char*) &al, sizeof(al));
      head--;
    }

    file.close();
  }
};

void test1(){
  FixedRecordFile fr("data.bin" , MOVE_TO_LAST);

  Alumno alumnos[10] = {
      {"A001", "Ana", "Perez", "INF", 1, 1200.50},
      {"A002", "Luis", "Gomez", "ADM", 2, 1100.00},
      {"A003", "Mia", "Lopez", "DER", 3, 1300.75},
      {"A004", "Juan", "Diaz", "MED", 4, 1400.25},
      {"A005", "Sara", "Mora", "PSI", 1, 1250.00},
      {"A006", "Leo", "Vega", "ARQ", 2, 1350.45},
      {"A007", "Rita", "Solis", "CIV", 3, 1450.60},
      {"A008", "Tito", "Luna", "IND", 4, 1550.20},
      {"A009", "Lola", "Nuez", "INF", 1, 1150.30},
      {"A010", "Paco", "Rio", "ADM", 2, 1050.90}
  };

  for(int i = 0; i < 10; i++) {
      fr.add(alumnos[i]);
  }

  vector<Alumno> v_al = fr.load();

  for(int i = 0; i < v_al.size(); i++) {
      v_al[i].print();
  }

  fr.del(5);

  cout<<"Eliminando la posicion 5"<<endl;

  v_al = fr.load();

  for(int i = 0; i < v_al.size(); i++) {
      v_al[i].print();
  }

  Alumno al3{"A011", "Eva", "Campos", "BIO", 1, 1175.80};

  fr.add(al3);

  cout<<endl;

  v_al = fr.load();

  for(int i = 0; i < v_al.size(); i++) {
      v_al[i].print();
  }
}

int main(){
//  test1();

  Alumno al1{"A011", "Eva", "Campos", "BIO", 1, 1175.80};

  FixedRecordFile file("data.bin", MOVE_TO_LAST);

  file.add(al1);

  vector<Alumno> alumnos = file.load();

  for(auto al : alumnos){
    al.print();
  }

  return 0;
}