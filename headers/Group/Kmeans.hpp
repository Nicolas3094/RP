#ifndef KMEANS_H
#define KMEANS_H

#include "../IndexHeader.hpp"
void Centroides(vector<Datos> , vector<Datos> &, int const);
void AgruparC(vector<Datos> &, vector<Datos>& );
void ActualizarC(vector<Datos> &, vector<Datos> &);
void KMeans(string const, string const, int const);

#endif //KMEANS_H
