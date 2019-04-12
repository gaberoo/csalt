#include <string.h>

#include <gsl/gsl_statistics.h>

#include "csalt.h"

/*
 * For x=logit(p), this function returns s = log(sum(p)) where the
 * sum of p is less than or equal to 1. Calculations are designed to 
 * preserve accuracy even for values numerically near 0 or 1.
 */

double logit_sum_drop1(size_t n, const double* x, size_t drop) {
  // Take logp and logq for all values
  // x <- sort(x, decreasing=TRUE)
  double* logp = (double*) malloc(n*sizeof(double));
  double* logq = (double*) malloc(n*sizeof(double));

  log_p(n,x,logp);
  log_q(n,x,logq);

  size_t imax = gsl_stats_max_index(x,1,n);
  if (imax == drop) {
    size_t i1 = gsl_stats_max_index(x,1,drop);
    size_t i2 = gsl_stats_max_index(x+drop+1,1,n-(drop+1));
    imax = (x[i1] > x[i2]) ? i1 : i2;
  }

  double sum;
  
  // Find sum of logp, using different calculation method
  // if the max(x) < 0 or max(x) >= 0 to preserve accuracy
  
  if (x[imax] < 0.0) { // avoid calculating exp(lp1) when it can be numerically zero
    sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
      if (i != imax && i != drop) sum += exp(logp[i]-logp[imax]);
    }
    sum = logp[imax] + gsl_log1p(sum);
  } else { // avoid calculating exp(lp1) when it can be numerically one
    sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
      if (i != imax && i != drop) sum += exp(logp[i]);
    }
    sum = gsl_log1p(sum-exp(logq[imax]));
  }
  
  free(logp);
  free(logq);

  return sum;
}

double logit_sum(size_t n, const double* x) {
  return logit_sum_drop1(n,x,-1);
}


