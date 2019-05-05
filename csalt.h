#ifndef __CSALT_H__
#define __CSALT_H__

#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef double (*logit_update_t)(double x, const void* pars);

size_t max_index(size_t n, const double* x);

double logit1(double p);
double logit1_log(double logp);
void logit(size_t n, const double* p, double* logitp);
void logit_log(size_t n, const double* logp, double* logitp);

double log_p1(double x);
double log_q1(double x);
double p1(double x);

void log_p(size_t n, const double* x, double* logp);
void log_q(size_t n, const double* x, double* logq);
void p(size_t n, const double* x, double* logp);

double logit_sum(size_t n, const double* x);
double logit_sum_drop1(size_t n, const double* x, size_t i);

double log_sum_exp(double logu, double logv);

double logit_scale(double x, double logs);
void logit_scale_const(size_t n, const double* x, double logs, double* xout);
void logit_scale_vec(size_t n, const double* x, const double* logs, double* xout);

double prop_step(size_t n, const double* y, double* ynew, size_t i, 
                 logit_update_t fun, const void* fpars);

#ifdef __cplusplus
}
#endif

#endif /* __CSALT_H__ */
