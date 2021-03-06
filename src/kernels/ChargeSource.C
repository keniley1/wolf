#include "ChargeSource.h"

registerMooseObject("WolfApp", ChargeSource);

template <>
InputParameters
validParams<ChargeSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("coupled_species", "Species population density.");
  params.addRequiredParam<Real>("sign", "Sign to designate charge of species.");
  return params;
}

ChargeSource::ChargeSource(const InputParameters & parameters)
  : Kernel(parameters),

    _coupled_val(coupledValue("coupled_species")),
    _sign(getParam<Real>("sign")),
    _q(1.602177e-19),
    _eps0(8.854188e-12),
    _coupled_id(coupled("coupled_species"))
{
}

Real
ChargeSource::computeQpResidual()
{
  return -(_q / _eps0) * _sign * _coupled_val[_qp] * _test[_i][_qp];
}

Real
ChargeSource::computeQpJacobian()
{
  return 0;
}

Real
ChargeSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_id)
    return -(_q / _eps0) * _sign * _phi[_j][_qp] * _test[_i][_qp];

  else
    return 0;
}
