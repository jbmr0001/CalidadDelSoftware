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
 * @brief Fichero que almacenará la clase del árbol AVL.
 * Created on 4 de noviembre de 2020, 17:38
 */
#include <iostream>

/**
 * @brief Plantilla de la clase Nodo
 *
 * Esta clase representa un nodo del árbol AVL
 */
template<typename U>
class Nodo2 {
public:
	Nodo2<U> *izq; 	///< Nodo a la izquierda del nodo actual
	Nodo2<U> *der;	///< Nodo a la derecha del nodo actual
	U dato;			///< Contenido que contendrá el nodo
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
 * Clase que representa un árbol AVL
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
 * @param [in] orig Árbol que queremos copiar
 */
template<typename T>
AVL<T>::AVL(const AVL<T>& orig) {
	copiar(raiz, orig.raiz);
}

/**
 * @brief Operador de igualación
 *
 * @param [in] orig Árbol que queremos copiar
 * @return El árbol copiado
 */
template<typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& orig) {
	copiar(raiz, orig.raiz);
	return *this;
}

/**
 * @brief Función para copiar 2 árboles
 *
 * @param [in,out] nuevo Árbol que se va a sobreescribir
 * @param [in] viejo Árbol que se quiere copiar
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
 * En el destructor llamamos a la función de destruir desde la raíz
 */
template<typename T>
AVL<T>::~AVL() {
	destruir(raiz);
}

/**
 * @brief Método para destruir un nodo y sus hijos
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
 * @brief Método para buscar un dato en el Árbol
 *
 * @param [in] dato Dato que queremos encontrar
 * @param [in] p Nodo del que se empieza a realizar la búsqueda
 * @return Devolvemos el dato que queriamos buscar si se encuentra en el árbol o en caso contrario devolvemos un 0
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
 * @brief Método para realizar una búsqueda recursiva
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
 * @brief Método para aplicar una rotación hacia la derecha a una rama
 *
 * @param [in] p Nodo del que se realizará la rotación hacia la derecha
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
 * @brief Método para aplciar una rotación hacia la izquierda a una rama
 *
 * @param [in] p Nodo del que se realizará la rotación hacia la derecha
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
 * @brief Método para invocar un recorrido en Inorden
 */
template<typename T>
void AVL<T>::reccoreInorden() {
	inorden(raiz, 0);
}

/**
 * @brief Método que realiza un recorrido en Inorden
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
 * @brief Método para insertar un nuevo nodo en el Árbol
 *
 * @param [in] c Nodo nuevo a insertar
 * @param [in] dato Dato que contiene el nuevo Nodo
 * @return Devuelve la variación de la altura del árbol producida por la insercción
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
 * @brief Función para insertar un dato en el árbol en la parte derecha
 *
 * @param [in,out] c Nodo que se rotaría hacia la izquierda
 * @param [in] dato Dato a introducir
 * @param [in,out] p Nodo en el que se insertará el dato
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
 * @brief Función para insertar un dato en la parte izquierda del árbol
 *
 * @param [in,out] c Nodo que se rotaría hacia la derecha
 * @param [in] dato Dato a introducir
 * @param [in,out] p Nodo en el que se introducirá el dato
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
 * @brief Método público para insertar un dato en el Árbol
 *
 * @param [in] dato Dato que queremos insertar
 * @return Devuelve True si se ha insertado correctamente el dato o False en caso contrario
 */
template<typename T>
bool AVL<T>::insertar(T& dato) {
	return inserta(raiz, dato);
}

/**
 * @brief Metodo para calcular el número de niveles de un árbol
 *
 * @param [in] nodo Nodo inicial donde se empieza a contar
 * @param [in] nivel Nivel que se encuentra el nodo en el Árbol
 * @param [in,out] nNiveles Número de niveles que tiene el árbol
 * @return Devuelve el número de niveles que tiene el árbol
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
 * @brief Método para calcular la áltura de un árbol
 *
 * @return Devuelve la áltura de un árbol
 */
template<typename T>
unsigned int AVL<T>::altura() {
	int nNiveles = 0;
	alturaArbolAVL(raiz, 0, nNiveles);
	return nNiveles;
}

/**
 * @brief Método público para obtener el número de elementos que hay en el árbol
 *
 * @return El número de elementos que hay en el árbol
 */
template<typename T>
unsigned int AVL<T>::numElementos() {
	return numElementosAVL(raiz);
}

/**
 * @brief Método para calcular el número de elementos que tiene un nodo
 *
 * @param [in] nodo Nodo del que se empieza a contar
 * @return El número de elementos de elementos que tiene el Nodo incluyendose a sí mismo
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
 * @brief Método para realizar una búsqueda Iterativa sobre un dato
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

