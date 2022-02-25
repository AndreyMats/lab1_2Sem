#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include"func_int.h"

#define DEF_SUM(type) void sum_##type (void* a, void* b , void* c) { \
    *((type*)c) =  *((type*)a) + *((type*)b);\
} 
DEF_SUM(int)
DEF_SUM(float)

#define DEF_MULT(type) void mult_##type (void* a, void* b , void* c) { \
    *((type*)c) =  (*((type*)a)) * (*((type*)b));\
} 
DEF_MULT(int)
DEF_MULT(float)

#define DEF_TRANSP(type) void transp_##type (void* a , void* b){\
    *((type*)b) = *((type*)a);  \
}
DEF_TRANSP(int)
DEF_TRANSP(float)

int main_menu(){
    int res; 
    printf("1.Ввoд данные.\n");
    printf("2.Обработка данных.\n");
    printf("3.Вывод данных.\n");
    printf("4.Выход.\n");
    while(1){
        int n = scanf("%d", &res);
        if(n && n > 0 && n < 5 ){break;}
        else{
            printf("Некорректный ввод.Выберите один из предложенных ответов.\n");
        }
    }
    return res;
}

int choice_type(){
    int res;
    printf("Выберите тип данных:\n");
    printf("1.Целые числа.\n");
    printf("2.Вещественные числа.\n");
    scanf("%d" , &res);
    return res;
}

int GetVariantHand(){
    int variant;
    printf("Выберите вариант опреации:\n");
    printf("1.Матричное сложение.\n");
    printf("2.Матричное умножение.\n");
    printf("3.Транспонирование.\n");
    printf("4.Прибавление к строке линейной комбинации других строк.\n");
    scanf("%d", &variant);
    return variant;
}

void* get_factors(int number){
    void* factors = malloc(number * sizeof(float));
    for(int i = 0; i < number; i++){
        printf("factor[%d]: " , i);
        scanf("%f" , &((float*)factors)[i]);
    }
    return factors;
}

void CreateRingInt(RingInfo* ringinfo){
    ringinfo -> size = sizeof(int);
    ringinfo -> size_p1 = sizeof(int*);
    ringinfo -> size_p2 = sizeof(int**);
    ringinfo -> sum = sum_int;
    ringinfo -> mult = mult_int;
    ringinfo -> transp =  transp_int;
}

void CreateRingFloat(RingInfo* ringinfo){
    ringinfo -> size = sizeof(float);
    ringinfo -> size_p1 = sizeof(float*);
    ringinfo -> size_p2 = sizeof(float**);
    ringinfo -> sum = sum_float;
    ringinfo -> mult = mult_float;
    ringinfo -> transp = transp_float;
}

RingInfo* CreateRing(int num_type){
    RingInfo* ringinfo = (RingInfo*)malloc(sizeof(RingInfo));
    if(!ringinfo){
        printf("Memory can't allocate!\n");
    }
    switch(num_type){
        case 1:
            CreateRingInt(ringinfo);
            break;
        case 2:
            CreateRingFloat(ringinfo);
            break;
    }
    return ringinfo;
}

int inputData(matrix* Mrx1 , matrix* Mrx2){
    int num_type = choice_type();
    RingInfo* ringinfo = CreateRing(num_type);
    Mrx1 -> ringinfo = ringinfo;
    Mrx2 -> ringinfo = ringinfo;
    switch(num_type){
        printf("Ok");
        case 1:
            inputDataInt(Mrx1);
            inputDataInt(Mrx2);
            break;
        case 2:
            inputDataFloat(Mrx1);
            inputDataFloat(Mrx2);
            break;
    }
    return num_type;
}

matrix* SumMatrix(matrix* Mrx1 , matrix* Mrx2 ){
    if(Mrx1 -> lenght != Mrx2 -> lenght || Mrx1 -> hight != Mrx2 -> hight){
        printf("Summation cannot be performed\n");
        return NULL;
    }
    matrix* resMrx = (matrix*)malloc(sizeof(matrix));
    resMrx -> lenght = Mrx1 -> lenght;
    resMrx -> hight = Mrx1 -> hight;
    resMrx -> ringinfo = Mrx1 -> ringinfo;
    resMrx -> Mpoint = (void***)malloc((Mrx1 -> hight) * (Mrx1-> ringinfo -> size_p2));
    for(int i = 0; i < Mrx1 -> hight; i++){
        ((int***)(resMrx->Mpoint))[i] = malloc((Mrx1 -> lenght) *(Mrx1 -> ringinfo -> size_p1));
        for(int j = 0; j < Mrx1 -> lenght; j++){
            ((int***)(resMrx-> Mpoint))[i][j] = malloc(1 * (Mrx1 -> ringinfo -> size));
            resMrx -> ringinfo -> sum(((int***)(Mrx1-> Mpoint))[i][j] , ((int***)(Mrx2-> Mpoint))[i][j] , ((int***)(resMrx-> Mpoint))[i][j]);
        }
    }
    return resMrx;
}

