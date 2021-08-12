/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   ListaEnlazada.h
 * @author: Juan Bautista
 * @brief Fichero para almacenar la Lista enlazada
 *
 * Created on 20 de octubre de 2020, 16:38
 */

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <string>

/**
 * @brief Clase Lista Enlazada
 *
 * Clase que representa una Lista Enlazada
 */
template<typename T>
class ListaEnlazada {
	/**
	 * @brief Plantilla de la clase Nodo
	 *
	 * Esta clase representa un nodo de la Lista Enlazada
	 */
	template<class U>
	class Nodo {
	public:
		U dato;		///< Contenido del nodo
		Nodo* sig;		///< Nodo siguiente

		/**
		 * @brief Constructor parametrizado
		 *
		 * @param [in] aDato Dato a introducir en el nodo
		 * @param [in] aSig Nodo siguiente al nodo
		 */
		explicit Nodo(const U& aDato, Nodo* aSig = 0) :
				dato(aDato), sig(aSig) {
		}

		/**
		 * @brief Destructor de la clase Nodo
		 */
		~Nodo() {
		}
	};
public:
	/**
	 * @brief Clase Iterador
	 */
	template<typename V>
	class Iterador {
	public:
		Nodo<V> *nodo;
		/**
		 * @brief Constructor parametrizado
		 * @param [in] aNodo Nodo a iterar
		 */
		explicit Iterador(Nodo<V> *aNodo) :
				nodo(aNodo) {
		}

		/**
		 * @brief Destructor de la clase Iterador
		 */
		~Iterador() {
		}

		/**
		 * @brief Función para saber si se ha llegado al final de la iteración
		 *
		 * @return Delvolvemos un boolean que indica si es último nodo
		 */
		bool fin() {
			return (nodo == 0);
		}

		/**
		 * @brief Función para iterar al nodo siguiente
		 */
		void siguiente() {
			nodo = nodo->sig;
		}

		/**
		 * @brief Función para saber si hay nodo siguiente
		 *
		 * @return Devuelve un boolean que indica si hay un nodo siguiente
		 */
		bool haySiguiente() {
			return nodo != 0;
		}

		/**
		 * @brief Función para acceder al dato del iterador
		 *
		 * @return Devuelve el nodo siguiente
		 */
		V &dato() {
			return nodo->dato;
		}
	};
	ListaEnlazada();
	ListaEnlazada(const ListaEnlazada<T>& origen);
	~ListaEnlazada();

	Iterador<T> iterador() const;
	ListaEnlazada<T> &operator=(const ListaEnlazada<T>& list);
	void insertaInicio(T& dato);
	void insertaFinal(T& dato);
	void inserta(Iterador<T> &i, T& dato);
	void borraInicio();
	void borraFinal();
	void borrar(Iterador<T> &i);
	bool insertaOrdenado(T& dato);
	void borrarRepetidos();

	T &inicio();
	T &final();
	int tama() {
		return _tam;
	}
private:
	Nodo<T> *_cabecera;		///< Puntero hacia el nodo cabecera(Primero) de la lista enlazada
	Nodo<T> *_cola;			///< Puntero hacia el nodo cola(Último) de la lista enlazada
	unsigned long int _tam;	///< Tamaño de la lista enlazada
};

/**
 * @brief Constructor de la clase Lista Enlazada
 */
template<typename T>
ListaEnlazada<T>::ListaEnlazada() :
		_cabecera(0), _cola(0), _tam(0) {
}

/**
 * @brief Constructor copia de la clase Lista Enlazada
 *
 * @param origen [in] Lista Enlazada que queremos copiar
 */
template<typename T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T>& origen) {
	Nodo<T> *i = origen._cabecera;
	_tam = origen._tam;
	_cabecera = _cola = 0;
	while (i) {
		Nodo<T> *nuevo = new Nodo<T>(i->dato, 0);
		if (_cola != 0) {
			_cola->sig = nuevo;
		}
		if (_cabecera == 0) {
			_cabecera = nuevo;
		}
		_cola = nuevo;
		i = i->sig;
	}
}
/**
 * @brief Destructor de la clase Lista Enlazada
 */
