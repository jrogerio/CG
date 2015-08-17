/*
 * Elemento.hpp
 *
 *  Created on: 13 de ago de 2015
 *      Author: plab
 */

#ifndef LINKEDLIST_ELEMENTO_HPP_
#define LINKEDLIST_ELEMENTO_HPP_

template<typename T>
class Elemento {
private:
	T *info;
	Elemento<T>* _next;

public:
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

	~Elemento()
	{
		delete info;
	}

	Elemento<T>* getProximo() const
	{
		return _next;
	}

	T getInfo() const
	{
		return *info;
	}

	void setProximo(Elemento<T>* next)
	{
		_next = next;
	}
};


#endif /* LINKEDLIST_ELEMENTO_HPP_ */
