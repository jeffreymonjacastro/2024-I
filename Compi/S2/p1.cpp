#include<iostream>
using namespace std;

const int q0=0;
const int q1=1;
const int q2=2;
const int q3=3;
const int q4=4;
const int q5=5;

class Scanner1 {
public:
    string source;
    int current;
    char c;
    Scanner1(string source) {
        this->source = source;
        current = 0;
        c = source[current];
    }
    bool reconocer();
};

bool Scanner1::reconocer() {
    int state = q0;
    c = source[current];
    while(c != '\0'){
        if (state == q0){
            if (c == '0'){
                state = q1;
                c = source[++current];
            }else if(c == '1'){
                state = q2;
                c = source[++current];
            }
        }else if(state == q1){
            if (c == '0'){
                state = q5;
                c = source[++current];
            }else if(c == '1'){
                state = q5;
                c = source[++current];
            }
        }else if(state == q2){
            if (c == '0'){
                state = q3;
                c = source[++current];
            }else if(c == '1'){
                state = q5;
                c = source[++current];
            }
        }else if(state == q3){
            if (c == '0'){
                state = q5;
                c = source[++current];
            }else if(c == '1'){
                state = q4;
                c = source[++current];
            }
        }else if(state == q4){
            if (c == '0'){
                state = q3;
                c = source[++current];
            }else if(c == '1'){
                state = q5;
                c = source[++current];
            }
        }else if(state == q5){
            if (c == '0'){
                state = q5;
                c = source[++current];
            }else if(c == '1'){
                state = q5;
                c = source[++current];
            }
        }
    }
    if(state == q1 || state == q1 || state == q3){
        return true;
    }else{
        return false;
    }
}


int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cout << "Error: Debe ingresar un archivo de entrada" << std::endl;
        return 1;
    }
    string input = argv[1];

    Scanner1 scanner(input);
    if (scanner.reconocer()) {
        std::cout << "Cadena reconocida" << std::endl;
    } else {
        std::cout << "Cadena no reconocida" << std::endl;
    }
    return 0;
}
