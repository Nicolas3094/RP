#ifndef HEADERS_GROUP_FDR_HPP_
#define HEADERS_GROUP_FDR_HPP_
#include "../IndexHeader.hpp"

double fd(Datos,Datos);
void evalSet(vector<Datos>&, vector<Datos>,bool&,int);
void evalFD(vector<Datos>&, Datos, bool&,int);
vector<Datos> FDR(const string,const string,int const);

#endif /* HEADERS_GROUP_FDR_HPP_ */
