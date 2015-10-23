/* forward.h */

#ifndef FWD
#define FWD

void forward(int chain_len, int n_states, 
	     double *init_state_probs, double **trans_probs, double *emission_probs, 
	     int *emission_data, double **result_matrix, double *underflow_vector, 
	     double **out);

void forward_print(int n_states, int chain_len, double ** result_matrix);

#endif
