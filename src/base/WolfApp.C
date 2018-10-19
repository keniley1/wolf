#include "WolfApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "CraneApp.h"

template <>
InputParameters
validParams<WolfApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_output_syntax") = false;
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

registerKnownLabel("WolfApp");

WolfApp::WolfApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  CraneApp::registerObjects(_factory);
  WolfApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  CraneApp::associateSyntax(_syntax, _action_factory);
  WolfApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  CraneApp::registerExecFlags(_factory);
  WolfApp::registerExecFlags(_factory);
}

WolfApp::~WolfApp() {}

void
WolfApp::registerApps()
{
  registerApp(WolfApp);
}

void
WolfApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"WolfApp"});
}

void
WolfApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"WolfApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
WolfApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
WolfApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
WolfApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
WolfApp__registerApps()
{
  WolfApp::registerApps();
}

extern "C" void
WolfApp__registerObjects(Factory & factory)
{
  WolfApp::registerObjects(factory);
}

extern "C" void
WolfApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  WolfApp::associateSyntax(syntax, action_factory);
}

extern "C" void
WolfApp__registerExecFlags(Factory & factory)
{
  WolfApp::registerExecFlags(factory);
}
