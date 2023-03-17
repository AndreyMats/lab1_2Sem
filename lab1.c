#include<stdio.h>
#include<stdlib.h>
#include"handlers.h"

void MyDestructor(matrix* Mrx, int flag){
    if(!Mrx){
        return;
    }
    if(flag == 1){
        free(Mrx -> ringinfo);
    }
    for(int i = 0 ; i < Mrx -> hight ; i++){
        for(int j = 0; j < Mrx -> lenght; j++){
            free(((int***)(Mrx->Mpoint))[i][j]);
        }
        free(((int***)(Mrx->Mpoint))[i]);
    }
    free(Mrx-> Mpoint);
    free(Mrx);
}

int main(){
    matrix* Mrx1 = (matrix*)malloc(sizeof(matrix));
    matrix* Mrx2 = (matrix*)malloc(sizeof(matrix));
    matrix* resMrx;
    int variant;
    int num_type = 0;
    do{
        variant = main_menu();
        switch(variant){
            case 1:
                num_type = inputData(Mrx1 , Mrx2);
                break;
            case 2:
                resMrx = handData(Mrx1 , Mrx2 , num_type);
                break;
            case 3:
                outputData(Mrx1 , Mrx2 , resMrx , num_type);
                break;
            case 4:
                break;
        }
    }while(variant != 4);
    MyDestructor(Mrx1 , 1);
    MyDestructor(Mrx2 , 0);
    MyDestructor(resMrx, 0);
	//just comment   
 return 0;
}
	
