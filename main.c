#include <stdio.h>

unsigned int mbr,
             mar,
             pc,
             imm,
             reg[16];
unsigned char ro0,
              ro1,
              ro2,
              e,
              l,
              g,
              ir, 
            mem[154];




void busca(void);
void decodifica(void);
void executa(void);





int main(void) {
     pc = 0;
   mem[0] = 0x60;
   mem[1] = 0x00;
   mem[2] = 0x00;
   mem[3] = 0x12;
   
   mem[4] = 0x60;
   mem[5] = 0x80;
   mem[6] = 0x00;
   mem[7] = 0x22;
   
   mem[8] = 0x29;
   mem[9] = 0x00;
   mem[10] = 0x80;
   mem[11] = 0x00;

   mem[18] = 0x0;
   mem[19] = 0x0;
   mem[20] = 0x0;
   mem[21] = 0x6;
   
   mem[34] = 0x0;
   mem[35] = 0x0;
   mem[36] = 0x0;
   mem[37] = 0x10;

   bool x = true;
   while(x){
   busca();
   decodifica();
   executa();
   getchar();
  }
}


void busca(void){
    mar = pc;
  mbr = mem[mar++];
  mbr = (mbr<<8) + mem[mar++];
  mbr = (mbr<<8) + mem[mar++];
  mbr = (mbr<<8) + mem[mar++];

}


void decodifica(void){
    ir = mbr>>27;
 

  //ldbo stbo
  if(ir == 5 || ir ==6){
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF; 
     mar = mbr & 0x7FFFF;
  }

  //ld e st
  if(ir==12 || ir ==13){
    mar = mbr & 0xFF;    
    ro0 = (mbr >> 23) & 0xF;
    
        
  }
  //sum
  if(ir >= 5 && ir<=13){
     ro1 = (mbr>>15) & 0xF;
     ro0 = (mbr>>19) & 0xF;
     ro2 = (mbr>>23) & 0xF;
  }
  
  //todos com imm
  if(ir >= 16 && ir<=23){
     ro0 = (mbr>>23) & 0xF; 
     imm =  mbr & 0x007FFFFF; 
  }
  

  //jumps *DUVIDA* jumps devem receber apenas -mar: endereco de memoria- ou devem receber tambem, assim como o load, o conteudo do endereco de memoria X.
  if(ir >=24 && ir<=30){
    
    mar = mbr & 0xFF;

  }
  
  if(ir == 0){
    x = false;
  }


}

void executa(void){
  //LOAD
  if(ir == 12){
    mbr = mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    mbr = (mbr<<8) + mem[mar++];

 
    reg[ro0] = mbr;
    
  }
  
  if(ir == 13){

  }


    //SOMAR
  else if (ir == 5) {
     reg[ro2] = reg[ro1] + reg[ro0];
     printf("\n%i",reg[ro2]);
     
  }

  else if (ir == 6){
    reg[ro2] = reg[ro1] - reg[ro0];
  }

  else if(ir == 7){
    reg[ro2] = reg[ro1] * reg[ro0];
  }

  else if(ir == 8){
    reg[ro2] = reg[ro1]/reg[ro0];
  }
  
  else if(ir == 9){
    reg[ro2] = reg[ro1]&reg[ro0];
  }
  else if (ir == 10){
    reg[ro2] = reg[ro1]|reg[ro0];
  } 
  else if (ir == 10){
    reg[ro2] = reg[ro1]reg[ro0];
  }
  pc = pc + 4;

}
