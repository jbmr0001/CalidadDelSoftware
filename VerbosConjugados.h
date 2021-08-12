/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   VerbosConjugados.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la cabecera de la clase VerbosConjugados
 *
 * Created on 6 de noviembre de 2020, 16:38
 */

#ifndef VERBOSCONJUGADOS_H
#define VERBOSCONJUGADOS_H
#include <string>
#include "AVL.h"
#include "Palabra.h"

/**
 * @brief Clase que representa una clase con todos los verbos conjugados existentes
 */
class VerbosConjugados {
public:
	///////////////////CONSTRUCTORES/////////////////
	VerbosConjugados();
	VerbosConjugados(const VerbosConjugados& orig);
	virtual ~VerbosConjugados();
	/////////////////GETTERSY SETTERS////////////////////
	void setNombreFich(const std::string &unNombreFich);
	void setVConjugados(AVL<Palabra> unVConjugados);
	std::string getNombreFich();
	AVL<Palabra> getVConjugados();
	///////////////////////FUNCIONES////////////////////////
	void leerVerbos();
	bool buscar(Palabra pal);
	void mostrarAltura();
	////////////////////OPERADORES////////////////////////
	VerbosConjugados& operator =(const VerbosConjugados& ver);

private:
	std::string _nombreFich;		///< String que indica el nombre del fichero de verbos conjugados
	AVL<Palabra> _vconjugados;		///< Árbol AVL para almacenar todos los verbos conjugados
};

#endif /* VERBOSCONJUGADOS_H */

