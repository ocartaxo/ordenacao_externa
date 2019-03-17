#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

#define MAXMEM 512*1024*1024
#define MAXNARQS 100
typedef priority_queue<MinHeapNode, vector<MinHeapNode>, greater<MinHeapNode>> MinHeap;

#define ENTRADA "entrada.dat"
#define SAIDA "saida.dat"


bool estaoTodasMarcadas(MinHeap pq) {
    while(pq.empty() == false) {
        MinHeapNode raiz = pq.top();
        if (!raiz.estaMarcado())
            return false;
    }

    return true;

}

void juntaArquivos() {}

void escreveNoProximoArquivo(int proxArq, MinHeap& pq) {
    
    string s = to_string(proxArq);
    fstream arq(s.c_str(), ios::out);

    while(pq.empty() == false) {
        MinHeapNode mhn = pq.top();
        cout << "Estou escrevendo " << mhn.chave << " " << mhn.idade << " " << mhn.nome << " no arquivo " << proxArq <<  endl;
        arq << mhn.chave << " " << mhn.idade << " " << mhn.nome << endl;
        pq.pop();
    }

    arq.close();

}

void criaArquivosOrdenados() {

    ifstream entrada(ENTRADA);
    MinHeap pq;

    int maxReg = MAXMEM/sizeof(MinHeapNode);
    int nomeProximaArq = 1;
    int ini = nomeProximaArq;

    entrada.sync();

    // Lê a quantidade máxima de regitros que cabem na memória, e ordena
    for (int i = 0; i < maxReg; i++) {
        
            REG r = {0, 0, ""}; // Registro temporário
            entrada >>  r.chave >> r.idade >> r.nome;
            
            pq.push(MinHeapNode(r)); // adiciona ao heap
            
            MinHeapNode raiz = pq.top();

            if (entrada.peek() == EOF)
                break;

    }

    // Lê o arqquivo de entrada e joga nos arquivos de saída
    while(entrada.peek() != EOF){
        
        // abre a próxima run
        string s = to_string(nomeProximaArq);
        fstream proxArq(s.c_str(), ios::out);

        REG r;
        entrada >> r.chave >> r.idade >> r.nome;    // lê o proximo registro
        MinHeapNode proxReg = MinHeapNode(r);       // converte para MinHeapNode
        MinHeapNode raiz = pq.top();                // pega a raiz para comparar

        // Verifica se precisa marcar o registro que está sendo escrito
        if (proxReg < raiz){
            proxReg.mudaMarcacao(); // marca o próximo registro
            pq.pop();               // remove a raiz
            pq.push(proxReg);       // adiciona o próximo registro

            cout << "Marquei o registro" << proxReg.chave << endl;

        } else {
            pq.pop();
            pq.push(proxReg);
        }

        // Escreve a raiz no arquivo de saída
        proxArq << raiz.chave << " " << r.idade << " " << r.nome << endl;

        // Se todos os nós estiverem marcados, fecha o arquivo atual, e escreve no próximo arquivo
        if(estaoTodasMarcadas(pq)){
           
            nomeProximaArq++; // incrementa o nome da próximo arquivo
            proxArq.close(); // fecha o arquivo
            delete &proxArq; // libera a memória

             cout << "Todos os nos estao marcados, vou inseir no proximo arquivo" << endl;

            // Escreve os registros da memória no próximo arquivo
            escreveNoProximoArquivo(nomeProximaArq, pq);

        }

    }

    cout << "Terminei de ler da entrada" << endl;

    entrada.close();

    escreveNoProximoArquivo(nomeProximaArq, pq);


}

int main() {

    criaArquivosOrdenados();

} 