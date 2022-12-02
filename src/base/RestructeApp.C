#include "RestructeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
RestructeApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

RestructeApp::RestructeApp(InputParameters parameters) : MooseApp(parameters)
{
  RestructeApp::registerAll(_factory, _action_factory, _syntax);
}

RestructeApp::~RestructeApp() {}

void
RestructeApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"RestructeApp"});
  Registry::registerActionsTo(af, {"RestructeApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
RestructeApp::registerApps()
{
  registerApp(RestructeApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
RestructeApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  RestructeApp::registerAll(f, af, s);
}
extern "C" void
RestructeApp__registerApps()
{
  RestructeApp::registerApps();
}
