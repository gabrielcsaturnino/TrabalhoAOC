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
#define sub 0b01000;
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
void imprimir(void);

    
int main(void) {
   
  FILE *file = fopen("arquivo3", "rt"); 
  
    
   pc = 0;
   
  
  preencher(file);
  while(x){
   busca();
   decodifica();
   executa();
   imprimir();
    getchar();
  }

  
   
}


 
   
void preencher(FILE *file){
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
       
    }


    char line[50];
    unsigned int index = 0;
    while (fgets(line, sizeof(line), file)) {
        unsigned int opcode = 0,address =0;
        char valor =0;
        char tipo = 0,  instrucao[10], instrucao1[10], instrucao2[10], reg0=0,reg1=0,reg2=0;
        unsigned int palavra = 0;
       sscanf(line, "%*[^di]%c", &tipo);
    if (tipo == 'i') {
      if(strstr(line, "hlt") != NULL | strstr(line, "nop") !=NULL){
        sscanf(line, "%x;%*c;%*[^,], %*x", &address);
        if(strstr(line, "hlt")){
          opcode = hlt;
        }if(strstr(line, "nop")){
                opcode = nop;
        }
                palavra = opcode << 27;
    

          mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;


      }
         
      if(strstr(line, "not") !=NULL){
        opcode = not;
        sscanf(line, "%x;%*c;%[^,], %*x", &address,&instrucao);
        reg0 = extrair_numero_registrador(instrucao);
        palavra = opcode;
        palavra = (palavra<<27) | ((reg0 & 0xF)<<23);
      
	  mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;


      }

      if(strstr(line, "movr") !=NULL | strstr(line, "cmp") !=NULL){
        sscanf(line, "%x;%*c;%[^,], %[^,], %*[^,]", &address,&instrucao,&instrucao1);
        
        reg0 = extrair_numero_registrador(instrucao);
        reg1 = extrair_numero_registrador(instrucao1);
  
        if(strstr(line, "movr")){
          opcode = movr;
        }
        if(strstr(line,"cmp")){
          opcode = cmp;
        }
          palavra = opcode << 27;
          palavra |= ((reg0 & 0xF) << 23);
          palavra |= ((reg1 & 0xF) << 19);       
         
          
	  mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;


      }

                 

      if (strstr(line, "ld") != NULL | strstr(line, "st") !=NULL) {
        if (strstr(line, "ldbo") != NULL | strstr(line, "stbo") !=NULL) {
        sscanf(line, "%x;%*c;%[^,],%[^,], %x", &address,&instrucao,&instrucao1 ,&valor);
        if(strstr(line, "ldbo")){
          opcode = ldbo;
          }     
        if(strstr(line, "stbo")){
          opcode = stbo;
        }
          reg0 = extrair_numero_registrador(instrucao); 
          reg1 = extrair_numero_registrador(instrucao1); 
          palavra = opcode << 27;
          palavra  |= ((reg0 & 0xF) << 23);
          palavra  |= ((reg1 & 0xF) << 19);
          palavra  |= (valor & 0x7FFFFF);
      
	  
	  mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;


        }else{
        sscanf(line, "%x;%*c;%[^,], %x", &address,&instrucao ,&valor);
                if(strstr(line, "ld")){
                opcode = ld;
          }     if(strstr(line, "st")){
                opcode = st;
        }
                reg0 = extrair_numero_registrador(instrucao);
                palavra = opcode << 27;
                palavra |= ((reg0 & 0xF) << 23); 
                palavra |= (valor & 0x7FFFFF);          
      
		
		mem[address++] = (palavra >> 24) & 0xFF;
                mem[address++] = (palavra >> 16) & 0xFF;
                mem[address++] = (palavra >> 8) & 0xFF;
                mem[address++] = palavra & 0xFF;
        } 
    }
      if(strstr(line, "add") != NULL 
    |strstr(line, "sub") != NULL 
    |strstr(line, "mul") != NULL 
    |strstr(line, "div") != NULL 
    |strstr(line, "and") != NULL 
    |strstr(line, "or") != NULL 
    |strstr(line, "xor") != NULL ){
        
        if(strstr(line, "addi") !=NULL
        |strstr(line, "subi") !=NULL
        |strstr(line, "multi") !=NULL
        |strstr(line, "divi") !=NULL 
        |strstr(line, "lsh") !=NULL 
        |strstr(line, "rsh") !=NULL){
        sscanf(line, "%x;%*c;%[^,], %x", &address,&instrucao ,&valor);
        reg0 = extrair_numero_registrador(instrucao); 
        if(strstr(line, "addi")){
             opcode = addi;
        }if(strstr(line, "subi")){
             opcode = subi;
        } if(strstr(line, "multi")){
             opcode = multi;
        } if(strstr(line, "divi")){
             opcode = divi;
        } if(strstr(line, "lsh")){
             opcode = lsh;
        } if(strstr(line, "rsh")){
             opcode = rsh;
        
        }
        palavra = opcode << 27;
        palavra |= ((reg0 & 0xF)<<23);
        palavra |= (valor & 0x7FFFF);
        
          mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;


          }else
        {
        sscanf(line, "%x;%*c;%[^,],%[^,],%[^,] %*x", &address,&instrucao ,&instrucao1, &instrucao2);
        reg0 = extrair_numero_registrador(instrucao); 
        reg1 = extrair_numero_registrador(instrucao1);
        reg2 = extrair_numero_registrador(instrucao2);
        if(strstr(line, "add")){
            opcode = add;
        }
        if(strstr(line, "mul")){
          opcode = mul;
        }
        if(strstr(line, "div")){
          opcode = div;
        }
        if(strstr(line, "sub")){
          opcode = sub;
        }
        if(strstr(line, "or")){
          opcode = or;
        }
        if(strstr(line, "xor")){
          opcode = xor;
        }
        palavra = opcode << 27;
        palavra |= ((reg0 & 0xF) << 23);    
        palavra |= ((reg1 & 0xF) << 19);    
        palavra |= ((reg2 & 0xF) << 15);
         
          mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;

           

        }}     
      if(strstr(line, "movil") !=NULL | strstr(line, "movih") !=NULL){
        sscanf(line, "%x;%*c;%[^,], %x", &address, &instrucao, &valor);
        reg0 = extrair_numero_registrador(instrucao); 
        if(strstr(line, "movil")){
          opcode = movil;
        }
        if(strstr(line, "movih")){
          opcode = movih;
        }
        palavra = opcode << 27;
        palavra |= ((reg0 & 0xF)<<23);
        palavra |= (valor & 0x7FFFFF);
       
          mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;
      }
    

      if(strstr(line, "je")!=NULL 
        |strstr(line, "jne")!=NULL 
        |strstr(line, "jl")!=NULL 
        |strstr(line, "jle")!=NULL
        |strstr(line, "jg")!=NULL
        |strstr(line, "jge")!=NULL 
        |strstr(line, "jmp")!=NULL){
        sscanf(line, "%x;", &address);

        if(strstr(line, "je")){
          opcode = je;
          char *ptr = strstr(line, "je");
          sscanf(ptr, "je %x", &valor);
        }

        if(strstr(line, "jne")){
          opcode = jne;
          char *ptr = strstr(line, "jne");
          sscanf(ptr, "jne %x", &valor);
        }

        if(strstr(line, "jl")){
          if(strstr(line, "jle")){
             opcode = jle;
             char *ptr = strstr(line, "jle");
             sscanf(ptr, "jle %x", &valor);
             
          }else{
             opcode = jl;
             char *ptr = strstr(line, "jl");
             sscanf(ptr, "jl %d", &valor);
          }
        }

        if(strstr(line, "jg")){
          if(strstr(line, "jge")){
            opcode = jge;
            char *ptr = strstr(line, "jge");
            sscanf(ptr, "jge %x", &valor);
          }else{
            opcode = jg;
            char *ptr = strstr(line, "je");
            sscanf(ptr, "je %x", &valor);
          }
        }

        if(strstr(line, "jmp")){
          opcode = jmp;
          char *ptr = strstr(line, "jmp");
          sscanf(ptr, "jmp %x", &valor);
        
        }
        palavra |= opcode << 27;
        palavra |=0 << 23;
        palavra |= (valor & 0x7FFFFF);
        
	  mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;

             } 
   

     
  }
   if(tipo == 'd'){
        sscanf(line, "%x;%*[^;];%x", &address, &valor);
        palavra = valor;
         
	  mem[address++] = (palavra >> 24) & 0xFF;
          mem[address++] = (palavra >> 16) & 0xFF;
          mem[address++] = (palavra >> 8) & 0xFF;
          mem[address++] = palavra & 0xFF;
       
    }  
}
fclose(file);
}


