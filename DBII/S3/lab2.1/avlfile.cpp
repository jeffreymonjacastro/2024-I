#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Record{
	int cod;
	char nombre[15];
	char carrera[15];
	int ciclo;

	// Atributos del nodo
	int height;
	int left = -1;
	int right = -1;
	
	void setData() {
		cout << "Codigo:";
		cin >> cod;
		cout << "Nombre: ";
		cin >> nombre;
		cout << "Ciclo: ";
		cin >> ciclo;
	}

	void showData() {
		cout << "\nCodigo: " << cod;
		cout << "\nNombre: " << nombre;
		cout << "\nCiclo : " << ciclo <<endl;
	}   
};

Record readNode(fstream &file, long pos){
	Record node;
	file.seekg(pos + sizeof(Record));
	file.read((char *)&node, sizeof(Record));
	return node;
}

void writeNode(fstream &file, long pos, Record &node){
	file.seekp(pos + sizeof(Record));
	file.write((char *)&node, sizeof(Record));
}

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

		// Check if there is data in the file
		if (file.tellg() / sizeof(Record)){
			file.seekg(0, ios::beg);
			file.read((char*)&pos_root, sizeof(long));
		} else {
			file.seekg(0, ios::beg);
			pos_root = -1; 
			file.write((char*)&pos_root, sizeof(long));
		}

		file.close();
	}
	
	Record find(int key){
		fstream file(filename, ios::in | ios::app | ios::binary);

		return find(file, pos_root, key);
	}
	
	void insert(Record record){
		fstream file(filename, ios::in | ios::app | ios::binary);

		insert(file, pos_root, record);
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
			return record;
		}

		Record node = readNode(file, pos_node);

		if (key == node.cod){
			return node;
		} else if (key < node.cod){
			return find(file, node.left, key);
		} else {
			return find(file, node.right, key);
		}
	}	

	void insert(fstream &file, long pos_node, Record record){
		if (pos_node == -1){
			pos_node = file.tellp();
			writeNode(file, pos_node, record);
			return;
		}

		/*
		if (node == nullptr)
			node = new NodeBT<T>(value);
		else if (value < node->data)
			insert(node->left, value);
		else
			insert(node->right, value); 
		*/
	}
	
	vector<Record> inorder(long pos_node, vector<Record> &result){
		/*
		if (node == nullptr)
			return;
		displayPreOrder(node->left);
		cout << node->data << endl;
		displayPreOrder(node->right);
		*/
	}
};


void writeFile(string filename){
    AVLFile file(filename);
    Record record;
    for (int i = 0; i < 4; i++)
    {
        record.setData();
        file.insert(record);
    }   
}

void readFile(string filename){
    AVLFile file(filename);        
    cout<<"--------- show all sorted data -----------\n";
	vector<Record> result = file.inorder();
	for(Record re : result){
		re.showData();
	}      
}

int main(){
    writeFile("data.dat");
    readFile("data.dat");
    return 0;
}

