#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	/*Atributos*/
	//int valor;
	char expresion;
	struct nodo *sig;
}Nodo;

typedef struct pila{
	int size;
	Nodo *Tope;
}Pila;

void push(Pila *,Nodo *);
Nodo* pop(Pila *);
int isEmpty(Pila *);
void initialize(Pila *);
void printStack(Pila *);
void copyNodo(Nodo *, Nodo *);
int menu();
void copyString(char *, char *);
int sizeString(char *);
void clean_stdin();
void Mayu(char* c);
void Dobles(char* c);
int Precedencia(char a);


int main(){
	int opcion;
	Pila pila;
	Nodo nodo, *aux;
	char *CadenaAuxiliar;
	nodo.expresion = malloc(255);/*Tamaño de la cadena de entrada inicial*/
	CadenaAuxiliar = malloc(255);
	initialize(&pila);
		printf("PROGRAMA 1 NOTACION INFIJA A POSTFIJA\n");
		printf("*BY JUAN CARLOS SARMIENTO GUTIERREZ**\n");
		printf("*************************************\n");
		printf("**Ingresa la expresion a transformar*\n");
		scanf("%[^\n]",CadenaAuxiliar);
		Mayu(CadenaAuxiliar);
		Dobles(CadenaAuxiliar);
		

		char Caracter[1];
		char Cadena[100];
		int contador = 0;
		
		while (*CadenaAuxiliar != '\0'){
			*Caracter = *CadenaAuxiliar;
			if(*Caracter>=65 && *Caracter<=90){
				//printf("ENCONTRE UN OPERANDO\n");
				Cadena[contador]=*Caracter;
				//printf("VALOR DEL CONTADOR ANTERIOR %d\n",contador);
				contador++;
				//printf("VALOR DEL CONTADOR NUEVO %d\n",contador);
			}else{
				if (!isEmpty(&pila)){
					//printf("LA PILA NO ESTA VACIA\n");
					if (Precedencia(*Caracter)>Precedencia(pila.Tope->expresion)){
						//printf("LA PRECEDENCIA DEL OPERADOR %c ES MAYOR QUE LA DEL OPERADOR %c\n",*Caracter,pila.Tope->expresion);
						nodo.expresion = *Caracter;
						nodo.sig = NULL;
						push(&pila,&nodo);
						//printf("COMO LA PRECEDENCIA ERA MAYOR INSERTE EL OPERADOR A LA PILA\n");
					}else if (Precedencia(*Caracter)<=Precedencia(pila.Tope->expresion)){
						//printf("LA PRECEDENCIA DEL OPERADOR %c ES MENOR QUE LA DEL OPERADOR %c\n",*Caracter,pila.Tope->expresion);
						while (!pila.size==0){
							//printf("ENTRE AL PROCESO DE REDUCCION\n");
							aux = pop(&pila);
							//printf("EL OPERADOR ACUAL EN EL TOPE DE LA PILA ES %c\n",aux->expresion);
							Cadena[contador]= aux->expresion;
							//printf("EL OPERADOR %c SE INTRODUJO A LA CADENA EN LA POSICION %d QUEDANDO ASI %c\n",aux->expresion,contador,Cadena[contador]);
							contador++;
						}
						//printf("TERMINE Y AHORA INSERTO EL SIGUIENTE OPERADOR QUE ES %c\n",*Caracter);
						nodo.expresion = *Caracter;
						nodo.sig = NULL;
						push(&pila,&nodo);
					}
				}else{
					//printf("LA PILA ESTA VACIA E INGRESE UN ELEMENTO\n");
					nodo.expresion = *Caracter;
					nodo.sig = NULL;
					push(&pila,&nodo);
				}
			}
			CadenaAuxiliar++;
		}
		/*En caso de que la pila se haya quedado con operadores consecutivos de mayor precedencia*/

		while (!pila.size==0){
				Nodo *new;
				new = pop(&pila);
				Cadena[contador]=new->expresion;
				contador++;
		}
			
		Cadena[contador]='\0';
		
		/*Imprimir la cadena final*/
		contador = 0;
		printf("\n");
		printf("/////////////////////////////////////////////////////////////////////\n");
		printf("LA EXPRESION A NOTACION POSTFIJA ES: ");
		while (Cadena[contador]!='\0'){
			printf("%c",Cadena[contador]);
			contador++;
		}
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
	aux->expresion = malloc(sizeof(char));
	
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
			printf("--Operador: %c\n",aux->expresion);
			printf("---------------\n");
			aux = aux->sig;
		}
	}
}

/*Esta funcion copia el Nodo n1 en el Nodo n2*/
void copyNodo(Nodo *n1, Nodo *n2){
	char a;
	a = n1->expresion;
	n2->expresion = a;
	n2->sig = n1->sig;
}

/*Esta funcion transfroma la expresion a mayusculas y valida que tenga solo caraacteres validos*/
void Mayu(char* c){
    while (*c){
        if (*c>=97 && *c<=122){
            *c=*c-32;
        }else if(*c>=65 && *c<=90){
            //LA EXPRESION YA ESTA EN MAYUSCULAS
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

/*Funcion para validar que no se repitan letras*/
void Dobles(char* c){
	char a[1];
	while (*c){
		*a = *c;
		c++;
		while (*c){
			if(*c>=65 && *c<=90){
				//ES UNA LETRA
				if (*a == *c){
				printf("REPETISTE UNA LETRA, PRUEBA OTRA VEZ\n");
				exit(1);
				}
			}
			c++;
		}
	}
}