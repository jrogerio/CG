/*
 * ListaEnc.hpp
 *
 * Author: plab
 */

#include "Elemento.hpp"
#include <iostream>

template<typename T>
class ListaEnc {

private:
	Elemento<T> *_head;
	int _size;

public:
	ListaEnc() :
			_head(0), _size(0) {
	}
	//~ListaEnc(); // a completar

	// inicio
	void adicionaNoInicio(const T& dado);
	T retiraDoInicio();
	void eliminaDoInicio();

	// posicao
	void adicionaNaPosicao(const T& dado, int pos);
	int posicao(const T& dado) const;
	T* posicaoMem(const T& dado) const;
	bool contem(const T& dado);
	T retiraDaPosicao(int pos);

	//fim
	void adiciona(const T& dado) {
		Elemento<T> *element = new Elemento<T>(dado, 0);

		if (_size == 0) {
			_head = element;
		} else {
			Elemento<T> *last = _head;
			while (last->next() != 0) {
				last = last->next();
			}
			last->next(element);
		}
		++_size;
	}

	T retira() {
		Elemento<T> *new_last = _head;
		if (_size < 2) {
			T returned = _head->info();
			delete _head;
			_head = 0;
			--_size;
			return returned;
		} else {
			while (new_last->next()->next() != 0) {
				new_last = new_last->next();
			}
			T returned = new_last->next()->info();
			delete new_last->next();
			new_last->next(0);
			--_size;
			return returned;
		}
	}



	// especifico
	T retiraEspecifico(const T& dado);
	void adicionaEmOrdem(const T& data);
	bool listaVazia() const;
	bool igual(T dado1, T dado2);
	bool maior(T dado1, T dado2);
	bool menor(T dado1, T dado2);
	void destroiLista();

};
