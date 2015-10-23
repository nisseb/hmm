
#include<iostream>

#include<stdlib.h>
#include<time.h>
#include<math.h>

#define SIZE 3
#define CHAIN_LEN 10

using namespace std;

void forward(int chain_len, int n_states, 
		double *init_state_probs, double **trans_probs, double *emission_probs, 
	        int *emission_data, double **result_matrix)
{
  
  /* First step with initial parameters */
  

  for (int i = 0; i < n_states; i++)
    {
      result_matrix[i][0] = init_state_probs[i] * emission_probs[emission_data[i]];
    }
  
  
  for (int j = 1; j < chain_len; j++)
    {
      for (int i = 0; i < n_states; i++)
	{
	  
	  double temp_sum = 0;
	  for (int k = 0; k < n_states; k++)
	    {
	      temp_sum = temp_sum + result_matrix[k][j-1] * trans_probs[k][i];
	    }
	  result_matrix[i][j] = temp_sum * emission_probs[emission_data[i]];
	}
    }
}

void forward_print(int n_states, int chain_len, double ** result_matrix)
{
  printf("Forward algorithm: \n");
  for (int i = 0; i < n_states; i++)
    {
      for (int j = 0; j < chain_len; j++)
	{
	  printf("%0.4f ", result_matrix[i][j]);
	}
      std::cout << '\n';
    }
}


int main(int argc, char *argv[])
{
  
  /* Allocate memory */
  double *init_state_probs = new double[SIZE];
  double *emission_probs = new double[SIZE];

  double **trans_probs = new double*[SIZE];
  double **result_matrix = new double*[SIZE];
  for (int i = 0; i < SIZE; i++)
    {
      trans_probs[i] = new double[CHAIN_LEN];
      result_matrix[i] = new double[CHAIN_LEN];
      
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
  forward(CHAIN_LEN, SIZE, 
	     init_state_probs, trans_probs, emission_probs, 
	     emission_data, result_matrix);
  forward_print(SIZE, CHAIN_LEN, result_matrix);
  return 0;
}


