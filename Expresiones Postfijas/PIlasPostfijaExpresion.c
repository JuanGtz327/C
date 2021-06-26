#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct nodo{
	/*Atributos*/
	//int valor;
	double expresion;
	struct nodo *sig;
}Nodo;

typedef struct pila{
	int size;
	Nodo *Tope;
}Pila;

void push(Pila *,Nodo *);
Nodo* pop(Pila *);
Nodo* popInicios(Pila *);
int isEmpty(Pila *);
void initialize(Pila *);
void printStack(Pila *);
void copyNodo(Nodo *, Nodo *);
int menu();
void copyString(char *, char *);
int sizeString(char *);
void clean_stdin();
void Valida(char* c);
int Precedencia(char a);
double ANumero(char a);

/*
EN EL FINAL DE LA PRACTICA ESTA ES METODO A NUMERO, EL CUAL SE ENCARGA DE CONVERTIR CADA LETRA A
SU CORRESPONDIENTE NUMERO EN ESTE CASO:

A------------------  3
B------------------  8
C------------------  4
D------------------  9
E------------------  2
F------------------  4
G------------------  7

*/

int main(){
	int opcion;
	Pila pila;
	Nodo nodo, *aux, *aux2;
	char *CadenaAuxiliar;
	CadenaAuxiliar = malloc(255);
	initialize(&pila);
		printf("**PROGRAMA 2 EVALUACION EXPRESION POSTFIJA**\n");
		printf("*****BY JUAN CARLOS SARMIENTO GUTIERREZ****\n");
		printf("********************************************\n");
		printf("Ingresa la expresion en minusculas a evaluar\n");
        printf("********************************************\n");
		scanf("%[^\n]",CadenaAuxiliar);
		Valida(CadenaAuxiliar);

		char Caracter[1];
		char Cadena[100];
		int contador = 0;
		double Resultado=0;
		while (*CadenaAuxiliar != '\0'){
			*Caracter = *CadenaAuxiliar;
			switch (*Caracter){
            case '+':
                if(pila.size>0){
                    double o1,o2;
                    aux = pop(&pila);
                    aux2 = pop(&pila);
                    o1=aux->expresion;
                    o2=aux2->expresion;
                    nodo.expresion=o1+o2;
                    //printf("SUMA RESULTADO %lf\n",nodo.expresion);
                    nodo.sig = NULL;
                    push(&pila,&nodo);
                }
                break;
            case '-':
                if(pila.size>0){
                    double o1,o2;
                    aux = pop(&pila);
                    aux2 = pop(&pila);
                    o1 = aux->expresion;
                    o2 = aux2->expresion;
                    nodo.expresion=o2-o1;
                    //printf("RESTA RESULTADO de restar %lf con %lf es %lf\n",o1,o2,nodo.expresion);
                    nodo.sig = NULL;
                    push(&pila,&nodo); 
                }
                break;
            case '*':
                if(pila.size>0){
                    double o1,o2;
                    aux = pop(&pila);
                    aux2 = pop(&pila);
                    o1 = aux->expresion;
                    o2 = aux2->expresion;
                    nodo.expresion=o1*o2;
                    //printf("MULTIPLICACION RESULTADO %lf\n",nodo.expresion);
                    nodo.sig = NULL;
                    push(&pila,&nodo); 
                }
                break;
            case '/':
                if(pila.size>0){
                    double o1,o2;
                    aux = pop(&pila);
                    aux2 = pop(&pila);
                    o1 = aux->expresion;
                    o2 = aux2->expresion;
                    if (!o1==0){
                        nodo.expresion=o2/o1;
                        //printf("DIVISION RESULTADO DE DIVIDIR %lf entre %lf es %lf\n",o2,o1,nodo.expresion);
                        nodo.sig = NULL;
                        push(&pila,&nodo);   
                    }else{
                        printf("NO SE PUEDE DIVIDIR ENTRE 0\n");
                        exit(1);
                    }
                }
                break; 
            case '^':
                if(pila.size>0){
                    //printf("ENTRE A LA POTENCIA\n");
                    double a1,a2,a3;
                    aux = pop(&pila);
                    aux2 = pop(&pila);
                    a1 = aux->expresion;
                    a2 = aux2->expresion;
                    a3=pow(a2,a1);
                    nodo.expresion=a3;
                    //printf("POTENCIA RESULTADO %lf\n",nodo.expresion);
                    nodo.sig = NULL;
                    push(&pila,&nodo); 
                    //printStack(&pila);
                }
                break; 
            default:
                //printf("SE ENCONTRO UN NUMERO\n");
                nodo.expresion=ANumero(*Caracter);
                nodo.sig = NULL;
                push(&pila,&nodo);
                //printf("SE INSERTO EL NUMERO %c A LA PILA\n",*Caracter);
                break;
            }	
			CadenaAuxiliar++;
		}
		/*Imprimir Resultado*/
		printf("\n");
		printf("/////////////////////////////////////////////////////////////////////\n");
		printf("EL RESULTADO DE LA EXPRESION ES: %lf",pila.Tope->expresion);
		printf("\n");
		printf("/////////////////////////////////////////////////////////////////////");
		//printStack(&pila);
	return 0;
}

