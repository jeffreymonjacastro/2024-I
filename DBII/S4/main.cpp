#include "HashFile.h"

using namespace std;

const int N_BUCKETS = 4;

void writeFile(string filename){
    StaticHashFile file(filename, N_BUCKETS);
    Record record;
    for (int i = 0; i < 15; i++)
    {
        record.setData();
        file.writeRecord(record);
    }   
}

void readFile(string filename){
    StaticHashFile file(filename, N_BUCKETS);
    cout<<"--------- show all data -----------\n";
    file.scanAll();
    cout<<"--------- search Pancho -----------\n";
    Record record = file.search("Pancho");
    record.showData();
}

int main(){
    writeFile("data.dat");
    readFile("data.dat");
    return 0;
}