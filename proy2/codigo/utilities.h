#include<iostream>
#include<algorithm>
#include<math.h>
#include<random>
using namespace std;

class Utilities{
   public:
      static double** crearMatriz(int r, int c){
	 double** res = new double*[r];
	 for(int i=0;i<r;++i){
	    res[i] = new double[c];
	 }
	 return res;
      }
};
