#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Record {
  int cod;
  char nombre[15];
  char carrera[15];
  int ciclo;

  int height;
  int left = -1;
  int right = -1;

  void setData() {
		cout << "Codigo:";
		cin >> cod;
		cout << "Nombre: ";
		cin >> nombre;
    cout << "Carrera: ";
    cin >> carrera;
		cout << "Ciclo: ";
		cin >> ciclo;
	}

	void showData() {
		cout << endl << "Codigo: " << cod;
		cout << endl << "Nombre: " << nombre;
    cout << endl << "Carrera: " << carrera;
		cout << endl << "Ciclo : " << ciclo << endl;
	}   
};

Record readRecord(fstream &file, long pos){
  Record record;
  file.seekg(pos + sizeof(Record) + sizeof(long), ios::beg);
  file.read((char *)&record, sizeof(Record));
  return record;
}

// void writeRecord(fstream &file, long pos, Record &record){
//   file.seekp(pos + sizeof(Record) + sizeof(long), ios::beg);
//   file.write((char *)&record, sizeof(Record));
// }

class AVLFile {
private:
  string filename;
  long pos_root;

public:
  AVLFile(string filename): filename(filename){
    fstream file(filename, ios::in | ios::app | ios::binary);

    if (!file.is_open()){
      cerr << "Error al abrir el archivo" << endl;
      exit(1);
    }

    file.seekg(0, ios::end);

    if (size()) {
      file.seekg(0, ios::beg);
      file.read((char *)&pos_root, sizeof(long));
    } else {
      pos_root = -1;
      file.write((char *)&pos_root, sizeof(long));
    }

    file.close();
  }

  int size(){
    ifstream file(filename, ios::in | ios::binary);

    if (!file.is_open()){
      cerr << "Error al abrir el archivo" << endl;
      exit(1);
    }
    
    file.seekg(sizeof(long), ios::end);
    
    return (file.tellg() / sizeof(Record));
  }

  Record find(int key){
    fstream file(filename, ios::in | ios::app | ios::binary);

    if (!file.is_open()){
      cerr << "Error al abrir el archivo" << endl;
      exit(1);
    }

    return find(file, pos_root, key);
  }

  void insert(Record record){
    fstream file(filename, ios::in | ios::app | ios::binary);

    if (!file.is_open()){
      cerr << "Error al abrir el archivo" << endl;
      exit(1);
    }

    return insert(file, pos_root, record);
  }

  vector<Record> inorder(){
    vector<Record> result;

    inorder(pos_root, result);
    
    return result;
  }

private:
  Record find(fstream &file, long pos_node, int key){
    if (pos_node == -1){
      Record record;
      record.cod = -1;
      return record;
    }

    Record record = readRecord(file, pos_node);

    if (record.cod == key){
      return record;
    } else if (record.cod < key){
      return find(file, record.right, key);
    } else {
      return find(file, record.left, key);
    }

    // if (record.cod == key){
    //   return record;
    // } else if (record.cod < key){
    //   return find(file, record.right, key);
    // } else {
    //   return find(file, record.left, key);
    // }
  }

  void insert(fstream &file, long &pos_node, Record &record){
    if (pos_node == -1){
      pos_node = 1;
      file.seekg(0, ios::beg);
      file.write((char *)&pos_node, sizeof(long));
      file.seekp(0, ios::end);
      file.write((char *)&record, sizeof(Record));
    }
  }

  void inorder(long pos_node, vector<Record> &result){

  }
};

int main(){
  AVLFile avl("data.dat");

  Record al1{1, "Juan", "CS", 5};

  cout << avl.size() << endl;

  avl.insert(al1);

  cout << avl.size() << endl;

  avl.find(1).showData();


  return 0;
}