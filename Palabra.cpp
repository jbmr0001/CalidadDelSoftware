/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Palabra.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar la implementaci�n de Palabra
 * 
 * Created on 11 de octubre de 2020, 19:00
 */

#include "Palabra.h"
#include <string>
#include <stdlib.h> 
#include <iostream>
#include <algorithm>
#include "VDinamico.h"
#include <bits/stdc++.h>
#include <locale>
#include <stdexcept>
////////////////////////////////CONSTRUCORES///////////////////////////


/**
 * @brief Constructor por defecto de la clase Palabra
 */
Palabra::Palabra() :
		_palabra("") {
}

/**
 * @brief Constructor parametrizado de la clase Palabra
 *
 * @param [in] unaPalabra String con el contenido de la palabra
 */
Palabra::Palabra(std::string const &unaPalabra) :
		_palabra(unaPalabra) {
}

/**
 * @brief Constructor copia de la clase Palabra
 *
 * @param [in] orig Palabra a copiar
 */
Palabra::Palabra(const Palabra& orig) :
		_palabra(orig._palabra) {
}

/**
 * @brief Desctructor de la clase Palabra
 */
Palabra::~Palabra() {
}

///////////////GETTERS Y SETTERS//////////////

/**
 * @brief Funci�n para obtener el contenido de la palabra
 *
 * @return Devuelve un String con el contenido de la palabra
 */
std::string Palabra::getPalabra() {
	return this->_palabra;
}

/**
 * @brief Funci�n para establecer el contenido de la palabra
 *
 * @param [in] unaPalabra String a establecer como contenido de la palabra
 */
void Palabra::setPalabra(const std::string &unaPalabra) {
	this->_palabra = unaPalabra;
}
///////////////OPERADORES//////////////////

/**
 * @brief Operador < de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra es menor a la comparada
 */
bool Palabra::operator <(const Palabra& pal) const {
	return (_palabra < pal._palabra);
}

/**
 * @brief Operador > de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra es mayor a la comparada
 */
bool Palabra::operator>(const Palabra& pal) const {
	return (_palabra > pal._palabra);
}

/**
 * @brief Operador == de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra es igual a la comparada
 */
bool Palabra::operator ==(const Palabra& pal) const {
	return (_palabra == pal._palabra);
}

/**
 * @brief Operador != de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra no es igual a la comparada
 */
bool Palabra::operator!=(const Palabra& pal) const {
	return (_palabra != pal._palabra);
}

/**
 * @brief Operador <= de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra es menor o igual a la comparada
 */
bool Palabra::operator<=(const Palabra& pal) const {
	return (_palabra <= pal._palabra);
}

/**
 * @brief Operador >= de la clase Palabra
 *
 * @param [in] pal Palabra con la que comparar
 * @return Devuelve un boolean que indica si la palabra es mayor o igual a la comparada
 */
bool Palabra::operator>=(const Palabra& pal) const {
	return (_palabra >= pal._palabra);
}
///////////////FUNCIONES////////////////////

/**
 * @brief M�todo para poner al rev�s la palabra
 *
 * @return Devuelve un objeto de tipo palabra con la palabra al rev�s
 */
Palabra Palabra::reves() {
	std::string pal = "";
	Palabra palabra;
	int i = _palabra.length() - 1;
	while (i >= 0) {
		pal += _palabra[i];
		i--;
	}
	palabra.setPalabra(pal);
	return palabra;
}

/**
 * @brief M�todo para poner al reves una palabra pasada como parametro y asignarla
 *
 * @param pal Palabra que queremos poner como al rev�s
 * @return Devuelve el resultado de la palabra
 */
void Palabra::reves(std::string pal) {
	if(pal!=""){
		std::string aux = "";
		int i = pal.length() - 1;
		while (i >= 0) {
			aux += pal[i];
			i--;
		}
		this->setPalabra(aux);
	}
}

/**
 * @brief M�todo para saber si la palabra es pal�ndromo
 *
 * @param [in] pal Palabra a comprobar
 * @return Devuelve un boolean que indica si la palabra es pal�ndroma
 */
