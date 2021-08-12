/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   VerbosConjugados.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar la implementación de la clase Verbos conjugados
 * 
 * Created on 6 de noviembre de 2020, 16:38
 */

#include "VerbosConjugados.h"
#include <fstream>
#include <sstream>
/////////////////////////CONSTRUCTORES///////////////////////

/**
 * @brief Constructor por defecto de la clase VerbosConjugados
 */
VerbosConjugados::VerbosConjugados() :
		_nombreFich("verbos_conjugados_sin_tildes_desordenados.txt") {
	leerVerbos();
}

/**
 * @brief Constructor copia de la clase VerbosConjugados
 *
 * @param [in] orig VerbosConjugados a copiar
 */
VerbosConjugados::VerbosConjugados(const VerbosConjugados& orig) :
		_nombreFich(orig._nombreFich) {
}

/**
 * @brief Destructor de la clase VerbosConjugados
 */
VerbosConjugados::~VerbosConjugados() {
}
//////////////////////////OPERADORES///////////////////////

/**
 * @brief Operador = de la clase VerbosConjugados
 *
 * @param [in] ver Nombre de fichero a igualar
 * @return Devuelve un puntero a el VerbosConjugados actual
 */
VerbosConjugados& VerbosConjugados::operator =(const VerbosConjugados& ver) {
	_nombreFich = ver._nombreFich;
	return *this;
}

///////////////////////GETTERS Y SETTERS/////////////////////////////

/**
 * @brief Método para obtener el nombre del fichero de verbos conjugados
 *
 * @return Devuelve un String con el nombre del fichero
 */
std::string VerbosConjugados::getNombreFich() {
	return this->_nombreFich;
}

/**
 * @brief Método para obtener todos los verbos conjugados
 *
 * @return Devuelve un objeto de la clase AVL con todos los verbos conjugados
 */
AVL<Palabra> VerbosConjugados::getVConjugados() {
	return _vconjugados;
}

/**
 * @brief Método para establecer el nombre del fichero de verbos conjugados
 *
 * @param [in] unNombreFich String con el nombre del fichero
 */
void VerbosConjugados::setNombreFich(const std::string &unNombreFich) {
	this->_nombreFich = unNombreFich;
}

/**
 * @brief Método para establecer el AVL de verbos conjugados
 *
 * @param [in] unVConjugados Un AVL de verbos conjugados
 */
void VerbosConjugados::setVConjugados(AVL<Palabra> unVConjugados) {
	this->_vconjugados = unVConjugados;
}
//////////////////////////FUNCIONES//////////////////////////

/**
 * @brief Método para leer el fichero de verbos e insertarlo en el AVL
 */
void VerbosConjugados::leerVerbos() {
	std::ifstream fe;
	string linea;
	std::string palabra;

	fe.open(getNombreFich()); //abrimos fichero
	if (fe.good()) {
		while (!fe.eof()) { //bucle hasta llegue a la ultima linea
			getline(fe, linea); //leemos la linea
			std::stringstream ss;

			ss << linea;
			getline(ss, palabra); //extraemos la palabra en forma de string de la linea leida
			Palabra pal(palabra); //creamos una Palabra con el string leido
			_vconjugados.insertar(pal);
		}

		fe.close();
	}
}

/**
 * @brief Función para buscaar una palabra en los verbos conjugados
 *
 * @param [in] pal Objeto de tipo palabra a buscar
 * @return Devuelve un boolean que indica si la palabra ha sido encontrada
 */
bool VerbosConjugados::buscar(Palabra pal) {
	Palabra result; //palabra con el resultado encontrado
	if (_vconjugados.buscaIt(pal, result)) {
		return true;
	}
	return false;
}

/**
 * @brief Función para mostrar la altura y número de elementos del AVL
 */
void VerbosConjugados::mostrarAltura() {
	std::cout << "Altura AVL: " << _vconjugados.altura()
			<< " Numero elementos: " << _vconjugados.numElementos()
			<< std::endl;
}
