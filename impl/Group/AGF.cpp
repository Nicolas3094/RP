#include "../../headers/Group/AGF.hpp"

vector<vector<double>> FuzzyC(vector<Datos>& data, vector<Datos>& centroids, int m, double epsilon, int C){
	int N;
	N=data.size();
	vector<vector<double>> vc(N,vector<double>(C,0));
	double **uaux,** u=new double*[N];
	uaux = new double*[N];
	for(int i=0; i<N; i++){
	 	u[i]=new double[C];
	  	uaux[i]=new double[C];
	  	for(int j=0; j<C; j++){
	  		u[i][j]=0;
	   		uaux[i][j]=0;
		}
	}
	Centroides(data, centroids, C); //centroides aleatorios
	int k=0;
	double max;

	while (true){
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

	for(int i=0; i<N; i++){
		for(int j=0; j<C; j++){
			vc[i][j] = u[i][j];
		}
	}
	for(int i=0; i<N; i++){
		u[i]=nullptr; uaux=nullptr;
		delete[] u[i]; delete[] uaux;
	}
	u=nullptr; uaux = nullptr;
	delete[] u; delete[] uaux;

	return vc;
}
Vector<double> CentroideDatos(vector<Datos> dat){
	Vector<double> vec(0,dat[0].data.Dimension());
	for(auto vect : dat){
		vec+= vect.data;
	}
	return vec/dat.size();
}

vector<vector<Grupo>> PoblacionIni(vector<Data> dat, int poblacion, int m, double epsilon, int C){
	vector<vector<Grupo>> v;
	vector<Grupo> grupos;
	vector<Datos> centroids;
	for(int i=0; i<poblacion; i++){
		FuzzyC(dat,centroids,m,epsilon,C);
		for(Datos centro : centroids){
			Grupo g1;
			g1.centroid = centro.data;
			g1.etiqueta=centro.clase;
			grupos.push_back(g1);
		}
		centroids.clear();
		v.push_back(grupos);
		grupos.clear();
	}
	return v;
}

double Uij(vector<Datos> xi,vector<Grupo> ck,int i, int j, int m){
	double r1,r2,uij;
	uij=0;
	r1 = Dist(xi[i].data, ck[j].centroid);
	for(unsigned k=0; k<ck.size();k++){
		r2 = Dist(xi[i].data, ck[j].centroid);
		uij += pow(r1/r2,2/(m-1));
	}
	return 1/uij;
}
double Jm(vector<Datos> xi,vector<Grupo> ck,int m){
	double sum=0;
	for(unsigned i=0; i<xi.size(); i++){
		for(unsigned j=0; j<ck.size(); j++){
			sum += pow(Uij(xi,ck,i,j,m),m)*pow(Dist(xi[i].data,ck[j].centroid),2);
		}
	}
	return sum;
}
vector<double> GetProb(vector<Datos> data,vector<vector<Grupo>> poblacionI, int m){
	  	 vector<double> fitnesPob;
		 float sum = 0;
		 for(vector<Grupo> value: poblacionI){
		   	double res = Jm(data,value,m);
		   	fitnesPob.push_back(1/res);
		  	sum += 1/res;
		 }
		 for(auto& vl : fitnesPob){
		 	vl = vl/sum;
		 }
		 return fitnesPob;
}
void GeTMaximum(vector<double> , int& , int& );
void GeTMaximum(vector<double> arr, int& max1, int& max2){
	double ps=0;
	int pos;
	for(int i=0; i< arr.size(); i++){
		if(ps<arr[i]){
			ps=arr[i];
			pos=i;
		}
	}
	max1=pos;
	ps=0;
	for(int i=0; i< arr.size(); i++){
		if(ps<arr[i] && i!=max1){
			ps=arr[i];
			pos=i;
		}
	}
	max2 = pos;
}
vector<int> SelectionParents(vector<Datos> data, vector<vector<Grupo>> poblacionI,int m){
	vector<double> probPobl;
	vector<int> positions;
	int max1, max2;
	probPobl = GetProb(data, poblacionI, m);
	GeTMaximum(probPobl,max1,max2);
	positions.push_back(max1);
	positions.push_back(max2);
	return positions;
}

vector<Grupo> Cruza(vector<Grupo> g1, vector<Grupo> g2){
	vector<Grupo> hijo;
	map<int, bool> visit,visit2;
	for(int i=0; i<g1.size(); i++){
			if(i<g1.size()/2){
				int pos = int((rand()/MAX_RAN)*g1.size());
				if(visit[pos]) {
					i--;
					continue;
				}
				visit[pos]=true;
				hijo.push_back(g1[pos]);
			}else{
				int pos = int((rand()/MAX_RAN)*g1.size());
				if(visit2[pos]) {
					i--;
					continue;
				}
				visit2[pos]=true;
				hijo.push_back(g2[pos]);
			}

		}
    Mutation(hijo);
	return hijo;
}

void Mutation(vector<Grupo>& hijo){
	for(int i=0; i<hijo.size(); i++){
		int pos = int((rand()/MAX_RAN)*hijo[i].centroid.size());
		hijo[i].centroid[pos] += (int(rand()/MAX_RAN)==0 ? -1 : 1)*(rand()/MAX_RAN)*5;
	}
}

void Normalization(vector<Datos> data,vector<Grupo>& g, int m, double epsilon, int C){
	vector<Datos> centroids;
	int N = data.size();
	int k=0;
	double max;

	double **uaux,**u;
	u=new double*[N];
	uaux = new double*[N];
	for(int i=0; i<N; i++){
	 	u[i]=new double[C];
	  	uaux[i]=new double[C];
	  	for(int j=0; j<C; j++){
	  		u[i][j]=0;
	   		uaux[i][j]=0;
		}
	}
	for(unsigned i=0; i<g.size(); i++){
		Datos dat;
		dat.data= g[i].centroid;
		dat.clase = g[i].etiqueta;
		dat.pos=i;
		centroids.push_back(dat);
	}

	while (true){
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
	for(int i=0; i<C; i++){
		g[i].centroid=centroids[i].data;
		for(int k=0; k<N; k++){
			g[i].pts.push_back(u[k][i]);
		}
	}
	for(int i=0; i<N; i++){
		u[i]=nullptr; uaux=nullptr;
		delete[] u[i]; delete[] uaux;
	}
	u=nullptr; uaux = nullptr;
	delete[] u; delete[] uaux;

}


void Discrimiar(vector<Data>data,vector<vector<Grupo>> pob, int m, int NumPob){
	vector<double>  probPobl = GetProb(data, pob, m);
	if(pob.size()==NumPob) return;
	double min=1;
	int pos;
	for(int i=0; i< probPobl.size(); i++){
		if(probPobl[i]<min){
			min =probPobl[i];
			pos=i;
		}
	}
	pob.erase(pob.begin()+pos);
	return Discrimiar(data,pob,m,NumPob);

}
vector<Grupo> MejorInd(vector<Data>data,vector<vector<Grupo>> pob, int m){
	vector<double>  probPobl = GetProb(data, pob, m);
	double min=1;
	int pos;
	for(int i=0; i< probPobl.size(); i++){
		if(probPobl[i]<min){
			min =probPobl[i];
			pos=i;
		}
	}
	return pob[pos];
}
void AGD(string const IN, string const OUT){

		int cls, dim, N,C,NumPob,iter;
		double epsilon,m;
		vector<Datos> data;
		vector<vector<Grupo>> poblacionI;
		vector<double> probPobl;
		iter=10;
		print("Numero de generaciones: ");
		cin>>iter;
		print("Numero de clases: ");
	    C=4;
		cin>>C;
		print("Numero de poblaciones: ");
		NumPob = 5;
		cin>>NumPob;
		print("Valor difuso m : ");
	    m=2;
	    cin >> m;
	    print("Valor de epsilon: ");
	    epsilon=0.01;
	    cin>>epsilon;

	    ReadFl(IN, data,cls,dim);


	    poblacionI = PoblacionIni(data,NumPob,m,epsilon,C);

	    for(int i=0; i<iter; i++){

	    	Discrimiar(data, poblacionI, m,NumPob);

	    	vector<int> parents =  SelectionParents(data, poblacionI, m);

	    	vector<Grupo> p1 = poblacionI[parents[0]];
	    	vector<Grupo> p2 = poblacionI[parents[1]];

   		    vector<Grupo> hijo=Cruza(p1,p2);

  		    Normalization(data,hijo,m,epsilon,hijo.size());

  		    poblacionI.push_back(hijo);
	    }

	    vector<Grupo> besG =MejorInd(data,poblacionI,m);

	    ofstream outfile(OUT+"DGeneticAlgorithm.txt");
	    outfile <<"@Algoritmo genético difuso."<<endl;
	    outfile << "@Numvariables " << dim << endl;
	    outfile << "@NumClases " << C << endl;
	    outfile << "@Epsilon " << epsilon<< endl;
	    outfile << "@m " << m<< endl;
	    outfile << "@NumPoblacion " << NumPob<< endl;
	    outfile << "@Iteraciones "  << iter << endl;
	    outfile << "@Nomvariables ";
	    for(int i=0; i<dim; i++){
	       	outfile <<"x"<<i+1<<" ";
	    }
	    outfile<<endl;
	    for (unsigned j = 0; j < data.size(); j++){
	       	outfile << data[j]<<", ";
	       	for(int k=0; k<C; k++){
	       		outfile<<besG[k].pts[j]<<",";
	       	}
	       	outfile<<endl;
	    }
}
