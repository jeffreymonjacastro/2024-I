#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

using namespace std;
int SIZE = 36;
struct Record
{
    int cod;
	char nombre[12];
	int ciclo;
	
	long left, right;
	
	void setData() {
        cout << "Codigo: ";
        cin >> cod;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Ciclo: ";
        cin >> ciclo;
        left = -1;
        right = -1;
    }

    void showData() {
        cout << "\nCodigo: " << cod;
        cout << "\nNombre: " << nombre;
        cout << "\nCiclo : " << ciclo;
        cout << "\nleft : " << left;
        cout << "\nright : " << right <<endl;
    }   
};

class AVLFile {
private:
    string filename;
    long pos_root;
public:
    AVLFile(string filename){
		this->pos_root = 0;
		this->filename = filename;
        init_root();
	}
	
    Record find(int key){
        fstream file(this->filename, ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw ("No se pudo abrir el archivo");
        Record record=find(pos_root,key,file);
        file.close();
		return record;
	}
	
	void insert(Record record){
        fstream file(this->filename,ios::app| ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw ("No se pudo abrir el archivo");
		insert(pos_root, record);
        file.close();
	}
	
    vector<Record> inorder(){
		fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw ("No se pudo abrir el archivo");
        
        vector<Record> result;
		inorder(pos_root, result, file);
        
        file.close();
        return result;
	}

private:
    void init_root(){
        fstream file(this->filename, ios::app|ios::binary | ios::in | ios::out);
        
        file.seekg(0, ios::end);
        int tam = file.tellg();
        if (tam == 0) pos_root = -1;
        else pos_root = 0;
        file.close();
    }
	Record find(long pos_node, int key, fstream &file){
        if (pos_node == -1) throw ("No se encontro el registro");
        file.seekg(pos_node,ios::beg);
        Record record;
        file.read((char*)&record, SIZE);
        if(record.cod == key) return record;
        else if(record.cod > key) return find(record.left, key, file);
        else if(record.cod < key) return find(record.right, key, file);
	}

	void insert(long &pos_node, Record record){
        if(pos_node == -1){
            fstream file(this->filename,ios::app| ios::binary | ios::in | ios::out);
            file.seekp(0, ios::end);
            pos_node = file.tellg();
            file.write((char*)&record, sizeof(Record));
            file.close();
        } 
        else{
            fstream file(this->filename, ios::binary | ios::in | ios::out);
            file.seekg(pos_node, ios::beg);
            Record father;
            file.read((char*)&father, sizeof(Record));
            if(record.cod < father.cod) {
                insert(father.left, record);
                file.seekp(pos_node, ios::beg);
                file.write((char*)&father, sizeof(Record));
            }else if(record.cod > father.cod){ 
                insert(father.right, record);
                file.seekp(pos_node, ios::beg);
                file.write((char*)&father, sizeof(Record));
            }

        }
	}
	
	void inorder(long pos_node, vector<Record> &result, fstream &file){
        // Si no encuentra ningun nodo
        if (pos_node == -1)
            return;
        
        // Desplazar el cursor hacia la posicion deseada
        file.seekg(pos_node, ios::beg);
        
        // Leyendo "record"
        Record record;
        file.read((char*) &record, sizeof(Record));
        
        // Logica "InOrder"
        inorder(record.left, result, file);
        result.push_back(record);
        inorder(record.right, result, file);
	}


};


void writeFile(string filename){
    AVLFile file(filename);
    Record record;
    for (int i = 0; i < 4; i++) {
        record.setData();
        cout << "Estoy antes del insert\n";
        file.insert(record);
        cout << "Estoy despues del insert\n";
    }   
}

void readFile(string filename){
    AVLFile file(filename);        
    cout<<"--------- show all sorted data -----------\n";
	vector<Record> result = file.inorder();
	for(Record re : result) {
		re.showData();
	}      
}

int main(){
    //swriteFile("data.dat");
    readFile("data.dat");
    //readRecord("data.dat", 20);
    return 0;
}

