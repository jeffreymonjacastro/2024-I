#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Record
{
	int cod;
	char nombre[12];
	int ciclo;

	long left = -1, right = -1;
	int height = 0;

	void setData()
	{
		cout << "Codigo:";
		cin >> cod;
		cout << "Nombre: ";
		cin >> nombre;
		cout << "Ciclo: ";
		cin >> ciclo;
	}

	void showData()
	{
		cout << "\nCodigo: " << cod;
		cout << "\nNombre: " << nombre;
		cout << "\nCiclo : " << ciclo << endl;
		cout << "Izq : " << left << endl;
		cout << "Der : " << right << endl;
		cout << "Altura : " << height << endl;
	}
};

class AVLFile
{
private:
	string filename;
	long pos_root;

public:
	AVLFile(string filename)
	{
		fstream file(filename, ios::binary | ios::in | ios::out);
		this->pos_root = -1;
		this->filename = filename;
		if (!file)
		{
			cout << "File not found, creating new file\n";
			ofstream file2(this->filename, ios::binary);
			file2.write((char *)(&pos_root), sizeof(long));
			file2.close();
		}
		else
		{
			file.read((char *)(&pos_root), sizeof(long));
		}
		file.close();
	}

	Record find(int key)
	{
		fstream file(this->filename, ios::binary | ios::in | ios::out);
		Record record = find(pos_root, key, file);
		file.close();
		return record;
	}

	void insert(Record record)
	{
		fstream file(this->filename, ios::binary | ios::in | ios::out);
		insert(pos_root, record, file);
		file.close();
	}

	vector<Record> inorder()
	{
		fstream file(this->filename, ios::binary | ios::in | ios::out);
		vector<Record> result;
		inorder(pos_root, result, file);
		file.close();
		return result;
	}

	void printAll()
	{
		fstream file(this->filename, ios::binary | ios::in | ios::out);
		long pos = 0;
		Record record;
		// get the root
		file.seekg(0, ios::beg);
		file.read((char *)(&pos), sizeof(long));

		cout << "Root: " << pos << endl;

		int count = 0;
		while (file.read((char *)(&record), sizeof(Record)))
		{
			cout << count++ << ": " << record.cod << " | " << record.nombre << " | " << record.ciclo << " | " << record.left << " | " << record.right << " | " << record.height << endl;
		}
		file.close();
	}

