#include <vector>
#include <queue>
#include <cstring>
#include <fstream>

using namespace std;

#define MARCADO 1
#define DESMARCADO 0

typedef struct registro{
    int chave, idade;
    char nome[21];
}REG;

class MinHeapNode {
    public:
        // Construtor do nó
        MinHeapNode(REG r) {
            this->chave = r.chave;      // copia a chave 
            this->idade = r.idade;      // copia a idade
            strcpy(this->nome, r.nome); // copia o nome
            marcacao = DESMARCADO;      // seta como desmarcado
        }

        void changeMark() {
            marcacao = (marcacao)? DESMARCADO : MARCADO;
        }
        
        bool estaMarcado() {return this->marcacao;}
        
        bool operator > (const MinHeapNode& x) const {
            if (marcacao)
                return true;
            
            else
                return this->chave > x.chave;
        };
        bool operator < (const MinHeapNode& x) const {
            if (marcacao) {return false;}
            
            else {return this->chave < x.chave;}
        }

    public:
        int chave;
        int idade;
        char nome[21];

    private:
        bool marcacao; // Marcacao do nó
};

class comparaNo {
    public:
        bool operator() (const MinHeapNode& x, const MinHeapNode& y){
            return x > y;
        }
};

class MinHeap {

    public:
        void insere(REG r) {pq.push(MinHeapNode(r));}
        
        MinHeapNode trocaRaiz(REG r){
            
            MinHeapNode raiz = pq.top();
            MinHeapNode registroAtual = MinHeapNode(r);

            pq.pop();
            if (registroAtual < raiz){
                registroAtual.changeMark();
                pq.push(registroAtual);
            }
            else {
                pq.push(registroAtual);
            }
            
            return raiz;
        }
        bool estaoTodosMarcados(){

            priority_queue<MinHeapNode, vector<MinHeapNode>, comparaNo> temp = pq;    
           
            while(temp.empty() == false){
                MinHeapNode raiz = pq.top();
                if(!raiz.estaMarcado())
                    return false;

                temp.pop();
            }

        }

    private:
        priority_queue<MinHeapNode, vector<MinHeapNode>, comparaNo> pq;

};

int main() {

    ifstream in = ifstream("entrada100.dat");

    vector<REG> vet;

    while(!in.eof()) {
        REG r;
        in >> r.chave >> r.idade >> r.nome;
        vet.push_back(r);
    }
    
    priority_queue<MinHeapNode, vector<MinHeapNode>, comparaNo> pq;

   
    for(const REG& p: vet) {
        pq.push(MinHeapNode(p));
    } 
    
    priority_queue<MinHeapNode, vector<MinHeapNode>, comparaNo> pq1 = pq;

    while(pq1.empty() == false){
        MinHeapNode node = pq1.top();
        std::cout << node.chave << " " << node.idade << " " << node.nome << endl;
        pq1.pop();
    }

    REG t = {2, 20, "Otavio"};
    pq.push(MinHeapNode(t));
    cout << endl << "apos a insercaco da chave 2" << endl;
    while(pq.empty() == false){
        MinHeapNode node = pq.top();
        cout << node.chave << " " << node.idade << " " << node.nome << endl;
        pq.pop();
    }

}
