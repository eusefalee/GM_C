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

#include "GroundMotionSim.h"
registerMooseObject("MastodonApp", GroundMotionSim);


InputParameters
GroundMotionSim::validParams()
{
  InputParameters params = PiecewiseLinearBase::validParams();
  params.addRequiredParam<Real>("M", "Magnitude of Event");
  params.addRequiredParam<Real>("R", "Joyner-Boore or Epicentral Distance");
  params.addRequiredParam<Real>("Vs30", "Shear Wave Velocity at 30m");
  params.addParam<std::string>("F","'SS'","Style of Faulting");
  params.addParam<std::string>("R_type", "'Rjb'", "Indicates whether R distance is Joyner-Boore or Epicentral distance");
  params.addParam<int>("n",1,"Number of Simulations to run for each set of inputs");
  params.set<std::vector<Real>>("xy_data") = {};
  params.addClassDescription(
      "Calculates a ground acceleration history using a ground motion model written in a python script");
  return params;
}


// Define arbitrarily large size of preallocated arrays for t and Acc
#define BUFSIZE 20000

GroundMotionSim::GroundMotionSim(const InputParameters & parameters) : PiecewiseLinearBase(parameters)
{
  const auto M = this->template getParam<Real>("M");
  const auto R = this->template getParam<Real>("R");
  const auto V = this->template getParam<Real>("Vs30");
  const auto F = this->template getParam<std::string>("F");
  const auto n = this->template getParam<int>("n");
  const auto R_type = this->template getParam<std::string>("R_type");

//   // Return error and exit if F out of bounds
//   (F < 0 || F >= 3) ? std::cout << "Invalid F value" std::endl return 0;

//   // Convert F style of faulting from real value to string with fault type
//   //    The continuous range of F allows for using sampling distributions although Fault type is a discrete variable
//   std::string Fstr = (F >=0 && F < 1) ? " 'SS' " : (F >= 1 && F < 2) ? " 'TF' " : (F >= 2 && F < 3) ? " 'NF' ";

  // Convert input parameters to strings
  std::string Mstr = std::to_string(M);
  std::string Rstr = std::to_string(R);
  std::string Vstr = std::to_string(V);
  std::string nstr = std::to_string(n);
  
  // Concatenate command with input parameters
  std::string command = "python $HOME/projects/mastodon/python/mastodonutils/GMSim.py GroundMotionSim ";
  command += Mstr + " " + R_type + " " + Rstr + " " + Vstr + " " + F + " " + nstr;

  // Convert command to C character string for use in parse_output function
  char const *cmd = command.c_str();

  // Initialize time and acceleration variables
  std::string t;
  std::string Acc;

  // Run command line parsing function
  parse_output(cmd,t,Acc);

  // Initialize vectors to hold data
  std::vector<Real> x;
  std::vector<Real> y;
  x.reserve(BUFSIZE);
  y.reserve(BUFSIZE);

  // Build an istream that holds the input string
  std::istringstream iss(t.substr(1,t.length()));
  std::istringstream jss(Acc.substr(1,Acc.length()));

  // Iterate over the istream, using >> to grab floats
  // and push_back to store them in the vector
  std::copy(std::istream_iterator<Real>(iss),
          std::istream_iterator<Real>(),
          std::back_inserter(x));

  std::copy(std::istream_iterator<Real>(jss),
          std::istream_iterator<Real>(),
          std::back_inserter(y));

  // Set the x (time) and y(acc) values in the PiecewiseLinearBase class
  setData(x,y);  


}


void
GroundMotionSim::parse_output(const char* cmd, std::string &t,std::string &Acc) const {
    // Function to execute command line commands that run a pythong script
    // which calculates the acceleration history for a ground motion.
    // The function then reads the output and saves it into strings

    // Initializing variables
    std::array<char, BUFSIZE> buffer;
    std::string result;

    // This variable is used to track when the output changes from
    // time array to acceleration array
    char trackbuf;

    // Run command and check for command line errors
    auto pipe = popen(cmd, "r"); // get rid of shared_ptr
    if (!pipe) throw std::runtime_error("popen() failed!");

    // Iterate over the output of the command line
    while (!feof(pipe)) {

        if (fgets(buffer.data(), BUFSIZE, pipe) != nullptr){

            // Check if the end of the t vector has been reached
            if (trackbuf == 'A'){

                trackbuf = 'A';
            }else {
                trackbuf = buffer[0];
            }

            // append strings with command line data
            if (trackbuf != 'A'){
            //result += buffer.data();
                t += buffer.data();
            } 
            else {
                Acc += buffer.data();
            }
        }
    }

    // Close command line
    auto rc = pclose(pipe);

    if (rc == EXIT_SUCCESS) { // == 0

    } else if (rc == EXIT_FAILURE) {  // EXIT_FAILURE is not used by all programs, maybe needs some adaptation.

    }

    // Remove "t=" and "Acc=" from strings
    t.erase(0,3);
    Acc.erase(0,5);
    return;
}
