#include "../../headers/Group/MinMax.hpp"

void CrearClases(double FRAC, vector<Datos> &data, vector<Alpha> &alfas)
{
    bool itr = true;
    Alpha alf;
    int clase = 1,
    randInt = (int)(data.size() - 1) * rand() / MAX_RAN;

    data[randInt].clase = clase;
    alf.data = data[randInt];
    alf.pos = randInt;
    while (itr)
    {
        //Crear lista de distancias...
        vector<double> distL, minL;
        CrearListaDist(data, alf.data, distL);
        alf.ditancias = distL;
        alfas.push_back(alf);
        MenorDist(alfas, minL);
        int ind;
        FindMaxDist(minL, ind);
        int np = clase * (clase - 1) / 2;
        if (np == 0)
        {
            alf.pos = ind;
            data[ind].clase = ++clase;
            alf.data = data[ind];
        }
        else
        {
            double suma = 0;
            for (int i = 0; i < alfas.size(); i++)
            {
                for (int j = i + 1; j < alfas.size(); j++)
                {
                    suma += alfas[i].ditancias[alfas[j].pos];
                }
            }
            suma *= FRAC / np;
            if (minL[ind] > suma)
            {
                alf.pos = ind;
                data[ind].clase = ++clase;
                alf.data = data[ind];
            }
            else
            {
                itr = false;
            }
        }
    }
}

void CrearListaDist(vector<Datos> VECS, Datos VEC, vector<double> &listaOut)
{
    for (int i = 0; i < VECS.size(); i++)
    {
        listaOut.push_back(Dist(VECS[i].data, VEC.data));
    }
}

void FindMaxDist(vector<double> data, int &MaxVec)
{
    double distMax, aux = -1;
    int index;
    for (int i = 0; i < data.size(); i++)
    {
        distMax = data[i];
        if (distMax > aux)
        {
            aux = distMax;
            index = i;
        }
    }
    MaxVec = index;
}

void MenorDist(vector<Alpha> lista, vector<double> &nwls)
{
    if (lista.size() <= 1)
    {
        nwls = lista[0].ditancias;
        return;
    }
    for (int j = 0; j < lista[0].ditancias.size(); j++)
    {
        float min, aux;

        for (int i = 0; i < lista.size(); i++)
        {
            if (i == 0)
            {
                min = lista[i].ditancias[j];
                aux = min;
            }
            aux = lista[i].ditancias[j];
            if (aux < min)
            {
                min = aux;
            }
        }
        nwls.push_back(min);
    }
}

void MinMaxF(string const PATH_IN, string const PATH_OUT, double const FRAC)
{
    vector<Datos> data, outDat;
    int randInt, index = 0, clase = 0, dim;
    vector<Alpha> alfas;

    ReadFl(PATH_IN, data,clase,dim);
    ofstream outfile(PATH_OUT + "MinMax.dat");
     outfile << "Programa C++ para el algoritmo Min-Max" << endl;
    outfile << "f: " << FRAC << "\n\n";


    CrearClases(FRAC, data, alfas);

    vector<double> finList;

    MenorDist(alfas, finList);

    for (int i = 0; i < data.size(); i++)
    {
        Datos dat = data[i];
        bool esAlpha = false;
        for (int j = 0; j < alfas.size(); j++)
        {
            if (dat.data == alfas[j].data.data)
            {
                esAlpha = true;
                break;
            }
        }
        if (!esAlpha)
        {
            double mindist, aux;
            int cls;
            for (int j = 0; j < alfas.size(); j++)
            {
                aux = Dist(dat.data, alfas[j].data.data);
                if (j == 0)
                {
                    mindist = aux;
                }
                if (aux <= mindist)
                {
                    mindist = aux;
                    cls = alfas[j].data.clase;
                }
            }
            data[i].clase = cls;
        }
    }

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].clase == 0)
        {
            for (int j = 0; j < alfas.size(); j++)
            {
                if (data[i].data == alfas[j].data.data)
                {
                    data[i].clase = alfas[j].data.clase;
                    break;
                }
            }
        }
        outfile << data[i] << "| C" << data[i].clase << endl;
    }

    outfile.close();
}
