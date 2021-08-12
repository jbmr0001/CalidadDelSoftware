/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Palabra.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la cabecera de la Palabra
 *
 * Created on 11 de octubre de 2020, 19:00
 */

#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include "VDinamico.h"


/**
 * @brief Clase que representa una palabra
 */
class Palabra {
public:
	//////////////////////CONSTRUCTORES////////////////////////////
	Palabra();
	explicit Palabra(const std::string &unaPalabra);
	Palabra(const Palabra& orig);
	~Palabra();
	/////////////////////FUNCIONES///////////////////////////
	Palabra reves();
	void reves(std::string pal);
	bool anagrama(Palabra pal);
	bool palindromo(Palabra pal);
	VDinamico<Palabra> getCombinaciones();
	void limpiar();
	void convertirPrimeraLetraMinuscula();
	bool primeraLetraEsMayus();
	////////////////////////GETTERS Y SETTERS//////////////////
	void setPalabra(const std::string &unaPalabra);
	std::string getPalabra();
	////////////////////////OPERADORES/////////////////////
	bool operator<(const Palabra& pal) const;
	bool operator>(const Palabra& pal) const;
	bool operator==(const Palabra& pal) const;
	bool operator!=(const Palabra& pal) const;
	bool operator<=(const Palabra& pal) const;
	bool operator>=(const Palabra& pal) const;

private:
	std::string _palabra;		///< String con el contenido de la palabra

};

#endif /* PALABRA_H */

