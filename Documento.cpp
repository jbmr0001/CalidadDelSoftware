/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   Documento.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar la implementación de la clase Documento.
 *
 * Created on 20 de octubre de 2020, 17:57
 */

#include "Documento.h"
#include <string>
#include <iostream>
#include "Palabra.h"
#include "VerbosConjugados.h"
#include <fstream>
//////////////////////////CONSTRUCTORES/////////////////////

/**
 * @brief Constructor por defecto de la clase Documento
 */
Documento::Documento() :
		_nombreFich(""), _inexistentes(), _dicc("dicc-espanol-sin.txt") {
}

/**
 * @brief Constructor parametrizado de la clase Documento
 *
 * @param [in] unNombreFich Nombre del documento
 */
Documento::Documento(const std::string &unNombreFich) :
		_nombreFich(unNombreFich), _inexistentes(), _dicc(
				"dicc-espanol-sin.txt") {
}

/**
 * @brief Constructor copia de la clase Documento
 *
 * @param [in] orig Documento que queremos copiar
 */
Documento::Documento(const Documento& orig) :
		_nombreFich(orig._nombreFich), _inexistentes(orig._inexistentes), _dicc(
				orig._dicc) {
}

/**
 * @brief Destructor de la clase Documento
 */
Documento::~Documento() {
}
/////////////////////////GETTERS Y SETTERS///////////////////////////

/**
 * @brief Método para obtener el nombre del documento
 *
 * @return El nombre del documento
 */
std::string Documento::getNombreFich() {
	return this->_nombreFich;
}

/**
 * @brief Método para obtener el diccionario que se le aplica al Documento
 *
 * @return Un objeto de la clase Diccionario siendo este el Diccionario que se le aplica al Documento
 */
Diccionario Documento::getDiccionario() {
	return this->_dicc;
}

/**
 * @brief Método para obtener las palabras que no están en el diccionario
 *
 * @return Una lista enlazada con todas las palabras que no aparecen en el documento
 */
ListaEnlazada<Palabra> Documento::getInexistentes() {
	return this->_inexistentes;
}

/**
 * @brief Método para modificar el nombre del fichero
 *
 * @param [in] unNombreFich Nombre del fichero
 */
void Documento::setNombreFich(const std::string &unNombreFich) {
	this->_nombreFich = unNombreFich;
}

/**
 * @brief Método para modificar el diccionario a aplicar en el Documento
 *
 * @param [in] unDiccionario Nuevo Diccionario del documento
 */
void Documento::setDiccionario(const Diccionario &unDiccionario) {
	this->_dicc = unDiccionario;
}

/////////////////////OPERADORES///////////////////

/**
 * @brief Operador de asignación
 *
 * @param [in] doc Documento del que queremos copiar sus datos
 * @return El mismo objeto pero copiado
 */
Documento& Documento::operator =(const Documento& doc) {
	_nombreFich = doc._nombreFich;
	//_inexistentes=doc._inexistentes;
	_dicc = doc._dicc;
	return *this;
}

/////////////////////////FUNCIONES//////////////////////////////

/**
 * @brief Método para mostrar las palabras que no aparecen en el diccionario
 */
void Documento::MostrarInexistentes() { //Se recorre con in iterador la lista y la mostramos
	ListaEnlazada<Palabra>::Iterador<Palabra> it = _inexistentes.iterador();
	int contador = 0;
	while (it.haySiguiente()) {
		std::cout << contador << ": " << it.nodo->dato.getPalabra()
				<< std::endl;
		it.siguiente();
		contador++;
	}
}

/**
 * @brief Método para insertar una Palabra en la lista de palabras inexistentes
 *
 * @param [in] p Palabra que se quiere añadir a la lista enlazada
 */
void Documento::addInexistente(Palabra p) {
	_inexistentes.insertaOrdenado(p);

}

/**
 * @brief Método para chequear el texto del Documento
 */
void Documento::chequearTexto() {
	_dicc.setNombreFich("dicc-espanol-sin.txt");
	_dicc.leerDiccionario(); //función para cargar la palabras del diccionario
	VerbosConjugados v; //variable auxiliar para asignarle losverbos
	std::fstream fe;
	string palabra;
	fe.open(getNombreFich()); //abrimos flujo de lectura de fichero

	while (fe >> palabra) { //leemos cada palabra en formato de string
		Palabra pal(palabra);
		pal.limpiar(); //la mandamos a limpiarse de signos no alfabéticos solo en caso de leer quijote2.txt
		v = _dicc.getVerbos();
		if (!_dicc.buscarDicotomica(pal) && !v.buscar(pal)) { //en caso de no encontrar la palabra en el diccionario la insertamos
			addInexistente(pal);
		}
	}
	// Cerramos el archivo
	fe.close();
	_inexistentes.borrarRepetidos(); //funcion imlementada para borrar repetidos
	//MostrarInexistentes();
	std::cout << std::endl << "TamaÃ±o inexistentes: " << _inexistentes.tama()
			<< std::endl;    //Mostramos el tamaño de la lista
	v.mostrarAltura();
	borrarNombresPropios();
}

/**
 * @brief Método para borrar los nombres propios y las palabras que cambiando la primera letra minúsculas se encuentran en el diccionario
 */
void Documento::borrarNombresPropios() {
	ListaEnlazada<Palabra>::Iterador<Palabra> it = _inexistentes.iterador(); //creamos un iterador
	VerbosConjugados v;    //variable auxiliar para asignarle losverbos
	while (it.haySiguiente()) {    //recorremos todala lista
		v = _dicc.getVerbos();
		Palabra pal(it.nodo->dato.getPalabra()); //creamos una palabra auxiliar con la palabra obtenida del iterador
		if (pal.primeraLetraEsMayus()) { //en caso de ser un nombre propio ya que no se encentra en el diccionario y tiene la primera mayus
			pal.convertirPrimeraLetraMinuscula(); //pasamos su primera letara a minuscula
			if (!_dicc.buscarDicotomica(pal) && !v.buscar(pal)) {
				_inexistentes.borrar(it);    //se borra
			}
		}
		it.siguiente();
	}
	std::cout << "Tamaño tras borrado de nombres propios: "
			<< _inexistentes.tama() << std::endl;
}
