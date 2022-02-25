#include<stdio.h>
#include<stdlib.h>

void inputDataInt(matrix* Mrx){
    int lenght , hight;
    int curItem;
    printf("Введите размеры матрицы:\n");
    printf("row: ");
    scanf("%d" , &hight);
    printf("cols: ");
    scanf("%d" , &lenght);
    Mrx -> hight = hight;
    Mrx -> lenght = lenght;
    Mrx -> Mpoint = malloc(hight * sizeof(int**));
    for(int i = 0; i < hight ; i++){
        ((int***)(Mrx -> Mpoint))[i] = (int**)malloc(lenght * sizeof(int*));
        for(int j = 0; j < lenght; j++){
            ((int***)(Mrx-> Mpoint))[i][j] = (int*)malloc(sizeof(int));
            scanf("%d" , &curItem);
            *(((int***)(Mrx -> Mpoint))[i][j]) = curItem;
        }
    }
    return;
}


void inputDataFloat(matrix* Mrx){
    int lenght , hight;
    float curItem;
    printf("Введите размеры матрицы:\n");
    printf("row: ");
    scanf("%d" , &hight);
    printf("cols: ");
    scanf("%d" , &lenght);
    Mrx -> hight = hight;
    Mrx -> lenght = lenght;
    Mrx -> Mpoint = malloc(hight * sizeof(float**));
    for(int i = 0; i < hight ; i++){
        ((float***)(Mrx -> Mpoint))[i] = (float**)malloc(lenght * sizeof(float*));
        for(int j = 0; j < lenght; j++){
            ((float***)(Mrx-> Mpoint))[i][j] = (float*)malloc(sizeof(float));
            scanf("%f" , &curItem);
            *(((float***)(Mrx -> Mpoint))[i][j]) = curItem;
        }
    }
}

void outputDataMrxInt(matrix* Mrx){
    for(int i = 0; i < Mrx -> hight; i++){
        for(int j = 0; j < Mrx -> lenght; j++){
            printf("%d " , *(((int***)(Mrx->Mpoint))[i][j]));
        }
        printf("\n");
    }
}

void outputDataMrxFloat(matrix* Mrx){
    for(int i = 0; i < Mrx -> hight; i++){
        for(int j = 0; j < Mrx -> lenght; j++){
            printf("%f " , *(((float***)(Mrx->Mpoint))[i][j]));
        }
        printf("\n");
    }
}