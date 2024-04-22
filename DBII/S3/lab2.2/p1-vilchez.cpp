#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


struct Registro {
	string key;
};

const int BLOCK_FACTOR = 2;

struct DataPage {
	Registro registros[BLOCK_FACTOR];
	int n;
};

struct IndexPage {
	string keys[BLOCK_FACTOR];
	long pages[BLOCK_FACTOR + 1];
	int n;
};

long searchInIndex(string key, IndexPage& indexPage) {
	for (int i = 0; i < indexPage.n; ++i) {
		if (key <= indexPage.keys[i]) {
			return indexPage.pages[i];
		}
	}
	return indexPage.pages[indexPage.n];
}

vector<Registro> searchInData(string key, ifstream& dataFile, long pageOffset) {
	vector<Registro> result;
	DataPage dataPage;
	dataFile.seekg(pageOffset, ios::beg);
	dataFile.read(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
	for (int i = 0; i < dataPage.n; ++i) {
		if (dataPage.registros[i].key == key) {
			result.push_back(dataPage.registros[i]);
		}
	}
	return result;
}

void add(Registro registro, fstream& dataFile, IndexPage& index1, IndexPage& index2, IndexPage& index3) {
	// Buscar la posición de inserción en el index1
	int index1Pos = -1;
	for (int i = 0; i < index1.n; ++i) {
		if (registro.key <= index1.keys[i]) {
			index1Pos = i;
			break;
		}
	}
	if (index1Pos == -1) {
		index1Pos = index1.n;
	}

	if (index1.n < BLOCK_FACTOR) {
		// Hay espacio en la página de índice 1, insertar la clave y la dirección
		for (int i = index1.n; i > index1Pos; --i) {
			index1.keys[i] = index1.keys[i - 1];
			index1.pages[i + 1] = index1.pages[i];
		}
		index1.keys[index1Pos] = registro.key;
		index1.pages[index1Pos + 1] = index1.pages[index1Pos];
		index1.n++;
	} else {
		IndexPage newIndex1;
		newIndex1.n = index1.n / 2;
		index1.n -= newIndex1.n;
		for (int i = 0; i < newIndex1.n; ++i) {
			newIndex1.keys[i] = index1.keys[index1.n + i];
			newIndex1.pages[i + 1] = index1.pages[index1.n + i + 1];
		}
		if (index1Pos <= index1.n) {
			// Insertar en la página de índice 1
			add(registro, dataFile, newIndex1, index2, index3);
		} else {
			// Insertar en la página de índice 2
			add(registro, dataFile, index1, newIndex1, index3);
		}
	}
	long nextPage = searchInIndex(registro.key, index3);
	DataPage dataPage;
	dataFile.seekg(nextPage, ios::beg);
	dataFile.read(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
	if (dataPage.n < BLOCK_FACTOR) {
		// Hay espacio en la página de datos
		dataPage.registros[dataPage.n] = registro;
		dataPage.n++;
		dataFile.seekp(nextPage, ios::beg);
		dataFile.write(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
	} else {
		// Desbordamiento en la página de datos, crear una nueva página de datos y ajustar el enlace
		DataPage newDataPage;
		newDataPage.n = dataPage.n / 2;
		dataPage.n -= newDataPage.n;
		newDataPage.registros[0] = registro;
		newDataPage.n++;
		long newPageOffset = dataFile.tellp();
		dataFile.write(reinterpret_cast<char*>(&newDataPage), sizeof(DataPage));
		dataPage.registros[dataPage.n - 1].key = newDataPage.registros[0].key;
		dataPage.registros[dataPage.n - 1].n = newDataPage.registros[0].n;
		dataPage.registros[dataPage.n - 1].nextPage = newPageOffset;
		dataFile.seekp(nextPage, ios::beg);
		dataFile.write(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
	}
}

vector<Registro> search(string key, ifstream& dataFile, IndexPage& index1, IndexPage& index2, IndexPage& index3) {
	vector<Registro> result;
	long nextPage = searchInIndex(key, index1);
	if (nextPage == 0) {
		return result;
	}
	nextPage = searchInIndex(key, index2);
	if (nextPage == 0) {
		return result;
	}
	nextPage = searchInIndex(key, index3);
	if (nextPage == 0) {
		return result;
	}
	return searchInData(key, dataFile, nextPage);
}

vector<Registro> rangeSearch(string beginKey, string endKey, ifstream& dataFile, IndexPage& index1, IndexPage& index2, IndexPage& index3) {
	vector<Registro> result;

	long nextPage = searchInIndex(beginKey, index1);
	if (nextPage == 0) {
		return result;
	}

	long endPage = searchInIndex(endKey, index1);
	if (endPage == 0) {
		return result;
	}

	while (nextPage != endPage) {
		DataPage dataPage;
		dataFile.seekg(nextPage, ios::beg);
		dataFile.read(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
		for (int i = 0; i < dataPage.n; ++i) {
			if (dataPage.registros[i].key >= beginKey && dataPage.registros[i].key <= endKey) {
				result.push_back(dataPage.registros[i]);
			}
		}
		nextPage = dataPage.registros[dataPage.n - 1].nextPage;
	}

	DataPage dataPage;
	dataFile.seekg(endPage, ios::beg);
	dataFile.read(reinterpret_cast<char*>(&dataPage), sizeof(DataPage));
	for (int i = 0; i < dataPage.n; ++i) {
		if (dataPage.registros[i].key >= beginKey && dataPage.registros[i].key <= endKey) {
			result.push_back(dataPage.registros[i]);
		}
	}

	return result;
}