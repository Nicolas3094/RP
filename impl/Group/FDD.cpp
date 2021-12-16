#include "../../headers/Group/FDD.hpp"
//producto punto funcion discriminante
double fdd(Vector<double> zi,Vector<double> xi){
	double f1 = xi*zi;
	double f2 = 0.5*(zi*zi);
	return (f1-f2);
}

void FDD(const string name, const string name2){
		vector<Datos> data,data2, wi;

	    int CLASES, DIM, cls,dm;
	    ReadFl(PATH_IN+name+".txt", data, CLASES, DIM);
	    ReadFl(PATH_IN+name2+".txt", data2, cls, dm);

	    //Crea vectores extendidos zi's
	    vector<Vector<double>> Z(CLASES,Vector<double>(DIM,0.0));
	    vector<int> n(CLASES,0);
	    for(int i=0; i<data.size(); i++){
	    	int cls = data[i].clase;
	    	for(int j=0; j<CLASES; j++){
	    		if(cls==j+1){
	    			Z[j] += data[i].data;
	    			n[j]++;
	    			break;
	    		}
	    	}
	    }
	    for(int i=0; i<CLASES;i++){
	    	Z[i] /= n[i];
	    }
	    for(int i=0; i<data2.size(); i++){
	    	double aux=0,max=0;
	    	int cls=1;
	    	max = fdd(Z[0],data2[i].data);
	    	for(int j=1; j<CLASES; j++){
	    		aux = fdd(Z[j],data2[i].data);
	    		if(aux>max){
	    			cls=j+1;
	    			max=aux;
	    		}
	    	}
	    	data2[i].clase=cls;
	    }

	    ofstream outfile(PATH_IN+"FDD/" +name+ ".dat");
	    outfile << "@Programa C++ para el algoritmo FDD" << endl;
	    for(int i=0; i<data2.size();i++){
	    	print(data2[i]<<","<<data[i].clase);
	    	outfile<< data2[i]<<','<<data[i].clase<<endl;
	    }

	    outfile.close();
}
