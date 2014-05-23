function_start: lock_and_wait
                if(init_done)
                  jump to actual_function_start

                init_local_var
                replace code at function_start with "jump to actual_function_start"
                unlock
actual_function_start:
                normal stuff