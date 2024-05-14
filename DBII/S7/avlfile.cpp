#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

struct Record{
    int cod;
	char nombre[12];
	int ciclo;
	
	long left = -1, right = -1;
	

	int height = 0;

	void setData() {
        cout << "Codigo:";
        cin >> cod;
        cout << "Nombre:";
        cin >> nombre;
        cout << "Ciclo:";
        cin >> ciclo;
        cout<<endl;
    }

    void showData() {
        cout << "\nCodigo: " << cod;
        cout << "\nNombre: " << nombre;
        cout << "\nCiclo : " << ciclo;
        cout << "\nleft : " << left;
        cout << "\nright : " << right;
		cout << "\nheight : " << height;
        cout<<endl;

    }   
};


class AVLFile
{
private:
    string filename;
    long pos_root;
    
    bool filexist(string f){
        ifstream file(f);

        bool ans = file.good();

        file.close();    

        return ans;
    }

public:
    AVLFile(string filename){
		this->filename = filename;
        if( filexist(filename)){
            cout<<"El archivo ya existe"<<endl;
            long pos;
            fstream file(filename , ios::in | ios::out | ios::binary);
            file.seekg(0 , ios::beg);
            file.read((char*)&pos , sizeof(Record));
            file.close();

            this->pos_root = pos;
        }
        else{
            cout<<"Creando nuevo archivo"<<endl;
            ofstream file(filename , ios::binary);
            this->pos_root = -1;
            file.write((char*)&pos_root , sizeof(Record));
            file.close();
        }
	}
	
    Record find(int key){
        fstream file(filename , ios::in | ios::out | ios::binary);
		Record ans =  find(pos_root, key , file);
        file.close();
        return ans;
	}
	
	void insert(Record& record){
        fstream file(filename , ios::in | ios::out | ios::binary);
		insert(pos_root, record , file);
        file.close();
	}

    void remove(int key){
        fstream file(filename , ios::in | ios::out | ios::binary);
		remove(pos_root, -1 ,key , file);
        file.close();
    }
	
    vector<Record> inorder(){
        
		fstream file(filename , ios::in | ios::out | ios::binary);
        vector<Record> ans;
        inorder(pos_root , ans , file);
        file.close();
        return ans;
	}

    vector<Record> rangeSearch(int begin , int end){
        fstream file(filename , ios::in | ios::out | ios::binary);
        vector<Record> ans;
        rangeSearch(this->pos_root , begin , end , ans , file);
        file.close();
        return ans;
    }

private:
    
    Record read_record(long pos , fstream& file){
        if(pos <= 0 ) return Record{};
 
        file.seekg(pos*sizeof(Record) , ios::beg);
        Record r{};
        file.read( (char*)&r ,  sizeof(Record));
        return r;
    }

	void write_record(long pos, Record r, fstream& file ){
		if( pos <= 0) return;
        
        file.seekg(pos*sizeof(Record) , ios::beg);

		file.write((char*)&r , sizeof(Record) );
	}


    long fmin(long pos_node , fstream& file){
        if( pos_node == -1) return -1;

        Record node = read_record(pos_node , file);

        if( node.left != -1){
            return fmin(node.left , file);
        }
        else{
            return pos_node;
        }

    }

	Record find(long pos_node, int key , fstream& file){
	
        if( pos_node  == -1){
            return Record{};
        }
        Record node = read_record(pos_node , file);

        if( key < node.cod	){
            return find(node.left , key , file);
        }

        else if(key > node.cod){
            return find(node.right , key , file);
        }

        else{
            return node;
        }
	}



