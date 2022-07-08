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

#include "GroundMotionSimulation.h"

registerMooseObject("MastodonApp", GroundMotionSimulation);

InputParameters
GroundMotionSimulation::validParams()
{
  InputParameters params = Function::validParams();
  params.addRequiredParam<Real>("M", "Moment Magnitude of Ground Motion.");
  params.addRequiredParam<Real>("Vs30", "Shear Wave Velocity at 30m.");
  params.addRequiredParam<Real>("Rval", "Epicentral or Joyner-Boore Distance.");
  params.addRequiredParam<string>("Dist", "'Repi' or 'Rjb' to indicate epicentral or JB distance.");
  params.addRequiredParam<string>("F", "Fault type: 'NF' (Normal), 'TF' (Thrust), or 'SS' (Strike-Slip).");
  params.addParam<int>("n", 1, "Number of simulations.");
  params.addClassDescription(
      "Simulates acceleration time-history of a ground motion based on the input parameters.");
  return params;
}

GroundMotionSimulation::GroundMotionSimulation(const InputParameters & parameters)
  : Function(parameters), _num_sims(getParam<Real>("num_sims"))
{
}

Real
GroundMotionSimulation::value(Real t, const Point &) const
{
  Real M = getParam<Real>("M");
  Real Vs30 = getParam<Real>("Vs30");
  Real Rval = getParam<Real>("Rval");
  string Dist = getParam<string>("Dist");
  string F = getParam<string>("F");


  // Perform Distance Conversion
  if Dist == 'Repi'{
    Repi = Rval;
    Rjb = GroundMotionSimulation::REPI2RJB(M,Repi);
    R = Rjb;
  }
  else if Dist == 'Rjb'
  {
    Rjb = Rval;
    Repi = GroundMotionSimulation::RJB2REPI(M,Rjb);
    R = Rjb;
  }
 
}

// sinc function (tends to 1 as x -> 0)
inline Real
OrmsbyWavelet::sinc(Real x) const
{
  return (x == 0) ? 1.0 : sin(x) / x;
}