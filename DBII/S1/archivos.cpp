#include <iostream>
#include <fstream>

using namespace std;

// Record
class Alumno {
  public:
    char Nombre[20];
    char Carrera[10];
};

// Escribir un Registro
ostream& operator <<(ostream& stream, Alumno& al){
  stream.write(al.Nombre, 20);
  stream.write(al.Carrera, 10);
  stream << flush; // Fuerza la limpieza del buffer

  return stream;
}

// Leer un  Registro
istream& operator >>(istream& stream, Alumno& al){
  stream.read(al.Nombre, 20);
  stream.read(al.Carrera, 10);
  stream.get(); // Read \n
  return stream;
}

void testWrite(){
  Alumno al1 {"Pedro", "CS"};
  Alumno al2 {"Marta", "IND"};
  Alumno al3 {"Santos", "MEC"};
  Alumno al4 {"Javier", "CD"};
  Alumno al5 {"Elena", "BIO"};

  // app: Abre el archivo y mueve el cursor al final
  ofstream outFile("archivo.dat", ios::app | ios::binary);

  if (!outFile.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  outFile<<al1;
  outFile<<al2;
  outFile<<al3;
  outFile<<al4;
  outFile<<al5;

  outFile.close();
}

void testReadB(){
  ifstream inFile("archivo.dat", ios::in | ios::binary);

  if (!inFile.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  int count = 0;

  while (!inFile.eof()){
    Alumno al;
    inFile >> al;
    cout << count++ << ": " << al.Nombre << "-" << al.Carrera << endl;
  }
}

void testRead(int i){
  Alumno al;

  ifstream inFile("archivo.txt", ios::in | ios::binary);

  if (!inFile.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  inFile.seekg(i * sizeof(al), ios::beg);
  inFile.read((char *) &al, sizeof(al));
  inFile >> al;
  cout << al.Nombre << "-" << al.Carrera << endl;

  inFile.close();
}

int main(){
  testWrite();
  // testRead();
  // testRead(2);

  return 0;
}