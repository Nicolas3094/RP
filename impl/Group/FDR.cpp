#include "../../headers/Group/FDR.hpp"
//funcion discriminante
double fd(Datos z1,Datos x2){
	return (x2.data*z1.data);
}
//Evalua si los datos de entrada "wi" cumplen para TODOS los elementos del conjunto de datos "data"
void evalSet(vector<Datos>& wi, vector<Datos> data,bool& eq, int factor){
	vector<Datos> DAT = data;
	int cs =1;
	bool rs=false;
	bool boolval[DAT.size()];
	for(int i =0; i<DAT.size(); i++){
		boolval[i]=false;
	}
	int j=0;
	while(!DAT.empty()){
		Datos dat;
		for(int i=0; i<DAT.size(); i++){
		 	if(DAT[i].clase==cs){
		 		dat=DAT[i];
		 		DAT.erase(DAT.begin()+i);
		  		if(cs==wi.size()) cs=1;
		    	else cs++;
		    	break;
		    }
		 }
		evalFD(wi,dat,rs,factor);
		boolval[j++]=rs;
	}
	for(int i =0; i<data.size(); i++){
		eq=true;
		if(!boolval[i]){
			eq=false;
			break;
		}
	}
}

//Evalua si los datos de entrada "ws" cumplen para el dato "data"
void evalFD(vector<Datos>& ws, Datos data, bool& EQ,int factor){
	bool ch[ws.size()];
	for(int i=0; i< ws.size(); i++){
		int sgn = 0;
    	float fdi = fd(ws[i],data);
    	ch[i]=true;
    	if(ws[i].clase==data.clase){
    		if(fdi<=0) sgn=1;
    	}else{
    		if(fdi>=0) sgn=-1;
	  	}
    	if(sgn!=0){
			ch[i]=false;
			ws[i].data += sgn*factor*data.data;
    	}
	  }
	for(bool bl : ch){
		if(bl) EQ=true;
		else{
			EQ=false;
			break;
		}
	}
}
vector<Datos> FDR(const string name,const string name2, int const factor){
		vector<Datos> data,data2, wi;
	    string const nm=name;
	    int CLASES, DIM,cls,dm;

	    ReadFl(PATH_IN+nm+".txt", data, CLASES, DIM);
	    ReadFl(PATH_IN+name2+".txt", data2, cls, dm);

	    //Crea vectores extendidos wi's en 0's
	    for(int i=0; i<CLASES; i++){
	    	Datos dat;
	    	dat.clase=i+1;
	    	for(int j=0; j<=DIM; j++){
	    		dat.data.push_back(0);
	    	}
	    	wi.push_back(dat);
	    }

	    //extender al factor
	    for(Datos& dato : data){
	    	dato.data.push_back(factor);
	    }

	    bool EST,eq = false;
	    EST=true;
	    //iterar hasta encontrar solucion
    	int iter=0;
	    while(!eq && EST){
	        evalSet(wi,data,eq, factor);
	        iter++;
	        if(iter>7000) EST=false;
	    }
	    ofstream outfile(PATH_IN+"FDR/" +name+ ".dat");
	    outfile << "@Programa C++ para el algoritmo FDR" << endl;
	    outfile << "@Factor: "<<factor << endl;

	    if(EST){
		    for(int i=0; i<data2.size(); i++){
		    	 double aux=0,max=0;
		    	 int cls=1;
		    	 max = fd(wi[0], data2[i]);
		    	 for(int j=1; j<wi.size(); j++){
		    		 aux = fd(wi[j], data2[i]);
		    		 if(aux>max){
		    	    	cls=j+1;
		    	    	max=aux;
		    		 }
		    	}
		    	data2[i].clase=cls;
		    }
	    	outfile << "@W_i finales: " << endl;
	    	for(Datos el:wi){
	    	   	outfile<< el<<endl;
	    	}
	    	outfile << endl;
	    	outfile << "@Resultado de agrupamiento: "<<endl;
		    outfile<<"@Representacion:";
		    for(int i=0; i<DIM;i++){
		    	outfile <<"x"<<i+1<<",";
		    }
		    outfile<<"c"<<endl;
	    	for(Datos dat: data2){
	    		for(int i=0; i<DIM; i++){
	    			cout<<dat.data[i]<<",";
	    			outfile <<dat.data[i]<<",";
	    		}
	    		print(dat.clase);
	    		outfile<<dat.clase<<endl;
	    	}
	    }else{
	    	outfile << "@W_i finales: No converge" << endl;
	    	print("No converge");
	    }
	    outfile.close();
	    return wi;
}
