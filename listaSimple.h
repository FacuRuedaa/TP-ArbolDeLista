#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11];
    char nombreDoctor[30];
}stPaciente;

typedef struct _nodo {
   stPaciente dato;
   struct _nodo *siguiente;
} nodo;

nodo* inicLista();
nodo* crearNodo(stPaciente dato);
nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo);
void muestraUnPaciente (stPaciente a);
void muestraNodo(nodo *nodo);
void muestraLista(nodo* lista);
nodo* buscarUltimo(nodo* lista);
nodo* agregarAlFinal(nodo* lista, nodo* nuevo);
nodo* borrarLista(nodo* lista);
nodo* eliminarPrimerNodo(nodo* lista);
int cuentaLista(nodo* lista);
stPaciente verPrimero(nodo* lista);
int buscarPaciente(nodo* lista, char nombre[], char apellido[]);

#endif // LISTA_H_INCLUDED
