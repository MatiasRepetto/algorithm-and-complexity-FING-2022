/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include <cstddef>

bool tieneParEstudiante(nat estudiante, Asignacion lstAsig){
  Asignacion auxAsig = copia_asignacion(lstAsig);
  bool existe = false;
  nat aux = cantidad(auxAsig);
  while(aux > 0 && !existe){
    if(eid(primer_par(auxAsig)) == estudiante){
      existe = true;
    }
    auxAsig = resto_pares(auxAsig);
    aux = aux - 1;
  }
  return existe;
}

par encontrarParEstudiante(nat estudiante, Asignacion lstAsig){
  par response;
  Asignacion auxAsig = copia_asignacion(lstAsig);
  bool existe = false;
  nat aux = cantidad(auxAsig);
  while(aux > 0 && !existe){
    if(eid(primer_par(auxAsig)) == estudiante){
      existe = true;
      response = primer_par(auxAsig);
    }
    auxAsig = resto_pares(auxAsig);
    aux = aux - 1;
  }
  return response;
}

Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{ 
  Asignacion responseAsignacion = crear_asignacion();

  nat cantidadPares = 0;
  nat counterBool = 0;
  for(nat i = 0; i <= m; i++){
    counterBool = counterBool + C[i];
  }
   
  nat h = 0;
  while(cantidadPares < counterBool){
    nat e = hPrefs[h][hPrefs[h][h++]];
    if(!tieneParEstudiante(e, responseAsignacion)){
      par aux;
      aux.eid = e;
      aux.hid = h;
      insertar_par(aux, responseAsignacion);
      C[h] = C[h]-1;
      cantidadPares = cantidadPares + 1;
    }else{
      par auxiliarProposicion = encontrarParEstudiante(e, responseAsignacion);
      bool esMejorProposicion = false;
      for(nat i = 0; i<=m ; i++){
        if(ePrefs[e][i] == hid(auxiliarProposicion)){
          esMejorProposicion = false; break;
        }
        if(ePrefs[e][i] == h){
          esMejorProposicion = true; break;
        }
      }
      if(esMejorProposicion){
        par aux2;
        aux2.eid = e;
        aux2.hid = h;
        C[hid(auxiliarProposicion)] = C[hid(auxiliarProposicion)]+1;
        remover_par(auxiliarProposicion, responseAsignacion);
        insertar_par(aux2, responseAsignacion);
      }
    }
    
  } 
    
  return responseAsignacion; // se debe retornar algo de tipo asignacion
}
