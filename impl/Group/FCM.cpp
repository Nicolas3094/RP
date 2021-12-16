#include "../../headers/Group/FCM.hpp"

double FObject(double** mat,vector<Datos> xi,vector<Datos> ck,int m){
	double sum=0;
	for(int i=0; i<xi.size(); i++){
		for(int j=0; j<ck.size(); j++){
			sum += pow(mat[i][j],m)*pow(Dist(xi[i].data,ck[j].data),2);
		}
	}
	return sum;
}
void NuCentro(double** mat,vector<Datos> xi,vector<Datos>& ck,int m){
	int N,C;
	N=xi.size();
	C=ck.size();
	double f1,f2;
	Vector<double> x;
	for(int j=0; j<C; j++){
		f2=0;
		x.clear();
		for(int i=0 ; i<xi[0].data.size(); i++){
			x.push_back(0);
		}
		for(int i=0; i<N; i++){
			f1= pow(mat[i][j],m);
			x += xi[i].data*f1;
			f2+= f1;
		}
		x = x/f2;
		ck[j].data=x;
	}

}
double MaxM(double** m1,double** m2,int N,int C){
	double res=0;
	for(int i=0; i<N; i++){
	   	for(int j=0; j<C; j++){
	   		double max = abs(pow(m1[i][j],1)-pow(m2[i][j],1));
	   		if(max>res) res=max;
	   	}
	 }

	 return res;
}
void EqualM(double** m1,double** m2,int N,int C){
	 for(int i=0; i<N; i++){
	   	for(int j=0; j<C; j++){
	   		m2[i][j]=m1[i][j];
	  	}
	  }
}
void Member(double** mat, vector<Datos> xi,vector<Datos> ck,int m){
	int N,C;
	N= xi.size();
	C=ck.size();
	double suma;
	for(int i=0; i<N;i++){
		suma=0;
		for(int j=0; j<C; j++){
			mat[i][j] = membresia(xi[i],j,ck,m);
			suma += mat[i][j];
		}
	}

}
double membresia(Datos xi,int j, vector<Datos> cj,int m){
	double dij=Dist(xi.data,cj[j].data);
	double sum=0;
	for(int k=0; k<cj.size(); k++){
		double dik = Dist(xi.data,cj[k].data);
		sum += pow(dij/dik,2/(m-1));
		if(dik==0 && dij == 0){
			sum=1;
			break;
		}


	}
	sum = 1/sum;
	if(sum>1) throw std::invalid_argument("Membresia mayor a 1.");
	return sum;
}

void FCM(string const PATH_IN, string const PATH_OUT, int const K)
{
    vector<Datos> data,centroids,aux, original;
    int cls, dim, N,C;
    double epsilon,m, **uaux;
    C=K;
    print("Digite el valor difusivo m>1: ");
    cin>>m;
    print("Digite el valor de epsilon: ");
    cin>>epsilon;
    bool itr = true;

    ReadFl(PATH_IN, data,cls,dim);
    ofstream outfile(PATH_OUT +"FCM"+PATH_IN);
    N=data.size();

    double** u=new double*[N];
    uaux = new double*[N];
    for(int i=0; i<N; i++){
    	u[i]=new double[C];
    	uaux[i]=new double[C];
    	for(int j=0; j<C; j++){
    		u[i][j]=0;
    		uaux[i][j]=0;
    	}
    }
    Centroides(data, centroids, K); //centroides aleatorios
    int k=0;
    double max;

    while (itr){
       Member(u,data,centroids,m); //actualiza uij
       NuCentro(u,data,centroids,m); //actualiza centroides
       k++;
       if(k==1){
    	   EqualM(u,uaux,N,C);
    	   continue;
       }
       max = MaxM(u,uaux,N,C);
       if(epsilon > max) break;
       EqualM(u,uaux,N,C);

    }

    outfile << "@Programa C++ para el algoritmo C-MEANS Difuso" << endl;
    outfile << "@Numvariables " << dim << "\n";
    outfile << "@NumClases " << K << "\n";
    outfile << "@Epsilon " << epsilon<< "\n";
    outfile << "@m " << m<< "\n";
    for(Datos data : centroids){
        outfile <<"@Centroide ";
        outfile<<data<<","<<data.clase<<endl;
    }
    outfile << "@Nomvariables ";
    for(int i=0; i<dim; i++){
    	outfile <<"x"<<i+1<<" ";
    }
    for(int i=0; i<C; i++){
    	outfile<<"C"<<i+1<<" ";
    }
    outfile<<endl;
    for (unsigned j = 0; j < N; j++){
      	outfile << data[j]<<", ";
      	for(int k=0; k<C; k++){
      		outfile<< u[j][k]<<",";
      	}
      	outfile<<endl;
    }
    print("Termina k-means difuso correctamente.");
    for(int i=0; i<N; i++){
    	u[i]=nullptr;
    	uaux[i]=nullptr;
    	delete[] u[i];
    	delete[] uaux[i];
    }
    u = nullptr;
    delete[] u;
    uaux=nullptr;
    delete[] uaux;
}
