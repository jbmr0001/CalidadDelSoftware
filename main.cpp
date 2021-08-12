/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * @file:   main.cpp
 * @author: Juan Bautista
 * @brief Fichero para almacenar el hilo principal
 *
 * Created on 4 de noviembre de 2020, 17:36
 */

#include <cstdlib>
#include "AVL.h"
#include "GestorTextos.h"
#include "Documento.h"
#include "VDinamico.h"
#include "VerbosConjugados.h"
#include <sstream>
#include <fstream>
#include "VDinamico.h"
#include "ListaEnlazada.h"
#include <chrono>

using namespace std;


VDinamico<Palabra> vd;		///< Vector dinámico para guardar las palabras
ListaEnlazada<Palabra> le;	///< Lista enlazada para guardar las palabras
AVL<Palabra> avl;			///< Árbol AVL para guardar las palabras

/**
 * @brief Función para probar los tiempos de inserción
 */
void pruebaTiempos() { //funcion para llenar las estructuras de datos de verbos y usarlas en la prueba de tiempos
	std::ifstream fe;
	string linea;
	std::string palabra;

	fe.open("verbos_conjugados_sin_tildes_desordenados.txt"); //abrimos fichero
	if (fe.good()) {
		while (!fe.eof()) { //bucle hasta llegue a la ultima linea
			getline(fe, linea); //leemos la lÃ­nea
			std::stringstream ss;

			ss << linea;
			getline(ss, palabra); //extraemos la palabra en forma de string de la lÃ­nea leida
			Palabra pal(palabra); //creamos una Palabra con el string leido
			vd.insertar(pal);
			le.insertaFinal(pal);
			avl.insertar(pal);
		}

		fe.close();
	}
}

/**
 * @brief Hilo principal del programa
 *
 * @param [in] argc Contiene el número de argumentos que se han introducido
 * @param [in] argv Array de punteros a caracteres
 * @return Devuelve 0 para comprobar si la ejecución ha sido correcta
 */
int main(int argc, char** argv) {
	GestorTextos gt;
	gt.addDocumento("quijote2.txt");
	gt.getDocumentos()[0].chequearTexto();
	cout << "Inexistentes Práctica 2=10387 y tras borrado 9205" << endl;

	//PRUEBA TIEMPOS
	/*
	 //Datos tomados en Informe Tiempos.png
	 pruebaTiempos();
	 Palabra buscar1("desfecho");//palabra al pricipio
	 Palabra buscar2("acarrazas");//palabra entre medias
	 Palabra buscar3("guarreamos");//palabra al final

	 auto start=std::chrono::system_clock::now();

	 //avl.buscaIt(buscar3,buscar1);
	 //vd.busquedaBin(buscar3);
	 avl.buscaR(buscar3,buscar1);

	 auto end=std::chrono::system_clock::now();
	 std::chrono::duration<float,std::milli> duration=end-start;

	 std::cout<<duration.count()<<""<<std::endl;
	 */
	return 0;
}

