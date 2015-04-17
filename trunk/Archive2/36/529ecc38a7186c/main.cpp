476         // memory
477         if(diagnosticsResourceMonitoringMask & ResourceDiagnosticsMemory){                                                          
478             s64 usage=GetMemoryUsageInBytes();                                                                                      
479             out << '\t' << MemoryUsage{usage};          
480             if(usage>peakMemoryUsageInBytes){           
481                 peakMemoryUsageInBytes=usage;            
482             }
483         }
484         // process name
485         out << '\t' << processName;                                                                                                 
486         // event name
487         out << '\t' << event.name;                                                                                                  
488         // percentage used physical memory                                                                                          
489         if(diagnosticsResourceMonitoringMask & ResourceDiagnosticsPercentageUsedPhysicalMemory){                                    
490             out << '\t' << GetPercentagePhysicalMemoryInUse();                                                                      
491         }
492         // free virtual memory
493         if(diagnosticsResourceMonitoringMask & ResourceDiagnosticsFreeVirtualMemory){                                               
494             out << '\t' << FreeVirtualMemory{GetFreeVirtualMemoryInBytes()};                                                        
495         }                                                                                                                           
496         // inodes                                                                                                                   
497         if(diagnosticsResourceMonitoringMask & ResourceDiagnosticsInodes){                                                          
498             out << '\t' << InodeCount{GetFreeInodeCount(inodeDevicePath)};                                                          
499         }
500         // disk space
501         if(diagnosticsResourceMonitoringMask & ResourceDiagnosticsDiskSpace){                                                       
502             out << '\t' << DiskSpace{GetFreeDiskSpaceInBytes(diskFreeSpacePath)};                                                   
503         }
