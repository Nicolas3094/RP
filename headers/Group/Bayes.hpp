
#ifndef HEADERS_GROUP_BAYES_HPP_
#define HEADERS_GROUP_BAYES_HPP_

#include "../IndexHeader.hpp"

double Cmedia(vector<Datos>, int, int);
double PXY(int,double, double, vector<Datos>,Vector<double> );
double PrXY(Vector<double>, double, vector<Datos>,Vector<double>);
void Bayes(const string, const string);
void NaiveB(vector<Datos>&,vector<Datos>&, const int, int const );
double media(vector<Datos>, int);
Vector<double> VMedia(vector<Datos>);
Vector<double> CMedia(vector<Datos>, int);
double Sxy(vector<Datos>,int,int,int);
Matriz<double> COV(vector<Datos>,int );
double VAR(vector<Datos>,int,int);
double fd(Vector<double>, int, Vector<double>,Matriz<double> );
void Gauss(vector<Datos>&,int const, int const );
Matriz<double> cov(vector<Datos>,int);
#endif /* HEADERS_GROUP_BAYES_HPP_ */