template<typename T>
ListaEnlazada<T>::~ListaEnlazada() {
	if (_cabecera) {
		Nodo<T> *elimina = _cabecera;
		while (elimina) {
			_cabecera = _cabecera->sig;
			delete elimina;
			elimina = _cabecera;
		}
		_cola = 0;
	}
}

/**
 * @brief Función para iterar la cabecera de la lista
 *
 * @return Devuelve un iterador a la cabecera
 */
template<typename T>
ListaEnlazada<T>::Iterador<T> ListaEnlazada<T>::iterador() const {
	return Iterador<T>(_cabecera);
}

/**
 * @brief Constructor copia de la Lista Enlazada
 *
 * @param [in] list Lista Enlazada que copiar
 * @return Devuelve la Lista Enlazada copiada
 */
template<typename T>
ListaEnlazada<T> &ListaEnlazada<T>::operator =(const ListaEnlazada<T>& list) {
	if (_cabecera) { //borramos todos los nodos (mismo codigo que el destructor)
		Nodo<T> *elimina = _cabecera;
		while (elimina) {
			_cabecera = _cabecera->sig;
			delete elimina;
			elimina = _cabecera;
		}
		_cola = 0;
	}
	Nodo<T> *i = list._cabecera; //copiamos la lista(mismo codigo que el construcor copia)
	_cabecera = _cola = 0;
	_tam = list._tam;
	while (i) {
		Nodo<T> *nuevo = new Nodo<T>(i->dato, 0);
		if (_cola != 0) {
			_cola->sig = nuevo;
		}
		if (_cabecera == 0) {
			_cabecera = nuevo;
		}
		_cola = nuevo;
		i = i->sig;

	}
	return *this;
}

/**
 * @brief Función para insertar en el principio de la Lista Enlazada
 *
 * @param [in] dato Dato de tipo T a insertar
 */
template<typename T>
void ListaEnlazada<T>::insertaInicio(T& dato) {
	Nodo<T> *nuevo = new Nodo<T>(dato, _cabecera);
	if (_cola == 0) {
		_cola = nuevo;
	}
	_cabecera = nuevo;
	_tam++;
}

/**
 * @brief Función para insertar en el final de la Lista Enlazada
 *
 * @param [in] dato Dato de tipo T a insertar
 */
template<typename T>
void ListaEnlazada<T>::insertaFinal(T& dato) {
	Nodo<T> *nuevo = new Nodo<T>(dato, 0);
	if (_cola != 0) {
		_cola->sig = nuevo;
	}
	if (_cabecera == 0) {
		_cabecera = nuevo;

	}
	_cola = nuevo;
	_tam++;
}

/**
 * @brief Función para insertar en medio de la Lista Enlazada
 *
 * @param [in] i Iterador a la posición en la que insertar
 * @param [in] dato Dato de tipo T a insertar
 */
template<typename T>
void ListaEnlazada<T>::inserta(Iterador<T>& i, T& dato) {
	if (!i.fin()) {
		if (i.nodo == _cabecera) {
			insertaInicio(dato);
		} else if (i.nodo == _cola) {
			insertaFinal(dato);
		} else {
			Nodo<T> *anterior = 0;
			anterior = _cabecera;
			while (anterior->sig != i.nodo) {
				anterior = anterior->sig;
			}
			Nodo<T> *nuevo = new Nodo<T>(dato, i.nodo);
			anterior->sig = nuevo;
			tama++;
		}
	}
}

/**
 * @brief Función para borrar el primer Elemento de la Lista Enlazada
 */
template<typename T>
void ListaEnlazada<T>::borraInicio() {
	Nodo<T> *borrado = _cabecera;
	_cabecera = _cabecera->sig;
	delete borrado;
	if (_cabecera == 0) {
		_cola = 0;
	}
	_tam--;
}

