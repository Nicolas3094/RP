#include "../../../headers/Lineal/Vector/VecOp.hpp"
template<typename T>
const double V_OPERATOR<T>::DIST( Vector<T> v1,  Vector<T> v2){
	Vector<T> res = v1-v2;
	return res.Magnitud();
}
template<typename T>
const int V_OPERATOR<T>::DELTA_KR(ulong i,ulong j){
	return (i==j?1:0);
}
template<typename T>
Vector<T> V_OPERATOR<T>::UNIT(Vector<T> vec){
	const double magnitud = vec.Magnitud();
	return vec/magnitud;
}
template class V_OPERATOR<int>;
template class V_OPERATOR<double>;
template class V_OPERATOR<float>;

ostream&  operator <<(ostream& COUT, Vector<double>& DAT){
    COUT << "(";
    for(unsigned i = 0; i< DAT.size(); i++){
        COUT <<DAT[i];
        if(i!=DAT.size()-1){
            COUT << ", ";
        }
    }
    COUT << ")";
    return COUT;
}
ostream&  operator <<(ostream& COUT, Vector<int>& DAT){
    COUT << "(";
    for(unsigned i = 0; i< DAT.size(); i++){
        COUT <<DAT[i];
        if(i!=DAT.size()-1){
            COUT << ", ";
        }
    }
    COUT << ")";
    return COUT;
}

Vector<float> operator*(float val,Vector<float> vec){
	Vector<float> res = vec*val;
	return (res);
}
Vector<int> operator*(int val,Vector<int> vec){
	Vector<int> res = vec*val;
	return (res);
}
Vector<double> operator*(double val,Vector<double> vec){
	Vector<double> res = vec*val;
	return (res);
}

Vector<float> operator/(float val,Vector<float> Vec){
	Vector<float> vec= Vec;
	for(ulong i=0; i<vec.Dimension(); i++){
		vec[i] = val/vec[i];
		if(vec[i]<pow(1,10)) vec[i]=0;
	}
	return vec;
}
Vector<int> operator/(int val,Vector<int> Vec){
	Vector<int> vec= Vec;
	for(ulong i=0; i<vec.Dimension(); i++){
		vec[i] = val/vec[i];
		if(vec[i]<pow(1,10)) vec[i]=0;
	}
	return vec;
}
Vector<double> operator/(double val,Vector<double> Vec){
	Vector<double> vec= Vec;
	for(ulong i=0; i<vec.Dimension(); i++){
		vec[i] = val/vec[i];
		if(vec[i]<pow(1,10)) vec[i]=0;
	}
	return vec;
}

double Dist(const vector<int>& v1,const vector<int>& v2){
    if(v1.size() != v2.size())throw invalid_argument( "Dist: Diferente dimension" );
    if(v1.size() != v2.size()) return -1;
    if(v1 == v2) return 0;
    double res=0;
    for(unsigned i = 0; i < v1.size(); i++){
        res += pow(v1[i]-v2[i],2);
    }
    return sqrt(res);
}
double Dist(const vector<double>& v1,const vector<double>& v2){
    if(v1.size() != v2.size())throw invalid_argument( "Dist: Diferente dimension" );
    if(v1.size() != v2.size()) return -1;
    if(v1 == v2) return 0;
    double res=0;
    for(unsigned i = 0; i < v1.size(); i++){
        res += pow(v1[i]-v2[i],2);
    }
    return sqrt(res);
}
double Dist(const vector<float>& v1,const vector<float>& v2){
    if(v1.size() != v2.size())throw invalid_argument( "Dist: Diferente dimension" );
    if(v1 == v2) return 0;
    double res=0;
    for(unsigned i = 0; i < v1.size(); i++){
        res += pow(v1[i]-v2[i],2);
    }
    return sqrt(res);
}
