#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>
#include <numeric>

extern "C" {
#include "../csalt.h"
}

TEST_CASE("Logit", "[calc]") {
  double p[] = { 0.1, 0.2, 0.7 };
  double logp[] = { log(0.1), log(0.2), log(0.7) } ;
  size_t n = 3;

  SECTION("logit") {
    double logitp[n];
    logit(n,p,logitp);
    REQUIRE( logitp[0] == Approx(log(0.1/0.9)) );
    REQUIRE( logitp[1] == Approx(log(0.2/0.8)) );
    REQUIRE( logitp[2] == Approx(log(0.7/0.3)) );
  }

  SECTION("logit_log") {
    double logitp[n];
    logit(n,p,logitp);
    REQUIRE( logitp[0] == Approx(log(0.1/0.9)) );
    REQUIRE( logitp[1] == Approx(log(0.2/0.8)) );
    REQUIRE( logitp[2] == Approx(log(0.7/0.3)) );
  }

  SECTION("logit_sum") {
    double logitp[n];
    logit(n,p,logitp);

    REQUIRE( logit_sum(n,logitp) == 0.0 );

    double lp2[2]; logit(2,p,lp2);
    REQUIRE( logit_sum(2,lp2) == Approx(log(0.3)) );

    REQUIRE( logit_sum_drop1(n,logitp,0) == Approx(log(0.9)) );
    REQUIRE( logit_sum_drop1(n,logitp,2) == Approx(log(0.3)) );
    REQUIRE( logit_sum_drop1(n,logitp,1) == Approx(log(0.8)) );
  }

  SECTION("logit_scale") {
    REQUIRE( logit_scale(logit1(p[2]),log(0.0001)) == Approx(logit1(p[2]*0.0001)) );
    REQUIRE( logit_scale(logit1(0.0001),log(1.5)) == Approx(logit1(0.0001*1.5)) );
    REQUIRE( logit_scale(logit1(0.9999),log(0.0001)) == Approx(logit1(0.9999*0.0001)) );
  }
}

TEST_CASE("stepping", "[mcmc]") {
  gsl_rng* rng = gsl_rng_alloc(gsl_rng_taus2);
  gsl_rng_set(rng,1987);

  double p[] = { 0.1, 0.2, 0.7 };
  double logp[] = { log(0.1), log(0.2), log(0.7) } ;
  double logitp[] = { logit1(0.1), logit1(0.2), logit1(0.7) } ;

  SECTION("prop_step") {
    double logitpnew[3];
    double dbt = prop_step(3,logitp,logitpnew,1,3.0,rng);

    REQUIRE( logitpnew[0] == Approx(-1.9859) );
    REQUIRE( logitpnew[1] == Approx(-3.332177) );
    REQUIRE( logitpnew[2] == Approx(1.694589) );
    REQUIRE( logit_sum(3,logitpnew) == 0.0 );

    double dbt2 = (log_p1(logitpnew[1])-logp[1]) 
                    + 2*(log_q1(logitpnew[1])-log(1.0-p[1]));

    REQUIRE( dbt == Approx(dbt2) );
  }

  gsl_rng_free(rng);
}
