#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct Record
{
    int codigo;
    char nombre[12];
    int ciclo;
    long left = -1, right = -1;
    int height = 1;
    void setData()
    {
        cout << "Codigo:";
        cin >> codigo;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Ciclo: ";
        cin >> ciclo;
    }
    void showData()
    {
        cout << "\nCodigo: " << codigo;
        cout << "\nNombre: " << nombre;
        cout << "\nCiclo : " << ciclo << endl;
    }
};

Record readNode(fstream &file, long pos)
{
    Record node;
    file.seekg(pos + sizeof(Record));
    file.read((char *)&node, sizeof(Record));
    return node;
}

void writeNode(fstream &file, long pos, Record &node)
{
    file.seekp(pos + sizeof(Record));
    file.write((char *)&node, sizeof(Record));
}

class AVLTree
{
private:
    string filename;
    long pos_root;

public:
    // static methods
    static void writeMockData(string filename)
    {

        fstream file(filename, ios::out);

        long header = -1;
        file.write((char *)&header, sizeof(Record));
        file.close();

        Record node;
        AVLTree tree(filename);

        for (int i = 0; i < 10; i++)
        {
            int codigo = 1000;
            Record node = {codigo + i, "Node", i};
            tree.insert(node);
        }

        // print inserted records

        cout << "-----------------Inserted Records-----------------" << endl;

        cout << "Header: " << tree.getHeader() << endl;

        for (int i = 0; i < 10; i++)
        {
            Record res = tree.find(i);
            cout << endl
                 << "Left: " << res.left << " Right: " << res.right << " Height: " << res.height;
            res.showData();
        }
        /*
        // insert new record
        Record newRecord = {98450, "Heider", 10};
        tree.insert(newRecord);
        Record res = tree.find(98450);
        res.showData();
        */

        // traverse the tree
        /*
        cout << "-----------------Inorder Traversal-----------------" << endl;
        vector<Record> result = tree.inorderTraversal();
        for (int i = 0; i < result.size(); i++)
        {
            result[i].showData();
        }
        */
    }

    AVLTree(string filename)
    {
        this->filename = filename;
        this->pos_root = getHeader();
    }

    long getHeader()
    {
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        long header;
        file.seekg(0);
        file.read((char *)&header, sizeof(long));
        file.close();
        return header;
    }

    Record find(int codigo)
    {
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        Record node = readNode(file, codigo * sizeof(Record));
        return node;
    }

    void insert(Record record)
    {
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        if (!file)
        {
            file.open(this->filename, ios::out);
        }
        // check if is the first record
        if (this->pos_root == -1)
        {
            this->pos_root = sizeof(Record);
            file.seekp(0);
            file.write((char *)&this->pos_root, sizeof(long));

            file.seekp(this->pos_root);
            file.write((char *)&record, sizeof(Record));
            file.close();
        }
        else
        {
            Record root = readNode(file, this->pos_root);
            pos_root = insertAVL(root, record, file);

            file.seekp(0);
            file.write((char *)&this->pos_root, sizeof(Record));
        }
        file.close();
    }

    vector<Record> inorderTraversal()
    {
        vector<Record> result;
        return result;
    }

private:
    long insertAVL(Record &current, Record &record, fstream &file)
    {
        if (record.codigo < current.codigo)
        {
            if (current.left == -1)
            {
                current.left = file.tellp();
                writeNode(file, current.left, record);
            }
            else
            {
                Record left = readNode(file, current.left);
                insertAVL(left, record, file);
            }
        }
        else if (record.codigo > current.codigo)
        {
            if (current.right == -1)
            {
                current.right = file.tellp();
                writeNode(file, current.right, record);
            }
            else
            {
                Record right = readNode(file, current.right);
                insertAVL(right, record, file);
            }
        }
        else
        {
            return current.codigo;
        }

        current.height = 1 + max(height(current.left), height(current.right));

        int balance = getBalance(current);

        // Left Left Case
        if (balance > 1 && record.codigo < readNode(file, current.left).codigo)
        {
            return rightRotate(current, file);
        }

        // Right Right Case
        if (balance < -1 && record.codigo > readNode(file, current.right).codigo)
        {
            return leftRotate(current, file);
        }

        // Left Right Case
        if (balance > 1 && record.codigo > readNode(file, current.left).codigo)
        {
            Record T2 = readNode(file, readNode(file, current.left).right);
            current.left = leftRotate(readNode(file, current.left), file);
            return rightRotate(current, file);
        }

        // Right Left Case
        if (balance < -1 && record.codigo < readNode(file, current.right).codigo)
        {
            Record T2 = readNode(file, readNode(file, current.right).left);
            current.right = rightRotate(readNode(file, current.right), file);
            return leftRotate(current, file);
        }

        writeNode(file, current.codigo, current);

        return current.codigo;
    }

    int height(long pos)
    {
        if (pos == -1)
            return 0;
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        Record node = readNode(file, pos);
        return node.height;
    }

    int getBalance(Record node)
    {
        if (node.codigo == -1)
            return 0;
        return height(node.left) - height(node.right);
    }

    long rightRotate(Record y, fstream &file)
    {
        Record x = readNode(file, y.left);
        Record T2 = readNode(file, x.right);

        // Perform rotation
        x.right = y.codigo;
        y.left = T2.codigo;

        // Update heights
        y.height = max(height(y.left), height(y.right)) + 1;
        x.height = max(height(x.left), height(x.right)) + 1;

        // Write the nodes back to the file
        writeNode(file, x.codigo, x);
        writeNode(file, y.codigo, y);

        // Return new root
        return x.codigo;
    }

    long leftRotate(Record x, fstream &file)
    {
        Record y = readNode(file, x.right);
        Record T2 = readNode(file, y.left);

        // Perform rotation
        y.left = x.codigo;
        x.right = T2.codigo;

        // Update heights
        x.height = max(height(x.left), height(x.right)) + 1;
        y.height = max(height(y.left), height(y.right)) + 1;

        // Write the nodes back to the file
        writeNode(file, x.codigo, x);
        writeNode(file, y.codigo, y);

        // Return new root
        return y.codigo;
    }
};

int main()
{
    AVLTree::writeMockData("data.dat");

    return 0;
}