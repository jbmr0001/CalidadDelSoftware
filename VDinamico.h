/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   VDinamico.h
 * @author: Juan Bautista
 * @brief Fichero que almacenará la clase del vector dinámico
 *
 * Created on 11 de octubre de 2020, 18:22
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

using std::string;
#include <climits>
#include <algorithm>


/**
 * @brief Clase que representa un vector dinámico
 */
template<typename T>
class VDinamico {
public:
	/////////////////CONSTRUCTORES////////////////////
	VDinamico();
	explicit VDinamico(unsigned long int tam);
	VDinamico(const VDinamico<T>& origen);
	VDinamico(const VDinamico<T>& origen, unsigned int inicio,
			unsigned int num);
	~VDinamico();
	////////////////OPERADORES//////////////////////
	VDinamico &operator=(const VDinamico<T>& origen);
	T& operator[](unsigned long int pos);
	////////////////FUNCIONES/////////////////////////
	void insertar(const T& dato, unsigned long int pos = UINT_MAX);
	T borrar(unsigned long int pos = UINT_MAX);
	void ordenar();
	void ordenarRev();
	unsigned int busquedaBin(T const &dato);

	unsigned int tam();
	int potenciador(unsigned long int tama);
	void aumenta();
	void disminuye();
private:
	unsigned long int _tamal; ///< Entero que representa el tamaño lógico del vector dinámico
	unsigned long int _tamaf; ///< Entero que representa el tamaño físico del vector dinámico
	T *_v;		///< Puntero de tipo T sobre el que se irá guardando el vector
};

//////////////////////////CONSTRUCTORES//////////////////////////

/**
 * @brief Constructor por defecto de la clase VDinamico
 */
template<typename T>
VDinamico<T>::VDinamico() :
		_tamal(0), _tamaf(1) {
	_v = new T[_tamaf];
}

/**
 * @brief Destructor de la clase VDinamico
 */
template<typename T>
VDinamico<T>::~VDinamico() {
	delete[] _v;
}

/**
 * @brief Constructor de la clase VDinamico dado un tamaño lógico
 *
 * @param [in] tam Entero con el tamaño lógico
 */
template<typename T>
VDinamico<T>::VDinamico(unsigned long int tam) :
		_tamal(0), _tamaf(potenciador(tam)) {
	_v = new T[_tamaf];
}

/**
 * @brief Constructor copia de la clase VDinamico
 *
 * @param [in] origen VDinamico a copiar
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen) :
		_tamal(origen._tamal), _tamaf(origen._tamaf)
{
	_v = new T[_tamaf];
	for (unsigned long int i = 0; i < origen._tamal; i++) {
		_v[i] = origen._v[i];
	}
}

/**
 * @brief Constructor copia parcial de la clase VDinamico
 *
 * @param [in] origen VDinamico del que copiar
 * @param [in] inicio Entero con la posición inicial de copia
 * @param [in] num Entero con el número elementos a copiar
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned int inicio,
		unsigned int num) : //constructor copia parcial
		_tamal(num), _tamaf(potenciador(num)) {
	_v = new T[_tamaf];
	for (int i = 0; i < _tamal; i++) {
		_v[i - inicio] = origen._v[i];
	}
}

//////////////////////OPERADORES/////////////////////

/**
 * @brief Operador = de la clase VDinamico
 *
 * @param [in] origen VDinamico a copiar
 * @return Devuelve un puntero al VDinamico actual ya copiado
 */
template<typename T>
VDinamico<T>& VDinamico<T>::operator =(const VDinamico<T>& origen) {
	if(this != &origen){
		if (_v) {
			delete[] _v;
			_tamal = origen._tamal;
			_v = new T[_tamaf = origen._tamaf];
			for (unsigned long int i = 0; i < _tamal; i++) {
				_v[i] = origen._v[i];
			}
		}
	}
	return *this;
}

/**
 * @brief Operador de acceso a posiciones de la clase VDinamico
 *
 * @param [in] pos Entero con la posición a acceder
 * @return Devuelve un objeto de tipo T con el dato accedido
 */
template<typename T>
T& VDinamico<T>::operator[](unsigned long int pos) {
	if(pos>=_tamal){
		throw ("Index out of bounds");
	}
	return _v[pos];
}
/////////////////////FUNCIONES/////////////////////////

/**
 * @brief Método para aumentar el tamaño físico a la potencia de 2 inmediatamente superior
 *
 * @param [in] tama Entero con el tamaño a aumentar
 * @return Devuelve un Entero con el nuevo tamaño lógico
 */
template<typename T>
int VDinamico<T>::potenciador(unsigned long int tama) {
	int tnuevo; //tamaÃ±o nuevo
	int potencia = 0;
	do {
		tnuevo = 2 ^ potencia;
		potencia++;
	} while (tnuevo < tama);
	return tnuevo;
}

