#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//Se utiliza una lista ENLAZADA para no tener limitaciones y poder agregar tantos productos se requieran sin gastar memoria no ocupada.
//Se observa la estructura de cada nodo de la lista el cual cosntituye de 4 tipos de variables (la cantidad el nombre el criterio y el puntero al siguiente nodo en la memoria).
// Definición de la estructura del nodo de la lista
struct Producto {                                                                     // se crea una estructura con 4 variables.
    char nombre[100];
    int cantidad; 
    int necesario;                                                                    // 1 si es necesario, 0 si no es necesario
    struct Producto* siguiente;
};

typedef struct Producto* NProducto;                                                   // Acortara el nombre de [struct Producto*]
 
// Función para agregar un nuevo producto al inventario
NProducto agregarProducto(NProducto cabeza, char nombre[], int cantidad, int necesario) {  
    NProducto nuevoProducto = (NProducto)malloc(sizeof(struct Producto));
    strcpy(nuevoProducto->nombre, nombre);
    nuevoProducto->cantidad = cantidad;
    nuevoProducto->necesario = necesario;
    nuevoProducto->siguiente = cabeza;
    return nuevoProducto;
}

// Función para eliminar un producto del inventario
NProducto eliminarProducto(NProducto cabeza, char nombre[]) {                              
    NProducto actual = cabeza;                                                             
    NProducto anterior = NULL;
    while (actual != NULL) {                                                           // El bucle while repetira la ejecucion mientras que la estructura "actual" sea diferente de NULL (nula).                                                     
        if (strcmp(actual->nombre, nombre) == 0) {                                     // Se usa condicional if para definir la accion a tomar dependiento si el nombre actual coincide con el nombre leido en el renglon 125 o no. 
            if (anterior == NULL) {                                                    // La condicional if determinara la accion dependiendo si la variable "aneterior" es NULL.
                cabeza = actual->siguiente;                                                
            } else {                                                                   // Si la variable "anterior" no es NULL, el puntero siguiente de el sera igual al puntero "siguiente" de "actual"
                anterior->siguiente = actual->siguiente;
            }
            printf("\nProducto %s eliminado correctamente.\n\n\n\n\n\n",nombre);       // imprime si el producto fue eliminado correctamente.
            free(actual);                                                              // la funcion free deasigna la memoria de "actual".
            return cabeza;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    printf("\nEl producto '%s' no se encontró en el inventario.\n\n\n\n", nombre);
    return cabeza;
}


//BUSQUEDA LINEAL
//Al no haber establecido ningun algoritmo de ordenamiento ya que no es necesario, se realiza una busqueda lineal.
//Se recorre linealmente la lista de productos y seleccionando aquellos que cumplen con el criterio de necesidad.
//Se establecio uns busqueda lineal y no una busqueda binaria porque no se esta buscando un elemento en especifico sino que se estan filtrando varios elementos en base a una propiedad.

// Función para filtrar los productos necesarios o no necesarios  

void filtrarProductos(NProducto cabeza, int necesario) {
    int cont=0;                                                                        // se crea un contador para determinar si hay productos necesarios/no necesarios en el inventario 
	NProducto actual = cabeza;
    printf("\nProductos que %s necesarios:\n", necesario ? "son" : "no son");
    while (actual != NULL) {                                                           // El bucle while repetira la ejecucion mientras que la estructura "actual" sea diferente de NULL (nula).    
        if (actual->necesario == necesario) {                                          // Se usa condicional if para definir la accion a tomar dependiento si la variable "necesario" de la estructura actual es necesario (1) o no (0). 
            printf("Nombre: %s, Cantidad: %d\n", actual->nombre, actual->cantidad);
            actual = actual->siguiente;
            cont++;
        }
        else {                                                                         // Si no es necesario, el valor de "actual" se volvera el valor del "siguiente actual" y se repite el bucle.
            actual = actual->siguiente;
        }
    }
    if (cont == 0) {                                                                   // Se usa la condicional if para imprimir un aviso que no se presentan productos cuando la variable "cont" tenga valor 0.
    printf("\tEl inventario no contiene productos que %s necesarios.",necesario ? "son" : "no son");
    }
    printf("\n\n\n\n\n\n");
}

// Función para imprimir el inventario completo          
void imprimirInventario(NProducto cabeza) {
    NProducto actual = cabeza;

    printf("\nInventario:\n");
    while (actual != NULL) {                                                           // El bucle while repetira la ejecucion mientras que la estructura "actual" sea diferente de NULL (nula).
        printf("Nombre: %s, Cantidad: %d, %s necesario\n", actual->nombre, actual->cantidad, actual->necesario ? "Es" : "No es");                  // Se imprimiran todos los prodcutos del inventario.
        actual = actual->siguiente;
    }
    printf("\n\n\n\n\n\n");
}

// Función para liberar la memoria de la lista enlazada
void liberarInventario(struct Producto* cabeza) {
    while (cabeza != NULL) {                                                           // El bucle while repetira la ejecucion mientras que la estructura "actual" sea diferente de NULL (nula).    
        NProducto temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

//Funcion principal
int main() {                                                                           
    NProducto inventario = NULL;                                       
    int eleccion;

   
    do {                                                                                // El bucle do-while sirve para no terminar la ejecucion del algoritmo y volver a imprimir el menu.
    system("cls");                                                                      // Limpia la pantalla, elimina datos anteriores.
        printf("\tINVENTARIO\n\n1. Agregar producto\n2. Eliminar producto\n3. Filtrar productos necesarios\n4. Filtrar productos no necesarios\n5. Mostrar inventario\n0. Salir\n");
       	printf("\nSeleccione una opción: ");
        scanf("%d", &eleccion);     
        
		switch (eleccion) {                                                             // La condicional switch ejecutara el bloque de sentencias que coincida con la variable, en este caso, llamada "eleccion".
            case 1: {
                char nombre[100];
                int cantidad, necesario;
                printf("\nIngrese el nombre del producto: ");
                scanf("%s", nombre);                                                    // se lee la variable char
                printf("Ingrese la cantidad: ");
                scanf("%d", &cantidad);                                                 // se lee la variable entera
                do{
                	  printf("¿Es necesario? (1: Sí, 0: No): ");
                scanf("%d", &necesario);
				} while ((necesario<0) || (necesario>1));                               // Uso de do-while para tener un rango especifico de 0-1 para que no tome otros valores como verdaderos
               
                inventario = agregarProducto(inventario, nombre, cantidad, necesario);  // se llama a la funcion agregarProducto, con los parametros del inventario y las variables leidas en renglon 111,113,115.
                printf("\nProducto %s agregado correctamente.\n\n\n\n\n\n",nombre);
                system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
            }
            case 2: {
            	if(inventario!=NULL){                                                   // Se usa condicional if para definir la accion a tomar dependiento si el inventario tiene productos en el o no.
                char nombre[100];
                printf("\nIngrese el nombre del producto a eliminar: ");
                scanf("%s", nombre);  //se lee la variable char
                inventario = eliminarProducto(inventario, nombre);                      // se llama a la funcion de eliminarProducto, con los parametros del inventario y el nombre leido en renglon 125.
                }
                else{                                                                   // Si el inventario no tiene productos, se indicara que esta vacio.
				printf("\nEl inventario esta vacio.\n\n\n\n\n\n");
				}
				system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
            }
            case 3:
				filtrarProductos(inventario, 1);                                        // Filtrar productos necesarios (necesario = 1)
				system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
            case 4:
				    filtrarProductos(inventario, 0);                                    // Filtrar productos no necesarios (necesario = 0)
				system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
            case 5:
            	if(inventario!=NULL){                                                   // Se usa condicional if para definir la accion a tomar dependiento si el inventario tiene productos en el o no.
                imprimirInventario(inventario);
                }
                else{                                                                   // Si el inventario no tiene productos, se indicara que esta vacio.
                	printf("\nEl inventario esta vacio.\n\n\n\n\n\n");
				}
				system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
            case 0:
                break;
            default:
                printf("\nOpción no válida. Intente nuevamente.\n\n\n\n\n");
				system("pause");                                                        // Pausara el sistema hasta presionar alguna tecla para permitir leer el aviso.
				break;
        }
    } while (eleccion != 0);

    liberarInventario(inventario);                                                      // Liberar la memoria antes de salir
    return 0;
}

