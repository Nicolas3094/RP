#include "../../headers/Group/Kmeans.hpp"

void Centroides(vector<Datos> data, vector<Datos> &clases, int const K)
{
    Datos* aux;
    int cls = 0;
    for (int i = 0; i < K; i++)
    {
        int post = (int)(data.size() - 1) * rand() / MAX_RAN;
        aux = &data[post];
        aux->pos = post;
        aux->clase = ++cls;
        clases.push_back(*aux);
    }
    aux =nullptr;
    delete aux;
 
}
void AgruparC(vector<Datos> &data, vector<Datos> &centroid)
{

    for (unsigned i = 0; i < data.size(); i++)
    {
        double min, aux;
        int cls;
        for (unsigned j = 0; j < centroid.size(); j++)
        {
            aux = Dist(data[i].data, centroid[j].data);
            if (j == 0)
                min = aux;
            if (min >= aux)
            {
                min = aux;
                cls = centroid[j].clase;
            }
        }
        data[i].clase = cls;
    }
}

void ActualizarC(vector<Datos> &data, vector<Datos> &centro)
{
    for (unsigned i = 0; i < centro.size(); i++)
    {
        double n = 0;

        for (unsigned k = 0; k < data[0].data.size(); k++)
            centro[i].data[k] = 0;

        for (unsigned j = 0; j < data.size(); j++)
        {
            if (data[j].clase == centro[i].clase)
            {
                n++;
                for (unsigned k = 0; k < data[0].data.size(); k++)
                    centro[i].data[k] += data[j].data[k];
            }
        }
        for (unsigned k = 0; k < data[0].data.size(); k++)
            centro[i].data[k] /= n;
   
    }
}

void KMeans(string const PATH_IN, string const PATH_OUT, int const K)
{

    vector<Datos> data,centroids,aux, original;
    int cls, dim;
    bool itr = true;

    ReadFl(PATH_IN, data,cls,dim);
    ofstream outfile(PATH_OUT +to_string(K)+"Kmeans.dat");

    outfile << "@Programa C++ para el algoritmo K-MEANS" << endl;
    outfile << "@Numvariables " << dim << "\n";
    outfile << "@NumClases " << K << "\n";

    Centroides(data, centroids, K);

    while (itr)
    {
        aux = centroids;
        AgruparC(data, centroids);
        ActualizarC(data, centroids);
        for (int i = 0; i < K; i++)
        {
            if (aux[i].data == centroids[i].data)
            {
                itr = false;
            }
            else
            {
                break;
            }
        }
    }
    for(Datos data : centroids){
    	outfile <<"@Centroide ";
    	outfile<<data<<","<<data.clase<<endl;
    }
    for (unsigned j = 0; j < data.size(); j++)
            {
    	outfile << data[j] <<","<< data[j].clase <<endl;
     }
    outfile.close();
    print("termina k-means");
}
