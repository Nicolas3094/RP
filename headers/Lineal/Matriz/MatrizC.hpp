
#ifndef HEADERS_LINEAL_MATRIZ_MATRIZC_HPP_
#define HEADERS_LINEAL_MATRIZ_MATRIZC_HPP_

#include "../Lineal.hpp"
#include "../Vector/VecOp.hpp"

template<typename T>
class Matriz {
private:
	vector<Vector<T>> _Mat;
	ulong col;
	ulong row;
public:
	Matriz();
	Matriz(ulong, ulong);
	Matriz(vector<Vector<T>>);
	Matriz(Vector<T>);

	bool CUADRADA();

	const ulong COL();
	const ulong ROW();
	const ulong DIM();

	void AddCol(const Vector<T>&, bool);
	void DelCol(ulong);
	void AddRow(Vector<T>, bool);
	void DelRow(ulong);

	Vector<T>& _Col(ulong);
	Vector<T> _Row(ulong);

	Vector<T>& operator [] (ulong);

	void operator = ( Matriz<T>);

	Matriz<T> operator *= (T);
	Matriz<T> operator * (T);
	Matriz<T> operator / (T);
	Matriz<T> operator /= (T);

	Vector<T> operator * (Vector<T>);

	Matriz<T> operator * (Matriz<T>);
	Matriz<T> operator + (Matriz<T>);
	Matriz<T> operator - (Matriz<T>);
	bool operator == (Matriz<T>);

	~Matriz();
};

ostream&  operator <<(ostream&, Matriz<double>);
ostream&  operator <<(ostream&, Matriz<float>);
ostream&  operator <<(ostream&, Matriz<int>);
ostream&  operator <<(ostream&, Matriz<char>);



#endif /* HEADERS_LINEAL_MATRIZ_MATRIZC_HPP_ */
