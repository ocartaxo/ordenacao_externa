#include "heap.h"
#include <cstring>


MinHeapNode::MinHeapNode(REG r) {
    chave = r.chave;
    idade = r.idade;
    marcacao = false;
    strcpy(nome, r.nome);
}

void MinHeapNode::mudaMarcacao(){
    marcacao = (marcacao)? DESMARCADO : MARCADO;
};

bool MinHeapNode::estaMarcado(){
    return marcacao;
}

bool MinHeapNode::operator >(const MinHeapNode& x) const {

    if(marcacao) {return true;}

    return chave > x.chave;
}

bool MinHeapNode::operator <(const MinHeapNode& x) const {
    if (marcacao) {return false;}

    return chave < x.chave;
}


bool ComparaNo:: operator () (const MinHeapNode& x, const MinHeapNode& y) const {
    return x > y ;
}