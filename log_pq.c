
#include <stdlib.h>
#include <gsl/gsl_math.h>

/*
 * For x = logit(p), this function returns log(p) and log(1-p). 
 * Special care is taken to ensure accuracy when coordinates 
 * are numerically close to 0 or 1.
 */

double log_p1(double x) {
  if (x < 0.0) return -gsl_log1p(exp(x)) + x;
  else return -gsl_log1p(1.0/exp(x));
}

double log_q1(double x) {
  if (x < 0.0) return -gsl_log1p(exp(x));
  else return -gsl_log1p(1.0/exp(x)) - x;
}

void log_p(size_t n, const double* x, double* logp) {
  for (size_t i = 0; i < n; ++i) logp[i] = log_p1(x[i]);
}

void log_q(size_t n, const double* x, double* logq) {
  for (size_t i = 0; i < n; ++i) logq[i] = log_q1(x[i]);
}

double p1(double x) { return exp(log_p1(x)); }

void p(size_t n, const double* x, double* p) {
  for (size_t i = 0; i < n; ++i) p[i] = p1(x[i]);
}
