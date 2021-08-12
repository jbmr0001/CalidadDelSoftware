/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Diccionario.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la cabecera de la clase Diccionario
 *
 * Created on 20 de octubre de 2020, 17:23
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include <string>
#include "VDinamico.h"
#include "Palabra.h"
#include "VerbosConjugados.h"

/**
 * @brief Clase que representa un diccionario
 */
class Diccionario {
public:
	Diccionario();
	explicit Diccionario(const std::string &unNombreFich);
	Diccionario(const Diccionario& orig);
	virtual ~Diccionario();
	/////////////////////////FUNCIONES//////////////////////////
	bool buscarDicotomica(Palabra unaPalabra);
	void mostrarDiccionario();
	/////////////////////GETTERS Y SETTERS/////////////////////
	void setNombreFich(const std::string &unNombreFich);
	void setVerbos(const VerbosConjugados &unosVerbosConjugados);
	std::string getNombreFich() const;
	VerbosConjugados getVerbos() const;
	///////////////////FUNCIONES////////////////////
	void leerDiccionario();

private:
	std::string _nombreFich; 		///< Nombre del fichero del diccionario
	VerbosConjugados _verbos;	///< Verbos conjugados que hay en el diccionario
	VDinamico<Palabra> _terminos;	///< Terminos

};

#endif /* DICCIONARIO_H */

