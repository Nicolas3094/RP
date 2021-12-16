#include"../../headers/Group/Recocido.hpp"
double Uniform(){
	return rand()/MAX_RAN;
}
int SELECT(int i, int j){
	return i+(rand()%(j-i+1));
}
int SELECT(vector<int>& L){
	int select = (rand()%(L.size()-1));
	int res = L[select];

	return res;
}
double Pr(double E,double T){
	return exp(-(E)/T);
}
double J_C(vector<Datos> data,Cluster P){
	int n, C;
	double dst;
	n=P.p.size();
	C=P.w[0].size();
	double sum=0;
	for(int i=0; i<n; i++){
		for(int j=0; j<C; j++){
			dst =pow(Dist(data[i].data,P.centroid[j].data),2);
			dst *= P.w[i][j];
			sum+=dst;
		}
	}
	return sum;
}

vector<vector<int>> initW(int n,int C){
	vector<int> vx(C,0);
	vector<vector<int>> vc(n,vx);
	for(int i=0; i<n; i++){
		for(int j=0; j<C; j++){
			vc[i][j] = round(rand()/MAX_RAN);
		}
	}
	return vc;
}
void Centros(vector<Datos> data, Cluster& Ct){
	int N,C, suma;
	C =Ct.w[0].size();
	N=data.size();
	for(int j=0; j<C; j++){
		Vector<double> x(data[0].data.Dimension(),0);
		suma=0;
		for(int i=0; i<N; i++){
			if(Ct.w[i][j]==1){
				x += data[i].data;
				suma++;
				break;
			}
		}
		Datos rg;
		rg.clase=j+1;
		rg.data=x/suma;
		rg.pos=j;
		Ct.centroid.push_back(rg);
	}
}

Cluster SA(vector<Datos> data,int MaxIt, double Ti, double mu, double Tf, Cluster C0){
	Cluster Cp,C=C0;
	double T,delta,prob;
	T=Ti;
	do{
		for(int i=0; i<MaxIt; i++){
			Cp = Delta(C);
			Centros(data,Cp);
			delta = J_C(data,Cp)-J_C(data,C);
			prob = Pr(delta,T);
			if(delta<0 || prob >= Uniform()){
				C=Cp;
			}
		}
		T = mu*T;
	}while(T>Tf);
	return C;
}

Cluster Delta(Cluster P){
	Cluster Pp;

	int C = P.w[0].size();
	int n = P.w.size();
	vector<int> L, Lc;
	map<int, bool> visit;
	vector<int> pp;
	for(int i=0; i<n; i++){
		for(int j=0; j<C; j++){
			if(P.w[i][j]==1){
				if(visit[j]) break;
				visit[j]=true;
				L.push_back(P.p[i]);
				break;
			}
		}
	}
	for(int j=1; j<=C; j++){
		bool add = true;
		for(auto val : L){
			if(val==j){
				add=false;
				break;
			}
		}
		if(add){
			Lc.push_back(j);
		}
	}

	Pp.p=P.p;
	Pp.w=P.w;
	int i = SELECT(1,n);
	do{
		int m = SELECT(0,L.size());
		if(L.size()==C || m>0){
			Pp.p[i]=SELECT(L);

		}else{
			Pp.p[i]=SELECT(Lc);
		}
	}while(Pp.p[i]==P.p[i]);
	Pp.w[i][Pp.p[i]]=1;
	Pp.w[i][P.p[i]] =0;

	return Pp;
}
void initP(vector<Datos> data,Cluster& C){
	int K = C.w[0].size();
	vector<int> p;
	for(unsigned i=0; i< data.size(); i++){
		  for(int j=0; j<K; j++){
			  if(C.w[i][j]==1){
				  p.push_back(j+1);
				  break;
			  }
		  }
	}
	Centros(data, C);
	C.p = p;
}
void RecocidoSimulado(string const IN, string const OUT){
	  vector<Datos> data;
	  Cluster P;
	  int K, dim, iter;
	  double Ti,Tf, mu;
	  print("Temperatura inical  (Para datos grandes se recomienda aprox 200):");
	  cin >> Ti;
	  print("Temperatura final  (aprox. 10):");
	  cin>>Tf;
	  print("Factor mu de Temperatura (<1): ");
	  cin>>mu;
	  print("Iteraciones (aprox 20): ");
	  cin>>iter;
	  ReadFl(IN, data,K,dim);
	  K=data.size() + round((rand()/MAX_RAN)*20);

	  P.w  =initW(data.size(),K);
  	  initP(data,P);
 	  Cluster NewC = SA(data,iter,Ti,mu,Tf,P);

 	  vector<int> validCls;
 	  map<int, bool> visit;
 	  ofstream outfile(OUT +to_string(K)+"Recocido.dat");
 	  outfile << "@Programa C++ para el algoritmo Recocido Simulado" << endl;
 	  outfile << "@Numvariables " << dim << "\n";
 	  for(unsigned i=0; i<data.size(); i++){
 		  data[i].clase = NewC.p[i];
 		  if(visit[NewC.p[i]]) continue;
 		  visit[NewC.p[i]] = true;
 		  validCls.push_back(NewC.p[i]);
 	  }
 	  outfile << "@NumClasesInicial " << K << "\n";
 	  outfile << "@NumClases " << validCls.size() << "\n";
 	  outfile << "@Ti " << Ti << "\n";
 	  outfile << "@Tf " << Tf << "\n";
 	  outfile << "@mu " << mu << "\n";
 	 outfile << "@NumIteraciones " << iter << "\n";
 	 for(Data dt: data){
 		 outfile << dt <<", "<< dt.clase << endl;
 	 }

 	 print("Terminado con exito: Recocido Simulado");
}
