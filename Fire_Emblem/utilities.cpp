#include "utilities.h"
using namespace std;

double** Utilities::crearMatriz(int r, int c){
   double** res = new double*[r]; 
   for(int i=0;i<r;++i){
      res[i] = new double[c];
   }
   return res;
}

