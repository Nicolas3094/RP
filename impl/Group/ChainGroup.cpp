#include"../../headers/Group/ChainGroup.hpp"

void ChainGroup(string const PATH_IN, string const PATH_OUT, int const UMBRAL)
{
    int clase = 1, DIM;
    double dist;
    vector<Datos> data, outDat;

    ReadFl(PATH_IN, data,clase,DIM);

    ofstream outfile(PATH_OUT + "ChainMap.dat");

    outfile << "Programa C++ para el algoritmo Chain Map" << endl;
    outfile << "Umbral: " << UMBRAL << "\n\n";

    CreateStk(data, outDat, outfile);

    outfile << "Clase: " << clase << "\n";

    for (int i = 0; i < outDat.size(); i++)
    {

        dist = i == 0 ? 0 : Dist(outDat[i].data, outDat[i - 1].data);

        outDat[i].clase = dist <= UMBRAL ? clase : ++clase;

        if (outDat[i - 1].clase != outDat[i].clase && i != 0)
        {
            outfile << "Clase: " << clase << "\n";
        }
        outfile << outDat[i] << "\n";
    }
    outfile.close();
}

void CreateStk(vector<Datos> dataIn, vector<Datos> &stk, ofstream &fl)
{
    // posicion ''random'' toma valores de [0,19]
    int pos = (int)(dataIn.size() - 1) * rand() / MAX_RAN;
    Datos cero;
    cero.data = dataIn[pos].data;
    stk.push_back(cero);
    dataIn.erase(dataIn.begin() + pos); //borra el primer valor de los datos de entrada


    while (!dataIn.empty())
    {

        double min = 0; //distancia minima
        int level = 0;  //posicion
        for (int i = 0; i < dataIn.size(); i++)
        {

            double res = Dist(cero.data, dataIn[i].data); //resultado del calculo de Dist


            min = i == 0 ? res : min;

            if (min > res)
            { //comparativa si hay un nuevo minimo

                level = i; //almacena la posicion
                min = res; //almacena el resultado
            }
        }
        cero = dataIn[level];                 //redefine el vec cero
        stk.push_back(cero);                  //almacena el resultado
        dataIn.erase(dataIn.begin() + level); //Lo elimina de la estructura principal de datos
    }
}
