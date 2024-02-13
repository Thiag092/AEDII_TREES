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

}

int cantidadNodos( tArbol * pArbol ) {

}

tArbol * buscarMin( tArbol * pArbol ) {

		
}

void eliminarElemento( tArbol ** pArbol, int pCodigo ) {
	
}

