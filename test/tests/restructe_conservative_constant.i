#use the full upwinding to solve the restruction
# use GenericConstantMaterial to setting velocity_porosity
# or use the GenericFunctionMaterial to setting velocity_porosity
# 2022 12 7 set BCs the OutflowBC and InflowBC contain the velocity_porosity

[Mesh]
  coord_type = RZ
  [block]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 100
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
    type = ConservativePorosity
    variable = porosity 
    upwinding_type = full
    coeff_vector = '1 0 0'
    velocity_porosity = velocity_porosity
  []
  [velocity_timeDe]
    type = MassLumpedTimeDerivative
    variable = porosity 
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
    type = MaterialRealAux
    property = velocity_porosity
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
#    type = GenericConstantMaterial
#    prop_names = 'velocity_porosity'
#    prop_values = '1e-4'
#  []
#  [velocity_porosity_material]
#    type = GenericFunctionMaterial
#    prop_names = 'velocity_porosity'
#    prop_values = velocity_porosity_functon
#  []
[]

[BCs]
  [right_flow]
    type = OutflowBC
    variable = porosity
    boundary = right
    outlet_conc = 1
  []
  [left_flow]
    type = InflowBC
    variable = porosity
    boundary = left
    inlet_conc = 1
  []
#  [right_dirichlet]
#    type = DirichletBC
#    variable = porosity
#    value = 1
#    boundary = right
#  []
[]

[Executioner]
  type = Transient
  
  solve_type = JFNK
  num_steps = 100
  dt = 60

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-5

  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
  petsc_options_value = '201                hypre    boomeramg      4'
[]  
    
[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  exodus = true
#  csv = true
  execute_on = 'TIMESTEP_END'
[]

