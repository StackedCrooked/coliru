#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int solve_upper(double** A, double* b, double* x, int n) {
    int j;
    for(j = n - 1; j >= 0; j--) {
       int k; 
       double z=0;
       for(k = j + 1; k < n; k++) {
     z += A[j][k] * x[k];
       }
       x[j] = (b[j] - z) / A[j][j]; 
    }
    
    return 0;
}

double** transpose(double** A, int n) {
  double **B = (double **) malloc(n * sizeof(double *));
  int i;
  for(i=0; i<n; i++) {
      B[i] = (double *) malloc(n * sizeof(double));  
  }
  
  int j;
  for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
	B[i][j] = A[j][i];
      }
  }

  return B;
}

int solve_lower(double** A, double* b, double* x, int n) {
    int j;
    for(j = 0; j <= n - 1 ; j++) {
       int k; 
       double z=0;
       for(k=0; k<j; k++) {
	 z += A[j][k] * x[k];
       }
       x[j] = (b[j] - z) / A[j][j]; 
    }
    
    return 0;
}

int cholesky(double** A, int n) {  //Wir überschreiben A, da wir für die neuen Einträge nicht mehr auf die bereits 
	int i,j,k;					   //überschriebenen Einträge der alten Matrix zurückgreifen müssen.
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i < j) 
			{
				A[i][j] = 0;
			}
			else if(i == j) 
			{
				double z = 0;
				for(k = 0; k < i; k++) 
				{
					z += A[i][k] * A[i][k];
				}
				A[i][j] = sqrt(A[i][i] - z);
				
				if(A[i][j] == 0) {   //Teilen durch Null nicht definiert, also abbrechen.
					return 0;  
				}
			}
			else if(i > j) 
			{
				double z = 0;
				for(k = 0; k < j; k++) 
				{
					z += A[i][k] * A[j][k];
				}
				A[i][j] = (A[i][j] - z) / A[j][j];
			}
		}
	}
	return 1;
}

int main() 
{  

  double **A1 = (double **) malloc(3 * sizeof(double *));
  int i,j;
  for(i=0; i<3; i++) {
      A1[i] = (double *) malloc(3 * sizeof(double));  
  }
  A1[0][0] = 1;  A1[0][1] = 0;  A1[0][2] = 0;
  A1[1][0] = 0;  A1[1][1] = 2;  A1[1][2] = 0;
  A1[2][0] = 0;  A1[2][1] = 0;  A1[2][2] = 3; 

  double **A2 = (double **) malloc(3 * sizeof(double *));
  for(i=0; i<3; i++) {
      A2[i] = (double *) malloc(3 * sizeof(double));  
  }
  A2[0][0] = 1;  A2[0][1] = 2;  A2[0][2] = 3;
  A2[1][0] = 0;  A2[1][1] = 4;  A2[1][2] = 5;
  A2[2][0] = 0;  A2[2][1] = 0;  A2[2][2] = 6; 
  
  double **A3 = (double **) malloc(3 * sizeof(double *));
  for(i=0; i<3; i++) {
      A3[i] = (double *) malloc(3 * sizeof(double));  
  }
  A3[0][0] = 1;  A3[0][1] = 0;  A3[0][2] = 0;
  A3[1][0] = 2;  A3[1][1] = 3;  A3[1][2] = 0;
  A3[2][0] = 4;  A3[2][1] = 5;  A3[2][2] = 6; 
  
  double b1[3] = {1, 4, 9};
  double b2[3] = {6, 9, 6};
  double b3[3] = {3, 12, 28};
  
  double x1[3], x2[3], x3[3];
  
  
  solve_upper(A1, b1, x1, 3); 
  printf("solve_upper A1:\n");
  for(i=0; i<3; i++) {
      printf("%f  ", x1[i]);
  }
  printf("\n");
  
  solve_upper(A2, b2, x2, 3); 
  printf("solve_upper A2:\n");
  for(i=0; i<3; i++) {
      printf("%f  ", x2[i]);
  }
  printf("\n");
  
  solve_lower(A3, b3, x3, 3); 
  printf("solve_lower A3:\n");
  for(i=0; i<3; i++) {
      printf("%f  ", x3[i]);
  }
  printf("\n");
  
  
  
  for(i=0; i<3; i++) {
     free(A1[i]);
     free(A2[i]);
     free(A3[i]);
  }
  free(A1); free(A2); free(A3);
  
  
  
  //Aufgabe 2
  
  double **B1 = (double **) malloc(3 * sizeof(double *));
  for(i=0; i<3; i++) {
      B1[i] = (double *) malloc(3 * sizeof(double));  
  }
  B1[0][0] = 4;  B1[0][1] = 2;  B1[0][2] = 3;
  B1[1][0] = 2;  B1[1][1] = 4;  B1[1][2] = 2;
  B1[2][0] = 3;  B1[2][1] = 2;  B1[2][2] = 4; 
   
  cholesky(B1, 3); 
  printf("cholesky B1:\n");
  for(i=0; i<3; i++) {
	for(j=0; j<3; j++) {
	    printf("%f  ", B1[i][j]);
	}
	printf("\n");
  }
  printf("\n"); 
  
  double b4[3] = {1, 1, 1};
  double x4[3], x5[3];
  
  solve_lower(B1, b4, x4, 3);
  solve_upper(transpose(B1, 3), x4, x5, 3);
  
  printf("solve_B1 mit Cholesky:\n");
  for(i=0; i<3; i++) {
      printf("%f  ", x5[i]);
  }
  printf("\n");
  
  for(i=0; i<3; i++) {
     free(B1[i]);
  }
  free(B1);
  
  
  
  int k;
  for(k = 3; k <= 80; k = k * 2)
  {
	double **B2 = (double **) malloc(k * sizeof(double *));
	for(i = 0; i < k; i++) {
      B2[i] = (double *) malloc(k * sizeof(double)); 
	  for(j = 0; j < k; j++) {
		B2[i][j] = 0;
	  }
	}
  
	for(i = 0; i < k; i++) {
		if(i - 1 > 0) {
			B2[i][i - 1] = -1;
		}
		B2[i][i] = 2;
		if(i + 1 < k) {
			B2[i][i + 1] = -1;
		}
	}

	double b[k];
	for(i = 0; i < k; i++) {
		b[i] = 1;
	}
	double x[k], y[k];
  
    cholesky(B2, k); 
	solve_lower(B2, b, x, k);
	solve_upper(transpose(B2, k), x, y, k);
    
	printf("solve_B%d mit Cholesky:\n", k);
    
    for(i = 0; i < k; i++) {
      printf("%f  ", x[i]);
    }
	printf("\n");
	for(i = 0; i < k; i++) {
      printf("%f  ", y[i]);
	}
	printf("\n");
	
	for(i = 0; i < k; i++) {
		free(B2[i]);
	}
	free(B2); free(x); free(y); free(b);
  }
  
  return 0;

} 

 