[Mesh]
#  [block]
#    type = GeneratedMeshGenerator
#    dim = 2
#   []
  [left_rectangle]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 40
    ny = 10
    xmax = 1
    ymin = 0
    ymax = 0.5
    boundary_name_prefix = moving_block
  []
[]
