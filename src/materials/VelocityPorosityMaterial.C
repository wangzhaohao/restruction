//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "VelocityPorosityMaterial.h"
#include "libmesh/quadrature.h"

registerMooseObject("RestructeApp", VelocityPorosityMaterial);

InputParameters
VelocityPorosityMaterial::validParams()
{
  InputParameters params = Material::validParams();

  params.addRequiredCoupledVar("temp", "Coupled Temperature");
  params.addClassDescription("the restructing of MOX pore velocity");

  return params;
}

VelocityPorosityMaterial::VelocityPorosityMaterial(const InputParameters & parameters)
  : Material(parameters),
  _velocity_pore(declareADProperty<Real>("velocity_pore")),
  _temperature(coupledValue("temp")),
  _grad_temperature(coupledGradient("temp"))
{
}

void
VelocityPorosityMaterial::computeProperties()
{
  for(unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
    auto qp_temperature = _temperature[qp];
    if (qp_temperature < 0)
    {
      std::stringstream msg;
      msg << "WARNING: In VelocityPorosityMaterial: negative temperature!\n"
        << "\tResetting to zero.\n"
        << "\t_qp: " << qp <<"\n"
        << "\ttemp: " << qp_temperature << "\n"
        << "\telem: " << _current_elem->id() << "\n"
        << "\tproc: " << processor_id() << "\n";
      mooseWarning(msg.str());
      qp_temperature = 0;
    }

    Real delta_H = 0; // J/mole
    Real P0 = 0; //dynes/cm^2
    if (qp_temperature <= 2000)
    {
      P0 = std::exp(33.7085);
      delta_H = 5.98e5;
    }
    else if (qp_temperature <= 2200)
    {
      P0 = std::exp(33.7085 + (35.813 - 33.7085) *( qp_temperature - 2000.0 ) / 200.0 );//By interpolation
      delta_H = (5.98 + (6.35 - 5.98) * (qp_temperature - 2000.0) / 200) * 1e5;//By interpolation
    }
    else
    {
      P0 = std::exp(35.813);
      delta_H = 6.35e5; 
    }
    _velocity_pore[qp] = 5e-16 * (0.988 + 6.395e-6 * qp_temperature + 3.543e-9 * std::pow(qp_temperature, 2) + 3e-12 * std::pow(qp_temperature, 3)) * std::pow(qp_temperature, -2.5) * delta_H * 1e7 * P0 * std::exp(-delta_H / 8.314 / qp_temperature) * _grad_temperature[qp](0);

    _velocity_pore[qp] = 0.01* 0.01 * _velocity_pore[qp];
  }

}