	void insert(long pos_node, Record record, fstream& file){
	
        // arbol vacio
        if( pos_node == -1){
            this->pos_root = 1;
            file.seekg(0 , ios::beg);
            file.write((char*)&pos_root , sizeof(Record));
            file.write((char*)& record , sizeof(Record));
			UpdateHight(pos_node , file);
            return;
        }
        // arbol no vacio
        Record node = read_record(pos_node , file);

        //node.showData();

        //cout<<endl;

        if( record.cod < node.cod){
            
            if(node.left == -1){
                //insertamos al final del archivo
            
                file.seekg( 0 , ios::end);
                long posLeftChildNode = file.tellp()/sizeof(Record);
                //cout<<"Posicion donde se inserta (izquierda): "<<posLeftChildNode<<endl; 
                file.write((char*)&record , sizeof(Record));
                node.left = posLeftChildNode;
                file.seekg( sizeof(Record)*pos_node, ios::beg);
                file.write((char*)&node , sizeof(node));
                //UpdateHight(pos_node , file);
            
            }
            else{
                insert( node.left , record , file);
            }
        }
        else if ( record.cod > node.cod){
            if( node.right == -1){
                //insertamos al final del archivo
                file.seekg( 0 , ios::end);
                long posRightChildNode = file.tellp()/sizeof(Record);
                //cout<<"Posicion donde se inserta (derecha): "<<posRightChildNode<<endl; 
                file.write((char*)&record , sizeof(Record));
                node.right = posRightChildNode;
                file.seekg( sizeof(Record)*pos_node, ios::beg);
                file.write((char*)&node , sizeof(node));
                //UpdateHight(pos_node , file);
            }
            else{
                insert(node.right , record , file);
            }
        }

		balance(pos_node , file);
	}

    void remove(long pos_node, long pos_parent , int key , fstream& file ){
            if(pos_node == -1) return;

            Record node = read_record(pos_node , file);

            if( key < node.cod){
                remove(node.left , pos_node , key , file);
            }
            else if( key > node.cod){
                remove(node.right , pos_node , key , file);

            }
            else{
                if( node.left == -1 && node.right == -1){
                    if( pos_parent == -1){
                        this->pos_root = -1;
                        file.seekg(0 , ios::beg);
                        file.write((char*)&pos_root , sizeof(Record)  );
                        return;
                    }

                    Record parent_node = read_record(pos_parent , file);

                    if( parent_node.left == pos_node) parent_node.left = -1;
                    else if( parent_node.right == pos_node) parent_node.right = -1;
                    else{
                        cout<<"Esto no es posible"<<endl;
                    }

                    write_record(pos_parent , parent_node , file);

                    return;

                }

                if( node.left == -1){
                    long pos = node.right;

                    if( pos_parent == -1){
                        Record r = read_record( pos , file );
                        file.write((char*)&r , sizeof(Record));
                        return;
                    }

                    Record parent_node = read_record(pos_parent , file);

                    if( parent_node.left == pos_node) parent_node.left = pos;
                    else if (parent_node.right == pos_node) parent_node.right = pos;
                    else{
                        cout<<"Esto no es posible"<<endl;
                    }

                    write_record(pos_parent , parent_node , file);

                    return;
                }

                if( node.right == -1){
                    long pos = node.left;


                    if( pos_parent == -1){
                        Record r = read_record( pos , file );
                        file.write((char*)&r , sizeof(Record));
                        return;
                    }

                    Record parent_node = read_record(pos_parent , file);

                    if( parent_node.left == pos_node) parent_node.left = pos;
                    else if (parent_node.right == pos_node) parent_node.right = pos;
                    else{
                        cout<<"Esto no es posible"<<endl;
                    }

                    write_record(pos_parent , parent_node , file);

                    return;
                }

                long pos_sucesor = fmin(node.right , file);

                Record sucesor = read_record(pos_sucesor , file);

                swap(sucesor.nombre , node.nombre);
                swap(sucesor.ciclo , node.ciclo);
                swap(sucesor.cod , node.cod);

                write_record(pos_sucesor , sucesor , file);
                write_record(pos_node , node , file);

                remove(node.right , pos_node , key , file);
            }

            balance(pos_node , file);

    }
	
	void inorder(long pos_node, vector<Record> &result , fstream& file){
	
        if( pos_node == -1){
            return;
        }
        Record node = read_record(pos_node , file);

        inorder(node.left , result , file);    
        result.push_back(node);
        inorder(node.right , result , file);
    }

    void rangeSearch( long pos_node ,int begin , int end , vector<Record>& ans , fstream& file ){
            if( pos_node == -1) return;

            Record node = read_record(pos_node , file);

            if( node.cod >=  begin){
                rangeSearch(node.left , begin , end , ans , file);
            }


            if( node.cod >= begin && node.cod <= end){
                ans.push_back(node);
            }

            if( node.cod <= end){
                rangeSearch(node.right , begin , end , ans , file);
            }


    }

	long height( long pos_node , fstream& file){
		if( pos_node == -1){
			return -1;
		}

		Record node = read_record(pos_node , file);

		return node.height;
	}

