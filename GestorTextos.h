/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   GestorTextos.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la cabecera de la Gestor de Textos
 *
 * Created on 20 de octubre de 2020, 17:57
 */

#ifndef GESTORTEXTOS_H
#define GESTORTEXTOS_H
#include "Diccionario.h"
#include "Documento.h"
#include "VDinamico.h"

/**
 * @brief Clase que representa la Gestión de diferentes Documentos
 */
class GestorTextos {
public:
	//////////////////CONSTRUCTORES/////////////////
	GestorTextos();
	GestorTextos(const GestorTextos& orig);
	virtual ~GestorTextos();
	//////////////////GETTERS Y SETTERS/////////////
	Diccionario getDiccionario() const;
	/////////////////FUNCIONES////////////////
	void addDocumento(std::string nombreFich);
	Documento buscarDocumento(std::string nombreFich);
	VDinamico<Documento> getDocumentos();

private:
	Diccionario _diccionario;///< Diccionario que utilizará el gestor de documentos
	VDinamico<Documento> _documentos;	///< Documentos que hay que gestionar

};

#endif /* GESTORTEXTOS_H */

