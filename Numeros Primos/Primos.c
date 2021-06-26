#include <stdio.h>
#include <string.h>

int isPrime(int num){
	if(!(num>1))
	    return 1;
	for(int i=2;i<=num/2;i++){
		if(num%i==0)
	    return 1;
	}
	return 0;
}

int main(){
	int Max;
	FILE* flujo = fopen("Primos.txt","w");	
	char aux[10];
	printf("Ingresa hasta que numero quieres calcular primos\n");
	scanf("%d",&Max);
	printf("--LISTA DE PRIMOS HASTA EL NUMERO %d--\n",Max);
	for (int i = 0; i < Max; ++i){
		if (isPrime(i)==0){
			sprintf(aux, "%d", i);
			strcat(aux,"\n");
			fputs(aux,flujo);
			printf("%d\n",i);
		}
	}
	fflush(flujo);
	fclose(flujo);
	return 0;
};