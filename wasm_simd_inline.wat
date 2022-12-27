(module
  (type (;0;) (func))
  (type (;1;) (func (param i32 i32) (result i32)))
  (func $__wasm_call_ctors (type 0))
  (func $total_sum (type 1) (param i32 i32) (result i32)
    i32.const 0
    local.get 0
    v128.load
    local.get 1
    v128.load
    i32x4.mul
    v128.store
    i32.const 0
    v128.load
    i32x4.extract_lane 0
    i32.const 0
    v128.load
    i32x4.extract_lane 1
    i32.add
    i32.const 0
    v128.load
    i32x4.extract_lane 2
    i32.add
    i32.const 0
    v128.load
    i32x4.extract_lane 3
    i32.add
    local.set 1
    local.get 1)
  (memory (;0;) 16)
  (global $__stack_pointer (mut i32) (i32.const 1048576))
  (global (;1;) i32 (i32.const 1048576))
  (global (;2;) i32 (i32.const 1048576))
  (global (;3;) i32 (i32.const 1048576))
  (global (;4;) i32 (i32.const 1048576))
  (global (;5;) i32 (i32.const 0))
  (global (;6;) i32 (i32.const 1))
  (export "memory" (memory 0))
  (export "__wasm_call_ctors" (func $__wasm_call_ctors))
  (export "total_sum" (func $total_sum))
  (export "__dso_handle" (global 1))
  (export "__data_end" (global 2))
  (export "__global_base" (global 3))
  (export "__heap_base" (global 4))
  (export "__memory_base" (global 5))
  (export "__table_base" (global 6)))
