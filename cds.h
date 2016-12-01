#define MAX 200

#ifndef cds_h
#define cds_h

struct cds
{
	int canciones;
	char nombre[200];
	char genero [200];
	char album[200];
	float precio;
};

typedef struct cds CD;
int indiceAlArreglo=0;// esta variable global se usara para almacenar el indice del ultimo cd ingresado al arreglo
CD listaCd[MAX];// declaracion de un arreglo de cds de 200 elementos


void insertarCd(CD cd){
	if (indiceAlArreglo >= 0 && indiceAlArreglo < MAX) { // verificamos que inidice este en los rangos correctos
        listaCd[indiceAlArreglo]=cd;
        indiceAlArreglo++;
    }else{
        printf("El indice apunta fuera del arreglo, favor de revisar la logica");
    }
}

 CD nuevoCd(){
    CD tmp;
    printf("Introduce el nombre del artista:");
    scanf("%*c%[^\n]",tmp.nombre); 
    printf("Introduce el genero:");
    scanf("%*c%[^\n]",tmp.genero);
    printf("Introduce el album:");
    scanf("%*c%[^\n]",tmp.album);
    printf("Introduce numero de canciones:");
    scanf(" %d",&tmp.canciones);   // El espacio antes del %c es para que ignore espacios en blanco
    printf("Introduce el precio:");
    scanf(" %f",&tmp.precio);
    insertarCd(tmp);
    return tmp;
}

void imprimeCd(CD cd){
    printf("Nombre del artista: %s\n",cd.nombre);
    printf("Genero: %s\n",cd.genero);
    printf("Nombre del album: %s\n",cd.album);
    printf("Numero de canciones: %d\n",cd.canciones);
    printf("precio:$%.2f\n",cd.precio);
    printf("**************************\n");
}

void imprimirLista(){
    int j=0;
    for (j = 0; j < indiceAlArreglo; j++) {
        printf("************CD#%i**********\n",j+1);
        imprimeCd(listaCd[j]);
    }
}


void buscarPorNombreArtista(char *nombre){
    int j=0;
    for (j = 0; j < indiceAlArreglo; j++) {
        if(strcmp(listaCd[j].nombre,nombre) == 0){
            printf("**************************\n");
            imprimeCd(listaCd[j]);
        }
    }
}

void buscarPorCanciones(int c){
    int j=0;
    for (j = 0; j < indiceAlArreglo; j++) {
        if(c == listaCd[j].canciones){
            printf("**************************\n");
            imprimeCd(listaCd[j]);
        }
    }
}

void calcularPromedioPrecio(){
    int j=0;
    int tmp=0;
    for (j = 0; j < indiceAlArreglo; j++) {
        tmp= tmp + listaCd[j].precio;
    }
    printf("\nEl promedio de los precios de los albunes en la BD es: $%d!",tmp/indiceAlArreglo);
}

int menu(){
    int opcion=0;
    printf("\n----------- Menu para la aplicacion de BD para Cds---------\n");
    printf("(1) Crear lista.\n");
    printf("(2) Guardar a archivo.\n");
    printf("(3) Leer desde archivo.\n");
    printf("(4) Mostrar lista.\n");
    printf("(5) Agregar Cd. \n");
    printf("(6) Obtener promedio de precios.\n");
    printf("(7) Buscar Cd por artista. \n");
    printf("(8) Buscar Cd por canciones. \n");
    printf("(9) Eliminar Cd \n");
    printf("(10)Modificar Cd \n");
    printf("(0) SALIR\n");
    printf("\n\nElige una opcion:");
    scanf("%d",&opcion);

    return opcion;
}

void grabarRegistros(CD r[], int tam){
    FILE *ptrF;

    if((ptrF=fopen("Cds.dat","w"))==NULL){
        printf("el archivo no se puede abrir\n");
    }else{
        fwrite(r,sizeof(CD),tam,ptrF);
    }

    fclose(ptrF);
}

int registrosEnArchivo()
{
	FILE *ptrF;
	int cont=0;
	CD tmp;
	if((ptrF=fopen("Cds.dat","rb"))== NULL)
	{
		printf("Error al abrir el archivo\n");
	}else{
		while(!feof(ptrF)){
			if(fread(&tmp,sizeof(CD),1,ptrF))
			cont++;
		}
	}
	fclose(ptrF);
	return cont;	
}


void leerRegistros(int tam){

    FILE *ptrF;

    if((ptrF=fopen("Cds.dat","rb"))==NULL){
        printf("el archivo no se puede abrir\n");
    }
    else{
        //for /*(int i=0;i<tam;i++)*/
        fread(listaCd,sizeof(CD),tam,ptrF);
    }

    fclose(ptrF);
}

void eliminarCd(int borrar){
    int b=borrar;
    printf("Introduce el numero de CD que deseas eliminar:\n");
    scanf("%d",&borrar);
    if(borrar >= 0 && borrar <= indiceAlArreglo){
       printf("**************************\n");
       imprimeCd(listaCd[borrar-1]);
       for(b=borrar; b<=indiceAlArreglo; b++){
       listaCd[b-1]=listaCd[b];
       }
       indiceAlArreglo--;
    }else{
      printf("El numero de CD es incorrecto, intentelo nuevamente");
    }
} 

int menuModifica(){
   int modif;
    printf("\n----------- Menu para modificacion de datos ---------\n");
    printf("(1) Cambiar nombre del artista.\n");
    printf("(2) Modificar el genero.\n");
    printf("(3) Cambiar el nombre del album.\n");
    printf("(4) Modificar el numero de canciones.\n");
    printf("(5) Cambiar el precio. \n");
    printf("(0) SALIR\n");
    printf("\n\nElige una opcion:");
    fflush(stdin); 
    scanf("%i",&modif);
    return modif;

}

void modificarCd(int modifica){
     printf("Ingresa el numero de CD que deseas modificar:");
	scanf("%d",&modifica);
	if(modifica>=0 && modifica<=indiceAlArreglo){
             printf("**************************\n");
	     imprimeCd(listaCd[modifica-1]); 
	     int modif=menuModifica();
	     switch(modif){
	            case 1: 
                    printf("El nombre del artista actual es: %s\n",listaCd[modifica-1].nombre);
	            printf("Introduce el nuevo artista:");
	            scanf("%*c%[^\n]",listaCd[modifica-1].nombre);
		    break;
		    case 2:
		    printf("El genero actual es: %s\n",listaCd[modifica-1].genero);
		    printf("Introduce el genero nuevo:");
		    scanf("%*c%[^\n]",listaCd[modifica-1].genero);
		    break;
		    case 3:
                    printf("El album actual es: %s\n",listaCd[modifica-1].album);
		    printf("Introduce el album nuevo:");
		    scanf("%*c%[^\n]",listaCd[modifica-1].album);
  		    break;
		    case 4:
		    printf("El numero de canciones actual es: %d\n",listaCd[modifica-1].canciones);
		    printf("Introduce el nuevo numero de canciones:");
		    scanf("%d",&listaCd[modifica-1].canciones);
	            break;
		    case 5:
 		    printf("El precio actual es: %.2f\n",listaCd[modifica-1].precio);
		    printf("Introduce el nuevo precio:");
		    scanf("%f",&listaCd[modifica-1].precio);
	            break;
		    default:
		    printf("Opcion no valida!!\n");
		    break; 
		  }
       }else{
         printf("Numero de CD no encontrado, intentalo nuevamente\n");
         }
    
}

#endif /* alumnos_h */

 