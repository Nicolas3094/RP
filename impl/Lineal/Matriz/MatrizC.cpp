#include "../../../headers/Lineal/Matriz/MatrizC.hpp"

template<typename T>
Matriz<T>::~Matriz(){}
template<typename T>
Matriz<T>::Matriz(){
	col=0;
	row=0;
}
template<typename T>
Matriz<T>::Matriz( ulong fila, ulong columna){
	_Mat = vector<Vector<T>>(columna, Vector<T>(fila,0));
	row = fila;
	col = columna;
}
template <typename T>
Matriz<T>::Matriz(vector<Vector<T>> DATS){
	_Mat = DATS;
	col = (ulong)DATS.size();
	row = (ulong)DATS[0].Dimension();
}
template <typename T>
Matriz<T>::Matriz(Vector<T> _VEC){
	row = _VEC.Dimension();
	col = 1;
	vector<Vector<T>> NW_VEC;
	NW_VEC.push_back(_VEC);
	_Mat = NW_VEC;
}

template<typename T>
bool Matriz<T>::CUADRADA(){
	return (col==row);
}

template<typename T>
const ulong Matriz<T>::DIM(){
	return (row);
}

template <typename T>
const ulong Matriz<T>::COL(){
	return col;
}
template <typename T>
const ulong Matriz<T>::ROW(){
	return row;
}

//Añade ''vector'' columna por la izquierda
template <typename T>
void Matriz<T>::AddCol(const Vector<T>& dat, bool izq){
	if(izq){
		_Mat.push_back(dat);
		col++;
		return;
	}
	_Mat.insert(_Mat.begin(), dat);
	col++;
}
template <typename T>
void Matriz<T>::DelCol(ulong pos){
	if(pos < 0 || pos > col ) throw out_of_range( "DelCol(): Posicion fuera de rango" );
	_Mat.erase(_Mat.begin()+pos);
	col--;
}
//Añade por ''co-vector'' fila al final
template <typename T>
void Matriz<T>::AddRow(Vector<T> dat, bool izq){
	for(ulong i = 0; i<col; i++){
		if(izq){
			_Mat[i].push_back(dat[i]);
		}else{
			_Mat[i].insert(_Mat[i].begin(),dat[i]);
		}
	}
	row++;
}
template <typename T>
void Matriz<T>::DelRow(ulong pos){
	if(pos < 0 || pos > row ) throw out_of_range( "DelRow: Posicion fuera de rango" );
	for(ulong i =0; i<col; i++){
		_Mat[i].erase(_Mat[i].begin()+pos);
	}
	row--;
}
template <typename T>
Vector<T>& Matriz<T>::_Col(ulong pos){
	return _Mat[pos];
}


template <typename T>
Vector<T> Matriz<T>::_Row(ulong pos){
	Vector<T> c_vec(col,0);
	for(ulong COL = 0; COL < col; COL++){
		c_vec[COL] = _Mat[COL][pos];

	}
	return c_vec;
}
template <typename T>
Vector<T>& Matriz<T>::operator[](ulong pos){
	return _Mat[pos];
}

template <typename T>
void Matriz<T>::operator = (Matriz<T> ot){
	_Mat.clear();
	for(ulong i =0; i< ot.COL(); i++)
		_Mat.push_back(ot[i]);
	col = ot.col;
	row = ot.row;
}

template <typename T>
bool Matriz<T>::operator==( Matriz<T> ot){
	for(ulong i =0; i<ot.COL(); i++)
		for(ulong j=0; j < ot.ROW(); j++)
			if(_Mat[i][j]!=ot[i][j])
				return false;
	return true;
}

