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
  [velocity_poroperty]
    type = VelocityPorosity
    variable = porosity 
  []
  [velocity_timeDe]
    type = TimeDerivative
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
  [velocity_poroperty_aux]
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
  [velocity_poroperty_material]
    type = VelocityPorosityMaterial
    temp = temp
  []
[]

[BCs]
[]

[Executioner]
  type = Transient
  
  solve_type = JFNK
  num_steps = 100
  dt = 60

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-5

#  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
#  petsc_options_value = '201                hypre    boomeramg      4'
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