/**
 * @brief Método para insertar elementos en el vector dinámico
 *
 * @param [in] dato Referencia de tipo T con el dato a insertar
 * @param [in] pos Entero con la posición en la que insertar el dato
 */
template<typename T>
void VDinamico<T>::insertar(const T& dato, unsigned long int pos) {
	if (pos == UINT_MAX) { //inserciÃ³n en Ãºltima posiciÃ³n
		if (_tamal == _tamaf) {
			aumenta();
		}
		_v[_tamal] = dato;
	} else { //inserciÃ³n entre medias
		if (pos > _tamal) {
			throw std::string("Posicion mayor que tamaño logico");
		}
		if (_tamal == _tamaf) {
			aumenta();
		}
		for (unsigned long int i = _tamal - 1; i >= pos; i--) {
			_v[i + 1] = _v[i]; //se desplazaz posiciÃ³n de cada elemento
		}
		_v[pos] = dato;
	}
	_tamal++;
}

/**
 * @brief Método para ordenar el vector dinámico
 */
template<typename T>
void VDinamico<T>::ordenar() { //algoritmo de ordenaciÃ³n por selecciÃ³n

	for (unsigned long int i = 0; i < _tamal; i++) {
		int min = i;
		for (unsigned long int j = i + 1; j < _tamal; j++) {
			if (_v[j] < _v[min]) {
				min = j;
			}
		}
		T aux = _v[i];
		_v[i] = _v[min];
		_v[min] = aux;
	}
}

/**
 * @brief Método para ordenar el vector dinámico pero en sentido contrario
 */
template<typename T>
void VDinamico<T>::ordenarRev() { //algoritmo de ordenaciÃ³n por selecciÃ³n
	for (int i = 0; i < _tamal; i++) {
		int max = i;
		for (int j = i + 1; j < _tamal; j++) {
			if (_v[j] > _v[max]) {
				max = j;
			}
		}
		T aux = _v[i];
		_v[i] = _v[max];
		_v[max] = aux;
	}
}

/**
 * @brief Método para borrar un elemento del vector dinámico dada una posición
 *
 * @param [in] pos Entero con la posición a borrar
 * @return Devuelve un Objeto de tipo T con el elemento borrado
 */
template<typename T>
T VDinamico<T>::borrar(unsigned long int pos) {
	T borrado;
	if (_tamal == 0 || pos >= _tamal) { //en caso de posiciÃ³n fuera de rando o vector no tenga elementos
		throw string("No se puede borrar");
	}
	if (pos == UINT_MAX) { //borrado Ãºltima posiciÃ³n
		borrado = _v[_tamal - 1];
	} else {
		borrado = _v[pos]; //borrado entre medias
		for (int i = pos; i < _tamal - 1; i++) {
			_v[i] = _v[i + 1];
		}
	}
	if (_tamal * 3 < _tamaf) { //disminuciÃ³n de tamaÃ±o fÃ­sico
		disminuye();
	}
	_tamal--;
	return borrado;
}

/**
 * @brief Método para realizar una búsqueda binaria en el vector dinámico
 *
 * @param [in] dato Objeto de clase T a buscar
 * @return Devuelve un Entero con la posición del objeto buscado
 */
template<typename T>
unsigned int VDinamico<T>::busquedaBin(T const &dato) {
	int inf = 0;
	int sup = _tamal - 1;
	while (inf <= sup) {
		int curIn = (inf + sup) / 2;
		if (_v[curIn] == dato) {
			return curIn;
		} else {
			if (_v[curIn] < dato) {
				inf = curIn + 1;
			} else {
				sup = curIn - 1;
			}
		}
	}
	return -1;
}

/**
 * @brief Método para reducir el tamaño físico el vector dinámico
 */
template<typename T>
void VDinamico<T>::disminuye() {
	_tamaf = _tamaf / 2;
	T *vaux = new T[_tamaf];
	for (int i = 0; i < _tamal; i++) {
		vaux[i] = _v[i];
	}
	delete[] _v;
	_v = vaux;
}

/**
 * @brief Método para aumentar el tamaño físico del vector dinámico
 */
template<typename T>
void VDinamico<T>::aumenta() {
	_tamaf = _tamaf * 2;
	T *vaux;
	vaux = new T[_tamaf];
	for (unsigned long int i = 0; i < _tamal; i++) {
		vaux[i] = _v[i];
	}
	delete[] _v;
	_v = vaux;
}

/**
 * @brief Método para obtener el tamaño del vector dinámico
 *
 * @return Devuelve un entero con el tamaño del vector dinámico
 */
template<typename T>
unsigned int VDinamico<T>::tam() {
	return _tamal;
}

#endif /* VDINAMICO_H */

