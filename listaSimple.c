#include "listaSimple.h"
#include <string.h>

nodo* inicLista(){
    return NULL;
}

nodo* crearNodo(stPaciente dato){
    nodo* nuevo = (nodo*) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    return nuevo;
}

nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo){
    if(lista==NULL){
        lista = nuevoNodo;
    }else{
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

void muestraUnPaciente (stPaciente a)
{
    printf("-----------------------------\n");
    printf("\nID DEL PACIENTE:...: %d", a.idPaciente);
    printf("\nNOMBRE.............: %s", a.nombrePaciente);
    printf("\nAPELLIDO...........: %s", a.apellidoPaciente);
    printf("\nDIAGNOSTICO........: %s", a.diagnostico);
    printf("\nFEHCA ATENCION.....: %s", a.fechaAtencion);
    printf("\nNOMBRE DOCTOR......: %s", a.nombreDoctor);
}

void muestraNodo(nodo *nodo){
    printf("\n nodo: %p - nodo->siguiente: %p\n",  nodo, nodo->siguiente);
    muestraUnPaciente(nodo->dato);
}

void muestraLista(nodo* lista){
    nodo* seg = lista;
    while(seg){  /// while(lista!=NULL)
        muestraNodo(seg);
        seg = seg->siguiente;
    }
}

nodo* buscarUltimo(nodo* lista){
    nodo* seg = lista;
    while(seg->siguiente!=NULL){
        seg = seg->siguiente;
    }

    return seg;
}

int buscarPaciente(nodo* lista, char nombre[], char apellido[]){
    nodo* seg = lista;
    int flag = 0;
    while(seg && flag == 0){
        if (strcmp(nombre, seg->dato.nombrePaciente) == 0 && strcmp(apellido, seg->dato.apellidoPaciente) == 0){
            flag = 1;
        }
        seg = seg->siguiente;
    }
    return flag;
}

nodo* agregarAlFinal(nodo* lista, nodo* nuevo){
    if(lista==NULL){
        lista = nuevo;
    }else{
        nodo* ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevo;
    }
    return lista;
}

nodo* borrarLista(nodo* lista){
    nodo* proximo;
    nodo* seg = lista;
    while(seg){
        proximo = seg->siguiente;
        free(seg);
        seg = proximo;
    }
    return seg;
}

nodo* eliminarUltimoNodo(nodo* lista){
    nodo* aux = lista;
    nodo* ante;
    while(aux->siguiente){    /// es igual a while(aux->siguiente != NULL)
        ante = aux;
        aux=aux->siguiente;
    }
    free(aux);
    ante->siguiente=NULL;
    return lista;
}

nodo* eliminarPrimerNodo(nodo* lista){
    nodo* aux=lista;
    lista=lista->siguiente;
    free(aux);
    return lista;
}

int cuentaLista(nodo* lista){
    nodo* seg=lista;
    int cont=0;
    while(seg){
        cont++;
        seg = seg->siguiente;
    }
    return cont;
}

stPaciente verPrimero(nodo* lista){
    return lista->dato;
}
