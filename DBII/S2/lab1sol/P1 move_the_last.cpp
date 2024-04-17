#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace  std;

//Alumno has a size of 24
struct Alumno{
    char codigo[5];
    char nombre[11];
    int ciclo;
    float mensualidad;
    Alumno(){
        strcpy(codigo, "");
        strcpy(nombre, "");
        ciclo = 0;
        mensualidad=0;
    }
    Alumno(const char* codigo,const char* nombre, int ciclo, float mensualidad){
        strcpy(this->codigo, codigo);
        strcpy(this->nombre, nombre);
        this->ciclo = ciclo;
        this->mensualidad = mensualidad;
    }
};

ostream& operator<<(ostream &os, Alumno al){
    os<<al.codigo<<"-"<<al.nombre<<"-"<<al.ciclo<<"-"<<al.mensualidad;
    return os;
}

class FixedRecordFile {
private:
    string filename;
    int type_del;
public:
    FixedRecordFile(string filename, int type_del){
        this->filename=filename;
        this->type_del=type_del;

        inicializar_archivo();
    }

    void inicializar_archivo(){
        ofstream file(this->filename, ios::app | ios::binary);
        long size_bytes = file.tellp();
        if(size_bytes <= 0) {
            int num_records = 0;
            file.seekp(0, ios::beg);
            file.write((char*)&num_records, sizeof(int));
        }
        file.close();
    }

    void add(Alumno al) {
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        int num_records = 0;
        //leer el numero de registros
        file.seekg(0, ios::beg);
        file.read((char*)&num_records, sizeof(int));

        //guardar el alumno al final
        file.seekg(num_records*sizeof(Alumno) + sizeof(int), ios::beg);
        file.write((char*)&al, sizeof(Alumno));
        cout<<"Escribiendo registro "<<num_records<<endl;

        //guardar el numero de registros
        num_records++;
        file.seekg(0, ios::beg);
        file.write((char*)&num_records, sizeof(int));
        file.close();
    }
    Alumno readRecord(int pos){
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        Alumno al;
        //leer el numero de registros
        int num_records = 0;
        file.seekg(0, ios::beg);
        file.read((char*)&num_records, sizeof(int));
        if(pos < num_records){
            file.seekg(pos*sizeof(Alumno) + sizeof(int), ios::beg);
            file.read((char*)&al, sizeof(Alumno));
        }
        file.close();
        return al;
    }
    bool deleteRecord(int pos){
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        //leer el numero de registros
        int num_records = 0; bool res = false;
        file.seekg(0, ios::beg);
        file.read((char*)&num_records, sizeof(int));
        if(pos < num_records && num_records > 0){
            //leer el ultimo registro
            Alumno al;
            file.seekg((num_records-1)*sizeof(Alumno) + sizeof(int), ios::beg);
            file.read((char*)&al, sizeof(Alumno));
            //sobreescribir en la posicion pos
            file.seekg(pos*sizeof(Alumno) + sizeof(int), ios::beg);
            file.write((char*)&al, sizeof(Alumno));
            //decrementar el numero de registros
            num_records--;
            file.seekg(0, ios::beg);
            file.write((char*)&num_records, sizeof(int));
        }
        file.close();
        return res;
    }
    vector<Alumno> loadAll(){
        ifstream file(filename, ios::binary);
        int num_records = 0;
        file.read((char*)&num_records, sizeof(int));
        vector<Alumno> res;
        Alumno al;
        for(int i=0;i<num_records;i++){
            file.read((char*)&al, sizeof(Alumno));
            res.push_back(al);
        }
        file.close();
        return res;
    }
};
void mostrarTodos(){
    FixedRecordFile file("datos.dat", 1);
    vector<Alumno> todos = file.loadAll();
    cout<<"-----------------\n";
    for(Alumno al : todos)
        cout<<al<<endl;
}

void testWrite(){
    FixedRecordFile file("datos.dat", 1);
    file.add(Alumno("C001", "Ana", 5, 1200.0));
    file.add(Alumno("C002", "Marcos", 2, 1000.0));
    file.add(Alumno("C003", "Juanita", 10, 2200.0));
    file.add(Alumno("C004", "Mario", 8, 3500.0));
    file.add(Alumno("C005", "Sofia", 9, 2800.0));
    file.add(Alumno("C006", "Carlos", 3, 2800.0));
    file.add(Alumno("C007", "Jose", 4, 2800.0));
    mostrarTodos();
    file.deleteRecord(1);
    mostrarTodos();
    file.deleteRecord(4);
    mostrarTodos();
}

void testRead(){
    FixedRecordFile file("datos.dat", 1);
    Alumno alumno = file.readRecord(2);
    cout<<"Alumno posicion "<<2<<endl;
    cout<<alumno<<endl;
}

int main(){
    testWrite();
    testRead();
    return 0;
}