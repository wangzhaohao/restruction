
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
MOXThermalTempl<is_ad>:;validParams()
{
	InputParameters params = Material::vaildParams();

	params.addRequiredCoupledVar("tempearture", "Coupled temperature");
	params.addCoupledVar("porosity", 0, "Coupled porosity");
	params.addParam<Real>("americium", 0, "the americium weight fraction in MOX");
	params.addParam<Real>("neptunium", 0, "the eptunium weight fraction in MOX");
	params.addParam<Real>("dev_O_M", 0, "the stoichiomertic deviation");
}

template <bool is_ad>
MOXThermalTempl<is_ad>::MOXThermalTempl(const InputParameters & parameters) : Material(parameters),
	_temperature(coupledGenericValue<is_ad>("temperature")),

