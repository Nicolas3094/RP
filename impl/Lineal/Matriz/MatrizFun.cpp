#include "../../../headers/Lineal/Matriz/MartizFun.hpp"


template<typename T>
Matriz<T> SMATRIZ<T>::ID(ulong longitud){
	Matriz<T> inv(longitud,longitud);
	for(ulong i=0 ; i < longitud; i++){
		inv[i][i]=1;
	}
	return inv;
}
template<typename T>
Matriz<T> SMATRIZ<T>::T_(Matriz<T> Mat){
	Matriz<T> tr(Mat.COL(), Mat.ROW());
	for(ulong i=0; i<tr.ROW(); i++)
		for(ulong j =0; j<tr.COL(); j++)
			tr[j][i]=Mat[i][j];
	return tr;
}
template<typename T>
Matriz<T> SMATRIZ<T>::ESC_(Matriz<T> Mat, bool BOTTOM){
	Matriz<T> res = Mat;
	for(ulong i = 0; i < Mat.ROW(); i++){
		ulong INDEX = BOTTOM ? i : Mat.ROW()-i-1;
		T pivot = res[INDEX][INDEX];
		Vector<T> v_pivot= res._Row(INDEX);
		for(ulong j =0; j< i; j++){
			if(i==0 ) break;
			ulong J =BOTTOM ? j : Mat.ROW()-1-j;
			if(v_pivot[J] != 0 ){
				Vector<T> v_o = res._Row(J);
				T VALUE= v_pivot[J]/v_o[J];
				Vector<T> res_v = (VALUE*v_o)-v_pivot;
				for(ulong k = 0; k < res_v.Dimension(); k++)
					res[k][INDEX] = res_v[k];
				v_pivot= res._Row(INDEX);
				pivot =v_pivot[INDEX];
			}
		}
		if(pivot==0)
			for(ulong COL = 0; COL < res.COL(); COL++)
				res[COL][INDEX] += 1;
		else if(pivot != 1)
			for(ulong COL = 0; COL < res.COL(); COL++)
				res[COL][INDEX] /= pivot;
	}
	return res;
}

template<typename T>
Matriz<T> SMATRIZ<T>::INV_(Matriz<T> Mat){
	if(!Mat.CUADRADA()) throw invalid_argument( "INV_(): Matriz tiene que ser cuadrada." );

	Matriz<T> RES=SMATRIZ::EXT_(Mat, SMATRIZ::ID(Mat.DIM()));
	RES = SMATRIZ<T>::ESC_(RES, true);
	RES = SMATRIZ<T>::ESC_(RES, false);
	for(ulong i =0; i < Mat.DIM(); i++)
		RES.DelCol(0);
	return RES;
}
template<typename T>
Matriz<T> SMATRIZ<T>::EXT_(Matriz<T> Mat, Matriz<T> Mat2){
	Matriz<T> RES = Mat;
	for(ulong i=0; i<Mat2.COL(); i++)
		RES.AddCol(Mat2[i], true);
	return RES;
}


template<typename T>
const T SMATRIZ<T>::TRAZA( Matriz<T> MAT) {
	if(!MAT.CUADRADA()) throw invalid_argument( "TRAZA(): Matriz tiene que ser cuadrada." );
	T sum=0;
	for(ulong i=0; i<MAT.DIM(); i++)
		sum += MAT[i][i];
	return sum;
}




template class SMATRIZ<double>;
template class SMATRIZ<float>;
template class SMATRIZ<int>;
