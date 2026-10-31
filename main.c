#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
// #include "pessoa.h"
// #include "parametros.h"
// #include "simulacao.h"


// int main() {
    
    
    
    
    
//     return 0; 
// }


static uint32_t xorshift32(void) {
   static uint32_t state = 12345;
   uint32_t x = state;
   
   x ^= x << 13;
   x ^= x >> 17;
   x ^= x << 5;
   
   state = x;
   return x;
}

int main(){
   for(int i=0; i<20; i++) {
       int valor_sorteado = (int)(xorshift32() % 100u);
       printf("%d, ", valor_sorteado);
    }
    return 0;
}

