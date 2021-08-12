/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Diccionario.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar la implementacion de Diccionario
 * 
 * Created on 20 de octubre de 2020, 17:23
 */

#include "Diccionario.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "Palabra.h"

///////////////////////CONSTRUCTORES///////////////////
/**
 * @brief Contructor de la clase Diccionario
 */
Diccionario::Diccionario() :
		_nombreFich(""), _terminos() {
}

/**
 * @brief Constructor parametrizado de la clase Diccionario
 *
 * @param [in] unNombreFich ruta en la que se encuentra el diccionario
 */
Diccionario::Diccionario(const std::string &unNombreFich) :
		_nombreFich(unNombreFich), _terminos() {
}

/**
 * @brief Constructor copia de la clase Diccionario
 *
 * @param [in] orig Diccionario que queremos copiar
 */
Diccionario::Diccionario(const Diccionario& orig) :
		_nombreFich(orig._nombreFich) {
}

/**
 * @brief Destructor de la clase Diccionario
 */
Diccionario::~Diccionario() {
}
/////////////////////////FUNCIONES/////////////////////7

/**
 * @brief Función para mostrar todos los términos que hay dentro del diccionario
 */
void Diccionario::mostrarDiccionario() {
	for (unsigned int i = 0; i < _terminos.tam(); i++) {
		std::cout << _terminos[i].getPalabra() << std::endl;
	}

}

/**
 * @brief Función que realiza una búsqueda binaria para encontrar una palabra
 *
 * @param [in] unaPalabra Palabra que queremos encontrar
 * @return True si se encuentra la palabra o False en caso contrario
 */
bool Diccionario::buscarDicotomica(Palabra unaPalabra) {
	if (_terminos.busquedaBin(unaPalabra) < 79423) { //79423 maximo de palabras que alcanza el diccionario
		return true;
	}
	return false;
}
////////////////////GETTERS Y SETTERS//////////////////

/**
 * @brief Método para modificar el nombre del fichero
 *
 * @param [in] unNombreFich Nombre nuevo del fichero
 */
void Diccionario::setNombreFich(const std::string &unNombreFich) {
	this->_nombreFich = unNombreFich;
}

/**
 * @brief Método para modificar los verbos conjugados del Diccionario
 *
 * @param [in] unosVerbosConjugados Nuevos verbos conjugados del Diccionario
 */
void Diccionario::setVerbos(const VerbosConjugados &unosVerbosConjugados) {
	this->_verbos = unosVerbosConjugados;
}

/**
 * @brief Método para obtener el nombre del Diccionario
 *
 * @return El nombre del Diccionario
 */
std::string Diccionario::getNombreFich() const {
	return _nombreFich;
}

/**
 * @brief Método para obtener los verbos conjugados del Diccionario
 *
 * @return Los verbos conjugados del Diccionario
 */
VerbosConjugados Diccionario::getVerbos() const {
	return _verbos;
}

/**
 * @brief Método para leer el diccionario
 *
 * El diccionario se lee mediante un buffer de lectura de ficheros carga cada palabra en el VDinamico de palabras
 */
void Diccionario::leerDiccionario() {
	std::ifstream fe;
	string linea;
	std::string palabra;

	fe.open(getNombreFich()); //abrimos fichero
	if (fe.good()) {
		int total = 0;
		while (!fe.eof()) { //bucle hasta llegue a la ultima linea
			getline(fe, linea); //leemos la lÃ­nea
			std::stringstream ss;

			++total;
			ss << linea;
			getline(ss, palabra); //extraemos la palabra en forma de string de la lÃ­nea leida
			Palabra pal(palabra); //creamos una Palabra con el string leido
			_terminos.insertar(pal);
		}
		std::cout << "Palabras leidas diccionario: " << total << std::endl;
		std::cout << "TamaÃ±o diccionario: " << _terminos.tam() << std::endl;
		fe.close();
	}
}
