#ifndef HEADERS_LINEAL_VECTOR_VECOP_HPP_
#define HEADERS_LINEAL_VECTOR_VECOP_HPP_

#include "VecFun.hpp"

template<typename T>
class V_OPERATOR{
public:
	static const double DIST( Vector<T>,  Vector<T>);
	static const int DELTA_KR(ulong,ulong);
	static Vector<T> UNIT(Vector<T>);
};


ostream&  operator <<(ostream&, Vector<int>&);
ostream&  operator <<(ostream&, Vector<double>&);

Vector<float> operator*(float,Vector<float>);
Vector<int> operator*(int,Vector<int>);
Vector<double> operator*(double,Vector<double>);

Vector<float> operator/(float,Vector<float>);
Vector<int> operator/(int,Vector<int>);
Vector<double> operator/(double,Vector<double>);

double Dist(const vector<int>&,const vector<int>&);
double Dist(const vector<float>&,const vector<float>&);
double Dist(const vector<double>&,const vector<double>&);


#endif /* HEADERS_LINEAL_VECTOR_VECOP_HPP_ */
