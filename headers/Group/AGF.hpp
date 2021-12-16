

#ifndef HEADERS_GROUP_AGF_HPP_
#define HEADERS_GROUP_AGF_HPP_

#include "FCM.hpp"
void Mutation(vector<Grupo>& );
vector<vector<double>> FuzzyC(vector<Datos>& , vector<Datos>& , int , double , int );
vector<double> Codification(vector<Datos> );
void AGD(string const, string const);
vector<vector<double>> PoblacionIni(vector<Data> , int );
Vector<double> CentroideDatos(vector<Datos> );
void Discrimiar(vector<Data>,vector<vector<Grupo>> , int , int );
void Normalization(vector<Datos> ,vector<Grupo>& , int , double , int );
#endif /* HEADERS_GROUP_AGF_HPP_ */
