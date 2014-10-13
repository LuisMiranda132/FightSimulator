#include "RedNeural.h"

int main(){

   //Inicializacion de la red
   vector<float> pesos8;
   vector<float> pesos3;
   capa capaInterna;
   capa capaOutput;
   vector<capa> capas;

   for(int i=0;i<8;++i){
      pesos8.push_back(0.0f);
   }
   for(int i=0;i<3;++i){
      pesos3.push_back(0.0f);
      capaInterna.push_back(new Sigmoidal(pesos8));
   }
   for(int i=0;i<8;++i){
      capaOutput.push_back(new Sigmoidal(pesos3));
   }
   capas.push_back(capaInterna);
   capas.push_back(capaOutput);

   RedNeural red(capas);

   //Inicializacion de los ejemplos
   ejemplo2 one;
   one.first.push_back(1.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.first.push_back(0.0f);
   one.second = one.first;

   ejemplo2 two;
   two.first.push_back(0.0f);
   two.first.push_back(1.0f);
   two.first.push_back(0.0f);
   two.first.push_back(0.0f);
   two.first.push_back(0.0f);
   two.first.push_back(0.0f);
   two.first.push_back(0.0f);
   two.first.push_back(0.0f);
   two.second = two.first;

   ejemplo2 three;
   three.first.push_back(0.0f);
   three.first.push_back(0.0f);
   three.first.push_back(1.0f);
   three.first.push_back(0.0f);
   three.first.push_back(0.0f);
   three.first.push_back(0.0f);
   three.first.push_back(0.0f);
   three.first.push_back(0.0f);
   three.second = three.first;

   ejemplo2 four;
   four.first.push_back(0.0f);
   four.first.push_back(0.0f);
   four.first.push_back(0.0f);
   four.first.push_back(1.0f);
   four.first.push_back(0.0f);
   four.first.push_back(0.0f);
   four.first.push_back(0.0f);
   four.first.push_back(0.0f);
   four.second = four.first;

   ejemplo2 five;
   five.first.push_back(0.0f);
   five.first.push_back(0.0f);
   five.first.push_back(0.0f);
   five.first.push_back(0.0f);
   five.first.push_back(1.0f);
   five.first.push_back(0.0f);
   five.first.push_back(0.0f);
   five.first.push_back(0.0f);
   five.second = five.first;

   ejemplo2 six;
   six.first.push_back(0.0f);
   six.first.push_back(0.0f);
   six.first.push_back(0.0f);
   six.first.push_back(0.0f);
   six.first.push_back(0.0f);
   six.first.push_back(1.0f);
   six.first.push_back(0.0f);
   six.first.push_back(0.0f);
   six.second = six.first;

   ejemplo2 seven;
   seven.first.push_back(0.0f);
   seven.first.push_back(0.0f);
   seven.first.push_back(0.0f);
   seven.first.push_back(0.0f);
   seven.first.push_back(0.0f);
   seven.first.push_back(0.0f);
   seven.first.push_back(1.0f);
   seven.first.push_back(0.0f);
   seven.second = seven.first;

   ejemplo2 eight;
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(0.0f);
   eight.first.push_back(1.0f);  
   eight.second = eight.first;


   vector<ejemplo2> ejemplos;
   ejemplos.push_back(one);
   ejemplos.push_back(two);
   ejemplos.push_back(three);
   ejemplos.push_back(four);
   ejemplos.push_back(five);
   ejemplos.push_back(six);
   ejemplos.push_back(seven);
   ejemplos.push_back(eight);

   //aprendizaje
   red.aprender(ejemplos,0.1);

   return 0;
}
