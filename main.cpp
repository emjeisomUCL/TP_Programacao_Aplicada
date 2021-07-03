#include <iostream>
#include <math.h>

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

void leituraNumComplexo(Complexo *numComplex){
  cout<<"Componente real: ";
  cin>> numComplex -> real;
  cout<<"Componente imaginária: ";
  cin>> numComplex -> imag;
  cout<<endl;
}

void imprimeNumComplexo(Complexo *numComplex, char op){
  if(op == '|'){
    cout<<"\n"<< numComplex -> real;
  }else{
    if(numComplex -> imag < 0){
      cout<<"\n"<< numComplex -> real <<" - "<< numComplex -> imag * -1<<"j"<<endl;
    }else{
      cout<<"\n"<< numComplex -> real <<" + "<< numComplex -> imag<<"j"<<endl;
    }
  }
}

struct Complexo* adicaoComplexos(Complexo *numComplexA, Complexo *numComplexB){
  struct Complexo *numComplex = (struct Complexo*) malloc (sizeof(struct Complexo));
  numComplex -> real = numComplexA -> real + numComplexB -> real;
  numComplex -> imag = numComplexA -> imag + numComplexB -> imag;
  return numComplex;
}

struct Complexo* subtracaoComplexos(Complexo *numComplexA, Complexo *numComplexB){
  struct Complexo *numComplex = (struct Complexo*) malloc (sizeof(struct Complexo));
  numComplex -> real = numComplexA -> real - numComplexB -> real;
  numComplex -> imag = numComplexA -> imag - numComplexB -> imag;
  return numComplex;
}

// Operacao de Multiplicacao
// Para operações de Multiplicacao e Divisao foi usado como referencia o material do site https://www.todamateria.com.br/numeros-complexos/
struct Complexo* multiplicacaoComplexos(Complexo *numComplexA, Complexo *numComplexB){
  struct Complexo *numComplex = (struct Complexo*) malloc (sizeof(struct Complexo));
  numComplex -> real = numComplexA -> real * numComplexB -> real - numComplexA -> imag * numComplexB -> imag;
  numComplex -> imag = numComplexA -> real * numComplexB -> imag + numComplexA -> imag * numComplexB -> real;
  return numComplex;
}

// Operacao de Multiplicacao
// Para operações de Multiplicacao e Divisao foi usado como referencia o material do site https://www.todamateria.com.br/numeros-complexos/
struct Complexo* divisaoComplexos(Complexo *numComplexA, Complexo *numComplexB){
  struct Complexo *numComplex = (struct Complexo*) malloc (sizeof(struct Complexo));

  if(numComplexB -> real == 0 && numComplexB -> imag == 0){
    numComplex->real = 0;
    numComplex->imag = 0;
    return numComplex;
  }else{
    numComplex -> real = (numComplexA -> real * numComplexB -> real + numComplexA -> imag * numComplexB -> imag) / (pow(numComplexB -> real,2) + pow(numComplexB -> imag,2));
    numComplex -> imag = (numComplexB -> real * numComplexA -> imag - numComplexB -> imag * numComplexA -> real) / (pow(numComplexB -> real,2) + pow(numComplexB -> imag,2));
    return numComplex;
  }
}

struct Complexo* moduloComplexo(Complexo *numComplexA){
  struct Complexo *numComplex = (struct Complexo*) malloc (sizeof(struct Complexo));
  numComplex -> real = sqrt( pow(numComplexA -> real,2) + pow(numComplexA -> imag,2) );
  return numComplex;
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
      cout<<"\n"<< informacao.real <<" - "<< informacao.imag * -1<<"j"<<endl;
    }else{
      cout<<"\n"<< informacao.real <<" + "<< informacao.imag <<"j"<<endl;
    }
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
  
  Complexo numA, numB, *resultado;
  char op = ' ';

  tLista* complexos = new tLista;

  inicializaLista(complexos);

  cout << "\nO tamanho da lista é: "<< obterTamanho(complexos)<<endl;

  leituraNumComplexo(&numA);
  leituraNumComplexo(&numB);

  incluirNoFim(complexos, numA);
  incluirNoFim(complexos, numB);

  cout << "\nO tamanho da lista é: "<< obterTamanho(complexos)<<endl;
  //cout<<"\nInfo do ultimo elemento da lista: " <<complexos -> ultimo -> info << endl<< endl;

  /*
  // Menu de operacao. 
  cout<< "Informe o caractere da operação que deseja realizar ou digite (s) para sair...." <<endl;
  cout<< "\t + p/ Adicao" <<endl;
  cout<< "\t - p/ Subtracao" <<endl;
  cout<< "\t * p/ Multiplicacao" <<endl;
  cout<< "\t / p/ Divisao" <<endl;
  cout<< "\t | p/ Modulo" <<endl;
  cout<< "\t Operacao: ";
  cin>>op;
  cout<<endl;

  //Operaçoes iram ocorrer quantas vezes o usuario quiser, entao sera feito um laco de repeticao
  while(op != 's' && op != 'S'){

    if(op != '|'){
      leituraNumComplexo(&numA);
      leituraNumComplexo(&numB);
    }else{
      leituraNumComplexo(&numA);
    }

    switch(op){
      case '+':
        resultado = adicaoComplexos(&numA, &numB);
        imprimeNumComplexo(resultado, op);
      break;
      case '-':
        resultado = subtracaoComplexos(&numA, &numB);
        imprimeNumComplexo(resultado, op);
      break;
      case '*':
        resultado = multiplicacaoComplexos(&numA, &numB);
        imprimeNumComplexo(resultado, op);
      break;
      case '/':
        resultado = divisaoComplexos(&numA, &numB);
        imprimeNumComplexo(resultado, op);
      break;
      case '|':
        resultado = moduloComplexo(&numA);
        imprimeNumComplexo(resultado, op);
      break;
      default:
        cout<< REDB <<"OPCAO INVALIDA" << NC ;
      break;
    }

    cout<< "\n\nInforme o caractere da operação que deseja realizar ou digite (s) para sair...." <<endl;
    cout<< "\t + p/ Adicao" <<endl;
    cout<< "\t - p/ Subtracao" <<endl;
    cout<< "\t * p/ Multiplicacao" <<endl;
    cout<< "\t / p/ Divisao" <<endl;
    cout<< "\t | p/ Modulo" <<endl;
    cout<< "\t Operacao: ";
    cin>>op;
    cout<<endl;
  }

  cout<< GRN <<"\n\nFIM DA OPERACAO" << NC ;

  */


  cout<<endl<<endl;
  return 0;
}