//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "RestructeTestApp.h"
#include "RestructeApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
RestructeTestApp::validParams()
{
  InputParameters params = RestructeApp::validParams();
  return params;
}

RestructeTestApp::RestructeTestApp(InputParameters parameters) : MooseApp(parameters)
{
  RestructeTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

RestructeTestApp::~RestructeTestApp() {}

void
RestructeTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  RestructeApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"RestructeTestApp"});
    Registry::registerActionsTo(af, {"RestructeTestApp"});
  }
}

void
RestructeTestApp::registerApps()
{
  registerApp(RestructeApp);
  registerApp(RestructeTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
RestructeTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  RestructeTestApp::registerAll(f, af, s);
}
extern "C" void
RestructeTestApp__registerApps()
{
  RestructeTestApp::registerApps();
}
