#include "EFieldAdvectionEnergy.h"

registerMooseObject("WolfApp", EFieldAdvectionEnergy);

template <>
InputParameters
validParams<EFieldAdvectionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("mobility", "Electron mobility.");
  return params;
}

EFieldAdvectionEnergy::EFieldAdvectionEnergy(const InputParameters & parameters)
  : Kernel(parameters),

    _grad_potential(coupledGradient("potential")),

    _mobility(getParam<Real>("mobility"))
{
}

Real
EFieldAdvectionEnergy::computeQpResidual()
{
  return -(5 / 3) * _mobility * _u[_qp] * _grad_potential[_qp] * _grad_test[_i][_qp];
}

Real
EFieldAdvectionEnergy::computeQpJacobian()
{
  return -(5 / 3) * _mobility * _phi[_j][_qp] * _grad_potential[_qp] * _grad_test[_i][_qp];
}