#ifndef MINHEAP
#define MINHEAP

// Inclui os .h
#include <queue>
#include <vector>

// pega o template
using std::vector;
using std::priority_queue;

// Marcacao do nó
#define MARCADO 1
#define DESMARCADO 0

// Estrutura usada para ler do arquivo
struct REG {
    int chave, idade;
    char nome[21];
};


// Abstração do nó no heap mínimo
class MinHeapNode {
    // Valores no heap mínimo
    public:
        int chave;
        int idade;
        char nome[21];
    
    
    public:
        // Construtor
        MinHeapNode(REG r);
        // Muda a marcacao do nó
        void mudaMarcacao();
        // Rertorna a marcaçãod o nó
        bool estaMarcado();

        // Comparação entre dois nós do heap mínimo
        bool operator >(const MinHeapNode &x) const;

        bool operator <(const MinHeapNode &x) const;

    // marcacao do nó
    private:
        bool marcacao;
    
};


// Comparador de dois nós no heap mínimo
class ComparaNo {
    public:
        bool operator () (const MinHeapNode &x, const MinHeapNode &y) const;
};

#endif // MINHEAP