matrix* MultMatrix(matrix* Mrx1 , matrix* Mrx2){
    if(Mrx1 -> lenght != Mrx2 -> hight){
        printf("Multiplication cannot be performed\n");
        return NULL;
    }
    void* curConsq = malloc(1 * (Mrx1 -> ringinfo -> size));
    matrix* resMrx = (matrix*)malloc(sizeof(matrix));
    resMrx -> hight = Mrx1 -> hight;
    resMrx -> lenght = Mrx2 -> lenght;
    resMrx -> ringinfo = Mrx1 -> ringinfo;
    resMrx -> Mpoint = (void***)malloc((Mrx1 -> hight) * (Mrx1 -> ringinfo -> size_p2));
    for(int i = 0; i < Mrx1 -> hight; i++){
        ((int***)(resMrx -> Mpoint))[i] = malloc((Mrx2 -> lenght) * (Mrx1 -> ringinfo -> size_p1));
        for(int j = 0; j < Mrx2 -> lenght; j++){
            ((int***)(resMrx-> Mpoint))[i][j] = malloc(1 * (Mrx1 -> ringinfo -> size));
            Mrx1 -> ringinfo-> mult(((int***)(Mrx1-> Mpoint))[i][0] , ((int***)(Mrx2-> Mpoint))[0][j] , ((int***)(resMrx-> Mpoint))[i][j]);
            for(int k = 1; k < Mrx1 -> lenght; k++){
                Mrx1 -> ringinfo-> mult(((int***)(Mrx1-> Mpoint))[i][k] , ((int***)(Mrx2-> Mpoint))[k][j] , curConsq);
                Mrx1 -> ringinfo -> sum(((int***)(resMrx-> Mpoint))[i][j] , curConsq , ((int***)(resMrx-> Mpoint))[i][j]);
            }
        }
    }
    free(curConsq);
    return resMrx;
}

matrix* TranspositionMrx(matrix* Mrx){
    matrix* resMrx = (matrix*)malloc(sizeof(matrix));
    resMrx -> lenght = Mrx -> hight;
    resMrx -> hight = Mrx -> lenght;
    resMrx -> ringinfo = Mrx -> ringinfo;
    resMrx -> Mpoint = (void***)malloc((resMrx -> hight) * (Mrx -> ringinfo -> size_p2));
    for(int i = 0 ; i < resMrx -> hight; i++){
        ((int***)(resMrx -> Mpoint))[i] = malloc((resMrx -> lenght) * (resMrx -> ringinfo -> size_p1));
        for(int j = 0; j < resMrx -> lenght; j++){
            ((int***)(resMrx -> Mpoint))[i][j] = malloc(1 * (Mrx -> ringinfo -> size));
            Mrx -> ringinfo -> transp(((int***)(Mrx -> Mpoint))[j][i] , ((int***)(resMrx -> Mpoint))[i][j]);
        }
    }
    return resMrx;
}

matrix* SummationComboRows(matrix* Mrx){
    matrix* resMrx = (matrix*)malloc(sizeof(matrix));
    int index;
    printf("Введите номер строки к которой будет происходить прибавление: ");
    scanf("%d", &index);
    void* factors = get_factors(Mrx -> hight);
    float curConsq;
    resMrx -> hight = Mrx -> hight;
    resMrx -> lenght = Mrx -> lenght;
    resMrx -> ringinfo = Mrx -> ringinfo; 
    resMrx -> Mpoint = (void***)malloc((resMrx -> hight) * (resMrx -> ringinfo -> size_p2));
    for(int i = 0; i < Mrx -> hight; i++){
        ((int***)(resMrx -> Mpoint))[i] = malloc((resMrx -> lenght) * (resMrx -> ringinfo -> size_p1));
        if(i == index){
            for(int j = 0 ; j < resMrx -> lenght; j++){
                ((int***)(resMrx -> Mpoint))[i][j] = malloc(1 * (resMrx -> ringinfo -> size));
                *((float***)(resMrx -> Mpoint))[i][j] = (((float*)factors)[0]) * (*((float***)(Mrx->Mpoint))[0][j]);
                for(int k = 1; k < resMrx -> hight; k++){
                    curConsq = (((float*)factors)[k]) * (*((float***)(Mrx->Mpoint))[k][j]);
                    resMrx -> ringinfo -> sum(((float***)(resMrx -> Mpoint))[i][j] , (void*)(&curConsq) ,((float***)(resMrx -> Mpoint))[i][j] );
                }
            }
        }
        else{
           for(int j = 0; j < resMrx -> lenght; j++){
               ((int***)(resMrx -> Mpoint))[i][j] = malloc(1 * (resMrx -> ringinfo -> size));
                resMrx -> ringinfo -> transp(((int***)(Mrx -> Mpoint))[i][j] , ((int***)(resMrx -> Mpoint))[i][j]);
           } 
        }
    }
    free(factors);
    return resMrx;
}

matrix* handData(matrix* Mrx1 ,matrix* Mrx2 , int num_type){
    matrix* resMrx = NULL;
    int variant = GetVariantHand();
    switch(variant){
        case 1:
            resMrx = SumMatrix(Mrx1 , Mrx2);
            break;
        case 2:
            resMrx = MultMatrix(Mrx1 , Mrx2);
            break;
        case 3:
            resMrx = TranspositionMrx(Mrx1); 
            break;
        case 4:
            resMrx = SummationComboRows(Mrx1);
            break;
    }
    return resMrx;
}

void outputData(matrix* Mrx1 , matrix* Mrx2 , matrix* resMrx , int num_type){
    int variant;
    printf("Какую матрицу вывести в консоль:\n");
    printf("1.Матрица 1.\n");
    printf("2.Результирующая матрица.\n");
    scanf("%d" , &variant);
    switch(variant){
        case 1:
            if(num_type == 1){
                outputDataMrxInt(Mrx1);
            }
            else outputDataMrxFloat(Mrx1);
            break;
        case 2:
            if(num_type == 1){
                outputDataMrxInt(resMrx);
            }
            else outputDataMrxFloat(resMrx);
            break;
    }
    return;
}