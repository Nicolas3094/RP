

#ifndef HEADERS_LINEAL_MATRIZ_MARTIZFUN_HPP_
#define HEADERS_LINEAL_MATRIZ_MARTIZFUN_HPP_

#include "MatrizC.hpp"

template<typename T>
class SMATRIZ{
    public:
        static Matriz<T> ID(ulong);
        static Matriz<T> T_(Matriz<T>);
        static Matriz<T> INV_( Matriz<T>);
        static Matriz<T> ESC_( Matriz<T>, bool BOTTOM);
        static Matriz<T> EXT_( Matriz<T>, Matriz<T>);
        static const T TRAZA( Matriz<T>) ;

};


#endif /* HEADERS_LINEAL_MATRIZ_MARTIZFUN_HPP_ */
