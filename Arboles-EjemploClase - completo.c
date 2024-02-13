#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* Declaración de tipos de datos personalizados */
typedef char tString [25];

typedef struct {
	int codigo;
	tString descripcion;
} tDatos;

typedef struct nodoArbol {
	tDatos datos;
	struct nodoArbol * hijoIzquierdo;
	struct nodoArbol * hijoDerecho;
}tArbol;

/* Declaración de prototipos */
void crearArbolVacio( tArbol ** );
bool arbolVacio( tArbol * );
void insertarElemento( tArbol **, tDatos );
void recorrerEnPreorden( tArbol * );
void recorrerEnPostorden( tArbol * );
void recorrerEnInorden( tArbol * );
bool buscarElemento( tArbol *, int );
int cantidadNodos( tArbol * );
tArbol * buscarMin( tArbol * );
void eliminarElemento( tArbol **, int );

/* Declaración de variables */
tArbol * arbol;

/* Bloque principal */
int main() {
	tDatos dato;
	
	crearArbolVacio(&arbol);
	printf("Arbol vacio? %s\n", arbolVacio(arbol) == true ? "si" : "no" );
	
	dato.codigo = 74;
	strcpy(dato.descripcion, "Descripcion 74");	
	insertarElemento(&arbol, dato);
	
	dato.codigo = 85;
	strcpy(dato.descripcion, "Descripcion 85");	
	insertarElemento(&arbol, dato);
	
	dato.codigo = 53;
	strcpy(dato.descripcion, "Descripcion 53");	
	insertarElemento(&arbol, dato);
		
	printf("Arbol vacio? %s\n", arbolVacio(arbol) == true ? "si" : "no" );
	
	printf("existe el 53? %s\n", buscarElemento(arbol, 53) == true ? "si" : "no" );	
	printf("existe el 11? %s\n", buscarElemento(arbol, 11) == true ? "si" : "no" );
	
	printf("\nCantidad de elementos del arbol: %d\n\n", cantidadNodos(arbol));
	
	printf("Elementos del arbol: \n");
	recorrerEnInorden(arbol);
	
	eliminarElemento(&arbol, 53);
	
	printf("\nElementos del arbol luego de eliminar el 53: \n");
	recorrerEnInorden(arbol);
	
	return 0;
}

/* Implementación de funciones */
void crearArbolVacio( tArbol ** pArbol ) {	
	*pArbol = NULL;
	printf("Arbol vacio creado!\n");
}

bool arbolVacio( tArbol * pArbol ) {
	return pArbol == NULL;
}

void insertarElemento( tArbol ** pArbol, tDatos pDatos ) {
	if( arbolVacio(*pArbol) ) {
		/* Reservar memoria para el nodo y asignarle valores */
		(*pArbol) = (tArbol *) malloc(sizeof(tArbol));
	
		if( *pArbol == NULL ) {
			printf("No hay espacio disponible!\n");
		} else {
			/* Asignar valores al nodo */
			(*pArbol)->datos = pDatos;
			(*pArbol)->hijoIzquierdo = NULL;
			(*pArbol)->hijoDerecho = NULL;
		}
		
	}else {
		
		/* Definir para qué lado continuar recorriendo */
		if( pDatos.codigo > (*pArbol)->datos.codigo ) {
			insertarElemento( &(*pArbol)->hijoDerecho, pDatos);
		}else{
			if( pDatos.codigo < (*pArbol)->datos.codigo ) {
				insertarElemento( &(*pArbol)->hijoIzquierdo, pDatos);
			} else {
				/* El valor ya existe */
				printf("Elemento duplicado!\n");
			}	
		}		
	}
}

void recorrerEnPreorden( tArbol * pArbol ) {
	if( !(arbolVacio(pArbol)) ) { // pArbol != NULL
		printf("%d - %s\n", pArbol->datos.codigo, pArbol->datos.descripcion);
		recorrerEnPreorden(pArbol->hijoIzquierdo);
		recorrerEnPreorden(pArbol->hijoDerecho);
	}
}

void recorrerEnPostorden( tArbol * pArbol ) {
	if( !(arbolVacio(pArbol)) ) { // pArbol != NULL	
		recorrerEnPostorden(pArbol->hijoIzquierdo);
		recorrerEnPostorden(pArbol->hijoDerecho);
		printf("%d - %s\n", pArbol->datos.codigo, pArbol->datos.descripcion);
	}
}

void recorrerEnInorden( tArbol * pArbol ) {
	if( !(arbolVacio(pArbol)) ) { // pArbol != NULL	
		recorrerEnInorden(pArbol->hijoIzquierdo);
		printf("%d - %s\n", pArbol->datos.codigo, pArbol->datos.descripcion);
		recorrerEnInorden(pArbol->hijoDerecho);		
	}
}

bool buscarElemento( tArbol * pArbol, int pCodigo ) {
	if( arbolVacio(pArbol) ) {
		return false;		
	} else {
		if( pCodigo > pArbol->datos.codigo ) {
			buscarElemento(pArbol->hijoDerecho, pCodigo);
		}else{
			if( pCodigo < pArbol->datos.codigo ) {
				buscarElemento(pArbol->hijoIzquierdo, pCodigo);
			}else{
				return true;
			}
		}
	}
}

int cantidadNodos( tArbol * pArbol ) {
	if(!arbolVacio(pArbol)) {
		return 	1 
				+ cantidadNodos( pArbol->hijoIzquierdo )
				+ cantidadNodos( pArbol->hijoDerecho );		
	}else{
		return 0;
	}
}

tArbol * buscarMin( tArbol * pArbol ) {
	if( arbolVacio(pArbol)) {
		return NULL;
	} else {
		if( !arbolVacio(pArbol->hijoIzquierdo)) {
			return buscarMin( pArbol->hijoIzquierdo );
		}else {
			return pArbol;
		}
	}	
}

void eliminarElemento( tArbol ** pArbol, int pCodigo ) {
	tArbol * aux;
	
	if( arbolVacio(*pArbol)) {
		// No existe el nodo que se quiere eliminar
		printf("No existe el elemento que se desea eliminar\n");		
	} else {		
		if( pCodigo < (*pArbol)->datos.codigo ) {
			eliminarElemento( &((*pArbol)->hijoIzquierdo) , pCodigo);
		} else {
			if( pCodigo > (*pArbol)->datos.codigo ) {
				eliminarElemento( &((*pArbol)->hijoDerecho) , pCodigo);
			} else {
				// Se encontró el nodo que se desea eliminar
				if( (*pArbol)->hijoIzquierdo == NULL) {
					/* Por acá se eliminaría si es una hoja o si tiene un hijo derecho */
					aux = *pArbol;
					*pArbol = (*pArbol)->hijoDerecho;
					free(aux);
				} else {
					if( (*pArbol)->hijoDerecho == NULL) {
						/* Por acá se eliminaría si tiene un hijo izquierdo */
						aux = *pArbol;
						*pArbol = (*pArbol)->hijoIzquierdo;
						free(aux);
					} else {
						// significa que el nodo por eliminar tiene 2 hijos
						aux = buscarMin( (*pArbol)->hijoDerecho  );
						(*pArbol)->datos = aux->datos;
						eliminarElemento( &((*pArbol)->hijoDerecho) , (*pArbol)->datos.codigo );
					} 										
				}
			}
		}		
	}	
}

