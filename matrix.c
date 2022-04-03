#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [허정윤]  [2021041047] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); //a,b와 a의 전치행렬 T  
     
    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row<=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return NULL;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 NULL 리턴.

    int** matrix = (int**)malloc(sizeof(int*)*row);
    for(int i=0;i<row;i++) matrix[i] = (int*)malloc(sizeof(int)*col);
                                                                //이중 포인터로 matrix를 row크기만큼 동적할당. for문으로 각 칸당 다시 col크기 만큼 동적할당.

    if(matrix ==NULL){
        printf("Error: Allocate Fail\n");
        return NULL;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 NULL 리턴.

    return matrix;                                              //matrix를 리턴   
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if(row<=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            printf("%5d", matrix[i][j]);                        //col을 먼저 늘려 가로줄부터 출력
        }
        printf("\n");                                            //한개 가로줄이 출력되면 개행
    }

    if(matrix ==NULL){
        printf("Error: Allocate Fail\n");
        return;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.

    return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                            //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    for(int f_row=0;f_row<row;f_row++){
        free(matrix[f_row]);
    }

    free(matrix);
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j] = rand()%20;                           //0~19까지의 랜덤 값
        }
    }

    if(matrix ==NULL){
        printf("Error: Allocate Fail\n");
        return -1;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.

    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    int** matrix_sum = create_matrix(row, col);                 //더한 결과 행렬을 정의
    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];
        }
    }

    if(matrix_a ==NULL || matrix_b ==NULL){
        printf("Error: Allocate Fail\n");
        return -1;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.

    print_matrix(matrix_sum, row, col);
    free_matrix(matrix_sum, row, col);                          //출력과 해제
    
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.
    
    int** matrix_sub = create_matrix(row, col);                 //뺸 결과 행렬을 정의
    for(int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            matrix_sub[i][j]=matrix_a[i][j] - matrix_b[i][j];
        }
    }

    if(matrix_a ==NULL || matrix_b ==NULL){
        printf("Error: Allocate Fail\n");
        return -1;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.

    print_matrix(matrix_sub, row, col);
    free_matrix(matrix_sub, row, col);                          //출력과 해제

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    for(int t_row = 0; t_row < row; t_row++){
        for(int t_col =0; t_col < col ; t_col++){
            matrix_t[t_row][t_col] = matrix[t_col][t_row];      //matrix의 행과 열 index를 반대로 해서 matrix_t에 넣어준다.                
        }
    }

    if(matrix ==NULL || matrix_t ==NULL){
        printf("Error: Allocate Fail\n");
        return -1;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_mul = create_matrix(row, row);

    if(row <=0 || col<=0){
        printf("Error: Wrong size of row or col\n");
        return -1;
    }                                                           //row나 col이 0이하의 잘못된 값일경우 에러 메시지와 -1 리턴.

    for (int m_row = 0; m_row < row; m_row++){
        for(int m_col = 0; m_col < row; m_col++){               //곱한 결과 행렬의 크기는 (곱하는 앞행렬의 행갯수)*(곱하는 뒷행렬의 열갯수)
                                                                //여기서는 전치행렬과 곱하므로 두 값이 모두 row
            int sum=0;
            for(int k=0;k < col;k++){
                sum+= matrix_a[m_row][k]*matrix_t[k][m_col];    //반복문으로 각 연산을 해서 더해준뒤
            }
            matrix_mul[m_row][m_col] = sum;                     //반복이 끝나고 matrix_mul에 대입해준다.
        }
    }

    if(matrix_a ==NULL || matrix_t ==NULL){
        printf("Error: Allocate Fail\n");
        return -1;
    }                                                           //matrix가 NULL이 되버리면 에러메시지를 띄우고 -1 리턴.

    print_matrix(matrix_mul, row, row);
    free_matrix(matrix_mul, row, col);                          //출력과 할당 해제

    return 1;
}
