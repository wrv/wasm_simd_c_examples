(module
  (type (;0;) (func (param i32 i32) (result i32)))
  (import "env" "__linear_memory" (memory (;0;) 0))
  (func $total_sum (type 0) (param i32 i32) (result i32)
    (local v128)
    local.get 1
    v128.load align=1
    local.get 0
    v128.load align=1
    i32x4.mul
    local.tee 2
    i32x4.extract_lane 0
    local.get 2
    i32x4.extract_lane 1
    i32.add
    local.get 2
    i32x4.extract_lane 2
    i32.add
    local.get 2
    i32x4.extract_lane 3
    i32.add))
