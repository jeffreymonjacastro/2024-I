#include <iostream>
#include<fstream>
#include<cstdio>

using namespace std;

void writeString(fstream &stream, string str);

string readString(fstream &stream);

class Record {
private:
    string nombre;
    string carrera;
    int ciclo;

public:
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

    long write(fstream &stream) {
        long pos_begin = stream.tellp();
        stream.write((char*) &ciclo, sizeof(ciclo));
        writeString(stream, nombre);
        writeString(stream, carrera);
        return pos_begin;
    }

    bool read(fstream &stream) {
        stream.read((char *) &ciclo, sizeof(ciclo));
        if(stream.fail()) return false;
        nombre = readString(stream);
        carrera = readString(stream);
        return true;
    }
};

class VariableRecordFile {

private:
    string fileName;
    string indexName;

public:
    VariableRecordFile(string _fileName) {
        this->fileName = _fileName;
        this->indexName = _fileName + "_ind";
    }

/*
* function to write (append) in a binary file.
*/
    void writeRecord(Record obj) {
        fstream outFile;
        long pos;

        //write the record
        outFile.open(this->fileName, ios::binary | ios::app);
        if (outFile.is_open()) {
            long pos = obj.write(outFile);
            outFile.close();

            //write the position into the index file
            outFile.open(this->indexName, ios::binary | ios::app);
            if (outFile.is_open()) {
                outFile.write((char *) &pos, sizeof(pos));
                outFile.close();
            } else cout << "Could not open the index-file.\n";
        } else cout << "Could not open the file.\n";
    }

/*
* function to display all records
*/
    void scanAll() {
        fstream inFile;
        inFile.open(this->fileName, ios::in | ios::binary);
        Record obj;
        if (inFile.is_open()) {
            while (obj.read(inFile)) {
                obj.showData();
            }
            inFile.close();
        } else cout << "Could not open the file.\n";
    }

/*
* function to read a record
*/
    Record readRecord(int n) {
        fstream inFile;
        long pos;
        Record obj;

        //read the position from the index file
        inFile.open(this->indexName, ios::in | ios::binary);
        if (inFile.is_open()) {
            inFile.seekg(n * sizeof(pos));
            inFile.read((char *) &pos, sizeof(pos));
            inFile.close();

            //read the record
            inFile.open(this->fileName, ios::in | ios::binary);
            if (inFile.is_open()) {
                inFile.seekg(pos);
                obj.read(inFile);
                inFile.close();
            } else cout << "Could not open the file.\n";
        } else cout << "Could not open the index-file.\n";

        return obj;
    }

    int size() {
        int numRecords = 0;
        fstream inFile;
        inFile.open(this->indexName, ios::in | ios::binary);
        if (inFile.is_open()) {
            inFile.seekg(0, ios::end);
            numRecords = inFile.tellg() / sizeof(long);
            inFile.close();
        } else cout << "Could not open the index-file.\n";
        return numRecords;
    }
};

void writeString(fstream &stream, string str) {
    int len = str.size();
    stream.write((char*) &len, sizeof(len));
    stream.write(str.c_str(), len);
}

string readString(fstream &stream) {
    int len;
    stream.read((char *) &len, sizeof(len));
    char *buffer = new char[len + 1];
    stream.read(buffer, len);
    buffer[len] = '\0';
    string result = buffer;
    delete buffer;
    return result;
}
