# include <iostream>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500
#define T 20
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
long long sum_C = 0, sum_D = 0;

void* Addition(void* arg){
          int id = *(int*) arg;
          // Addition -> matC
          for (int i = id; i < MAX; i+=T) {
                    for (int j = 0; j < MAX; j++){
                              matC[i][j] = matA[i][j] + matB[i][j];
                    }
          }
          pthread_exit(NULL);
}

void* Multiplication(void* arg){
          int id = *(int*) arg;
          // Multiplication -> matD
          for (int i = id; i < MAX; i+=T) {
                    for (int j = 0; j < MAX; j++) {
                              matD[i][j] = 0;
                              for (int k = 0; k < MAX; k++) {
                                        matD[i][j] += matA[i][k] * matB[k][j];
                              }
                    }
          }
          pthread_exit(NULL);
}

/*
void* AddMatrix(void *arg){
          int *mat = (int*) arg;
          for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++){
                              sum_C +=  matC[i][j];
                    }
          }
          pthread_exit(NULL);
}

void* MulMatrix(void *arg){
          int *mat = (int*) arg;
          for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++){
                              sum_D +=  matD[i][j];
                    }
          }
          pthread_exit(NULL);
}
*/
int main()
{
          //get input
          for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++) {
                              cin >> matA[i][j];
                    }
          }
          for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++) {
                              cin >> matB[i][j];
                    }
          }
          pthread_t thread[T+2];
          int sum_id[T], mul_id[T];
          for (int i=0; i < T; i++)
          {
                    sum_id[i] = i;
                    mul_id[i] = i;
                    pthread_create(&thread[i], NULL, Addition, &sum_id[i]);
                    pthread_create(&thread[i], NULL, Multiplication, &mul_id[i]);
          }
          for (int i = 0; i < T; i++)
                    pthread_join(thread[i], NULL);


          // calculate SUM of matC// calculate SUM of matD
          /*
          pthread_create(&thread[T+1], NULL, AddMatrix, &matC);
          pthread_create(&thread[T+2], NULL, MulMatrix, &matD);
          pthread_join(thread[T+1], NULL);
          pthread_join(thread[T+2], NULL);
          */

          for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++){
                              sum_C +=  matC[i][j];
                              sum_D += matD[i][j];
                    }
          }
          cout << sum_C << endl;
          cout << sum_D << endl;
          return 0;
}
