# this is use the paper Modeling porosity migration in LWR and fast reactor MOX fuel using the finite element method

[Mesh]
  coord_type = RZ
  [block]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 200
    ny = 1
    xmax = 2.675e-3
  []
[]

[Variables]
  [porosity]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.15
  []
  [temp]
    initial_condition = 300
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
#temperature
  [heat_source]
    type = MOXHeatSource
    variable = temp
    function = volumetric_heat
    porosity_initial = 0.15
  []
  [heat_conduction]
    type = HeatConduction
    variable = temp
  []
  [heat_time]
    type = HeatConductionTimeDerivative
    variable = temp
  []
[]

[AuxVariables]
  [velocity_porosity]
    family = MONOMIAL
    order = FIRST
  []
[]

[AuxKernels]
  [velocity_porosity_aux]
    type = ADMaterialRealAux
    property = velocity_pore
    variable = velocity_porosity
  []
[]

[Functions]
  [volumetric_heat]
    type = ParsedFunction
    expression = (5/pi*2.675^2)*1e10*t
  []
  [surface_temperature]
    type = ParsedFunction
    expression = 650+0.065*t
  []
[]

[Materials]
  [velocity_porosity_material]
    type = VelocityPorosityMaterial
    temp = temp
  []
  [mox_thermal]
    type = MOXThermal
    temperature = temp
    americium = 0
    neptunium = 0
    dev_O_M = 2
    porosity = porosity
    density = 1.0662e4
    specific_heat = 0.4444
    outputs = all
  []
[]

[BCs]
  [surface_temp]
    type = FunctionDirichletBC
    function = surface_temperature
    boundary = right
    variable = temp
  []
[]

[Executioner]
  type = Transient
  
  solve_type = PJFNK
  end_time = 1e4
  dt = 10

  nl_rel_tol = 1e-4
  nl_abs_tol = 1e-4

  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
  petsc_options_value = '201                hypre    boomeramg      4'
[]  

[Outputs]
  exodus = true
#  csv = true
  execute_on = 'TIMESTEP_END'
[]

