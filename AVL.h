/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef AVL_H
#define AVL_H

/**
 * @file:   AVL.h
 * @author: Juan Bautista
 * @brief Fichero que almacenar� la clase del �rbol AVL.
 * Created on 4 de noviembre de 2020, 17:38
 */
#include <iostream>

/**
 * @brief Plantilla de la clase Nodo
 *
 * Esta clase representa un nodo del �rbol AVL
 */
template<typename U>
class Nodo2 {
public:
	Nodo2<U> *izq; 	///< Nodo a la izquierda del nodo actual
	Nodo2<U> *der;	///< Nodo a la derecha del nodo actual
	U dato;			///< Contenido que contendr� el nodo
	char bal;		///< Factor de equilibrio del nodo

	/**
	 * @brief Constructor parametrizado
	 *
	 * @param [in] ele Dato a introducir en el nodo
	 */
	explicit Nodo2(U &ele) :
			izq(0), der(0), dato(ele), bal(0) {
	}

	/**
	 * @brief Constructor copia
	 *
	 * @param [in] orig Nodo que queremos copiar
	 */
	Nodo2(const Nodo2<U> &orig) :
			izq(0), der(0), dato(orig.dato), bal(orig.bal) {
	}

	/**
	 * @brief Destructor de la clase Nodo
	 */
	~Nodo2() {
	}
};

/**
 * @brief Clase AVL
 *
 * Clase que representa un �rbol AVL
 */
template<typename T>
class AVL {
private:
	Nodo2<T> *raiz;	///< Nodo padre
private:
	int inserta(Nodo2<T>* &c, T &dato);
	void insertaDerecha(Nodo2<T>* &c, T &dato, Nodo2<T>* &p,int &deltaH);
	void insertaIzquierda(Nodo2<T>* &c, T &dato,Nodo2<T>* &p,int &deltaH);

	void rotDecha(Nodo2<T>*& p);
	void rotIzqda(Nodo2<T>*& p);

	void inorden(Nodo2<T> *p, int nivel);
	unsigned int alturaArbolAVL(Nodo2<T>* nodo, int nivel, int& nNiveles);
	unsigned int numElementosAVL(Nodo2<T>* nodo);
	Nodo2<T> *buscaClave(const T &dato, Nodo2<T> *p);
	void copiar(Nodo2<T>* &nuevo, Nodo2<T>* viejo);
	void destruir(Nodo2<T>* nodo);
public:
	AVL();
	AVL(const AVL<T>& orig);
	~AVL();

	void reccoreInorden();
	bool insertar(T &dato);
	unsigned int altura();
	unsigned int numElementos();
	AVL<T>& operator=(const AVL<T>& orig);
	bool buscaR(const T &dato, T &result);
	bool buscaIt(const T &dato, T &result);

};

/**
 * @brief Constructor de la clase AVL
 */
template<typename T>
AVL<T>::AVL() {
	raiz = 0;
}

/**
 * @brief Constructor copia de la clase AVL
 *
 * @param [in] orig �rbol que queremos copiar
 */
template<typename T>
AVL<T>::AVL(const AVL<T>& orig) {
	copiar(raiz, orig.raiz);
}

/**
 * @brief Operador de igualaci�n
 *
 * @param [in] orig �rbol que queremos copiar
 * @return El �rbol copiado
 */
template<typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& orig) {
	copiar(raiz, orig.raiz);
	return *this;
}

/**
 * @brief Funci�n para copiar 2 �rboles
 *
 * @param [in,out] nuevo �rbol que se va a sobreescribir
 * @param [in] viejo �rbol que se quiere copiar
 */
template<typename T>
void AVL<T>::copiar(Nodo2<T>*& nuevo, Nodo2<T>* viejo) {
	if (viejo) {
		nuevo = new Nodo2<T>(*viejo);
		copiar(nuevo->izq, viejo->izq);
		copiar(nuevo->der, viejo->der);
	} else {
		nuevo = 0;
	}
}

/**
 * @brief Destructor de la clase AVL
 *
 * En el destructor llamamos a la funci�n de destruir desde la ra�z
 */
template<typename T>
AVL<T>::~AVL() {
	destruir(raiz);
}

/**
 * @brief M�todo para destruir un nodo y sus hijos
 *
 * @param [in] nodo Nodo que se quiere eliminar junto a sus hijos
 */
