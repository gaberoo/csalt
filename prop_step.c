#include "csalt.h"

/*
 * Given a logit-scaled simplex point y, this function 
 * draws a new logit-scaled simplex point.
 */

double prop_step(size_t n, const double* y, double* ynew, size_t i, 
                 logit_update_t fun, const void* fpars) 
{
  // perturb ith logit
  memcpy(ynew,y,n*sizeof(double));
  ynew[i] = fun(y[i],fpars);
  
  // Calculate logp and logq for old and new draws
  double log_pi_old = log_p1(y[i]);
  double log_pi_new = log_p1(ynew[i]);

  double log_qi_old = log_q1(y[i]);
  double log_qi_new = log_q1(ynew[i]);

  // Log of the scaling value
  double log_scale = log_qi_new - logit_sum_drop1(n,y,i);
  
  // Logits of the rescaled simplex point
  for (size_t j = 0; j < n; ++j) {
    if (j != i) ynew[j] = logit_scale(y[j], log_scale);
  }
  
  // Add detailed balance term
  double dbt = (log_pi_new-log_pi_old) + (n-1.0)*(log_qi_new-log_qi_old);
  
  return dbt;
}
