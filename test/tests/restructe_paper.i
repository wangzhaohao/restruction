# this is use the paper Modeling porosity migration in LWR and fast reactor MOX fuel using the finite element method

[Mesh]
  coord_type = RZ
  [block]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 500
    ny = 1
    xmax = 5e-3
    ymax = 1e-3
  []
[]

[Variables]
  [porosity]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.05
  []
[]

[Kernels]
  [velocity_porosity]
    type = ADVelocityPore
    variable = porosity
  []
  [velocity_timeDe]
    type = ADTimeDerivative
    variable = porosity 
  []
  [porosity_diff]
    type = ADMatDiffusion
    variable = porosity
    diffusivity = '1e-12'
  []
[]

[AuxVariables]
  [temp]
    family = LAGRANGE 
    order = FIRST
  []
  [velocity_porosity]
    family = MONOMIAL
    order = FIRST
  []
[]

[AuxKernels] 
  [temp_function_aux]
    type = FunctionAux
    function = temp_function
    variable = temp
  []
  [velocity_porosity_aux]
    type = ADMaterialRealAux
    property = velocity_pore
    variable = velocity_porosity
  []
[]

[Functions]
  [temp_function]
    type = ParsedFunction
    value = -6190.60166*x-8.05175e7*x*x-8.10883e9*x*x*x+1.48088e12*x*x*x*x+2910.26613
  []
[]

[Materials]
  [velocity_porosity_material]
    type = VelocityPorosityMaterial
    temp = temp
  []
#  [velocity_porosity_material]
#    type = GenericFunctionMaterial
#    prop_names = 'velocity_porosity'
#    prop_values = velocity_porosity_functon
#  []
[]


[Executioner]
  type = Transient
  
  solve_type = JFNK
  num_steps = 10
  dt = 60

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-5

  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
  petsc_options_value = '201                hypre    boomeramg      4'
[]  

[Outputs]
  exodus = true
#  csv = true
  execute_on = 'TIMESTEP_END'
[]

