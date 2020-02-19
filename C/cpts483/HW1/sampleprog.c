void main(){
int A[3][4];
int B[4][5];
int C[3][5];
int D[3][5];
int E[3][5];
int tmp00[3][5];
for (int i = 0; i < 3; i++) {
   for (int j = 0; j < 4; j++) {
     int sum = 0;
     for (int k = 0; k < 3; k++)
       sum = sum + *((int *)A + i * 3 + k) *
                   *((int *)B + k * 4 + j);
     *((int *)tmp00 + i * 3 + j) = sum;
   }
 
}
int tmp01[3][5];
for (int i = 0; i < 15; i++) {
*(int *)tmp01[i] = *(int *)C[i] + *(int *)tmp00[i];
}
memcpy(tmp01, D, 8);
memcpy(D, E, 8);
int A[3][4][5][6];
int B[3][4][5][6];
int C[3][4][5][6];
int tmp02[3][4][5][6];
for (int i = 0; i < 360; i++) {
*(int *)tmp02[i] = *(int *)A[i] + *(int *)B[i];
}
memcpy(tmp02, C, 8);
}
