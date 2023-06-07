#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if _WIN32 || _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

void limpar(){
    #if _WIN32 || _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}
void pausar(){
    #if _WIN32 || _WIN64
        Sleep(1000);
    #else
        sleep(1);
    #endif
}

int contvizinho(char *pont, int i){    /*conta vizinhos*/
    int vizinho = 0;
    if(*(pont-31)=='1' && i>29 && i%30!=0){
        vizinho++;
    }
    if(*(pont-30)=='1' && i>29){
        vizinho++;
    }
    if(*(pont-29)=='1' && i>29 && i%30!=29){
        vizinho++;
    }
    if(*(pont-1)=='1' && i%30!=0){
        vizinho++;
    }
    if(*(pont+1)=='1' && i%30!=29){
        vizinho++;
    }
    if(*(pont+29)=='1' && i<870 && i%30!=0){
        vizinho++;
    }
    if(*(pont+30)=='1' && i<870){
        vizinho++;
    }
    if(i%30!=29 && i<870 && *(pont+31)=='1'){
        vizinho++;
    }
    return(vizinho);
}



int main(int argc, char * argv[]) {
    int i, j, cont=0;
    char celula[30][30], celulaux[30][30];
    char *p = &celula[0][0];
    char *paux = &celulaux[0][0];
    FILE *pont;
    pont = fopen(argv[1], "r");
    for(i=0;i<30;i++){
        for(j=0;j<30;j++){
            fscanf(pont, "%c\n",&celula[i][j]);
        }
    }

    int gerar = atoi(argv[2]);

    for(cont=0;cont<=gerar;cont++){
        printf("\ngeracao %d  de  %d\n",cont,gerar);
        for(i=0;i<30;i++){
            printf("\n");
            for(j=0;j<30;j++){
                printf("%c",celula[i][j]);
            }
        }
        printf("\n\n");
        for(i = 0;i<901;i++){
            int vizinho = contvizinho(p+i, i);
            if(*(p+i)=='1'){          /*VIVO*/
                if(vizinho==2 || vizinho==3){
                    *(paux+i)='1';
                }
                else{
                    *(paux+i)='0';
                }
            }
            else{                   /*MORTO*/
                if(vizinho==3){
                    *(paux+i)='1';
                }
                else{
                    *(paux+i)='0';
                }
            }
        }
        for(i=0;i<901;i++){
            *(p+i)=*(paux+i);
        }

        pausar();
        limpar();
    }
    fclose(pont);
    return 0;
}