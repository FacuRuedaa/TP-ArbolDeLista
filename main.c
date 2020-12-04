#include <stdio.h>
#include <stdlib.h>
#include "listaSimple.h"
#include "registroArchivo.h"

typedef struct {
    int idEspecialidad;
    char especialidadMedica[30];
    nodo* listaDePacientes;
    struct nodoArbol *der;
    struct nodoArbol *izq;
} nodoArbol;

nodoArbol* inicArbol ();
nodoArbol* crearNodoArbol (int nroEsp, char especialidad[]);
nodoArbol* buscarDatoArbol (nodoArbol* arbol, int nroEsp);
nodoArbol* agregarArbol (nodoArbol* arbol, int nroEsp, char especialidad[]);
nodoArbol* alta (nodoArbol* arbol, nodo* nuevoPaciente, int nroEsp, char especialidad[]);
void preorder (nodoArbol* arbol);
nodoArbol* pasarArchToArbol (char archivo[], nodoArbol* arbol);

int main()
{
    nodoArbol* arbolDePacientes = inicArbol();

    arbolDePacientes = pasarArchToArbol(arRegistro, arbolDePacientes);

    preorder(arbolDePacientes);

    return 0;
}


nodoArbol* inicArbol (){
    return NULL;
}

nodoArbol* crearNodoArbol (int nroEsp, char especialidad[]){
    nodoArbol* aux = (nodoArbol*) malloc(sizeof(nodoArbol));

    aux->idEspecialidad = nroEsp;
    strcpy(aux->especialidadMedica, especialidad);
    aux->listaDePacientes = inicLista();
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbol* buscarDatoArbol (nodoArbol* arbol, int nroEsp){
    nodoArbol* rta = NULL;
    if (arbol){
        if (nroEsp == arbol->idEspecialidad){
            rta = arbol;
        } else if (nroEsp > arbol->idEspecialidad){
            rta = buscarDatoArbol(arbol->der, nroEsp);
        } else {
            rta = buscarDatoArbol(arbol->izq, nroEsp);
        }
    }
    return rta;
}

nodoArbol* agregarArbol (nodoArbol* arbol, int nroEsp, char especialidad[]){
    if (arbol == NULL){
        arbol = crearNodoArbol(nroEsp, especialidad);
    } else{
        if (nroEsp > arbol->idEspecialidad){
            arbol->der = agregarArbol(arbol->der, nroEsp, especialidad);
        } else {
            arbol->izq = agregarArbol(arbol->izq, nroEsp, especialidad);
        }
    }
    return arbol;
}

nodoArbol* alta (nodoArbol* arbol, nodo* nuevoPaciente, int nroEsp, char especialidad[]){
    nodoArbol* arbolEncontrado = buscarDatoArbol(arbol, nroEsp);

    if (arbolEncontrado==NULL){
        arbol = agregarArbol(arbol, nroEsp, especialidad);
        arbol->listaDePacientes= agregarAlFinal(arbol->listaDePacientes, nuevoPaciente);
    } else {
        if (nroEsp == arbol->idEspecialidad){
            arbolEncontrado->listaDePacientes = agregarAlFinal(arbolEncontrado->listaDePacientes, nuevoPaciente);
        } else if (nroEsp > arbol->idEspecialidad) {
            arbol->der = alta(arbol->der, nuevoPaciente, nroEsp, especialidad);
        } else {
            arbol->izq = alta(arbol->izq, nuevoPaciente, nroEsp, especialidad);
        }
    }

    return arbol;
}

void preorder (nodoArbol* arbol){
    if(arbol!=NULL){
        printf("\n----------------------------\n");
        printf("ID...:%d\n", arbol->idEspecialidad);
        printf("ESPECIALIDAD....: %s\n", arbol->especialidadMedica);
        printf("----------------------------\n");
        muestraLista(arbol->listaDePacientes);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

nodoArbol* pasarArchToArbol (char archivo[], nodoArbol* arbol){
    FILE *pArchPacientes = fopen(archivo, "rb");

    if (pArchPacientes){
        stRegistroMedico aux;
        stPaciente pacienteAux;
        while (fread(&aux, sizeof(stRegistroMedico), 1, pArchPacientes)>0){
            pacienteAux.idPaciente = aux.idPaciente;
            strcpy(pacienteAux.apellidoPaciente, aux.apellidoPaciente);
            strcpy(pacienteAux.nombrePaciente, aux.nombrePaciente);
            strcpy(pacienteAux.diagnostico, aux.diagnostico);
            strcpy(pacienteAux.fechaAtencion, aux.fechaAtencion);
            strcpy(pacienteAux.nombreDoctor, aux.nombreDoctor);
            nodo* paciente = crearNodo(pacienteAux);
            arbol = alta(arbol, paciente, aux.idEspecialidad, aux.especialidadMedica);
        }
        fclose(pArchPacientes);
    }
    return arbol;
}
