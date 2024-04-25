#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#define MAX_B 3
using namespace std;

struct Record {
  char nombre[30];
  char carrera[20];
  int ciclo;

  void setData() {
    cout << "Alumno:";
    cin >> nombre;
    cout << "Carrera: ";
    cin >> carrera;
    cout << "Ciclo: ";
    cin >> ciclo;
  }

  void showData() {
    cout << "\nNombre: " << nombre;
    cout << "\nCarrera: " << carrera;
    cout << "\nCiclo : " << ciclo;
  }
};

struct Bucket{
  Record records[MAX_B];
  int size;
  long next_bucket;

  Bucket(){
    size = 0;
    next_bucket = -1;
  }

  void showData(){
    cout<<"["<<endl;
    for(int i=0;i<size;i++)
      records[i].showData();
    cout<<"]"<<endl;
  }
};

class StaticHashFile {
private:
  string filename;
  int N_BUCKETS;

public:
  StaticHashFile(string filename, int N_BUCKETS){
    this->filename = filename;
    this->N_BUCKETS = N_BUCKETS;
  }

  void writeRecord(Record record){
    //1- usando una funcion hashing ubicar la pagina de datos
    //2- leer la pagina de datos, 
    //3- verificar si size < MAX_B, si es asi, se inserta en esa pagina y se regresa al archivo
    //4- caso contrario, crear nuevo bucket, insertar ahi, mantener el enlace
    
    file.close();
      
  }

  Record search(string nombre){
    //1- usando una funcion hashing ubicar la pagina de datos
    //2- leer la pagina de datos, ubicar el registro que coincida con el nombre
    //3- si no se encuentra el registro en esa pagina, ir a la pagina enlazada iterativamente
  }

  void scanAll(){
    //1- abrir el archivo de datos y mostrar todo     
  }
};

