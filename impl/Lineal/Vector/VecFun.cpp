#include "../../../headers/Lineal/Vector/VecFun.hpp"

double round_up(double value, int decimal_places) {
    const double multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}

template<typename T> Vector<T>::Vector():vector<T>(){
}
template<typename T> Vector<T>::Vector(const vector<T>& cp):vector<T>(cp){
}
template<typename T> Vector<T>::Vector(ulong tm, T val):vector<T>(tm,val){
}

template<typename T>const double Vector<T>::Magnitud(){
	return sqrt((*this)*(*this));
}
template<typename T>const ulong Vector<T>::Dimension(){
	return vector<T>::size();
}

template<typename T> Vector<T> Vector<T>::operator*(T val){
	Vector<T> vec= (*this);
	for(ulong i=0; i<vec.size(); i++){
		vec[i] *= val;
	}
	return vec;
}
template<typename T>Vector<T> Vector<T>::operator/(T val){
	Vector<T> vec= (*this);
	for(ulong i=0; i<vec.size(); i++){
		vec[i] /= val;
	}
	return vec;
}
template<typename T>const T Vector<T>::operator*( Vector<T> v2){
	T sum =0;
	Vector<T> v1=*this;
	Vector<T> vec = v1.Dimension()>v2.Dimension()?v2:v1;
	for(ulong i = 0; i<vec.Dimension(); i++)
		sum += v1[i]*v2[i];
	return sum;
}
template<typename T> Vector<T> Vector<T>::operator+(Vector<T> vec2){
	Vector<T> vec1 = *this;
		Vector<T> res(vec1 > vec2 ? vec1.Dimension():vec2.Dimension(), 0);
		for(unsigned i=0; i<res.size(); i++){
			if(i > vec1.size()-1) res[i]+= vec2[i];
			else if(i > vec2.size()-1) res[i]+=vec1[i];
			else res[i] += vec1[i]+vec2[i];
		}
		return res;
}
template<typename T> Vector<T> Vector<T>::operator-(Vector<T> vec2){
	Vector<T> vec1 = *this;
	Vector<T> res(vec1 > vec2 ? vec1.Dimension():vec2.Dimension(), 0);
	for(unsigned i=0; i<res.size(); i++){
		if(i > vec1.size()-1) res[i]-= vec2[i];
		else if(i > vec2.size()-1) res[i]-=vec1[i];
		else res[i] += vec1[i]-vec2[i];
	}
	return res;
}
template<typename T> void Vector<T>::operator += (Vector<T> vec2){
	for(ulong i=0; i<Dimension(); i++){
		if( i>vec2.Dimension()-1 ) break;
		(*this)[i] += vec2[i];
	}
}
template<typename T> void Vector<T>::operator-=(Vector<T> vec2){
	for(ulong i=0; i<Dimension(); i++){
		if( i>vec2.Dimension()-1 ) break;
		(*this)[i] -= vec2[i];
	}
}
template<typename T>const T Vector<T>::operator*=( Vector<T> v2){
	return (*this)*v2;
}

template<typename T> void Vector<T>::operator*=(T val){
	for(ulong i=0; i<Dimension(); i++)
		(*this)[i] *= val;
}
template<typename T> void Vector<T>::operator/=(T val){
	for(ulong i=0; i<Dimension(); i++)
		(*this)[i] /= val;
}
template<typename T>
T Vector<T>::Sum(){
	T sum = 0;
	for(ulong i=0; i<Dimension();i++){
		sum += (*this)[i];
	}
	return sum;
}
template class Vector<char>;
template class Vector<int>;
template class Vector<float>;

template class Vector<double>;
