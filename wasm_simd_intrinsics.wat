(module
  (type (;0;) (func (param i32 i32 i32 i32)))
  (import "env" "__linear_memory" (memory (;0;) 0))
  (import "env" "__stack_pointer" (global (;0;) (mut i32)))
  (func $multiply_arrays (type 0) (param i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 v128 i32 i32 i32 i32 i32 v128 v128 v128 v128 v128 v128 i32 i32 i32 i32 v128 v128 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 4
    i32.const 144
    local.set 5
    local.get 4
    local.get 5
    i32.sub
    local.set 6
    local.get 6
    global.set 0
    local.get 6
    local.get 0
    i32.store offset=68
    local.get 6
    local.get 1
    i32.store offset=64
    local.get 6
    local.get 2
    i32.store offset=60
    local.get 6
    local.get 3
    i32.store offset=56
    i32.const 0
    local.set 7
    local.get 6
    local.get 7
    i32.store offset=52
    block  ;; label = @1
      loop  ;; label = @2
        local.get 6
        i32.load offset=52
        local.set 8
        local.get 6
        i32.load offset=56
        local.set 9
        local.get 8
        local.set 10
        local.get 9
        local.set 11
        local.get 10
        local.get 11
        i32.lt_s
        local.set 12
        i32.const 1
        local.set 13
        local.get 12
        local.get 13
        i32.and
        local.set 14
        local.get 14
        i32.eqz
        br_if 1 (;@1;)
        local.get 6
        i32.load offset=64
        local.set 15
        local.get 6
        i32.load offset=52
        local.set 16
        i32.const 2
        local.set 17
        local.get 16
        local.get 17
        i32.shl
        local.set 18
        local.get 15
        local.get 18
        i32.add
        local.set 19
        local.get 6
        local.get 19
        i32.store offset=76
        local.get 6
        i32.load offset=76
        local.set 20
        local.get 20
        v128.load align=1
        local.set 21
        local.get 6
        local.get 21
        v128.store offset=32
        local.get 6
        i32.load offset=60
        local.set 22
        local.get 6
        i32.load offset=52
        local.set 23
        local.get 23
        local.get 17
        i32.shl
        local.set 24
        local.get 22
        local.get 24
        i32.add
        local.set 25
        local.get 6
        local.get 25
        i32.store offset=72
        local.get 6
        i32.load offset=72
        local.set 26
        local.get 26
        v128.load align=1
        local.set 27
        local.get 6
        local.get 27
        v128.store offset=16
        local.get 6
        v128.load offset=32
        local.set 28
        local.get 6
        v128.load offset=16
        local.set 29
        local.get 6
        local.get 28
        v128.store offset=96
        local.get 6
        local.get 29
        v128.store offset=80
        local.get 6
        v128.load offset=96
        local.set 30
        local.get 6
        v128.load offset=80
        local.set 31
        local.get 30
        local.get 31
        i32x4.mul
        local.set 32
        local.get 6
        local.get 32
        v128.store
        local.get 6
        i32.load offset=68
        local.set 33
        local.get 6
        i32.load offset=52
        local.set 34
        local.get 34
        local.get 17
        i32.shl
        local.set 35
        local.get 33
        local.get 35
        i32.add
        local.set 36
        local.get 6
        v128.load
        local.set 37
        local.get 6
        local.get 36
        i32.store offset=140
        local.get 6
        local.get 37
        v128.store offset=112
        local.get 6
        v128.load offset=112
        local.set 38
        local.get 6
        i32.load offset=140
        local.set 39
        local.get 39
        local.get 38
        v128.store align=1
        local.get 6
        i32.load offset=52
        local.set 40
        i32.const 4
        local.set 41
        local.get 40
        local.get 41
        i32.add
        local.set 42
        local.get 6
        local.get 42
        i32.store offset=52
        br 0 (;@2;)
      end
    end
    i32.const 144
    local.set 43
    local.get 6
    local.get 43
    i32.add
    local.set 44
    local.get 44
    global.set 0
    return))
