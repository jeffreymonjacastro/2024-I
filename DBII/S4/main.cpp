#include "HashFile.h"

using namespace std;

const int N_BUCKETS = 4;

void writeFile(string filename){
	// Clean file
	ofstream file2(filename, ios::binary);
	file2.close();

    StaticHashFile file(filename, N_BUCKETS);
    Record record;
    ifstream fileIn("muchosdatos.txt", ios::in);
	if (!fileIn.is_open()) exit(1);

	cout << "-----------Writing file-----------" << endl;

    while(true)
    {
        record.setData(fileIn);
        if(fileIn.eof()) break;
        record.showData();
		cout << endl;
        file.writeRecord(record);
    }   
    fileIn.close();
}

void readFile(string filename){
    StaticHashFile file(filename, N_BUCKETS);
    cout<<"--------- show all data -----------\n";
    file.scanAll();
	cout<<"--------- search Natalia -----------\n";
	Record record = file.search("Natalia");

	if (record.nombre[0] != '\0'){
		record.showData();
		cout << endl;
	} else
		cout << "Record not found" << endl;

	cout<<"--------- search Pancho -----------\n";
	record = file.search("Pancho");

	if (record.nombre[0] != '\0')
		record.showData();
	else
		cout << "Record not found" << endl;
}

int main(){
    writeFile("data1.dat");
    readFile("data1.dat");
    return 0;
}