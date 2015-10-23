
#include<iostream>

#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "forward.h"

#define SIZE 3
#define CHAIN_LEN 10

using namespace std;

int main(int argc, char *argv[])
{
  
  /* Allocate memory */
  double *init_state_probs = new double[SIZE];
  double *emission_probs = new double[SIZE];
  double *underflow_vector = new double[CHAIN_LEN];

  double **trans_probs = new double*[SIZE];
  double **result_matrix = new double*[SIZE];
  double **logres_matrix = new double*[SIZE];

  for (int i = 0; i < SIZE; i++)
    {
      trans_probs[i] = new double[SIZE];
      result_matrix[i] = new double[CHAIN_LEN];
      logres_matrix[i] = new double[CHAIN_LEN];
      underflow_vector[i] = 0;
      
      for (int j = 0; j < CHAIN_LEN; j++)
	{
	  result_matrix[i][j] = 0;
	}
    }
  
  int *emission_data = new int[CHAIN_LEN];
  

  /* Assignment of data */
  double ep[SIZE] = {0.1, 0.4, 0.5};
  double isp[SIZE] = {0.2, 0.2, 0.6};
  
  double tp[SIZE][SIZE] = {{0.4, 0.3, 0.3}, 
			   {0.2, 0.4, 0.4}, 
			   {0.2, 0.3, 0.5}};
  
  
  srand(time(NULL));
  
  for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < CHAIN_LEN; j++)
	{
	  if (j == 0)
	    {
	      emission_probs[i] = ep[i];
	      init_state_probs[i] = isp[i];

	    }
	  if (i == 0)
	    {
	      emission_data[j] = (int)(rand() / (double)(RAND_MAX) * SIZE);
	    }
	}
    }
  
  for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
	{
	  trans_probs[i][j] = tp[i][j];
	}
    }

  /* Start using the forward function */

  /**/
  forward(CHAIN_LEN, SIZE, 
	  init_state_probs, trans_probs, emission_probs, 
	  emission_data, result_matrix, underflow_vector, logres_matrix);
  forward_print(SIZE, CHAIN_LEN, logres_matrix);
  /**/

  return 0;
}