template <typename T>
Matriz<T> Matriz<T>::operator*=(T num){
	for(ulong i=0; i< col; i++){
		for(ulong j=0;j< row; j++){
			_Mat[i][j]*= num;
		}
	}
	return _Mat;
}
template <typename T>
Matriz<T> Matriz<T>::operator*(T num){
	Matriz<T> Mat=_Mat;
	for(ulong i=0; i< col; i++){
		for(ulong j=0;j< row; j++){
			Mat[i][j]*= num;
		}
	}
	return Mat;
}
template <typename T>
Matriz<T> Matriz<T>::operator/=(T num){
	for(ulong i=0; i< col; i++){
		for(ulong j=0;j< row; j++){
			_Mat[i][j]/= num;
		}
	}
	return _Mat;
}
template <typename T>
Matriz<T> Matriz<T>::operator/(T num){
	Matriz<T> Mat=_Mat;
	for(ulong i=0; i< col; i++){
		for(ulong j=0;j< row; j++){
			Mat[i][j]/= num;
		}
	}
	return Mat;
}
template <typename T>
Matriz<T> Matriz<T>::operator*(Matriz<T> Mat){
	if(col != Mat.ROW() ) throw invalid_argument( "*: Dimensiones diferentes" );
	Matriz<T> mat(row, Mat.COL());
	for(ulong i =0; i < Mat.COL() ; i++){
		for(ulong j=0; j< mat.ROW(); j++){
			T sum = 0;
			for(ulong k =0; k < col; k++)
				sum += _Mat[k][j]*Mat[i][k];
			mat[i][j] = sum;
		}
	}
	return mat;
}
template <typename T>
Matriz<T> Matriz<T>::operator+(Matriz<T> Mat){
	if(Mat.col != col || Mat.row != row) throw invalid_argument( "+: Dimensiones diferentes" );
	else{
		Matriz<T> mat = Mat;
		for(ulong i =0; i < col ; i++)
			for(ulong j=0; j< row; j++){
				mat[i][j] = _Mat[i][j] + Mat[i][j];
				if(mat[i][j]<pow(1,-10)) mat[i][j]=0;
			}
		return mat;
	}
}


template <typename T>
Matriz<T> Matriz<T>::operator-(Matriz<T> Mat){
	if(Mat.COL() != col || Mat.ROW() != row) throw invalid_argument( "-: Dimensiones diferentes" );
	Matriz<T> mat = Mat;
	for(ulong i =0; i < col ; i++)
		for(ulong j=0; j< row; j++){
			mat[i][j] = _Mat[i][j] - Mat[i][j];
			if(mat[i][j]<pow(1,-10)) mat[i][j]=0;
		}
	return mat;
}

template<typename T>
Vector<T> Matriz<T>::operator * (Vector<T> _VEC){

	if(_VEC.Dimension() != DIM() || COL()<2) throw invalid_argument( "*: Dimensiones diferentes" );
	Matriz<T> COL_VEC(_VEC), COL_VECF;
	COL_VECF = (*this)*COL_VEC;
	Vector<T> vecf(_VEC.Dimension(),0);
	for(ulong i=0; i<_VEC.Dimension(); i++) vecf[i]=COL_VECF[0][i];
	return vecf;
}

template class Matriz<float>;
template class Matriz<int>;
template class Matriz<double>;

//template class Matriz<char>;

ostream&  operator <<(ostream& COUT, Matriz<double> _Mat){
	for(ulong i =0; i< _Mat.ROW(); i++){
			for(ulong j=0; j < _Mat.COL(); j++){
				COUT << (_Mat[j][i]) << " ";
			}
			COUT << endl;
		}
		return COUT;
}
ostream&  operator <<(ostream& COUT, Matriz<float> _Mat){
	for(ulong i =0; i< _Mat.ROW(); i++){
			for(ulong j=0; j < _Mat.COL(); j++){
				COUT << (_Mat[j][i]) << " ";
			}
			COUT << endl;
		}
		return COUT;
}
ostream&  operator <<(ostream& COUT, Matriz<int> _Mat){
	for(ulong i =0; i< _Mat.ROW(); i++){
		for(ulong j=0; j < _Mat.COL(); j++){
			COUT << (_Mat[j][i]) << " ";
		}
		COUT << endl;
	}
	return COUT;
}

