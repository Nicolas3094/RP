#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <random>
#include <time.h>
#include <iomanip>
using namespace std;

#include "Lineal/Vector/VecOp.hpp"
#include "Lineal/Matriz/MartizFun.hpp"


#define print(x) cout << x << "\n"
#define MAX_RAN 32767.1

string const PATH_IN = "Data\\";

struct Data{
    Vector<double> data;
    int clase;
    int pos;
};
typedef struct Data Datos;
struct Cluster{
	vector<int> p;
	vector<vector<int>> w;
	vector<Datos> centroid;
};
struct Grupo{
	int etiqueta;
	vector<double> pts; //no representa los valores de los puntos, si no la posicon del dato y su porcenatje en caso de ser difuso
	Vector<double> centroid;
};
typedef struct Grupo Grupo;
typedef vector<Vector<double>> Region;
typedef struct Cluster Cluster;
typedef unsigned int uint;
ostream& operator <<(ostream&, Datos& );
ofstream& operator <<(ofstream&, Datos&);

void ReadFl(string const, vector<Datos>&, int&, int&) ;
void CreatSpace(string const ,Region&,vector<double>& , int& , int& );

char const AT = '@';


#endif //INDEX_H
