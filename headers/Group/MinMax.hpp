#ifndef MINMAX_H
#define MINMAX_H

#include "../IndexHeader.hpp"

#define frac 0.4

struct AlphaMinMax{
    int pos;
    Datos data;
    vector<double> ditancias;
};  
typedef struct AlphaMinMax Alpha;

void MinMaxF(string const, string const,double const );
void FindMaxDist(vector<double>, int &);
void CrearListaDist(vector<Datos>, Datos, vector<double> &);
void CrearClases(double, vector<Datos>&, vector<Alpha>&);
void MenorDist(vector<Alpha>, vector<double> &);
#endif //MINMAX_H
