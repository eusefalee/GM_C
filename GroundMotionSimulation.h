/*************************************************/
/*           DO NOT MODIFY THIS HEADER           */
/*                                               */
/*                     MASTODON                  */
/*                                               */
/*    (c) 2015 Battelle Energy Alliance, LLC     */
/*            ALL RIGHTS RESERVED                */
/*                                               */
/*   Prepared by Battelle Energy Alliance, LLC   */
/*     With the U. S. Department of Energy       */
/*                                               */
/*     See COPYRIGHT for full restrictions       */
/*************************************************/

#pragma once

#include "Function.h"
#include "FunctionInterface.h"
#include <cmath>
#include <vector>

class GroundMotionSimulation;

/**
 * Class for Ground Motion Simulation function
 */
class GroundMotionSimulation : public Function
{
public:
  static InputParameters validParams();

  GroundMotionSimulation(const InputParameters & parameters);

  virtual Real value(Real t, const Point & p) const override;

private:
  // sinc function
  inline Real sinc(Real x) const;

  // number of simulations to run for set of input parameters
  const Real _num_sims;

  // Distance conversion Function
  Real REPI2RJB(Real M,string Dist){

    // Initialize variables
    d = 0;mean = 0;sigma = 0;beta = 0;alpha = 0;median = 0;

    if (M >= 3.25 && M <= 6.75)
    {
      while (Repi-d-median > 0.001)
      {
        d += 0.01;

        // Compute Average
        mean = (25.2859086858311 - 24.7579132762745 * M + 9.1067957463996 * pow(M,2) - 1.4924537794753 * pow(M,3) + 0.0943269381529 * pow(M,4)) +
              d * (1.0258015468051 - 0.9546610173338 * M + 0.3306850146342 * pow(M,2) - 0.0507022784386 * pow(M,3) + 0.0029166620192 * pow(M,4)) +
              pow(d,2) * (-0.0087847623757 + 0.008078532233 * M - 0.0027616254404 * pow(M,2) + 0.0004175139082 * pow(M,3) - 0.0000236750349 * pow(M,4)) +
              pow(d,3) * (0.0000210744968 - 0.0000192014444 * M + 0.0000064976695 * pow(M,2) - 0.0000009719658 * pow(M,3) + 0.0000000545396 * pow(M,4));
        
        // Compute Standard Deviation
        sigma = (50.4650608321051 - 48.0676507162484 * M + 17.1052739585892 * pow(M,2) - 2.7022941754681 * pow(M,3) + 0.1613658945296 * pow(M,4)) +
              d * (0.7371820139324 - 0.6752613553 * M + 0.2293488841656 * pow(M,2) - 0.0343077682523 * pow(M,3) + 0.00191302107 * pow(M,4)) +
              pow(d,2) * (-0.0056666537501 + 0.0051882394919 * M - 0.0017625955284 * pow(M,2) + 0.0002639958786 * pow(M,3) - 0.0000147580962 * pow(M,4)) +
              pow(d,3) * (0.0000113403782 - 0.000010388538 * M + 0.0000035364421 * pow(M,2) - 0.0000005318502 * pow(M,3) + 0.0000000299318 * pow(M,4));
      
        beta = pow(sigma,2)/mean;
        alpha = pow(mean/sigma,2)
        //median = 
      }
    }
    else if (M > 6.75 && M <= 8.25)
    {
      while (Repi-d-median > 0.001)
      {
        d += 0.01;

        // Computer Average
        mean = (41330.5714998843 - 22733.3089137796 * M + 4692.74801622372 * pow(M,2) - 431.089171902869 * pow(M,3) + 14.8828551078011 * pow(M,4)) +
            d * (-2416.16571885248 + 1313.68542796199 * M - 267.398312525097 * pow(M,2) + 24.1469682260178 * pow(M,3) - 0.8160573655126 * pow(M,4)) +
            pow(d,2) * (20.7418579312278 - 11.2634077165846 * M + 2.2898378394305 * pow(M,2) - 0.2065409463611 * pow(M,3) + 0.0069730227999 * pow(M,4)) +
            pow(d,3) * (-0.0518782359661 + 0.0281154133727 * M - 0.0057044823582 * pow(M,2) + 0.00051353589 * pow(M,3) - 0.0000173053232 * pow(M,4));    
        
        // Compute Sigma
        sigma = (12207.5188429977 - 7001.4407532747 * M + 1515.67332601025 * pow(M,2) - 146.912852179082 * pow(M,3) + 5.388523704157 * pow(M,4)) +
            d * (-1318.61674483966 + 718.285967089764 * M - 146.541924947989 * pow(M,2) + 13.2688348378962 * pow(M,3) - 0.4497899372784 * pow(M,4)) +
            pow(d,2) * (14.9495278339686 - 8.1301182336872 * M + 1.6558268525748 * pow(M,2) - 0.1496655480247 * pow(M,3) + 0.0050646642932 * pow(M,4)) +
            pow(d,3) * (-0.041450318097 + 0.0224827452608 * M - 0.004566514641 * pow(M,2) + 0.0004116109653 * pow(M,3) - 0.0000138901781 * pow(M,4));

        beta = pow(sigma,2)/mean;
        alpha = pow(mean/sigma,2);
        // median = 
      }
    }
    
    Rjb = d;

  }

