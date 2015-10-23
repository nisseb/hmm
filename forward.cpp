
#include<iostream>

#include<stdlib.h>
#include<math.h>

#include "forward.h"

using namespace std;

/*
  chain_len: length of markov chain
  n_states: number of descrete states
  init_state_probs: initalization probs for t=0
  trans_probs: transition probabilities for a state s(t-1) -> s(t)
  emission probs: probability for emission of observation x at state y
  emission_data: observed emission data
  result_matrix: stores result of forward algorithm
  underflow_vector: stores normalization for each time step
  out: log-probabilities of forward algorithm for each timestep.
*/
void forward(int chain_len, int n_states, 
	     double *init_state_probs, double **trans_probs, double *emission_probs, 
	     int *emission_data, double **result_matrix, double *underflow_vector, 
	     double **out)
{
  
  double temp_sum = 0;
  
  /* Calculate and scale all forward probabilities j=1:chain_len */
  for (int j = 0; j < chain_len; j++)
    {
      
      /* Calculate each time step */
      for (int i = 0; i < n_states; i++)
	{
	  
	  /* First step with initialization probabilities*/
	  if (j == 0)
	    {
	      result_matrix[i][0] = init_state_probs[i] * emission_probs[emission_data[i]];
	    }
	  
	  /* All other consecutive steps */
	  else
	    {
	      temp_sum = 0;
	      for (int k = 0; k < n_states; k++)
		{
		  temp_sum = temp_sum + result_matrix[k][j-1] * trans_probs[k][i];
		}
	      result_matrix[i][j] = temp_sum * emission_probs[emission_data[j]];
	    }
	}
      
      temp_sum = 0;

      /* After each time step, scale results to avoid underflow */

      for (int i = 0; i < n_states; i++)
	{
	  temp_sum = temp_sum + result_matrix[i][j];
	}
      
      for (int i = 0; i < n_states; i++)
	{
	  result_matrix[i][j] = result_matrix[i][j] / temp_sum;
	}
      
      underflow_vector[j] = temp_sum;
      
      /* Calculate log probabilities */

      for (int i = 0; i < n_states; i++)
	{
	  out[i][0] = log10(result_matrix[i][0] * underflow_vector[0]);
	}
  
      for(int i = 0; i < n_states; i++)
	{
	  for (int j = 1; j < chain_len; j++)
	    {
	      out[i][j] = out[i][j-1] + log10(result_matrix[i][j] * underflow_vector[j]);
	    }
	}
      
    }
}

void forward_print(int n_states, int chain_len, double **data)
{
  for (int i = 0; i < n_states; i++)
    {
      for (int j = 0; j < chain_len; j++)
	{
	  printf("%0.4f ", data[i][j]);
	}
      std::cout << '\n';
    }
}
