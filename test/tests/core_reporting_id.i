[Mesh]
  [pin1]
    type = ConcentricCircleMeshGenerator
    num_sectors = 2
    radii = '0.4 0.5'
    rings = ' 1 1 1'
    has_outer_square = on
    pitch = 1.26
    preserve_volumes = yes
    smoothing_max_it = 3
  []

  [pin2]
    type = ConcentricCircleMeshGenerator
    num_sectors = 2
    radii = '0.3 0.4'
    rings = ' 1 1 1'
    has_outer_square = on
    pitch = 1.26
    preserve_volumes = yes
    smoothing_max_it = 3
  []

  [assembly1]
    type = CartesianIDPatternedMeshGenerator
    inputs = 'pin1 pin2,
              pin2 pin1'
    pattern = '1 0 1 0;
               3 3 1 0;
               0 1 0 1;'
    assign_type = 'cell'
    id_name = 'pin_id'
  []

#  [assembly2]
#    type = CartesianIDPatternedMeshGenerator
#    inputs = 'pin1 pin2;
#              pin2 pin1;'
#    pattern = '0 1 1 0;
#               1 0 0 1;
#               1 0 0 1;
#               0 1 1 0;'
#    assign_type = 'cell'
#    id_name = 'pin_id'
#  []
#  [core]
#    type = CartesianIDPatternedMeshGenerator
#    inputs = 'assembly1 assembly2'
#    pattern = '0 1;
#               1 0;'
#    assign_type = 'cell'
#    id_name = 'assembly_id'
#  []
#  [bdg]
#    type = BlockDeletionGenerator
#    input = core
#    block = 'pin_id'
#  []
[]
#
#[Variables]
#  [u][]
#[]
#
#[Kernels]
#  [u_diffusion]
#    type = Diffusion
#    variable = u
#  []
#  [u_force]
#    type = BodyForce
#    variable = u
#    block = 1
#    value = 10
#  []
#[]
#
#[BCs]
#  [u_left]
#    type = DirichletBC
#    boundary = left
#    value = 1
#    variable = u
#   []
#[]
#
#[Executioner]
#  type = Steady
#[]
#
#[Outputs]
#  exodus = true
#[]
#
#    
