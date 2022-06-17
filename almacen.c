//Programa para cualquier empresa con un almac�n en el cu�l se desee facilitar el trabajo de b�squeda, inserci�n y retirada de los productos que maneje.

#include<stdio.h>
#include<string.h>
#define N 50
#define M 3
#define O 4

typedef struct{
	
	int codigo;
	int lleno;
	char nombre[N];
	
}tipo_1;

void inicializar(tipo_1 almacen[M][O][O]);
void cambio(char palabra[N]);
void insertar(tipo_1 almacen[M][O][O]);
void mostrar(tipo_1 almacen[M][O][O]);
void buscar(tipo_1 almacen[M][O][O]);
void retirar(tipo_1 almacen[M][O][O]);
void listado(tipo_1 almacen[M][O][O]);

int main(){
	
	int op;
	char key;
	tipo_1 almacen[M][O][O]; // 3 estanterias de 4 filas y 4 columnas
	
	inicializar(almacen);
	
	do{
		do{
			printf("\nElige que deseas hacer:\n\n");
			printf("\t(1) Insertar producto.\n");
			printf("\t(2) Mostrar distribucion.\n");
			printf("\t(3) Buscar producto.\n");
			printf("\t(4) Retirar producto.\n");
			printf("\t(5) Listado de productos.\n");
			printf("\t(6) Finalizar programa.\n");
			scanf(" %i",&op);
			
		}while(op<1 || op>6);
		system("cls");
		
		switch(op){
			case 1:
				insertar(almacen);
				break;
			case 2: 
				mostrar(almacen);
				break;	
			case 3:
				buscar(almacen);
				break;
			case 4:
				retirar(almacen);
				break;
			case 5:
				listado(almacen);
				break;
			case 6:
				return 0;
				break;
		}
		printf("\nDeseas realizar otra operacion?: (S/N) ");
		fflush(stdin);
		scanf(" %c",&key);
		system("cls");
	}while(key == 's' || key == 'S');
	
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void inicializar(tipo_1 almacen[M][O][O]){
	int i,j,k;
	
	i=0;
	while(i<M){
		j=0;
		while(j<O){
			k=0;
			while(k<O){
				almacen[i][j][k].lleno=0;
				almacen[i][j][k].codigo=0;
				k++;
			}
			j++;
		}
		i++;
	}
}

void cambio(char palabra[N]){ // Para quitar el salto de l�nea al final de un string
	int i;
	for(i=0;i<N;i++){
		if(palabra[i]=='\n'){
			palabra[i]='\0';
		}
	}
}

void insertar(tipo_1 almacen[M][O][O]){
	int i,j,k,aux,cont;
	
	cont=0;
	aux=0;
	
	i=0;
	while(i<M && aux==0){
		j=0;
		while(j<O && aux==0){
			k=0;
			while(k<O && aux==0){
				if(almacen[i][j][k].lleno==0){
					aux=1; // Para meter de uno en uno 
					
					printf("Escriba el nombre del producto: \n");
					fflush(stdin);
					fgets(almacen[i][j][k].nombre,N,stdin);
					cambio(almacen[i][j][k].nombre);
					printf("Escriba el Codigo del producto: ");
					scanf(" %i",&almacen[i][j][k].codigo);
					
					almacen[i][j][k].lleno=1; // Para asegurar que no se guarda nada en el mismo lugar
				}
				else{
					cont++;
					k++;
				}
			}
			j++;
		}
		i++;
	}
	
	if(cont==M*O*O){
		printf("ESTA TODO LLENO.\n\n"); 
	}
}

void mostrar(tipo_1 almacen[M][O][O]){
	int i,j,k,cont;
	
	i=0;
	while(i<M){
		printf("Estanteria %i\n\n",i);
		j=0;
		while(j<O){
			/*cont=j+1;
				while(cont<O){
					printf("\t");  **se muestra con tabulaciones
					cont++;
				}*/
			k=0;
			while(k<O){
				if(almacen[i][j][k].lleno==0){
					printf(" 0 ");
					k++;
				}
				else{
					printf(" 1 ");
					k++;
				}
				
			}
			printf("\n");
			j++;
		}
		i++;
		printf("\n");
	}
	
	printf("\n\n");
}

void buscar(tipo_1 almacen[M][O][O]){
	int i,j,k,cod,aux,op,aux2,cont;
	char nom[N];
	char key;
	
	do{
		printf("  Buscar por:\n");
		printf("\t(1) Codigo\n");
		printf("\t(2) Nombre\n");
		printf("\t(3) Posicion\n");
		printf(" ");
		scanf(" %i",&op);
	}while(op<1 || op>3);
	
	switch(op){
		case 1:{
			cont=0;
			aux=0;
			
			do{
				printf("Introduce el Codigo del producto que quieres buscar: ");
				scanf(" %i",&cod);
			}while(cod==0);
			
			
			i=0;
			while(i<M && aux==0){
				j=0;
				while(j<O && aux==0){
					k=0;
					while(k<O && aux==0){
						if(almacen[i][j][k].codigo==cod){
							system("cls");
							aux=1;
							printf("\n %s\n",almacen[i][j][k].nombre);
							printf("\tEstanteria: %i\n",i);
							printf("\tFila: %i\n",j);
							printf("\tColumna: %i\n\n",k);
						}
						else{
							k++;
							cont++;
						}
					}
					j++;
				}
				i++;
			}
			if(cont==M*O*O){
				system("cls");
				printf("\nNO hay ningun producto con ese codigo\n\n");
			}
			break;
		}
		case 2:{
			
			cont=0;
			aux=0;
			printf("Escriba el nombre del producto: \n");
			fflush(stdin);
			fgets(nom,N,stdin);
			cambio(nom);
			
			i=0;
			while(i<M && aux==0){
				j=0;
				while(j<O && aux==0){
					k=0;
					while(k<O && aux==0){
						aux2 = strcmp(nom,almacen[i][j][k].nombre);//si nom y almac.. son iguales aux2=0
						if(aux2==0 && almacen[i][j][k].codigo!=0){
							system("cls");
							aux=1;
							printf("\nCodigo: %i\n",almacen[i][j][k].codigo);
							printf("Estanteria: %i\n",i);
							printf("Fila: %i\n",j);
							printf("Columna: %i\n\n",k);
						}
						else{
							k++;
							cont++;
						}
					}
					j++;
				}
				i++;
			}
			
			if(cont==M*O*O){
				system("cls");
				printf("\nNO hay ningun producto con ese nombre\n\n");
			}
			break;
		}
		case 3:{
			system("cls");
			do{
				printf("\nSelecciona Estanteria: ");
				scanf(" %i",&i);
				printf("Selecciona Fila: ");
				scanf(" %i",&j);
				printf("Selecciona Columna: ");
				scanf(" %i",&k);
			
				if(almacen[i][j][k].lleno==0){
					system("cls");
					printf("\nNO hay nada guardado en esa posicion.\n");
				}
				else{
					system("cls");
					printf("Producto guardado:\n\n");
					printf("%s\n",almacen[i][j][k].nombre);
					printf("Codigo %i\n",almacen[i][j][k].codigo);
				}
				printf("\nQuieres consultar otra posicion?: (S/N) ");
				scanf(" %c",&key);	
				system("cls");
			}while(key=='s');
			
			break;
		}
	}
}

void retirar(tipo_1 almacen[M][O][O]){
	int i,j,k;
	char key,op;
	do{
		system("cls");
		printf("\nSlecciona la posicion del producto a retirar.\n");
		printf("Estanteria: ");
		scanf(" %i",&i);
		printf("Fila: ");
		scanf(" %i",&j);
		printf("Columna: ");
		scanf(" %i",&k);
	
		if(almacen[i][j][k].lleno==0){
			system("cls");
			printf("\nNO hay productos guardados\n");
		}
		else{
			system("cls");
			printf("\nEl producto que va a retirar es:\n");
			printf(" %s\n",almacen[i][j][k].nombre);
			printf(" Codigo: %i\n",almacen[i][j][k].codigo);
			printf("\nEstas seguro?:(S/N) ");
			scanf(" %c",&key);
			if(key=='s'){
				system("cls");
				printf("\nProducto retirado.\n\n");
				almacen[i][j][k].codigo=0;
				almacen[i][j][k].lleno=0;
				op='n';
			}
			else{
				system("cls");
				printf("\nQuieres volver a la ventana de retirada?:(S/N) ");
				scanf(" %c",&op);
			}
		}
	}while(op=='s');
	
}

void listado(tipo_1 almacen[M][O][O]){
	int i,j,k;
	
	i=0;
	while(i<M){
		printf("\nEstanteria %i\n\n",i);
		j=0;
		while(j<O){
			k=0;
			while(k<O){
				if(almacen[i][j][k].lleno==0){
					k++;
				}
				else{
					printf(" %s",almacen[i][j][k].nombre);
					k++;
				}
				
			}
			printf(" ");
			j++;
		}
		i++;
		printf("\n");
	}
}
