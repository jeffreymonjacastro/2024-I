#include <iostream>
#include <fstream>

using namespace std;

// Record
class Alumno {
  public:
    char Nombre[20]; // Tamaño fijo
    char Carrera[10];
};

// Escribir un Registro
ostream& operator <<(ostream& stream, Alumno& al){
  stream.write(al.Nombre, 20);
  stream.write(al.Carrera, 10);
  // stream << '\n';
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

string filename = "archivo.dat";

void testWrite(){
  Alumno al1 {"Pedro", "CS"};
  Alumno al2 {"Marta", "IND"};
  Alumno al3 {"Santos", "MEC"};
  Alumno al4 {"Javier", "CD"};
  Alumno al5 {"Elena", "BIO"};

  // app: Abre el archivo y mueve el cursor al final
  ofstream outFile(filename, ios::out | ios::binary);

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

void testRead(){
  ifstream inFile(filename, ios::in | ios::binary);

  if (!inFile.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  int count = 0;
  Alumno al;

  while (inFile.read((char*) &al, sizeof(Alumno))){ 
    cout << count++ << ": " << al.Nombre << "-" << al.Carrera << endl;
  }

  inFile.close();
}

void testRead(int i){
  Alumno al;

  ifstream inFile(filename, ios::in | ios::binary);

  if (!inFile.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  // Mover el puntero al comienzo del registro que deseamos.
  inFile.seekg(i * sizeof(al), ios::beg);

  // Leemos cada byte del archivo y se aplica typecast a char
  inFile.read((char *) &al, sizeof(al));

  cout << al.Nombre << "-" << al.Carrera << endl;

  inFile.close();
}

void testDelete(int i){
  fstream file(filename, ios::in | ios::out | ios::binary);

  if (!file.is_open()){
    cerr << "No se puede abrir el archivo";
    exit(1);
  }

  Alumno al;

  // Colocar el puntero a un registro arriba al que se desea eliminar

  while(file.seekg(i * sizeof(al) + sizeof(al), ios::beg)){
    file >> al;
    file.seekp(i * sizeof(al), ios::beg);
    file << al;
    i++;
  }

  file.close();
}

int main(){
  Alumno al;

  cout << sizeof(al) << endl;

  testWrite();

  cout << "Lista de Alumnos: " << endl;
  testRead();

  cout << "Alumno 0:" << endl;
  testRead(0);

  cout << "Delete alumno 0" << endl;
  testDelete(0);

  cout << "Alumnos que quedan: " << endl;
  testRead();

  return 0;
}