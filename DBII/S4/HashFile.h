#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

const int MAX_B = 3;


struct Record {
    char nombre[30];
    char carrera[20];
    int ciclo = 0;

    void setData(ifstream &file) {
        file.getline(nombre, 30, ',');
        file.getline(carrera, 20, ',');
        file>>ciclo; 
        file.get();
    }

    void showData() {
        cout<<setw(5)<<right<<nombre;
        cout<<setw(5)<<right<<carrera;
        cout<<setw(5)<<right<<ciclo;
    }
};

struct Bucket{
    Record records[MAX_B];
    int size;
    long nextBucket;

    Bucket(){
        size = 0;
        nextBucket = -1;
    }

    void showData(){
        cout<<"[ ";

        for(int i = 0; i < size; i++){
            records[i].showData();
			cout << " | ";
		}

		cout << "next: " << nextBucket;

        cout<<" ]"<<endl;
    }
};

class StaticHashFile {
private:
    string filename;
    int nBuckets;

public:
    StaticHashFile(string filename, int N_BUCKETS){
        this->filename = filename;
        this->nBuckets = N_BUCKETS;
		ifstream file(filename, ios::in | ios::binary);

		file.seekg(0, ios::end);
		int size = file.tellg() / sizeof(Bucket);

		if(!size)
			writeBuckets();
    }

    size_t fhash(string nombre){
        hash<string> hasheado;
        return hasheado(nombre);
    }

    void writeBuckets(){
        fstream file(filename, ios::in | ios::out | ios::binary);
        Bucket newBucket;
		file.seekg(0, ios::beg);
        for (int i = 0; i < nBuckets; i++){
            file.write((char*) (&newBucket), sizeof(Bucket));
        }
        file.close();
    }

    void writeRecord(Record record){
        //1- usando una funcion hashing ubicar la pagina de datos
        long index = fhash(record.nombre) % nBuckets;
		//cout << fhash(record.nombre) << " % " << nBuckets << " = " << index << endl;

        //2- leer la pagina de datos,
        fstream file(filename, ios::in | ios::out | ios::binary);
        file.seekg(index * sizeof(Bucket), ios::beg);
        Bucket mainBucket;
        file.read((char*) &mainBucket, sizeof(Bucket));

		// a) Verificar si el mainBucket tiene un nextBucket
		while (mainBucket.nextBucket != -1){
			index = mainBucket.nextBucket;
			file.seekg(mainBucket.nextBucket * sizeof(Bucket), ios::beg);
			file.read((char*) &mainBucket, sizeof(Bucket));
		}

        //3- verificar si size < MAX_B, si es asi, se inserta en esa pagina y se regresa al archivo
        if(mainBucket.size < MAX_B){
            mainBucket.records[mainBucket.size++] = record;
            file.seekg(index * sizeof(Bucket), ios::beg);
            file.write((char*) &mainBucket, sizeof(Bucket));
        }
        //4- caso contrario, crear nuevo bucket, insertar ahi, mantener el enlace
        else {
			// Escribir un nuevo bucket al final del archivo y actualizar el nextBucket del mainBucket
			int pos;
			file.seekg(0, ios::end);
			pos = file.tellg() / sizeof(Bucket);
			mainBucket.nextBucket = pos;

			Bucket newBucket;
			newBucket.records[newBucket.size++] = record;
			file.write((char *) &newBucket, sizeof(Bucket));

			file.seekg(index * sizeof(Bucket), ios::beg);
			file.write((char *) &mainBucket, sizeof(Bucket));
		}

        file.close();
    }

    Record search(string nombre){
        //1- usando una funcion hashing ubicar la pagina de datos
		long index = fhash(nombre) % nBuckets;

        //2- leer la pagina de datos, ubicar el registro que coincida con el nombre
		fstream file(filename, ios::in | ios::binary);
		file.seekg(index * sizeof(Bucket), ios::beg);
		Bucket mainBucket;
		file.read((char*) &mainBucket, sizeof(Bucket));

		for (int i = 0; i < mainBucket.size; i++){
			if (mainBucket.records[i].nombre == nombre){
				return mainBucket.records[i];
			}
		}

		//3- si no se encuentra el registro en esa pagina, ir a la pagina enlazada iterativamente
		while(mainBucket.nextBucket != -1){
			file.seekg(mainBucket.nextBucket * sizeof(Bucket), ios::beg);
			file.read((char*) &mainBucket, sizeof(Bucket));

			for (int i = 0; i < mainBucket.size; i++){
				if (mainBucket.records[i].nombre == nombre){
					return mainBucket.records[i];
				}
			}
		}

        return Record();
    }

    void scanAll(){
        //1- abrir el archivo de datos y mostrar todo
        fstream file(filename, ios::in | ios::binary);
        file.seekg(0, ios::beg);
        Bucket bucket;

		int i = 0;
        while (file.read((char*) &bucket, sizeof(Bucket))){
            cout << i++ << ": ";
			bucket.showData();
        }
        file.close();
    }
};

