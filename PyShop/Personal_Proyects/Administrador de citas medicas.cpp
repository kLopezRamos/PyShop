#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<string.h>

struct Citas {
	char nombre [100];
	char fecha [20];
	char motivo [100];
	
};
//se utilizara una lista que usa un arreglo estatico con un alongitud de 200 elementos.
//se realiza una estructura que se asemeja a la creacion de un nodo en una lista enlazada sin embargo aqui no se utiliza un puntero ya que no se trata de una estructura de datos dinamica.
//se eligio trabajar con una estructura de datos estatica por simplicidad en el programa.

main(){
		
	struct Citas citas[200];
	int numero_citas = 0, continuar=2, opcion, menu;
	
	
	
	while(continuar==2){
	system("cls");
	
	printf("\n\n\n\t\t\tConsultorio\n");
	printf("\t\t\tADMINISTRACION DE CITAS:\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t1.-Agregar cita nueva.\n");
	printf("\t\t\t2.-Buscar citas por fecha.\n");
	printf("\t\t\t3.-Ver todas las citas programadas\n");
	printf("\t\t\t4.-Calcelar (eliminar) citas.\n");
	printf("\t\t\t5.-Salir.\n");
	
	printf("\nElige el procedimiento a realizar: ");
	scanf("%d", &opcion);
	
	
	switch(opcion){
		case 1:
			do{
			system("cls"); //similar a cuando se agrega unelemento a una lista enlazada 
			//sin embrgo en la lista enlazada se necesita llamar a una funcion para agregar la variable en el nodo adecuado y en el nuevo elemnto de la lista ademas en la lista enlazada el primer elemento ingresado se imprime como el ultimo elemento
			//ya qu euna lista enlazada no tiene un limite de elementos establecido, aqui se guarda la variable ingresada 
			//referenciando las partes de los elementos de cada estructura (elemento) del arreglo, no se necesita crear un nuevo nodo para aguardar la informacion como en la lista elnazada sino que se guarda demanera directa
			if (numero_citas<200){
				printf("\n\nIngrese nombre de paciente: ");
				scanf(" %[^\n]", citas[numero_citas].nombre);
				printf("Ingresa la fecha de la cita en el formato (DD/MM/AAAA): ");
				scanf("%s", citas[numero_citas].fecha);
				printf("Ingrese el motivo de la consulta: ");
				scanf(" %[^\n]", citas[numero_citas].motivo);
				numero_citas++;

			} else{
				printf("\nAgenda llena. No se pueden ingresar mas pacientes");
			}
			printf("\n\nCita programada con exito!");
			printf("\nDeseas continuar con esta accion: 1.-Si 2.-No ");
			scanf("%d", &continuar);
			
		} while (continuar==1);
			break;
			
		case 2:
		do{	
		system("cls");
		if (numero_citas > 0) {
        char fecha_deseada[20];
        printf("\n\nFiltrar pacientes para fecha: ");
        scanf(" %[^\n]", fecha_deseada);
        printf("\n==== Pacientes para la fecha %s ====\n", fecha_deseada);

        int encontrados = 0; 
                                                  //Aqui realiza un busqueda lineal o secuencial
        for (int i = 0; i < numero_citas; i++) { //  se recorre una lista de elementos uno por uno en orden secuencial hasta encontrar el elemento deseado o determinar que no está en la lista
            if (strcmp(citas[i].fecha, fecha_deseada) == 0) { //compara ambos valores yde ser iguales regresa un cero 
                encontrados = 1;                              //Se establecio uns busqueda lineal y no una busqueda binaria porque no se esta buscando un elemento en especifico sino que se estan filtrando varios elementos en base a una propiedad.
                printf("\n\nNo. de paciente: %d\n", i + 1);
                printf("Paciente: %s\n", citas[i].nombre);
                printf("Motivo de visita: %s\n", citas[i].motivo);
            }
        }

        if (!encontrados) { //si encontrados es diferente de 1 
            printf("\nNo hay registro de citas para el %s\n", fecha_deseada);
        }
	}
	printf("\nDeseas continuar con esta accion: 1.-Si 2.-No ");
    scanf("%d", &continuar);
				
		}while (continuar==1);
			break;
			
		case 3:  //el imprimir cada elemento de la lista se comporta d emanera similar a cuando se atraviesa una lista enlazada donde se usa un bucle while
		//en listas enlazadas se utiliza un bucle while mientras el puntero sea diferente de NULL mientras que aqui se usa un bucle for mientras i sea menor al numero de citas que se incrementa cada que se añade un elemento al arreglo.
		system("cls");
		if(numero_citas>0){
			printf("\t\t\t====Citas Programadas====\n");
			for(int i = 0; i < numero_citas; i++){
				printf("\n\nNo. DE PACIENTE: %d\n", i + 1);
				printf("Fecha de cita: %s\n", citas[i].fecha);
                printf("Paciente: %s\n", citas[i].nombre);
                printf("Motivo de visita: %s\n", citas[i].motivo);
                
                printf("\n");
			}
		}else{
			printf("No hay ninguna cita programada aun.\n\n");
		}
		break;
	
		case 4:
			do{
			system("cls");
			if(numero_citas>0){
				int numero_paciente;
				printf("\n\nIngrese el numero de paciente que desea eliminar: ");
				scanf("%d", &numero_paciente);
				if(numero_paciente>=1 and numero_paciente<=numero_citas){
					for(int i = numero_paciente - 1; i< numero_citas - 1; i++){
						strcpy(citas[i].nombre, citas[i+1].nombre); // copia los caracteres del indice del arreglo de adelante en el indice actual porque s etrata de una lista en un arreglo.
						strcpy(citas[i].fecha, citas[i+1].fecha);// a diferencia de un alista enlazada, pila o cola, cuando se elimina algun elementode la misma no se necesita recorrer el contenido de lso elementos posteriores.
						strcpy(citas[i].motivo, citas[i+1].motivo);
					}
					numero_citas --;
					printf("La cita ha sido cancelada.");
				}else{
					printf("El numero de paciente ingresado no existe en la base de datos");
				}
			}else{
				printf("No hay citas registradas hasta el momento");
			}
			
		printf("\n Deseas continuar con esta accion? 1.- SI 2.-NO ");
			scanf("%d", &continuar);

		}	while(continuar==1);
			break;
			
		case 5:
			printf("Administracion de citas COMPLETADA.");
			continuar=0;
			break;
			
		default:
			printf("La opcion ingresada no existe.\n");
			continuar==2;
			break;
	}//fin de switch
if(continuar==2){
printf("Presiona 1 para regresar al menu principal: ");
scanf("%d", &menu);
}
}//fin de while

	}