	long balancingFactor(long pos_node , fstream& file){
		if( pos_node == -1) return 0;

		Record r = read_record(pos_node , file);

		return height(r.left , file) - height(r.right , file); 
	}

	void UpdateHight(long pos_node , fstream& file){
		if( pos_node == -1 ) return;

		Record r = read_record(pos_node , file);
		int left = height(r.left , file) , right = height(r.right , file);


		r.height = 1 + max(left,right);

		write_record(pos_node , r , file);
		
	}

    void balance(long pos_node , fstream& file){
            if( pos_node == -1 ) return;
        
            long factor = balancingFactor(pos_node , file);

            cout<<"Factor de balanceo para el nodo: "<<pos_node<<" es: "<<factor<<endl;

            if( factor > 1){
                    left_rota(pos_node , file);
            }
            else if( factor < -1){
                    right_rota(pos_node , file);
            }
            
            UpdateHight(pos_node , file);
            
    }

    void left_rota(long pos_node , fstream& file){
        if( pos_node == -1) return;

        Record r = read_record(pos_node , file);
        if(balancingFactor(r.left , file) >= 0){
            //ll
            LL(pos_node , file);
        }
        else{
            //lr

            //rr
            RR(r.left , file);
            //ll
            LL(pos_node , file);
        }
    }


    
    void right_rota(long pos_node , fstream& file){
        if( pos_node == -1) return;
        Record r = read_record(pos_node , file);
        if(balancingFactor(r.right , file) < 0){
            RR(pos_node , file);
        }
        else{
            //rl

            //ll
            LL(r.right , file);
            //rr
            RR(pos_node , file);
        }
    }

    void LL(long pos_node , fstream& file){

        if( pos_node == -1) return;

        Record n1 = read_record(pos_node , file);
        long pos_n2 = n1.left;
        Record n2 = read_record(pos_n2 , file);
        long temp = n2.right;
        n2.right = pos_n2;
        n1.left = temp;


        //swap(n1.height , n2.height);

        //cout<<"n1: "<<pos_node<<endl;
        //n1.showData();
        //cout<<endl;
        //cout<<"n2: "<<pos_n2<<endl;
        //n2.showData();

        write_record(pos_node , n2 , file);
        write_record(pos_n2 , n1 , file);


        UpdateHight(pos_node , file);
        UpdateHight(pos_n2 , file);
    }

    void RR(long pos_node , fstream& file){
        if( pos_node == -1) return;

        Record n1 = read_record(pos_node , file);
        long pos_n2 = n1.right;
        Record n2 = read_record(pos_n2 , file);
        long temp = n2.left;
        n2.left = pos_n2;
        n1.right = temp;

        write_record(pos_node , n2 , file);
        write_record(pos_n2 , n1 , file);

        UpdateHight(pos_node , file);
        UpdateHight(pos_n2 , file);
    }

};


void writeFile(string filename){
    AVLFile file(filename);
    Record record;
    for (int i = 0; i < 6; i++)
    {
        record.setData();
        file.insert(record);
    }   
}

void readFile(string filename){
    /*
    fstream file(filename , ios::binary | ios::in | ios::out);
    long pos_root;
    file.seekg(0 , ios::beg);
    file.read((char*)&pos_root , sizeof(Record));
    cout<<pos_root<<endl;
    file.seekg(pos_root*sizeof(Record) , ios::beg);
    Record r;
    file.read( (char*)&r , sizeof(Record));

    r.showData();
    */
    
    
    
    
    
    
    AVLFile file(filename);       
    cout<<"--------- show all sorted data -----------\n";
	vector<Record> result = file.inorder();
	for(Record re : result){
		re.showData();
	} 
    
    
    
    
    

    
    /*
    fstream file(filename , ios::in | ios::out | ios::binary);
    Record re;
    file.seekg( sizeof(long), ios::beg);
    while(file.read((char*)&re , sizeof(re))){
        re.showData();
    } 
    
    */
    
}

void remove_test(string filename){
    AVLFile file(filename);
    file.remove(5);

    vector<Record> result  = file.inorder();

    for(Record re : result){
		re.showData();
	} 
}

int main(){

    //writeFile("data.dat");
    //readFile("data.dat");
    //remove_test("data.dat");
    return 0;
}