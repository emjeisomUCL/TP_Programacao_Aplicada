#include <iostream>
#include <fstream>

using namespace std;

#define REDB "\e[41m"
#define GRN "\e[0;32m"
#define NC "\e[0m"

struct Complexo{
  double real;
  double imag;
};

void inicializaNumComplexo(Complexo *numComplex){
  numComplex->real = 0;
  numComplex->imag = 0;
}

void leituraNumComplexo(Complexo *numComplex, int index){
  cout<<index<<"° Componente real: ";
  cin>> numComplex -> real;
  cout<<index<<"° Componente imaginária: ";
  cin>> numComplex -> imag;
  cout<<endl;
}

/////////////////////// LISTA ///////////////////////

struct tNo{
  struct Complexo info;
  tNo* proximo;
};

tNo* criaNo(Complexo item){
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

void incluirNoFim(tLista* pLista, Complexo info){
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
    Complexo informacao = pLista -> marcador -> info;
    //cout<<"O numero comple : " << informacao.real <<" "<< informacao.imag<<"j"<<endl;
    if(informacao.imag < 0){
      cout<<""<< informacao.real <<" - "<< informacao.imag * -1<<"j"<<endl;
    }else{
      cout<<""<< informacao.real <<" + "<< informacao.imag <<"j"<<endl;
    }
    pLista -> marcador = pLista -> marcador -> proximo;
  }
}

void inluirNoArquivo(tLista* pLista, int index){
  pLista -> marcador = pLista -> primeiro;

  ofstream listaComplexos;

  listaComplexos.open ("lComplexosSaida.txt", ios::app);
  
  listaComplexos<<index<<" ª lista \n";

  while(!finalLista(pLista)){
    Complexo informacao = pLista -> marcador -> info;
    //cout<<"O numero comple : " << informacao.real <<" "<< informacao.imag<<"j"<<endl;
    if(informacao.imag < 0){
      listaComplexos<<""<< informacao.real <<" - "<< informacao.imag * -1<<"j"<<endl;
    }else{
      listaComplexos<<""<< informacao.real <<" + "<< informacao.imag <<"j"<<endl;
    }
    pLista -> marcador = pLista -> marcador -> proximo;
  }
  listaComplexos.close();
  cout<<endl;
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
  
  Complexo numComplex;
  tLista* complexos = new tLista;
  int qtd = 0, index = 0;
  char op = ' ';

    cout<< "\nInforme se ira gravar (g) ou ler (l) o banco de dados. \nPara sair digite (s)...";
    cout<<"\nOpcao: ";
    cin>>op;

  while(op != 's' && op != 'S'){

    inicializaLista(complexos);

    switch(op){

      case 'g': case 'G':
        cout<< "\nQuantidade de numeros que serao gravados: ";
        cin>>qtd;
        for(int i = 1; i <= qtd ; i++){
          leituraNumComplexo(&numComplex, i);
          incluirNoFim(complexos, numComplex);
        }
        cout << "\nO tamanho da lista é: "<< GRN << obterTamanho(complexos)<< NC <<endl;
        imprimirLista (complexos);
        index++;
      break;
      default:
        cout<< REDB <<"\nOpcao invalida!!!"<< NC <<endl;
      break;
    }


    inluirNoArquivo(complexos, index);



    cout<< "\nInforme se ira gravar(g) ou ler(l) o banco de dados. \nPara sair digite (s)...";
    cout<<"\nOpcao: ";
    cin>>op;
  }

  

  cout<< GRN <<"\nFIM DA APLICACAO!"<< NC <<endl;
  cout<<endl<<endl;
  return 0;

}