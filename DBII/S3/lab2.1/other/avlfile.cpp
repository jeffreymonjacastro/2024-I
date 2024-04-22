#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Record
{
    int cod;
	char nombre[12];
	int ciclo;
	
	long left, right;
	
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

class AVLFile
{
private:
    string filename;
    long pos_root;
public:
    AVLFile(string filename){
		this->pos_root = 0;
		this->filename = filename;
	}
	
    Record find(int key){
		return find(pos_root, key);
	}
	
	void insert(Record record){
		insert(pos_root, record);
	}
	
    vector<Record> inorder(){
		vector<Record> result;
		inorder(pos_root, result);
		return result;
	}

private:
	Record find(long pos_node, int key){
		/*
		if (node == nullptr)
			return false;
		else if (value < node->data)
			return find(node->left, value);
		else if (value > node->data)
			return find(node->right, value);
		else
			return true;
		*/
	}	

	void insert(long pos_node, Record record){
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

