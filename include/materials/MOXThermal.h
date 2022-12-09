#pragma once

#include "Material.h"
#include "MooseTypes.h"

// Forward Declarations (这个好像不是必须的)

/**
* this material is produce the MOX thermal properties and the model is from the 
*  Physical properties and irradiation behavior analysis of Np-and Am-bearing MOX fuels
*/
template <bool is_ad>
class MOXThermalTempl : public Material
{
	public: 
		static InputParameters validParams();

		MOXThermalTempl(const InputParameters & parameters);

	protected:
		virtual void computeProperties();

		const Real _americium;//weight fraction
		const Real _neptunium;//weight fraction
		const Real _dev_O_M;//stoichiometric deviation (2-x)
												
		const GenericVariableValeu<is_ad> & _temperature;
		const GenericVariableValeu<is_ad> & _porosity;

		GenericMaterialProperty<Real, is_ad> & _thermal_conductivity;
		GenericMaterialProperty<Real, is_ad> & _specific_heat;
		GenericMaterialProperty<Real, is_ad> & _density;
};

typedef MOXThermalTempl<false> MOXThermal;
typedef MOXThermalTempl<true> ADMOXThermal;
