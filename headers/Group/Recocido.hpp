

#ifndef HEADERS_GROUP_RECOCIDO_HPP_
#define HEADERS_GROUP_RECOCIDO_HPP_


#include "Kmeans.hpp"
Cluster Delta(Cluster );
double Uniform();
int SELECT(int , int );
int SELECT(vector<int>&);
double Pr(double ,double );
double J_C(vector<Datos> ,Cluster);
Cluster SA(vector<Datos> ,int , double , double, double , Cluster );
void RecocidoSimulado(string const, string const);
vector<vector<int>> initW(int ,int );
void initP(vector<Datos> ,Cluster& );
void Centros(vector<Datos> , Cluster& );
#endif /* HEADERS_GROUP_RECOCIDO_HPP_ */
