//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/**
* this material is produce the MOX thermal properties and the model is from the 
*  Physical properties and irradiation behavior analysis of Np-and Am-bearing MOX fuels
*/
#include "MOXThermal.h"

#include "libmesh/quadrature.h"

registerMooseObject("RestructeApp", ADMOXThermal);
registerMooseObject("RestructeApp", MOXThermal);

template <bool is_ad>
InputParameters
MOXThermalTempl<is_ad>::validParams()
{
	InputParameters params = Material::validParams();

	params.addRequiredCoupledVar("temperature", "Coupled temperature");
	params.addCoupledVar("porosity", 0, "Coupled porosity");
	params.addParam<Real>("americium", 0, "the americium weight fraction in MOX");
	params.addParam<Real>("neptunium", 0, "the eptunium weight fraction in MOX");
	params.addParam<Real>("dev_O_M", 0, "the stoichiomertic deviation");

  params.addParam<Real>("thermal_conductivity", "the thermal conductivity value");
  params.addParam<Real>("specific_heat", "the specific heat value of MOX");
  params.addParam<Real>("density", "the density value of MOX");

  return params;
}

template <bool is_ad>
MOXThermalTempl<is_ad>::MOXThermalTempl(const InputParameters & parameters) : Material(parameters),
  _americium(getParam<Real>("americium")),
  _neptunium(getParam<Real>("neptunium")),
  _dev_O_M(getParam<Real>("dev_O_M")),

	_temperature(coupledGenericValue<is_ad>("temperature")),
  _porosity(coupledGenericValue<is_ad>("porosity")),
  _my_thermal_conductivity(isParamValid("thermal_conductivity") ? getParam<Real>("thermal_conductivity") : 0),
  _my_specific_heat(isParamValid("specific_heat") ? getParam<Real>("specific_heat") : 0),
  _my_density(isParamValid("density") ? getParam<Real>("density") : 0),

  _thermal_conductivity(declareGenericProperty<Real, is_ad>("thermal_conductivity")),
  _specific_heat(declareGenericProperty<Real, is_ad>("specific_heat")),
  _density(declareGenericProperty<Real, is_ad>("density"))
{
}

template <bool is_ad>
void
MOXThermalTempl<is_ad>::computeProperties()
{
 for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
 {
   auto qp_temperature = _temperature[qp];
   if (qp_temperature < 0)
   {
     std::stringstream msg;
     msg << "WARNING: In MOXThermal : negative temperature!\n"
       << "\tResetting to zero. \n"
       << "\t_qp: " << qp << "\n"
       << "\ttemp: " << qp_temperature << "\n"
       << "\telem: " << _current_elem->id() << "\n"
       << "\tproc: " << processor_id() << "\n";
      mooseWarning(msg.str());
      qp_temperature = 0;
   }
   if (isParamValid("thermal_conductivity"))
   {
     _thermal_conductivity[qp] = _my_thermal_conductivity;
   }
   else
   {
     //the heat conduction model is Kato 
     auto qp_porosity = _porosity[qp];
     if (qp_porosity > 0.95)
       qp_porosity = 0.95;

     auto correction_porosity = (1 - qp_porosity)/(1 + qp_porosity/2);
     /*std::cout<<correction_porosity<<std::endl;*/

     auto correction_composition = 1.595e-2 + 2.713 * (2 - _dev_O_M) + (3.583e-1 * _americium) + (6.317e-2 * _neptunium) + (-2.625 * (2 - _dev_O_M) + 2.493) * 1e-4 * qp_temperature;

     /*std::cout<<correction_composition<<std::endl;*/

     _thermal_conductivity[qp] = correction_porosity *( (1.541e11 / std::pow(qp_temperature, 2.5)) * std::exp(-1.522e4 / qp_temperature) + 1 / correction_composition);
   }

  //specific heat
  _specific_heat[qp] = _my_specific_heat; //J/K-kg

  //density
  _density[qp] = _my_density; //kg/m^3
 }
}

template class MOXThermalTempl<false>;
template class MOXThermalTempl<true>;