int extrair_numero_registrador(const char *instrucao) {
    const char *ptr = instrucao;
    while (*ptr && *ptr != 'r') {
        ptr++;
    }

    if (*ptr == '\0' || !isdigit(*(ptr + 1))) {
        return -1;   
    }

    return atoi(ptr + 1);
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
  if(ir == 5 || ir == 6){
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF; 
     mar = mbr & 0x7FFFF;
  }

 
  if(ir >= 7 && ir<=13){
    
     ro0 = (mbr>>23) & 0xF;
     ro1 = (mbr>>19) & 0xF;
     ro2 = (mbr>>15) & 0xF;
        
}

 
  if(ir==14 || ir ==15){
    mar = mbr & 0xFF;    
    ro0 = (mbr >> 23) & 0xF;
     
  }
  
 
  if(ir >= 16 && ir<=23){
     ro0 = (mbr>>23) & 0xF; 
     imm =  mbr & 0x007FFFFF; 
  }
  

  if(ir >=24 && ir<=30){
    mar = mbr & 0x007FFFFF;

  }

}

void executa(void){
   if(ir == 1){
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
    
    mbr = mem[reg[ro1]+mar++]; 
    mbr = (mbr<<8) + mem[reg[ro1]+mar++]; 
    mbr = (mbr<<8) + mem[reg[ro1]+mar++];
    mbr = (mbr<<8) + mem[reg[ro1]+mar++];
    reg[ro0] = mbr;
 }


  if(ir == 6){
     mbr = reg[ro0];
     mem[mar+reg[ro1]] = mbr & 0xFF;
     mem[++mar+reg[ro1]] = mbr>>8 & 0xFF;
     mem[++mar+reg[ro1]] = mbr>>16 & 0xFF;
     mem[++mar+reg[ro1]] = mbr>>24 & 0xFF;
  }
 
  if(ir == 7){
    reg[ro0] = reg[ro1] + reg[ro2];
  
  }

   if (ir == 8){
    reg[ro0] = reg[ro1] - reg[ro2];
  
  }

   if(ir == 9){
    reg[ro0] = reg[ro1] * reg[ro2];
    
  }

   if(ir == 10){
    reg[ro0] = reg[ro1]/reg[ro2];
  
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

  if(ir == 14){
    mbr = mem[mar++]; 
    mbr = (mbr<<8) + mem[mar++]; 
    mbr = (mbr<<8) + mem[mar++];
    mbr = (mbr<<8) + mem[mar++];
    reg[ro0] = mbr;
  }
  
  if(ir == 15){
     mbr = reg[ro0];
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
     incremento();
     return;
  
    }
  }
  if(ir == 27){
     if(e == 1 || l == 1){
      pc = mar;
    }else{
     incremento(); 
      return;
    }
  }

  if(ir == 28){
    if(g ==  1){
      pc = mar;
    }else{
      incremento(); 
      return;
  
    }
  }
 
  
  if (ir == 29){
      if(e == 1 || g == 1){
          pc = mar;
  }else{
       incremento();
       return;
  
  } 
}
  if(ir == 30){
    pc = mar;
  }
  

  if(!(ir>=24 && ir<=30)){
	 incremento(); 
  }
}

void incremento(void){
  pc = pc + 4;   
}

void imprimir(){
  system("clear");  
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
    printf("\n\n Preciose enter para continuar o ciclo ou CTRL + C para encerrar o programa.");



}
