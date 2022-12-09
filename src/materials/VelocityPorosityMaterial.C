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
  _temperature(coupledValue("temp")),
  _grad_temperature(coupledGradient("temp")),
  _velocity_pore(declareADProperty<Real>("velocity_pore"))
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
		if (qp_temperature >= 1500 && qp_temperature <= 2000)
		{
			P0 = std::exp(33.785);
			delta_H = 5.98e5;
		}
		else if (qp_temperature <= 2200)
		{
			P0 = std::exp(34.8107);
			delta_H = 6.17e5; 
		}
		else
		{
			P0 = std::exp(35.813);
			delta_H = 6.35e5; 
		}
// 此处1e7是为了单位一制？大概是吧，不然这个扩散速率太小了
		_velocity_pore[qp] = 5e-16 * (0.988 + 6.395e-6 * qp_temperature + 3.543e-9 * std::pow(qp_temperature, 2) + 3e-12 * std::pow(qp_temperature, 3)) * std::pow(qp_temperature, -2.5) * delta_H * 1e7 * P0 * std::exp(-delta_H / 8.314 / qp_temperature) * _grad_temperature[qp](0); // 这里使用_qp的原因未知，猜测大概是因为qp设置成unsigned会丢失信息？

		_velocity_pore[qp] = 0.01* 0.01 * _velocity_pore[qp];
		// std::cout<<_temperature[qp]<<'\t';
		// std::cout<<qp_temperature<< '\t';
		// std::cout<<_velocity_porosity[qp]<<std::endl;
	}

}
