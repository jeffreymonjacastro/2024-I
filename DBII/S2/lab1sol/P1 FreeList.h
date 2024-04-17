#include <iostream>
#include<fstream>
#include<cstdio>

using namespace std;

class Record {
private:
    char nombre[30];
    char carrera[20];
    int ciclo;

    int nextDel;

public:
    void setData() {
        cout << "Alumno:";
        cin >> nombre;
        cout << "Carrera: ";
        cin >> carrera;
        cout << "Ciclo: ";
        cin >> ciclo;
        nextDel = 0;//registro activo
    }

    void showData() {
        cout << "\nNombre: " << nombre;
        cout << "\nCarrera: " << carrera;
        cout << "\nCiclo : " << ciclo;
    }

    int getNextDel() { return nextDel; }
    void setNextDel(int _nextDel) { this->nextDel = _nextDel; }
};

class FixedRecordFile {
private:
    string fileName;

public:
    FixedRecordFile(string _fileName) {
        this->fileName = _fileName;

        initFreeList();
    }

    /*
    * function to write in a binary file.
    */
    void writeRecord(Record obj) {
        ofstream outFile;
        outFile.open(fileName, ios::binary | ios::app);
        outFile.write((char *) &obj, sizeof(obj));
        outFile.close();
    }

    /*
    * function to display records of file
    */
    void scanAll() {
        ifstream inFile;
        inFile.open(fileName, ios::binary);
        //read the first pointer
        int delPointer;
        inFile.read((char *) &delPointer, sizeof(int));
        //read the records
        Record obj;
        while (inFile.read((char *) &obj, sizeof(obj))) {
            if (obj.getNextDel() == 0)
                obj.showData();
        }
        inFile.close();
    }


    /*
    * function to delete a record
    */
    void deleteRecord(int n) {
        fstream inFile;
        Record obj;
        inFile.open(this->fileName, ios::in | ios::out | ios::binary);
        if (inFile.is_open()) {
            //leer el encabezado
            int delPointer;
            inFile.read((char *) &delPointer, sizeof(int));

            //read the record
            inFile.seekg(n * sizeof(Record) + sizeof(int));
            inFile.read((char*) &obj, sizeof(Record));

            //change its delete pointer
            obj.setNextDel(delPointer);

            //write the record
            inFile.seekg(n * sizeof(Record) + sizeof(int));
            inFile.write((char*) &obj, sizeof(Record));

            //write the delete pointer
            inFile.seekg(0, ios::beg);
            inFile.write((char *) &n, sizeof(int));

            inFile.close();
        }else cout << "Could not open the file.\n";
    }

    /*
    * function to insert a record
    */
    void insertRecord(Record  obj) {
        Record temp;
        fstream outFile;
        outFile.open(this->fileName, ios::in | ios::out | ios::binary );
        if (outFile.is_open()) {
            int delPointer;
            outFile.read((char *) &delPointer, sizeof(int));

            if(delPointer == -1){
                outFile.seekg(0, ios::end);
                outFile.write((char *) &obj, sizeof(obj));
            } else {
                //read the current record
                outFile.seekg(delPointer * sizeof(Record) + sizeof(int));
                outFile.read((char *) &temp, sizeof(temp));

                //write the new record
                outFile.seekg(delPointer * sizeof(Record) + sizeof(int));
                outFile.write((char *) &obj, sizeof(obj));

                //change the del pointer
                delPointer = temp.getNextDel();
                
                //write the delete pointer
                outFile.seekg(0, ios::beg);
                outFile.write((char *) &delPointer, sizeof(int));
            }
            outFile.close();
        }else cout << "Could not open the file.\n";
    }

    /*
     * function to initialize the free-list
     * */
    void initFreeList() {
        bool ready = false;
        fstream inFile;
        //check if the free-list has already been created
        inFile.open(this->fileName, ios::in | ios::binary | ios::ate);
        if (inFile.is_open()) {
            long bytes = inFile.tellg();
            ready = bytes >= (sizeof(Record) + sizeof(int));
            inFile.close();
        }

        //create the file with the delete pointer to null
        if (!ready) {
            remove(this->fileName.c_str());
            inFile.open(this->fileName, ios::out | ios::binary);
            int firstPointer = -1;//Final de la lista
            inFile.write((char *) &firstPointer, sizeof(int));
            inFile.close();
        }
    }

    int size() {
        int numRecords = 0;
        fstream inFile;
        inFile.open(this->fileName, ios::in | ios::binary);
        if (inFile.is_open()) {
            inFile.seekg(0, ios::end);
            long bytes = inFile.tellg();
            numRecords = (bytes - sizeof(int)) / sizeof(Record);
            inFile.close();
        } else cout << "Could not open the file.\n";
        return numRecords;
    }

};