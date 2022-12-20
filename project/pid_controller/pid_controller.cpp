/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/

   _Kd = Kdi;
   _Kp = Kpi;
   _Ki = Kii;
   _output_lim_max = output_lim_maxi;
   _output_lim_min = output_lim_mini;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   _d_err = _dt > 0 ? (cte - _Kp) / _dt : 0;
   _p_err = cte;
   _i_err += cte * _dt;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control;
   cout << "errs: " << _d_err << " " << _p_err << " " << _i_err << " " << endl;
   // cout << "params: " << _Kd << " " << _Kp << " " << _Ki << " " << endl;
   control = -(_d_err * _Kd + _p_err * _Kp + _i_err * _Ki);
   cout << "raw control: " << control << endl;
   control = max(control, _output_lim_min);
   control = min(control, _output_lim_max);
   // cout << "limited control: " << control << endl;
   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  _dt = new_delta_time;
}