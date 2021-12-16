#include"../../headers/Group/Bayes.hpp"

double PXY(int pos, double X, double Y, vector<Datos> data,Vector<double> Ny){
	double cont=0.0;
	for(int i = 0; i<data.size();i++){
		if(data[i].data[pos]==X  && data[i].clase==Y) cont++;
	}
	return cont/Ny[Y-1];
}
double PrXY(Vector<double> Xi, double Y, vector<Datos> data,Vector<double> Ny){
	double prob=1.0;
	for(int i=0; i<Xi.size();i++){
		prob*= PXY(i,Xi[i], Y, data, Ny);
	}
	return prob;
}
double Cmedia(vector<Datos> dat, int xi, int Y){
	float md=0.0;
	float n=0.0;
	for(int i=0 ; i<dat.size(); i++){
		if(dat[i].clase==Y){
			md += dat[i].data[xi];
			n++;
		}
	}
	md/=n;
	return md;
}
Vector<double> CMedia(vector<Datos> Conj, int cls){
	int ns=0,dim = Conj[0].data.Dimension();
	Vector<double> md(dim,0.0);
	for(int X=0; X<dim; X++){
		md[X]= Cmedia(Conj,X, cls);
	}
	return md;
}
double media(vector<Datos> dat, int xi){
	float md=0.0;
	for(int i=0 ; i<dat.size(); i++){
		md += dat[i].data[xi];
	}
	md/=dat.size();
	return md;
}

Vector<double> VMedia(vector<Datos> Conj){
	int dim = Conj[0].data.Dimension();
	Vector<double> md(dim,0.0);
	for(int i=0; i<dim; i++){
		md[i] = media(Conj,i);
	}
	return md;
}
Matriz<double> cov(vector<Datos> dat, int C){
	ulong n = dat.size();
	ulong dim = dat[0].data.size();
	Matriz<double> v1,vt,v;
	Matriz<double> cero=SMATRIZ<double>::ID(dim);
	cero =cero-cero;
	v1 = Matriz<double>(VMedia(dat));
	vt = SMATRIZ<double>::T_(v1);
	v= (v1*vt);
	v*=(n/(n-1));
	for(int i=0; i<dat.size();i++){
		Matriz<double> xi = Matriz<double>(dat[i].data);
		Matriz<double> xt = SMATRIZ<double>::T_(xi);
		cero =cero + xi*xt;
	}
	cero = cero/(n-1);
	return(cero);
}
void Gauss(vector<Datos>& data, vector<Datos>& data2,int const CL, int const DM){
	//Vector Mu por clase
	vector<Vector<double>> media(CL,Vector<double>(DM,0.0));

	//Matriz Cov por clase
	vector<Matriz<double>> cov(CL);

	//Calcula vector mu y matriz de covarianza;
	for(int i=0; i< CL; i++){
		media[i] = CMedia(data,i+1);
		cov[i] = COV(data,i+1);
	}
	//clasifica por FD
	for(int i =0; i< data2.size(); i++){
		double aux,max,cls;
		cls=1;
		max=fd(data2[0].data,1, media[0],cov[0]);
		for(int j=0; j<CL;j++){
			aux = fd(data2[i].data,j+1, media[j],cov[j]);
			if(aux>max){
				cls=j+1;
				max=aux;
			}
		}
		data2[i].clase=cls;
	}
}
double fd(Vector<double> xi,int C, Vector<double> vecMed, Matriz<double> Cv){
	Matriz<double> fd1,fd2;
	Matriz<double> xt(xi),m,mt,Ci;
	m = Matriz<double>(vecMed);
	mt=SMATRIZ<double>::T_(m);
	xt = SMATRIZ<double>::T_(xt);
	Ci= Cv;
	Ci = SMATRIZ<double>::INV_(Ci);
	fd1 = (xt*Ci)*m;
	fd2 = mt*(Ci*m);
	fd2 *= 0.5;
	return (fd1[0][0]-fd2[0][0]);
}
Matriz<double> COV(vector<Datos> data,int C){
	int dim = data[0].data.Dimension();
	Matriz<double> mx=SMATRIZ<double>::ID(dim);
	for(int X=0; X<dim; X++){
		for(int Y=0; Y<dim; Y++){
			mx[X][Y]=Sxy(data,X,Y,C);
		}
	}
	return mx;
}
double Sxy(vector<Datos> data,int x,int y,int C){
	double c1,c2,mediax,mediay ;
	mediax = Cmedia(data,x,C);
	mediay = Cmedia(data,y,C);
	double n=0,sum=0;
	for(int i=0; i<data.size(); i++){
		if(data[i].clase==C){
			n++;
			sum += (data[i].data[x]-mediax)*(data[i].data[y] -mediay);
		}
	}
	sum /=(n-1);
	return sum;
}
double VAR(vector<Datos> data,int X,int C){
	return Sxy(data,X,X,C);
}

void NaiveB(vector<Datos>& data,vector<Datos>& dat2,int const CL, int const DM){
	//Acumulado de clase
	Vector<double> N_Y(CL,0.0);
	//Probabilidad de clase
	Vector<double> PR_C(DM,0.0);
	//Calcula frecuencias
	for(int i=0; i<data.size(); i++){
		for(int j=0; j<CL; j++){
			if(data[i].clase ==j+1){
				N_Y[j]++;
				break;
			}
		}
	}
	//Probabilidad de clase
	PR_C = N_Y/(N_Y.Sum());

	for(int i =0; i< dat2.size(); i++){
		double aux,max,cls;
		cls=1;
		max=PrXY(dat2[0].data,1,data,N_Y);
		for(int j=1; j<CL;j++){
			aux = PrXY(dat2[i].data, j+1,data, N_Y);
			if(aux>max){
				cls=j+1;
				max=aux;
			}
		}
		dat2[i].clase=cls;
	}
}
void Bayes(const string name, const string name2){

	vector<Datos> data, data2, wi;
	int CLASES, DIM, cls2, dim2;
	ReadFl(PATH_IN+name+".txt", data, CLASES, DIM);
	ReadFl(PATH_IN+name2+".txt", data2, cls2, dim2);

	int const CL = CLASES;
	int const DM = DIM;

	Gauss(data,data2,CL,DM);

	//NaiveB(data,data2,CL,DM);

	ofstream outfile(PATH_IN+"Bayes/Gauss" +name2+ ".dat");
	outfile << "@Programa C++ para el algoritmo Bayes Gauss" << endl;
	for(int i=0; i<data2.size(); i++){
		print(data2[i]<<","<<data2[i].clase);
		outfile<<data2[i]<<","<<data2[i].clase<<endl;
	}
	outfile.close();
}