	long getRoot(){
		return pos_root;
	}

private:
	Record find(long pos_node, int key, fstream &file)
	{
		if (pos_node == -1) return{};

		Record record;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)&record, sizeof(Record));
		if (key < record.cod)
		{
			return find(record.left, key, file);
		}
		else if (record.cod < key)
		{
			return find(record.right, key, file);
		}
		else
		{
			return record;
		}
	}

	void insert(long pos_node, Record record, fstream &file)
	{
		if (pos_node == -1)
		{
			this->pos_root = 0;
			file.seekp(0, ios::beg);
			file.write((char *)(&pos_root), sizeof(long));
			file.write((char *)(&record), sizeof(Record));
			return;
		}
		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		if (record.cod > a.cod)
		{
			if (a.right == -1)
			{
				int indx = 0;
				file.seekg(0, ios::end);
				indx = file.tellp() / sizeof(Record);
				file.write((char *)(&record), sizeof(Record));

				file.seekg(sizeof(int) + pos_node * sizeof(Record) + sizeof(int) + sizeof(a.nombre) + sizeof(int) + sizeof(long), ios::beg);
				file.write((char *)(&indx), sizeof(int));
				return;
			}
			insert(a.right, record, file);
		}
		else if (record.cod < a.cod)
		{
			if (a.left == -1)
			{
				int indx = 0;
				file.seekg(0, ios::end);
				indx = file.tellg() / sizeof(Record);
				file.write((char *)(&record), sizeof(Record));

				file.seekg(sizeof(int) + pos_node * sizeof(Record) + sizeof(int) + sizeof(a.nombre) + sizeof(int), ios::beg);
				file.write((char *)(&indx), sizeof(int));
				return;
			}
			insert(a.left, record, file);
		}

		balance(pos_node, file);
	}

	vector<Record> inorder(long pos_node, vector<Record> &result, fstream &file)
	{
		if (pos_node == -1) return result;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));
		inorder(a.left, result, file);
		result.push_back(a);
		inorder(a.right, result, file);
		return result;
	}

	/* AVL Stuff */

	int height(long pos_node, fstream &file)
	{
		if (pos_node == -1) return -1;
		
		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));
		return a.height;
	}

	bool isBalanced(long pos_node, fstream &file)
	{
		if (pos_node == -1) return false;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		int left = height(a.left, file);
		int right = height(a.right, file);

		if (abs(left - right) > 1) return false;

		return isBalanced(a.left, file) && isBalanced(a.right, file);
	}

	int balancingFactor(long pos_node, fstream &file)
	{
		if (pos_node == -1) return 0;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		return height(a.right, file) - height(a.left, file);
	}

	void updateHeight(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		a.height = max(height(a.left, file), height(a.right, file)) + 1;

		file.seekp(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.write((char *)(&a), sizeof(Record));
	}

	void LL(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		Record b;
		file.seekg(sizeof(long) + a.left * sizeof(Record), ios::beg);
		file.read((char *)(&b), sizeof(Record));

		a.left = b.right;
		b.right = pos_node;

		a.height = max(height(a.left, file), height(a.right, file)) + 1;
		b.height = max(height(b.left, file), height(b.right, file)) + 1;

		file.seekp(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.write((char *)(&a), sizeof(Record));

		file.seekp(sizeof(long) + a.left * sizeof(Record), ios::beg);
		file.write((char *)(&b), sizeof(Record));
	}

	void RR(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		Record b;
		file.seekg(sizeof(long) + a.right * sizeof(Record), ios::beg);
		file.read((char *)(&b), sizeof(Record));

		a.right = b.left;
		b.left = pos_node;

		a.height = max(height(a.left, file), height(a.right, file)) + 1;
		b.height = max(height(b.left, file), height(b.right, file)) + 1;

		file.seekp(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.write((char *)(&a), sizeof(Record));

		file.seekp(sizeof(long) + a.right * sizeof(Record), ios::beg);
		file.write((char *)(&b), sizeof(Record));
	}

	void left_rotate(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		if (balancingFactor(a.left, file) >= 0) 
			LL(pos_node, file);
		else {
			RR(a.left, file);
			LL(pos_node, file);
		}
	}

	void right_rotate(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		if (balancingFactor(a.right, file) <= 0) 
			RR(pos_node, file);
		else {
			LL(a.right, file);
			RR(pos_node, file);
		}
	}

	void balance(long pos_node, fstream &file)
	{
		if (pos_node == -1) return;

		Record a;
		file.seekg(sizeof(long) + pos_node * sizeof(Record), ios::beg);
		file.read((char *)(&a), sizeof(Record));

		if (balancingFactor(pos_node, file) > 1)
			left_rotate(pos_node, file);
		else if (balancingFactor(pos_node, file) < -1)
			right_rotate(pos_node, file);
		else
			updateHeight(pos_node, file);
	}
};

void writeFile(string filename)
{
	// clean file
	ofstream file2(filename, ios::binary);
	file2.close();
	AVLFile file(filename);

	Record r1 = {1001, "Juan", 1};
	Record r2 = {1008, "Pedro", 5};
	Record r3 = {1002, "Maria", 2};
	Record r4 = {1004, "Jose", 4};
	Record r5 = {1003, "Luis", 3};
	Record r6 = {1009, "Carlos", 9};
	file.insert(r1);
	file.insert(r2);
	file.insert(r3);
	file.insert(r4);
	file.insert(r5);
	file.insert(r6);
}

void readFile(string filename)
{
	AVLFile file(filename);
	cout << "--------- show all sorted data -----------\n";
	file.printAll();
	vector<Record> result = file.inorder();
	for (Record re : result)
	{
		re.showData();
	}

	cout << "--------- find data -----------\n";
	Record record = file.find(1002);
	record.showData();
}

int main()
{
	writeFile("data.dat");
	readFile("data.dat");
	return 0;
}
