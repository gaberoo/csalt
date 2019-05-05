#include "csalt.h"

/*
 * For x = logit(p) and l = log(s), this function returns logit(sp).
 * Return value is -log(exp(-l) + exp(-(x+l)) - 1)
 * which is algebraically equal to logit(sp).
 * Care is taken to maintain precision in the return value.
 */

double logit_scale(double x, double logs) {
  // Identify cases with l not large and closer to zero than x+l.
  // For these set u= -l and v= -(l+1), otherwise reverse the assignment.
  // If either l or x+l is near zero, -u will be the closest one
  // and exp(u)-1 will be evaluated as expm1(u) to retain precision.

  double u, v;

  if (logs < M_LN2 && fabs(logs) < fabs(x+logs)) {
    u = -logs;
    v = -logs - x;
  } else {
    u = -logs - x;
    v = -logs;
  }

  double ev = exp(v);         // ev is either exp(-(x+l)) or exp(-l) ...
  double eumo = expm1(u); // ... and eumo is the other choice minus one
 
  // Return value is to be -log(ev+eumo).
  // Next two lines choose among three ways to calculate it.

  double l2 = 0.0;
  double out = 0.0;

  // First, calculation of l2=log(eumo+ev) anticipates that ev does not dominate
  // ev+eumo and handles the special case of u large enough to make eumo=Inf.

  if (eumo == INFINITY) {
    l2 = ((u > v) ? u : v) + log1p(exp(-fabs(u-v)));
  } else {
    l2 = log(eumo+ev);
  }
  
  // Second, if ev dominates ev+eumo, then result is -v plus a quantity not far from zero.
  if (v > log(2.0*fabs(eumo))) {
    out = -(v + log1p(eumo/ev));
  } else {
    out = -l2;
  }
  
  return out;
}

void logit_scale_const(size_t n, const double* x, double logs, double* xout) {
  for (size_t i = 0; i < n; ++i) {
    xout[i] = logit_scale(x[i],logs);
  }
}

void logit_scale_vec(size_t n, const double* x, const double* logs, double* xout) {
  for (size_t i = 0; i < n; ++i) {
    xout[i] = logit_scale(x[i],logs[i]);
  }
}

