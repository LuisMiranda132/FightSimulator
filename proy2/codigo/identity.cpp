#include "RedNeural.h"

int main(){

   RedNeural red(8,3,8);
   
   double** ejemplos;
   ejemplos = Utilities::crearMatriz(8,8);
   ejemplos[0][0] = 1.0;
   ejemplos[1][1] = 1.0;
   ejemplos[2][2] = 1.0;
   ejemplos[3][3] = 1.0;
   ejemplos[4][4] = 1.0;
   ejemplos[5][5] = 1.0;
   ejemplos[6][6] = 1.0;
   ejemplos[7][7] = 1.0;
   double** targets = ejemplos;

   red.aprender(ejemplos,targets,0.1,8);
   for(int i=0;i<8;++i){
      cout << "Output de ejemplo " << i+1 << endl;
      double* temp = red.resolver(ejemplos[i]);
      for(int j=0;j<8;++j){
	 if(temp[j] < 0.5)
	 cout << 0 << endl;
	 else cout << 1 << endl;
      }
      cout << endl;
   }

   return 0;
}
