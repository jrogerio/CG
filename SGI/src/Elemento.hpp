/*
 * Elemento.hpp
 *
 * Author: plab
 */

#ifndef LINKEDLIST_ELEMENTO_HPP_
#define LINKEDLIST_ELEMENTO_HPP_

template<typename T>
class Elemento {
private:
	T _info;
	Elemento<T> *_next;

public:
	Elemento(const T &info, Elemento<T> *next) : _info(info), _next(next) {}

	~Elemento()
	{
	}

	Elemento<T>* next() const
	{
		return _next;
	}

	T info() const
	{
		return _info;
	}

	void next(Elemento<T>* next)
	{
		_next = next;
	}
};


#endif /* LINKEDLIST_ELEMENTO_HPP_ */