/*Apila un elemento en la pila*/
 void push(Pila *pila,Nodo *nodo){
	//printf("INSERTANDO %c\n",nodo->expresion);
	Nodo *aux;
	aux = (Nodo *)malloc(sizeof(Nodo));
	
	copyNodo(nodo,aux);
	
	if(isEmpty(pila)){
		pila->Tope = aux;
		pila->size++;
	}else{
		aux->sig = pila->Tope;
		pila->Tope = aux;
		pila->size++;
	}

	//printStack(pila);
}

/*Desapila un elemento de la pila*/
Nodo* pop(Pila *pila){
	Nodo *aux;
	if(isEmpty(pila)){
		printf("Error, no se pueden sacar elementos de la Pila\n");
		aux = NULL;
	}else{
		aux = pila->Tope;
		pila->Tope = pila->Tope->sig;
		pila->size--;
	}
	return aux;
}

/*Desapila un elemento de la pila*/
Nodo* popInicio(Pila *pila){
	Nodo *aux;
	if(isEmpty(pila)){
		printf("Error, no se pueden sacar elementos de la Pila\n");
		aux = NULL;
	}else{
		aux = pila->Tope;
		pila->Tope = pila->Tope->sig;
		pila->size--;
	}
	return aux;
}

/*Comprueba si la pila esta vacia*/
int isEmpty(Pila *pila){
	int respuesta = 0;
	if(!pila->Tope)
		respuesta = 1;
	return respuesta;
}

/*Inicializa la pila*/
void initialize(Pila *pila){
	pila->size = 0;
	pila->Tope = NULL;
}

/*Imprimir la pila*/
void printStack(Pila *pila){
	Nodo *aux;
	aux = pila->Tope;
	if(isEmpty(pila)){
		printf("---------------\n");
		printf("Pila Vacia\n");
		printf("---------------\n");
	}else{
		printf("---------------\n");
		
		while(aux){
			printf("--Valor: %lf\n",aux->expresion);
			printf("---------------\n");
			aux = aux->sig;
		}
	}
}

/*Esta funcion copia el Nodo n1 en el Nodo n2*/
void copyNodo(Nodo *n1, Nodo *n2){
	double a;
	a = n1->expresion;
	n2->expresion = a;
	n2->sig = n1->sig;
}

/*Esta funcion valida que solo haya numeros y signos de operacion*/
void Valida(char* c){
    while (*c){
        if (*c>=97 && *c<=122){
            //ES UN NUMERO
        }else{
            switch (*c){
            case 42:
                //MULTIPLICACION
                break;
            case 43:
                //SUMA
                break;
            case 45:
                //RESTA
                break;
            case 47:
                //DIVISION
                break;
			case 94:
                //POTENCIA
                break;	
            default:
            printf("INGRESASTE UN CARACTER NO VALIDO VERIFICA TU EXPRESION");
            exit(0);
                break;
            }
        }
        c++;
    }
    return c;
}

/*Metodo para determinar la precedencia de operadores*/
int Precedencia(char a){
	int poder=0;
	if (a == '+' || a == '-'){
		poder = 1;
	}else if (a == '*' || a == '/'){
		poder = 2;
	}else if (a == '^'){
		poder = 3;
	}
	return poder;
}

/*Metodo para transformar caracter a numero*/
double ANumero(char a){
    switch (a){
    case 'a':
        return 3;
        break;
    case 'b':
        return 8;
        break;
    case 'c':
        return 4;
        break;
    case 'd':
        return 9;
        break;
    case 'e':
        return 2;
        break;
    case 'f':
        return 4;
        break;
    case 'g':
        return 7;
        break;
    default:
        break;
    }
}