bool Palabra::palindromo(Palabra pal) {
	if(pal.getPalabra()!=""){
		if (_palabra == pal.reves()._palabra) {
			return true;
		}
	}
	return false;

}

/**
 * @brief M�todo para calcular todas las combinaciones con las letras de una palabra
 *
 * @return Devuelve un Vector Din�mico de palabras con todas las posibles combinaciones
 */
VDinamico<Palabra> Palabra::getCombinaciones() { //metodo mas eficiente
	VDinamico<Palabra> vPalabra;
	std::string aux = "";
	for (unsigned int i = 0; i < _palabra.length(); i++) { //pasamos cada letra de la palabra al vector
		aux.push_back(_palabra[i]); //conversion de char a string
		Palabra letra(aux); //creamos la palabra y la insertamos en el vectordinamico de palabras
		vPalabra.insertar(letra);
	}
	vPalabra.ordenar(); //ordenamos el vector, necesario para los anagramas
	return vPalabra;
}

/**
 * @brief M�todo que devuelve si dos palabras son anagramas
 *
 * @param [in] pal Palabra con la que comparar
 * @return Boolean que indica sin son anagramas
 */
bool Palabra::anagrama(Palabra pal) { //comparamos dos vectores de letras ordenados alfabéticamente
	VDinamico<Palabra> aux1 = this->getCombinaciones(); //se obtienen los vectores de palabras ordenados
	VDinamico<Palabra> aux2 = pal.getCombinaciones();
	bool anagrama = true;
	if (aux1.tam() == aux2.tam()) { //se comparan las dos palabras comparando cada posicion del vector ordenado
		for (unsigned int i = 0; i < this->getCombinaciones().tam(); i++) {
			if (aux1[i]._palabra != aux2[i]._palabra) {
				return false; //si todas las palabras de cada posición son iguales-> anagrama
			}
		}
	} else {
		return false;
	}
	return anagrama;
}

/**
 * @brief M�todo para quitar los s�mbolos no alfab�ticos de una palabras
 */
void Palabra::limpiar() {
	VDinamico<char> ca; //vector dinamico donde se almacenará la nueva palabra troceada
	char a = '�'; //para evitar que catalogue la ñ como no alfabética
	char car[_palabra.length()]; //array de char de la longuitud de palabra
	strcpy(car, _palabra.c_str()); //las ñ se insertan como n

	for (unsigned int i = 0; i < _palabra.length(); i++) { //recorremos toda la palabra y solo almecenamos las letras alfabéticas y las ñ
		if (isalpha(car[i])) {
			ca.insertar(car[i]);
		}
		if (car[i] == a) { //ñ
			//if(!isalpha(car[i+1])){
			ca.insertar(car[i]);
			//}
		}
	}

	string s = "";
	for (unsigned int i = 0; i < ca.tam(); i++) { //conversií de vector dinámico a string
		s = s + ca[i];
	}
	this->_palabra = s;

}

/**
 * @brief M�todo para convertir en min�scula la primera letra de la palabra
 */
void Palabra::convertirPrimeraLetraMinuscula() {
	char car[_palabra.length()]; //array de char de la misma longitud que la palabra
	strcpy(car, _palabra.c_str());      //conversión de palabra a array de char

	try{
		car[0] = tolower(car[0]); //convertimos a minúscula
	}catch (const std::out_of_range& oor) {
	    std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	string s = "";           //string auxiliar onde se irá guardando la palabra
	for (unsigned int i = 0; i < _palabra.length(); i++) {
		s = s + car[i];
	}
	this->_palabra = s;
}

/**
 * @brief M�todo para comprobar si la primera letra es may�scula
 *
 * @return Boolean que indica si la primera letra es may�scula
 */
bool Palabra::primeraLetraEsMayus() {
	char car[_palabra.length()];
	strcpy(car, _palabra.c_str());
	bool m = false;

	try{
		if (isupper(car[0])) {
			m = true;
		}
	}catch (const std::out_of_range& oor) {
	    std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	return m;
}

