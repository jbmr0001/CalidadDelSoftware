/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Documento.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la cabecera de la clase Documento.
 *
 * Created on 20 de octubre de 2020, 17:57
 */

#ifndef DOCUMENTO_H
#define DOCUMENTO_H
#include <string>
#include "Palabra.h"
#include "ListaEnlazada.h"
#include <string>
#include "Diccionario.h"

/**
 * @brief Clase que representa un documento a gestionar
 */
class Documento {
public:
    //////////////////CONSTRUCTORES//////////////
    Documento();
    explicit Documento(const std::string &unNombreFich);
    Documento(const Documento& orig);
    virtual ~Documento();
    /////////////////GETTERS Y SETTERS///////////
    std::string getNombreFich();
    Diccionario getDiccionario();
    ListaEnlazada<Palabra> getInexistentes();
    void setNombreFich(const std::string &unNombreFich);
    void setDiccionario(const Diccionario &unDiccionario);
    ////////////////FUNCIONES////////////////
    void MostrarInexistentes();
    void addInexistente(Palabra p);
    void chequearTexto();
    void borrarNombresPropios();
    //////////////OPERADORES///////////////////
    Documento& operator=(const Documento& doc);
private:
    std::string _nombreFich;				///< Nombre del documento
    ListaEnlazada<Palabra> _inexistentes;	///< Palabras que no contiene el diccionario
    Diccionario _dicc;						///< Diccionario

};

#endif /* DOCUMENTO_H */

