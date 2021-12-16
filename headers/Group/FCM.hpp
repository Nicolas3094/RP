

#ifndef HEADERS_GROUP_FCM_HPP_
#define HEADERS_GROUP_FCM_HPP_


#include "Kmeans.hpp"

double FObject(double**,vector<Datos>,vector<Datos>,int);
void Centroide(vector<Datos>, vector<Datos>&, int const);
double membresia(Datos,int, vector<Datos>,int);
void Member(double** , vector<Datos>,vector<Datos>,int);
void NuCentro(double**,vector<Datos>,vector<Datos>&,int);
void FCM(string const, string const, int const);
void EqualM(double**,double**,int,int);
double MaxM(double**,double**,int,int);
#endif /* HEADERS_GROUP_FCM_HPP_ */
