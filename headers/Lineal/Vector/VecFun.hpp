
#ifndef HEADERS_LINEAL_VECTOR_VECFUN_HPP_
#define HEADERS_LINEAL_VECTOR_VECFUN_HPP_

#include "../Lineal.hpp"
double round_up(double , int );
template<typename T>
class Vector : public vector<T>{
public:
	Vector();
	Vector(const vector<T>&);
	Vector(ulong,T);

	const double Magnitud();
	const ulong Dimension();
	T Sum();

	Vector<T> operator*(T);
	Vector<T> operator/(T);
	const T operator*( Vector<T>);

	Vector<T> operator+(Vector<T>);
	Vector<T> operator-( Vector<T>);

	void operator+=(Vector<T>);
	void operator-=(Vector<T>);
	const T operator*=(Vector<T>);
	void operator*=(T);
	void operator/=(T);
};





#endif /* HEADERS_LINEAL_VECTOR_VECFUN_HPP_ */
