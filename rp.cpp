#include "headers/Group/AGF.hpp"

int main(int, char **){
   srand(time(NULL));
   rand();
   string PATH;
   int cls;

   print("\n\n*****-Algoritmo Genetico Difuso-******\n\n");
   print("Esciba entrada de documento:");
   cin >> PATH;
   AGD(PATH, "");

   cin.get();
   return 0;
}
