#include <iostream>

using namespace std;

struct tNo{
  int info;
  tNo* proximo;
};

tNo* criaNo(int item){
  tNo* no = new tNo;

  no -> info = item;
  no -> proximo = NULL;

  return no;
}

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho;
};

void inicializaLista(tLista* pLista){
  pLista -> primeiro  = NULL;
  pLista -> ultimo = NULL;
  pLista -> marcador = NULL;
  pLista -> tamanho = 0;
}

int obterTamanho(tLista* pLista){
  return pLista -> tamanho;
}

bool listaVazia(tLista* pLista){
  return (pLista -> tamanho == 0);
}

bool finalLista(tLista* pLista){
  return (pLista -> marcador == NULL);
}

void incluirNoFim(tLista* pLista, int info){
  tNo* no;
  no = criaNo(info);

  if(listaVazia(pLista)){
    pLista -> primeiro = no;
  }else{
    pLista -> ultimo -> proximo = no;
  }

  pLista -> ultimo = no;
  pLista -> marcador = no;
  pLista -> tamanho++;
}

void imprimirLista (tLista* pLista){
  pLista -> marcador = pLista -> primeiro;

  while(!finalLista(pLista)){
    int informacao = pLista -> marcador -> info;
    cout<<"A informacao eh : " << informacao << endl;

    pLista -> marcador = pLista -> marcador -> proximo;
  }
}

void excluirPosicao(tLista* pLista, int pos){
  tNo* anterior;
  tNo* aux;
  tNo* apagado;

  if(!listaVazia(pLista)){
    pLista -> marcador = pLista -> primeiro;

    if(pos < obterTamanho(pLista)){
      if(pos == 0){
        pLista -> primeiro = pLista -> marcador -> proximo;
      }else{
        for(int i = 0; i<pos; i++){
          anterior = pLista -> marcador;
          pLista -> marcador = pLista -> marcador -> proximo;

          aux = pLista -> marcador -> proximo;
        }
        anterior -> proximo = aux;
      }
      apagado = pLista -> marcador;
      free(apagado);
    }
  }
}


int main()
{
  
  tLista* idades = new tLista;

  inicializaLista(idades);

  cout << "\nO tamanho da lista eh: "<< obterTamanho(idades)<<endl;

  int idadeJoao = 10;
  int idadeMaria = 20;
  int idadeJose = 20;

  incluirNoFim(idades, idadeJoao);
  incluirNoFim(idades, idadeMaria);
  incluirNoFim(idades, idadeJose);

  cout<<"O tamanho da lista eh: " << obterTamanho(idades) << endl;
  cout<<"\nInfo do ultimo elemento da lista: " <<idades -> ultimo -> info << endl<< endl;

  imprimirLista(idades);

  incluirNoFim(idades, 50);

  cout <<"\nImprimindo apos outra edicao: "<< endl;
  imprimirLista(idades);

  excluirPosicao(idades, 2);

  cout<<"\nImprimindo apos a remocao: "<< endl;
  imprimirLista(idades);



  cout<<endl<<endl;
  return 0;
}