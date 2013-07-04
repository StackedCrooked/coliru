#0  0x00007fffffffe7b0 in ?? ()
#1  0x000000000040320b in int Centurion::AudioStream::CallbackDispatcher<int (*)(void const*, void*, unsigned long, PaStreamCallbackTimeInfo const*, unsigned long)>(void const*, void*, unsigned long, PaStreamCallbackTimeInfo const*, unsigned long, void*) ()
#2  0x00007ffff7bb4053 in ?? () from /usr/lib/x86_64-linux-gnu/libportaudio.so.2
#3  0x00007ffff7bb6045 in ?? () from /usr/lib/x86_64-linux-gnu/libportaudio.so.2
#4  0x00007ffff7bbcf68 in ?? () from /usr/lib/x86_64-linux-gnu/libportaudio.so.2
#5  0x00007ffff6676e9a in start_thread (arg=0x7ffff32fa700) at pthread_create.c:308
#6  0x00007ffff70caccd in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:112
#7  0x0000000000000000 in ?? ()