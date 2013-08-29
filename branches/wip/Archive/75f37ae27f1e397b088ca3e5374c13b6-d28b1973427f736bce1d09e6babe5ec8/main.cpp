  1 #                                                                                                                                 
  2 # This file MUST be edited with the 'visudo' command as root.                                                                     
  3 #                                                                                                                                 
  4 # Please consider adding local content in /etc/sudoers.d/ instead of                                                              
  5 # directly modifying this file.                                                                                                   
  6 #                                                                                                                                 
  7 # See the man page for details on how to write a sudoers file.                                                                    
  8 #                                                                                                                                 
  9 Defaults    env_reset                                                                                                             
 10 Defaults    secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"                                             
 11 Defaults editor=/usr/bin/vim                                                                                                      
 12                                                                                                                                    
 13 # Host alias specification                                                                                                        
 14                                                                                                                                    
 15 # User alias specification                                                                                                        
 16                                                                                                                                    
 17 # Cmnd alias specification                                                                                                        
 18                                                                                                                                    
 19 # User privilege specification                                                                                                    
 20 root    ALL=(ALL:ALL) ALL                                                                                                          
 21 francis ALL=(ALL:ALL) ALL                                                                                                         
 22                                                                                                                                    
 23 # Members of the admin group may gain root privileges                                                                             
 24 %admin ALL=(ALL) ALL                                                                                                               
 25                                                                                                                                   
 26 # Allow members of group sudo to execute any command                                                                               
 27 %sudo   ALL=(ALL:ALL) ALL                                                                                                         
 28                                                                                                                                    
 29                                                                                                                                   
 30 root       ALL=(ALL) ALL                                                                                                           
 31 francis    ALL=(ALL) ALL                                                                                                          
 32 webserver  ALL=(sandbox) NOPASSWD: ALL                                                                                             
 33                                                                                                                                   
 34 # See sudoers(5) for more information on "#include" directives:                                                                    
 35                                                                                                                                   
 36                                                                                                                                    
 37 #includedir /etc/sudoers.d                                                                                                        
~                                                                                                                                     ~                                                                                                                                     