template<typename T>
void AVL<T>::destruir(Nodo2<T>* nodo) {
	if (nodo) {
		destruir(nodo->izq);
		destruir(nodo->der);
		nodo = nullptr;
		delete nodo;

	}
}

/**
 * @brief M�todo para buscar un dato en el �rbol
 *
 * @param [in] dato Dato que queremos encontrar
 * @param [in] p Nodo del que se empieza a realizar la b�squeda
 * @return Devolvemos el dato que queriamos buscar si se encuentra en el �rbol o en caso contrario devolvemos un 0
 */
template<typename T>
Nodo2<T> *AVL<T>::buscaClave(const T& dato, Nodo2<T>* p) {
	if (!p) {
		return 0;
	} else if (dato < p->dato) {
		return buscaClave(dato, p->izq);
	} else if (dato > p->dato) {
		return buscaClave(dato, p->der);
	} else {
		return p;
	}
}

/**
 * @brief M�todo para realizar una b�squeda recursiva
 *
 * @param [in] dato Dato que queremos buscar
 * @param [in,out] result Dato que hemos econtrado
 * @return True si encontramos el dato o False si no encontramos el dato
 */
template<typename T>
bool AVL<T>::buscaR(const T& dato, T& result) {
	Nodo2<T> *p = buscaClave(dato, raiz);
	if (p) {
		result = p->dato;
		return true;
	}
	return false;
}

/**
 * @brief M�todo para aplicar una rotaci�n hacia la derecha a una rama
 *
 * @param [in] p Nodo del que se realizar� la rotaci�n hacia la derecha
 */
template<typename T>
void AVL<T>::rotDecha(Nodo2<T>*& p) {
	Nodo2<T> *q = p, *l;
	p = l = q->izq;
	q->izq = l->der;
	l->der = q;
	q->bal--;
	if (l->bal > 0)
		q->bal -= l->bal;
	l->bal--;
	if (q->bal < 0)
		l->bal -= -q->bal;
}

/**
 * @brief M�todo para aplciar una rotaci�n hacia la izquierda a una rama
 *
 * @param [in] p Nodo del que se realizar� la rotaci�n hacia la derecha
 */
template<typename T>
void AVL<T>::rotIzqda(Nodo2<T>*& p) {
	Nodo2<T> *q = p, *r;
	p = r = q->der;
	q->der = r->izq;
	r->izq = q;
	q->bal++;
	if (r->bal < 0)
		q->bal += -r->bal;
	r->bal++;
	if (q->bal > 0)
		r->bal += q->bal;
}

/**
 * @brief M�todo para invocar un recorrido en Inorden
 */
template<typename T>
void AVL<T>::reccoreInorden() {
	inorden(raiz, 0);
}

/**
 * @brief M�todo que realiza un recorrido en Inorden
 *
 * @param [in] p Nodo del que partimos realizando el recorrido
 * @param [in] nivel Nivel del arbol donde se inicia el recorrido
 */
template<typename T>
void AVL<T>::inorden(Nodo2<T>* p, int nivel) {
	if (p) {
		inorden(p->izq, nivel + 1);
		std::cout << p->dato << " NIVEL " << nivel << std::endl;
		inorden(p->der, nivel + 1);
	}
}

/**
 * @brief M�todo para insertar un nuevo nodo en el �rbol
 *
 * @param [in] c Nodo nuevo a insertar
 * @param [in] dato Dato que contiene el nuevo Nodo
 * @return Devuelve la variaci�n de la altura del �rbol producida por la insercci�n
 */
template<typename T>
int AVL<T>::inserta(Nodo2<T>*& c, T& dato) {
	Nodo2<T> *p = c;
	int deltaH = 0;
	if (!p) {
		p = new Nodo2<T>(dato);
		c = p;
		deltaH = 1;
	} else if (dato > p->dato) {
		this->insertaDerecha(c,dato,p,deltaH);
	} else if (dato < p->dato) {
		this->insertaIzquierda(c,dato,p,deltaH);
	}
	return deltaH;
}

/**
 * @brief Funci�n para insertar un dato en el �rbol en la parte derecha
 *
 * @param [in,out] c Nodo que se rotar�a hacia la izquierda
 * @param [in] dato Dato a introducir
 * @param [in,out] p Nodo en el que se insertar� el dato
 * @param [in,out] deltaH Valor del delta
 */
