
#include <stdlib.h>
#include <gsl/gsl_math.h>

/* 
 * Return logit of probabilities p. If logp = true, the first argument 
 * contains natural logs of probabilites which helps preserve accuracy
 * for probailities near 1
 * 
 * Two different ways to write logit(p) on natural scale
 * Which method is used depends on which is more numerically 
 * accurate
 */

double logit1(double p) {
  if (p < 0.5) return log(p) - log1p(-p);
  else return log(p/(1.0-p));
}

double logit1_log(double logp) {
  if (logp < 0.5) return logp - log1p(-exp(logp));
  else return logp - log(-expm1(logp));
}

void logit(size_t n, const double* p, double* logitp) {
  for (size_t i = 0; i < n; ++i) logitp[i] = logit1(p[i]);
}
  
void logit_log(size_t n, const double* logp, double* logitp) {
  for (size_t i = 0; i < n; ++i) logitp[i] = logit1_log(logp[i]);
}

double log_sum_exp(double logu, double logv) {
  double max = (logu > logv) ? logu : logv;
  return max + log(exp(u-max)) + log(exp(v-max));
}