  // Distance conversion Function
  Real RJB2REPI(Real M,string Dist){

    // Initialize variables
    d = 0;mean = 0;sigma = 0;beta = 0;alpha = 0;median = 0;

    if (M >= 3.25 && M <= 6.75)
    {
      while (Repi-d-median > 0.001)
      {
        d += 0.01;

        // Compute Average
        mean = (25.2859086858311 - 24.7579132762745 * M + 9.1067957463996 * pow(M,2) - 1.4924537794753 * pow(M,3) + 0.0943269381529 * pow(M,4)) +
            d * (1.0258015468051 - 0.9546610173338 * M + 0.3306850146342 * pow(M,2) - 0.0507022784386 * pow(M,3) + 0.0029166620192 * pow(M,4)) +
            pow(d,2) * (-0.0087847623757 + 0.008078532233 * M - 0.0027616254404 * pow(M,2) + 0.0004175139082 * pow(M,3) - 0.0000236750349 * pow(M,4)) +
            pow(d,3) * (0.0000210744968 - 0.0000192014444 * M + 0.0000064976695 * pow(M,2) - 0.0000009719658 * pow(M,3) + 0.0000000545396 * pow(M,4));
        
        // Compute Standard Deviation
        sigma = (50.4650608321051 - 48.0676507162484 * M + 17.1052739585892 * pow(M,2) - 2.7022941754681 * pow(M,3) + 0.1613658945296 * pow(M,4)) +
            d * (0.7371820139324 - 0.6752613553 * M + 0.2293488841656 * pow(M,2) - 0.0343077682523 * pow(M,3) + 0.00191302107 * pow(M,4)) +
            pow(d,2) * (-0.0056666537501 + 0.0051882394919 * M - 0.0017625955284 * pow(M,2) + 0.0002639958786 * pow(M,3) - 0.0000147580962 * pow(M,4)) +
            pow(d,3) * (0.0000113403782 - 0.000010388538 * M + 0.0000035364421 * pow(M,2) - 0.0000005318502 * pow(M,3) + 0.0000000299318 * pow(M,4));
      
        beta = pow(sigma,2)/mean;
        alpha = pow(mean/sigma,2)
        //median = 
      }
    }
    else if (M > 6.75 && M <= 8.25)
    {
      while (Repi-d-median > 0.001)
      {
        d += 0.01;

        // Computer Average
        mean = (41330.5714998843 - 22733.3089137796 * M + 4692.74801622372 * pow(M,2) - 431.089171902869 * pow(M,3) + 14.8828551078011 * pow(M,4)) +
            d * (-2416.16571885248 + 1313.68542796199 * M - 267.398312525097 * pow(M,2) + 24.1469682260178 * pow(M,3) - 0.8160573655126 * pow(M,4)) +
            pow(d,2) * (20.7418579312278 - 11.2634077165846 * M + 2.2898378394305 * pow(M,2) - 0.2065409463611 * pow(M,3) + 0.0069730227999 * pow(M,4)) +
            pow(d,3) * (-0.0518782359661 + 0.0281154133727 * M - 0.0057044823582 * pow(M,2) + 0.00051353589 * pow(M,3) - 0.0000173053232 * pow(M,4));     
        
        // Compute Sigma
        sigma = (12207.5188429977 - 7001.4407532747 * M + 1515.67332601025 * pow(M,2) - 146.912852179082 * pow(M,3) + 5.388523704157 * pow(M,4)) +
            d * (-1318.61674483966 + 718.285967089764 * M - 146.541924947989 * pow(M,2) + 13.2688348378962 * pow(M,3) - 0.4497899372784 * pow(M,4)) +
            pow(d,2) * (14.9495278339686 - 8.1301182336872 * M + 1.6558268525748 * pow(M,2) - 0.1496655480247 * pow(M,3) + 0.0050646642932 * pow(M,4)) +
            pow(d,3) * (-0.041450318097 + 0.0224827452608 * M - 0.004566514641 * pow(M,2) + 0.0004116109653 * pow(M,3) - 0.0000138901781 * pow(M,4));

        beta = pow(sigma,2)/mean;
        alpha = pow(mean/sigma,2);
        // median = 
      }
    }
    
    Repi = d + median;

  }

  Real AriasAndDV(Real M, string F,){

    // Define Mixed-Effects Coefficients
    vector<double> a = {-2.2907, 0.434};
    double b1 = 0.249
    double b2 = 0.495
    double b11 = 1.4033
    double b21 = -0.0881
    vector<double> c1 = {0.487,-0.098}

  }
};
Footer
© 2022 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
Status
