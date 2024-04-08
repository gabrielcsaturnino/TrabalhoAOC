#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define hlt 0b00000;
#define nop 0b00001;
#define not 0b00010;
#define movr 0b00011;
#define cmp 0b00100;
#define ldbo 0b00101;
#define stbo 0b00110;
#define add 0b00111;
#define sup 0b01000;
#define mul 0b01001;
#define div 0b01010;
#define and 0b01011;
#define or 0b01100;
#define xor 0b01101;
#define ld 0b01110;
#define st 0b01111;
#define movil 0b10000;
#define movih 0b10001;
#define addi 0b10010;
#define subi 0b10011;
#define multi 0b10100;
#define divi 0b10101;
#define lsh 0b10110;
#define rsh 0b10111;
#define je 0b11000;
#define jne 0b11001;  
#define jl 0b11010;
#define jle 0b11011;
#define jg 0b11100;
#define jge 0b11101;
#define jmp 0b11110;


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


int extrair_numero_registrador();
void preencher(FILE *file);
void incremento(void);
void busca(void);
void decodifica(void);
void executa(void);


    
int main(void) {
   
  FILE *file = fopen("arquivo1", "rt"); 
  preencher(file);   
   for(int i = 0;i<154; i++){
    mem[i] = 0x0;
  }
   for(int i = 0;i<16;i++){
    reg[i] = 0;
  }
    
   pc = 0;
   mem[0] = 0x70;
   mem[1] = 0x00;
   mem[2] = 0x00;
   mem[3] = 0x86;
   
   mem[4] = 0x70;
   mem[5] = 0x80;
   mem[6] = 0x00;
   mem[7] = 0x8a;
   
   mem[8] = 0x71;
   mem[9] = 0x00;
   mem[10] = 0x00;
   mem[11] = 0x8e;

   mem[12] = 0x71;
   mem[13] = 0x80;
   mem[14] = 0x00;
   mem[15] = 0x92;

   mem[16] = 0x72;
   mem[17] = 0x00;
   mem[18] = 0x00;
   mem[19] = 0x96;
   
   /*corrigir*/
   mem[20] = 0x42;
   mem[21] = 0x9A; 
   mem[22] = 0x00;
   mem[23] = 0x00;
   
   mem[24] = 0x53;
   mem[25] = 0x12;
   mem[26] = 0x80;
   mem[27] = 0x00;

   
   mem[28] = 0x4B;
   mem[29] = 0xB0;
   mem[30] = 0x80;
   mem[31] = 0x00;
 
   mem[32] = 0x3c;
   mem[33] = 0x03;
   mem[34] = 0x08;
   mem[35] = 0x00;
 

   mem[36] = 0x7c;
   mem[37] = 0x00;
   mem[38] = 0x00;
   mem[39] = 0x82;
   
   mem[40] = 0x0;
   mem[41] = 0x0;
   mem[42] = 0x0;
   mem[43] = 0x0;  
   

   /*dados*/
   mem[134] = 0x0; 
   mem[135] = 0x0;
   mem[136] = 0x0;
   mem[137] = 0x20;
   
   mem[138] = 0x0; 
   mem[139] = 0x0;
   mem[140] = 0x0;
   mem[141] = 0x3;
   
   mem[142] = 0x0; 
   mem[143] = 0x0;
   mem[144] = 0x0;
   mem[145] = 0x4;
   
   mem[146] = 0x0; 
   mem[147] = 0x0;
   mem[148] = 0x0;
   mem[149] = 0x5;
   
   mem[150] = 0x0;
   mem[151] = 0x0;
   mem[152] = 0x0;
   mem[153] = 0x3;
  
  preencher(file);
  while(x){
   busca();
   decodifica();
   executa();
   getchar();
  }

  
    printf("Registros:\n");
    for (int i = 0; i < 16; ++i) {
        printf("reg[%d]: 0x%X\n", i, reg[i]);
    }

    printf("\nMemória:\n");
    for (int i = 0; i < 154;++i) {
        printf("mem[%d]: 0x%X ", i, mem[i]);
  }
    printf("\nOutras variáveis:\n");
    printf("MBR: 0x%X\n", mbr);
    printf("MAR: 0x%X\n", mar);
    printf("IMM: 0x%X\n", imm);
    printf("PC: 0x%X\n", pc);
    printf("IR: 0x%X\n", ir);
    printf("RO0: 0x%X\n", ro0);
    printf("RO1: 0x%X\n", ro1);
    printf("RO2: 0x%X\n", ro2);
    printf("E: 0x%X\n", e);
    printf("L: 0x%X\n", l);
    printf("G: 0x%X\n", g);




}


 
   
