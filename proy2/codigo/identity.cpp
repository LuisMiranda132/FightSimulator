#include "RedNeural.h"

int main(){

   //Inicializacion de la red
   vector<double> pesos8;
   vector<double> pesos3;
   capa capaInterna;
   capa capaOutput;
   vector<capa> capas;

   for(int i=0;i<9;++i){
      pesos8.push_back(0.0);
   }
   pesos3.push_back(0.0);
   for(int i=0;i<3;++i){
      pesos3.push_back(0.0);
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
   one.first.push_back(1.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.first.push_back(0.0);
   one.second = one.first;
   one.first.insert(one.first.begin(),1.0);

   ejemplo2 two;
   two.first.push_back(0.0);
   two.first.push_back(1.0);
   two.first.push_back(0.0);
   two.first.push_back(0.0);
   two.first.push_back(0.0);
   two.first.push_back(0.0);
   two.first.push_back(0.0);
   two.first.push_back(0.0);
   two.second = two.first;
   two.first.insert(two.first.begin(),1.0);

   ejemplo2 three;
   three.first.push_back(0.0);
   three.first.push_back(0.0);
   three.first.push_back(1.0);
   three.first.push_back(0.0);
   three.first.push_back(0.0);
   three.first.push_back(0.0);
   three.first.push_back(0.0);
   three.first.push_back(0.0);
   three.second = three.first;
   three.first.insert(three.first.begin(),1.0);

   ejemplo2 four;
   four.first.push_back(0.0);
   four.first.push_back(0.0);
   four.first.push_back(0.0);
   four.first.push_back(1.0);
   four.first.push_back(0.0);
   four.first.push_back(0.0);
   four.first.push_back(0.0);
   four.first.push_back(0.0);
   four.second = four.first;
   four.first.insert(four.first.begin(),1.0);

   ejemplo2 five;
   five.first.push_back(0.0);
   five.first.push_back(0.0);
   five.first.push_back(0.0);
   five.first.push_back(0.0);
   five.first.push_back(1.0);
   five.first.push_back(0.0);
   five.first.push_back(0.0);
   five.first.push_back(0.0);
   five.second = five.first;
   five.first.insert(five.first.begin(),1.0);

   ejemplo2 six;
   six.first.push_back(0.0);
   six.first.push_back(0.0);
   six.first.push_back(0.0);
   six.first.push_back(0.0);
   six.first.push_back(0.0);
   six.first.push_back(1.0);
   six.first.push_back(0.0);
   six.first.push_back(0.0);
   six.second = six.first;
   six.first.insert(six.first.begin(),1.0);

   ejemplo2 seven;
   seven.first.push_back(0.0);
   seven.first.push_back(0.0);
   seven.first.push_back(0.0);
   seven.first.push_back(0.0);
   seven.first.push_back(0.0);
   seven.first.push_back(0.0);
   seven.first.push_back(1.0);
   seven.first.push_back(0.0);
   seven.second = seven.first;
   seven.first.insert(seven.first.begin(),1.0);

   ejemplo2 eight;
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(0.0);
   eight.first.push_back(1.0);  
   eight.second = eight.first;
   eight.first.insert(eight.first.begin(),1.0);

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

   //Testing
   salida s1 = red.resolver(eight.first);
   for(int i=0;i<s1[s1.size()-1].size();++i){
      cout << s1[s1.size()-1][i] << endl;
   }

   return 0;
}