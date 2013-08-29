#0  0x00007ffff70fd7b8 in main_arena () from /lib/x86_64-linux-gnu/libc.so.6
#1  0x0000000000406670 in Jellyot::GlId<void (*)(unsigned int)>::~GlId (this=0x863620, 
    __in_chrg=<optimised out>) at /home/elliot/Programming/Jellyot/include/GlId.hpp:31
#2  0x00000000004070ca in Jellyot::Shader::~Shader (this=0x863620, __in_chrg=<optimised out>)
    at /home/elliot/Programming/Jellyot/include/Shader.hpp:8
#3  0x00000000004070e4 in std::_Destroy<Jellyot::Shader> (__pointer=0x863620)
    at /usr/include/c++/4.7/bits/stl_construct.h:95
#4  0x0000000000406d5e in std::_Destroy_aux<false>::__destroy<Jellyot::Shader*> (__first=0x863620, 
    __last=0x863640) at /usr/include/c++/4.7/bits/stl_construct.h:105
#5  0x0000000000406905 in std::_Destroy<Jellyot::Shader*> (__first=0x863620, __last=0x863640)
    at /usr/include/c++/4.7/bits/stl_construct.h:128
#6  0x00000000004063bb in std::_Destroy<Jellyot::Shader*, Jellyot::Shader> (__first=0x863620, __last=0x863640)
    at /usr/include/c++/4.7/bits/stl_construct.h:155
#7  0x0000000000405ebf in std::vector<Jellyot::Shader, std::allocator<Jellyot::Shader> >::~vector (
    this=0x7fffffffe5f0, __in_chrg=<optimised out>) at /usr/include/c++/4.7/bits/stl_vector.h:403
#8  0x00000000004059aa in init_draw_data () at /home/elliot/Programming/Jellyot/src/main.cpp:55
#9  0x0000000000405b90 in main () at /home/elliot/Programming/Jellyot/src/main.cpp:88