/**
 * @brief Función para borrar el último elemento de la Lista Enlazada
 */
template<typename T>
void ListaEnlazada<T>::borraFinal() {
	Nodo<T> *anterior = 0;
	if (_cabecera != _cola) {
		anterior = _cabecera;
		while (anterior->sig != _cola) {
			anterior = anterior->sig;
		}
	}
	delete _cola;
	_cola = anterior;
	if (anterior != 0) {
		anterior->sig = 0;
	} else {
		_cabecera = 0;
	}
	_tam--;

}

/**
 * @brief Función para borrar una posición iterada
 *
 * @param [in] i Iterador a la posición a borrar
 */
template<typename T>
void ListaEnlazada<T>::borrar(Iterador<T>& i) {
	Nodo<T>* p = i.nodo;
	if (!i.fin()) {
		if (i.nodo == _cola) {
			borraFinal();
		} else if (i.nodo == _cabecera) {
			borraInicio();
		} else {
			Nodo<T> *anterior = 0;
			if (_cabecera != _cola) {
				anterior = _cabecera;
				while (anterior->sig != p) {
					anterior = anterior->sig;
				}
			}
			if(p->sig != nullptr){
				anterior->sig = p->sig;
				_tam--;
			}

		}
	}

}

/**
 * @brief Función para acceder a la primera posición de la Lista Enlazada
 *
 * @return Devuelve el nodo cabecera
 */
template<typename T>
T &ListaEnlazada<T>::inicio() {
	if (!_cabecera) {
		throw std::string("No hay cabecera");
	}
	return _cabecera->dato;
}

/**
 * @brief Función para acceder a la última posición de la Lista Enlazada
 *
 * @return Devuelve el nodo cola
 */
template<typename T>
T &ListaEnlazada<T>::final() {
	if (!_cola) {
		throw std::string("No hay cola");
	}
	return _cola->dato;
}

/**
 * @brief Función de inserción ordenada en la Lista Enlazada
 *
 * @param [in] dato Dato de tipo T a insertar
 * @return Devuelve si la inserción ha sido ordenada en forma de boolean
 */
template<typename T>
bool ListaEnlazada<T>::insertaOrdenado(T& dato) {
	//comprobacion de que esta ordenada
	if (_cabecera != 0) { //para evitar casos en la que esta vacÃ­a
		Nodo<T> *aux = _cabecera;
		while (aux->sig != 0) { //recorremos toda la lista hasta elmomento que el el siguiente es menor que el anterior
			if (aux->dato > aux->sig->dato) {
				return false;
			}
			aux = aux->sig;
		}
	}
	Nodo<T> *nuevo = new Nodo<T>(dato, _cabecera);
	if (_cabecera == 0) { //en caso de primera inserciÃ³n
		_cabecera = nuevo;
	} else if (dato < _cabecera->dato) { //en caso de ser menor que la cabecera
		nuevo->sig = _cabecera;
		_cabecera = nuevo;
		_tam++;

	} else { //inserciÃ³n ordenada
		Nodo<T> *actual = _cabecera;

		while (actual->sig != 0 && actual->sig->dato < dato) { //avanzamos mientras sea menor que dato
			actual = actual->sig;

		}
		if (dato != actual->dato) {
			nuevo->sig = actual->sig;
			actual->sig = nuevo;

			_tam++;
		}
	}
	return true;
}

/**
 * @brief Función para borrar los elementos repetidos de la Lista Enlazada
 */
template<typename T>
void ListaEnlazada<T>::borrarRepetidos() {
	Nodo<T> *aux = _cabecera;
	while (aux->sig != 0) { //recorremos toda la lista y en caso de ser igual el dato adelantamos punteros
		if (aux->dato == aux->sig->dato) {
			aux->sig = aux->sig->sig;
			_tam--;
		} else {
			aux = aux->sig;
		}
	}
}

#endif /* LISTAENLAZADA_H */

