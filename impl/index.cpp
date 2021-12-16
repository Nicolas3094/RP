#include "../headers/IndexHeader.hpp"
void CreatSpace(string const PATH,Region& space,vector<double>& etiquetas, int& C, int& Dim){
    ifstream fl(PATH);
    vector<Vector<double>> lst;
    string str;
    vector<string> info;
    vector<string> datas;
    int version=0, dimension, clases;
    long int fecha;
    clases=-1;
    string const ver = "@VerArch";
    string const fech = "@Fecha";
    string const numvar =  "@Numvariables";
    string const nomvar = "@Nomvariables";
    string const numClass = "@NumClases";

    map<int,bool> etiqVisit;

    while (getline(fl, str, '\n')){
        if(str.at(0) == AT){
            if(str.substr(0, str.find(' ')) == ver)
                version = stoi(str.substr(str.find(' ')+1));
            else if(str.substr(0, str.find(' ')) == numvar)
                dimension =  stoi(str.substr(str.find(' ')+1));
            else if(str.substr(0, str.find(' ')) == numClass)
                clases = stoi(str.substr(str.find(' ')+1));
            else if(str.substr(0, str.find(' ')) == fech)
                fecha = stoi(str.substr(str.find(' ')+1));

        }else{

        	string bot;
        	string aux = str;
        	Vector<double> vec;
        	for(int i =0; i<dimension; i++){
        		bot = aux.substr(0,aux.find(','));
        	    vec.push_back((double)stoi(bot));
        	    aux = aux.substr(aux.find(',')+1);
        	 }
          	int cls;
            cls=clases>0?stoi(aux):0;
        	vec.push_back(cls);
        	if(!etiqVisit[cls]){
        		etiqVisit[cls]=true;
        		etiquetas.push_back(cls);

        	}
            space.push_back(vec);
        }
    }
    C=clases;
    Dim=dimension;
    fl.close();

}

//Campturar datos en estructura
void ReadFl(string const PATH, vector<Datos>& lst, int& C, int& Dim){

    ifstream fl(PATH);
    
    string str;
    vector<string> info;
    vector<string> datas;

    int version=0, dimension, clases;
    long int fecha;
    clases=-1;
    string const ver = "@VerArch";
    string const fech = "@Fecha";
    string const numvar =  "@Numvariables";
    string const nomvar = "@Nomvariables";
    string const numClass = "@NumClases";
    while (getline(fl, str, '\n')){
        if(str.at(0) == AT){
            if(str.substr(0, str.find(' ')) == ver)
                version = stoi(str.substr(str.find(' ')+1));
            else if(str.substr(0, str.find(' ')) == numvar){
                dimension =  stoi(str.substr(str.find(' ')+1));
            }
            else if(str.substr(0, str.find(' ')) == numClass)
                clases = stoi(str.substr(str.find(' ')+1));
            else if(str.substr(0, str.find(' ')) == fech)
                fecha = stoi(str.substr(str.find(' ')+1));

        }else{
        	string bot;
        	string aux = str;
        	Datos datos;
        	vector<double> vec;

        	for(int i =0; i<dimension; i++){
        		bot = aux.substr(0,aux.find(','));
        	    vec.push_back((double)stoi(bot));
        	    aux = aux.substr(aux.find(',')+1);
        	 }
        	datos.clase=clases>0?stoi(aux):0;
        	datos.data = vec;
        	datos.pos = lst.size();
        	lst.push_back(datos);
        }
    }
    C=clases;
    Dim=dimension;
    fl.close();
}


ostream& operator <<(ostream& COUT, Datos& DAT){
    for(unsigned i = 0; i< DAT.data.size(); i++){
        COUT <<DAT.data[i];
        if(i!=DAT.data.size()-1) COUT << ",";
    }
    return COUT;
}
ofstream&  operator <<(ofstream& COUT, Datos& DAT){
    for(unsigned i = 0; i< DAT.data.size(); i++){
        COUT <<DAT.data[i];
        if(i!=DAT.data.size()-1) COUT << ",";
    }
    return COUT;
}
