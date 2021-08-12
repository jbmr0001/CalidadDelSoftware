/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   GestorTextos.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar la implementaci�n del Gestor de Textos
 * 
 * Created on 20 de octubre de 2020, 17:57
 */

#include "GestorTextos.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Palabra.h"
#include "Diccionario.h"
#include "ListaEnlazada.h"
#include <bits/stdc++.h>
#include <locale>
#include "Documento.h"
#include "VDinamico.h"

/////////////////////CONSTRUCTORES/////////////////

/**
 * @brief Constructor por defecto de la clase GestorTextos
 */
GestorTextos::GestorTextos() :
		_documentos() {
}

/**
 * @brief Constructor parametrizado de la clase GestorTextos
 *
 * @param [in] orig Gestor de documentos que queremos copiar
 */
GestorTextos::GestorTextos(const GestorTextos& orig) :
		_documentos(orig._documentos) {
}

/**
 * @brief Destructor de la clase GestorTextos
 */
GestorTextos::~GestorTextos() {
}

////////////////////////////GETTERS Y SETTERS/////////////////////

/**
 * @brief M�todo para obtener el diccionario que se utiliza en el Gestor de Documentos
 *
 * @return Un objeto de la clase Diccionario siendo este el diccionario que utiliza el Gestor de Documentos
 */
Diccionario GestorTextos::getDiccionario() const {
	return _diccionario;
}

/**
 * @brief M�todo para obtener los documentos que est� Gestionando el gestor
 *
 * @return Todos los documentos del gestor en un Vector din�mico
 */
VDinamico<Documento> GestorTextos::getDocumentos() {
	return _documentos;
}

////////////////////////////FUNCIONES////////////////////////////

/**
 * @brief M�todo para a�adir un nuevo documento al Gestor de Documentos
 *
 * @param [in] nombreFich Nombre del documento a a�adir
 */
void GestorTextos::addDocumento(std::string nombreFich) {
	Documento doc(nombreFich);
	_documentos.insertar(doc);

}