void preencher(FILE *file){
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
       
    }


    char line[50];
    unsigned int index = 0;
    int reg;
    while (fgets(line, sizeof(line), file)) {
        unsigned int opcode = 0, immediate = 0,address =0,valor =0;
        char tipo, registrador, instrucao[10];
        unsigned int palavra = 0;
        sscanf(line, "%*d;%c;%*[^,] , %*x", &tipo);
    if (tipo == 'i') {
            if (strstr(line, "ld") != NULL | strstr(line, "st") !=NULL) {
                sscanf(line, "%x;%c;%[^,], %x", &address,&tipo,&instrucao ,&valor);
                if(strstr(line, "ld")){
                opcode = ld;
          }     if(strstr(line, "st")){
                opcode = st;
        }
                reg = extrair_numero_registrador(instrucao);
                printf("\n%i", reg);
                registrador = reg;               
                palavra = opcode;
                palavra = (palavra << 23) | ((registrador & 0xF) << 19); // Deslocamento de 23 bits para o campo do opcode
                palavra = palavra | (valor & 0x7FFFFF);          
                printf("\npalavra:%x", palavra);
                
                
      } 
    }

    
}
fclose(file);
}


int extrair_numero_registrador(const char *instrucao) {
    const char *ptr = instrucao;
    
    // Encontrar o caractere 'r'
    while (*ptr && *ptr != 'r') {
        ptr++;
    }

    // Se 'r' não for encontrado ou se não houver um dígito depois
    if (*ptr == '\0' || !isdigit(*(ptr + 1))) {
        return -1; // Retorna -1 se não encontrar 'r' ou não houver um número de registrador válido
    }

    // Extrair o número do registrador
    return atoi(ptr + 1);
}


void busca(void){
  mar = pc;
  mbr = mem[mar++];
  mbr = (mbr<<8) + mem[mar++];
  mbr = (mbr<<8) + mem[mar++];
  mbr = (mbr<<8) + mem[mar++];
  printf("mbr: %x\n", mbr); 
}


void decodifica(void){
    ir = mbr>>27;
     
  

  if(ir == 0){
    x = false;
  }

   
  if(ir == 2){
    ro0 = (mbr>>23) & 0xF;
  }


  if(ir == 3 || ir == 4){
    ro0 = (mbr>>23) & 0xF;
    ro1 = (mbr>>19) & 0xF;
  }
  //ldbo stbo
  if(ir == 5 || ir == 6){
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF; 
     mar = mbr & 0x7FFFF;
  }

 
  if(ir >= 7 && ir<=13){
    
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF;
     ro2 = (mbr>>15) & 0xF;
     printf("%x %x %x", ro0, ro1, ro2);  
        
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
    
   if(ir == 1){
   incremento();
  }
   
   if(ir == 2){
    reg[ro0] = !reg[ro0];
  }

   if(ir == 3 ){
    reg[ro0] = reg[ro1];
  }
   
  
  if(ir == 4){
    if(reg[ro0] == reg[ro1]){
      e = 1;
    }else{
      e = 0;
    }

    if (reg[ro0]<reg[ro1]) {
       l = 1;
    }else{
       l = 0; 
    }

    if (reg[ro0]>reg[ro1]) {
        g = 1;
    }else{
        g = 0;
  }    
}

   if(ir == 5){
    reg[ro0] = (mem[mar]+reg[ro1]);
  }

  if(ir == 6){
   /*(mem[mar]+reg[ro1]) = reg[ro0];*/
  }
 
  if(ir == 7){
    reg[ro0] = reg[ro1] + reg[ro2];
    
    printf("\nSOMA - mem[ro1]:%i+mem[ro2]:%i", reg[ro1], reg[ro2]);   
  }

   if (ir == 8){
    reg[ro0] = reg[ro1] - reg[ro2];

    printf("\nSUB - mem[ro1]:%x - mem[ro2]:%x", reg[ro1], reg[ro2]);   
    printf("\n%i", reg[ro0]);
  }

   if(ir == 9){
    reg[ro0] = reg[ro1] * reg[ro2];
      
    
    printf("\nMULT - mem[ro1]:%i * mem[ro2]:%i", reg[ro1], reg[ro2]);   
  }

   if(ir == 10){
    reg[ro0] = reg[ro1]/reg[ro2];
    
    printf("\nDIV - mem[ro1]:%i/mem[ro2]:%i", reg[ro1], reg[ro2]);   
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
     mbr = reg[ro0];
     printf("resultado: %i", mbr); 
    /*
      *
      *mbr[01234567.....31]
      * 
      *
      *
      *
      * */
     mem[mar] = mbr & 0xFF;
     mem[++mar] = mbr>>8 & 0xFF;
     mem[++mar] = mbr>>16 & 0xFF;
     mem[++mar] = mbr>>24 & 0xFF;
  }


  

 if(ir == 16){
    reg[ro0] = 0;
    reg[ro0] = imm & 0xFFFF; 
  }

   if(ir == 17){
     
    reg[ro0] &=0xFFFF;
    reg[ro0] |=(imm&0xFFFF)<<16;
    
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

  if(ir == 24 || ir == 25){
    pc = mar;
    
  }
  
  if(ir == 26){
    if(l == 1){
      pc = mar;
    }else{
      return;
    }
  }
  if(ir == 27){
     if(e == 1 || l == 1){
      pc = mar;
    }else{
      return;
    }
  }

  if(ir == 28){
    if(g ==  1){
      pc = mar;
    }else{
      return;
    }
  }
 
  
  if (ir == 29){
      if(e == 1 || g == 1){
          pc = mar;
  }else{
      return;
  } 
}
  if(ir == 30){
    pc = mar;
  } 

  pc = pc + 4;
}

  void incremento(void){
     pc = pc + 4;
}