template<typename T>
void AVL<T>::insertaDerecha(Nodo2<T>*& c, T& dato,Nodo2<T>* &p,int &deltaH) {
	if (inserta(p->der, dato)) {
				p->bal--;
				if (p->bal == -1) {
					deltaH = 1;
				} else if (p->bal == -2) {
					if (p->der->bal == 1) {
						rotDecha(p->der);
						rotIzqda(c);
					}
				}
	}
}

/**
 * @brief Funci�n para insertar un dato en la parte izquierda del �rbol
 *
 * @param [in,out] c Nodo que se rotar�a hacia la derecha
 * @param [in] dato Dato a introducir
 * @param [in,out] p Nodo en el que se introducir� el dato
 * @param [in,out] deltaH Valor de delta
 */
template<typename T>
void AVL<T>::insertaIzquierda(Nodo2<T>*& c, T& dato,Nodo2<T>* &p,int &deltaH) {
	if (inserta(p->izq, dato)) {
				p->bal++;
				if (p->bal == 1) {
					deltaH = 1;
				} else if (p->bal == 2) {
					if (p->izq->bal == -1) {
						rotIzqda(p->izq);
						rotDecha(c);
					}
				}
	}
}
/**
 * @brief M�todo p�blico para insertar un dato en el �rbol
 *
 * @param [in] dato Dato que queremos insertar
 * @return Devuelve True si se ha insertado correctamente el dato o False en caso contrario
 */
template<typename T>
bool AVL<T>::insertar(T& dato) {
	return inserta(raiz, dato);
}

/**
 * @brief Metodo para calcular el n�mero de niveles de un �rbol
 *
 * @param [in] nodo Nodo inicial donde se empieza a contar
 * @param [in] nivel Nivel que se encuentra el nodo en el �rbol
 * @param [in,out] nNiveles N�mero de niveles que tiene el �rbol
 * @return Devuelve el n�mero de niveles que tiene el �rbol
 */
template<typename T>
unsigned int AVL<T>::alturaArbolAVL(Nodo2<T>* nodo, int nivel, int& nNiveles) {
	if (nodo) {
		alturaArbolAVL(nodo->izq, nivel + 1, nNiveles);
		if (nivel > nNiveles) {
			nNiveles = nivel;
		}
		alturaArbolAVL(nodo->der, nivel + 1, nNiveles);
	}
	return nNiveles;
}

/**
 * @brief M�todo para calcular la �ltura de un �rbol
 *
 * @return Devuelve la �ltura de un �rbol
 */
template<typename T>
unsigned int AVL<T>::altura() {
	int nNiveles = 0;
	alturaArbolAVL(raiz, 0, nNiveles);
	return nNiveles;
}

/**
 * @brief M�todo p�blico para obtener el n�mero de elementos que hay en el �rbol
 *
 * @return El n�mero de elementos que hay en el �rbol
 */
template<typename T>
unsigned int AVL<T>::numElementos() {
	return numElementosAVL(raiz);
}

/**
 * @brief M�todo para calcular el n�mero de elementos que tiene un nodo
 *
 * @param [in] nodo Nodo del que se empieza a contar
 * @return El n�mero de elementos de elementos que tiene el Nodo incluyendose a s� mismo
 */
template<typename T>
unsigned int AVL<T>::numElementosAVL(Nodo2<T>* nodo) {
	if (nodo) {
		return numElementosAVL(nodo->izq) + numElementosAVL(nodo->der) + 1;
	} else {
		return 0;
	}
}

/**
 * @brief M�todo para realizar una b�squeda Iterativa sobre un dato
 *
 * @param [in] dato Dato que queremos buscar
 * @param [in,out] result Variable donde almacenaremos el dato si lo encontramos
 * @return True si el dato es encontrado o False en caso contrario
 */
template<typename T>
bool AVL<T>::buscaIt(const T& dato, T& result) {
	Nodo2<T> *nodo = raiz;
	while (nodo) {
		if (dato < nodo->dato) {
			nodo = nodo->izq;
		} else if (dato > nodo->dato) {
			nodo = nodo->der;
		} else {
			result = nodo->dato;
			return true;
		}
	}
	return false;
}

#endif /* AVL_H */

