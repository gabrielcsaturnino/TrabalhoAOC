#include <stdio.h>
#include <stdbool.h>
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

bool x = true;



void busca(void);
void decodifica(void);
void executa(void);





int main(void) {
     pc = 0;
   mem[0] = 0x70;
   mem[1] = 0x00;
   mem[2] = 0x00;
   mem[3] = 0x12;
   
   mem[4] = 0x70;
   mem[5] = 0x80;
   mem[6] = 0x00;
   mem[7] = 0x22;
   
   mem[8] = 0x39;
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
     
    printf("\nmbr:%x", mbr);
    printf("\nir:%b", ir); 
  if(ir == 0){
    x = false;
  }


  //ldbo stbo
  if(ir == 5 || ir == 6){
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF; 
     mar = mbr & 0x7FFFF;
  }

 
  if(ir >= 7 && ir<=13){
     ro1 = (mbr>>15) & 0xF;
     ro0 = (mbr>>19) & 0xF;
     ro2 = (mbr>>23) & 0xF;
  
     printf("\nro0:%x", ro0);
     printf("\nro1:%x", ro1);
     printf("\nro2:%x", ro2);    
}

 
  //ld e st
  if(ir==14 || ir ==15){
    mar = mbr & 0xFF;    
    ro0 = (mbr >> 23) & 0xF;
   
        
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

}

void executa(void){
   

 
   if(ir == 5){
      reg[ro0] =*   
  }
   
   if(ir == 7){
     reg[ro2] = reg[ro1] + reg[ro0];
     printf("\nresultado:%i",reg[ro2]);     
  }

   if (ir == 8){
    reg[ro2] = reg[ro1] - reg[ro0];
  }

   if(ir == 9){
    reg[ro2] = reg[ro1] * reg[ro0];
  }

   if(ir == 10){
    reg[ro2] = reg[ro1]/reg[ro0];
  }
  
   if(ir == 11){
    reg[ro2] = reg[ro1]&reg[ro0];
  }
   if (ir == 12){
    reg[ro2] = reg[ro1]|reg[ro0];
      } 
   if (ir == 13){
    reg[ro2] = reg[ro1]^reg[ro0];
  }




  //LOAD
  if(ir == 14){
    mbr = mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    reg[ro0] = mbr;
    
  }
  
  if(ir == 15){
     mbr = reg[ro0++];
     mbr = (mbr<<8) + reg[ro0++];
     mbr = (mbr<<8) + reg[ro0++];
     mbr = (mbr<<8) + reg[ro0++];
    
     
  }


  



   if(ir == 16){
     
    reg[ro0] &=0x0000FFFF;
    reg[ro0] |=(imm&0xFFFF)<<16;
    
  } 

   if(ir == 17){
    reg[ro0] = 0;
    reg[ro0] = imm & 0x0000FFFF; 
  }

   if(ir == 18){
     reg[ro0] = reg[ro0] + imm; 
  }
   if(ir == 19){
     reg[ro0] = reg[ro0] - imm; 
  } 
    if(ir == 20){
     reg[ro0] = reg[ro0] * imm; 
  }
    if(ir == 21){
    reg[ro0] = reg[ro0] / imm;
  }
    if(ir == 22){
     reg[ro0] = reg[ro0] << imm; 
  }
    if(ir == 23){
     reg[ro0] = reg[ro0] >> imm; 
  }

  pc = pc + 4;

}

