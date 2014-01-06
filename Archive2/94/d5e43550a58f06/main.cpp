Process:         Qt Creator [21736]
Path:            /Users/USER/*/Qt Creator.app/Contents/MacOS/Qt Creator
Identifier:      org.qt-project.qtcreator
Version:         3.0.0 (3.0.0)
Code Type:       X86-64 (Native)
Parent Process:  launchd [247]
Responsible:     Qt Creator [21736]
User ID:         501

Date/Time:       2014-01-02 08:59:16.074 +0100
OS Version:      Mac OS X 10.9.1 (13B42)
Report Version:  11
Anonymous UUID:  E275CDCA-E035-9974-266F-F62B2AE99F74


Crashed Thread:  24  Thread (pooled)

Exception Type:  EXC_BAD_ACCESS (SIGSEGV)
Exception Codes: KERN_INVALID_ADDRESS at 0x0000000000000000

VM Regions Near 0:
--> 
    __TEXT                 0000000100000000-0000000100014000 [   80K] r-x/rwx SM=COW  /Users/USER/*/Qt Creator.app/Contents/MacOS/Qt Creator

Thread 0:: Dispatch queue: com.apple.main-thread
0   libsystem_kernel.dylib            0x00007fff92fd9a1a mach_msg_trap + 10
1   libsystem_kernel.dylib        	0x00007fff92fd8d18 mach_msg + 64
2   com.apple.CoreFoundation      	0x00007fff919ee315 __CFRunLoopServiceMachPort + 181
3   com.apple.CoreFoundation      	0x00007fff919ed939 __CFRunLoopRun + 1161
4   com.apple.CoreFoundation      	0x00007fff919ed275 CFRunLoopRunSpecific + 309
5   com.apple.HIToolbox           	0x00007fff9351af0d RunCurrentEventLoopInMode + 226
6   com.apple.HIToolbox           	0x00007fff9351acb7 ReceiveNextEventCommon + 479
7   com.apple.HIToolbox           	0x00007fff9351aabc _BlockUntilNextEventMatchingListInModeWithFilter + 65
8   com.apple.AppKit              	0x00007fff8ec1328e _DPSNextEvent + 1434
9   com.apple.AppKit              	0x00007fff8ec128db -[NSApplication nextEventMatchingMask:untilDate:inMode:dequeue:] + 122
10  com.apple.AppKit              	0x00007fff8ec069cc -[NSApplication run] + 553
11  libqcocoa.dylib               	0x0000000102c192a7 0x102c00000 + 103079
12  QtCore                        	0x0000000100dff05d QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) + 397
13  QtCore                        	0x0000000100e02162 QCoreApplication::exec() + 354
14  org.qt-project.qtcreator      	0x000000010000d3cc main + 22732
15  org.qt-project.qtcreator      	0x0000000100004cf4 start + 52

Thread 1:: Dispatch queue: com.apple.libdispatch-manager
0   libsystem_kernel.dylib        	0x00007fff92fde662 kevent64 + 10
1   libdispatch.dylib             	0x00007fff8d26743d _dispatch_mgr_invoke + 239
2   libdispatch.dylib             	0x00007fff8d267152 _dispatch_mgr_thread + 52

Thread 2:: com.apple.CFSocket.private
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   com.apple.CoreFoundation      	0x00007fff91a39d43 __CFSocketManager + 867
2   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
3   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
4   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 3:: QProcessManager
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   QtCore                        	0x0000000100da3478 0x100bf0000 + 1782904
2   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
3   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
4   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
5   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 4:: QThread
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   QtCore                        	0x0000000100e50213 qt_safe_select(int, fd_set*, fd_set*, fd_set*, timespec const*) + 547
2   QtCore                        	0x0000000100e50f58 QEventDispatcherUNIXPrivate::doSelect(QFlags<QEventLoop::ProcessEventsFlag>, timespec*) + 680
3   QtCore                        	0x0000000100e51dca QEventDispatcherUNIX::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) + 250
4   QtCore                        	0x0000000100dff05d QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) + 397
5   QtCore                        	0x0000000100c160e3 QThread::exec() + 115
6   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
7   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
8   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
9   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 5:: QThread
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   QtCore                        	0x0000000100e50213 qt_safe_select(int, fd_set*, fd_set*, fd_set*, timespec const*) + 547
2   QtCore                        	0x0000000100e50f58 QEventDispatcherUNIXPrivate::doSelect(QFlags<QEventLoop::ProcessEventsFlag>, timespec*) + 680
3   QtCore                        	0x0000000100e51dca QEventDispatcherUNIX::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) + 250
4   QtCore                        	0x0000000100dff05d QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) + 397
5   QtCore                        	0x0000000100c160e3 QThread::exec() + 115
6   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
7   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
8   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
9   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 6:
0   libsystem_kernel.dylib        	0x00007fff92fd9a1a mach_msg_trap + 10
1   libsystem_kernel.dylib        	0x00007fff92fd8d18 mach_msg + 64
2   com.apple.CoreFoundation      	0x00007fff919ee315 __CFRunLoopServiceMachPort + 181
3   com.apple.CoreFoundation      	0x00007fff919ed939 __CFRunLoopRun + 1161
4   com.apple.CoreFoundation      	0x00007fff919ed275 CFRunLoopRunSpecific + 309
5   com.apple.AppKit              	0x00007fff8edb31ce _NSEventThread + 144
6   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
7   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
8   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 7:: QQuickPixmapReader
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   QtCore                        	0x0000000100e50213 qt_safe_select(int, fd_set*, fd_set*, fd_set*, timespec const*) + 547
2   QtCore                        	0x0000000100e50f58 QEventDispatcherUNIXPrivate::doSelect(QFlags<QEventLoop::ProcessEventsFlag>, timespec*) + 680
3   QtCore                        	0x0000000100e51dca QEventDispatcherUNIX::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) + 250
4   QtCore                        	0x0000000100dff05d QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) + 397
5   QtCore                        	0x0000000100c160e3 QThread::exec() + 115
6   QtQuick                       	0x000000010c9f97fd 0x10c9c1000 + 231421
7   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
8   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
9   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
10  libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 8:: Qt bearer thread
0   libsystem_kernel.dylib        	0x00007fff92fdd9aa __select + 10
1   QtCore                        	0x0000000100e50213 qt_safe_select(int, fd_set*, fd_set*, fd_set*, timespec const*) + 547
2   QtCore                        	0x0000000100e50f58 QEventDispatcherUNIXPrivate::doSelect(QFlags<QEventLoop::ProcessEventsFlag>, timespec*) + 680
3   QtCore                        	0x0000000100e51dca QEventDispatcherUNIX::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) + 250
4   QtCore                        	0x0000000100dff05d QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) + 397
5   QtCore                        	0x0000000100c160e3 QThread::exec() + 115
6   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
7   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
8   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
9   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 9:: JavaScriptCore::BlockFree
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110044c95 0x10f109000 + 15973525
3   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
4   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
5   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
6   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 10:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 11:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 12:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 13:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 14:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 15:: JavaScriptCore::Marking
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtWebKit                      	0x0000000110045be7 0x10f109000 + 15977447
3   QtWebKit                      	0x0000000110045c78 0x10f109000 + 15977592
4   QtWebKit                      	0x00000001102850ff 0x10f109000 + 18333951
5   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
6   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
7   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 16:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 17:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 18:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 19:: Thread (pooled)
0   libsystem_kernel.dylib        	0x00007fff92fdd716 __psynch_cvwait + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f7c3b _pthread_cond_wait + 727
2   QtCore                        	0x0000000100c1b539 0x100bf0000 + 177465
3   QtCore                        	0x0000000100c1b3ca QWaitCondition::wait(QMutex*, unsigned long) + 170
4   QtCore                        	0x0000000100c167d0 0x100bf0000 + 157648
5   QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
6   libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
7   libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
8   libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 20:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 21:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 22:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 23:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 24 Crashed:: Thread (pooled)
0   libCPlusPlus.1.0.0.dylib      	0x000000010d2a16ba CPlusPlus::ClassOrNamespace::lookupType_helper(CPlusPlus::Name const*, QSet<CPlusPlus::ClassOrNamespace*>*, bool, CPlusPlus::ClassOrNamespace*) + 42
1   libCPlusPlus.1.0.0.dylib      	0x000000010d29dc9b CPlusPlus::ClassOrNamespace::lookupType(CPlusPlus::Name const*, CPlusPlus::Block*) + 187
2   libCPlusPlus.1.0.0.dylib      	0x000000010d29e3b4 CPlusPlus::LookupContext::lookup(CPlusPlus::Name const*, CPlusPlus::Scope*) const + 1188
3   libCppTools.dylib             	0x000000010d128e24 CppTools::CheckSymbols::checkName(CPlusPlus::NameAST*, CPlusPlus::Scope*) + 292
4   libCppTools.dylib             	0x000000010d1294ab CppTools::CheckSymbols::visit(CPlusPlus::SimpleNameAST*) + 11
5   libCPlusPlus.1.0.0.dylib      	0x000000010d21a88c CPlusPlus::SimpleNameAST::accept0(CPlusPlus::ASTVisitor*) + 28
6   libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
7   libCPlusPlus.1.0.0.dylib      	0x000000010d21956e CPlusPlus::BaseSpecifierAST::accept0(CPlusPlus::ASTVisitor*) + 46
8   libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
9   libCPlusPlus.1.0.0.dylib      	0x000000010d21987a CPlusPlus::ClassSpecifierAST::accept0(CPlusPlus::ASTVisitor*) + 138
10  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
11  libCppTools.dylib             	0x000000010d126dec CppTools::CheckSymbols::visit(CPlusPlus::SimpleDeclarationAST*) + 1084
12  libCPlusPlus.1.0.0.dylib      	0x000000010d21909f CPlusPlus::SimpleDeclarationAST::accept0(CPlusPlus::ASTVisitor*) + 31
13  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
14  libCPlusPlus.1.0.0.dylib      	0x000000010d219b91 CPlusPlus::DeclarationStatementAST::accept0(CPlusPlus::ASTVisitor*) + 49
15  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
16  libCPlusPlus.1.0.0.dylib      	0x000000010d21997a CPlusPlus::CompoundStatementAST::accept0(CPlusPlus::ASTVisitor*) + 74
17  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
18  libCppTools.dylib             	0x000000010d12a0c5 CppTools::CheckSymbols::visit(CPlusPlus::FunctionDefinitionAST*) + 581
19  libCPlusPlus.1.0.0.dylib      	0x000000010d21a1df CPlusPlus::FunctionDefinitionAST::accept0(CPlusPlus::ASTVisitor*) + 31
20  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
21  libCPlusPlus.1.0.0.dylib      	0x000000010d21a5aa CPlusPlus::LinkageBodyAST::accept0(CPlusPlus::ASTVisitor*) + 74
22  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
23  libCPlusPlus.1.0.0.dylib      	0x000000010d21a9cd CPlusPlus::NamespaceAST::accept0(CPlusPlus::ASTVisitor*) + 93
24  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
25  libCPlusPlus.1.0.0.dylib      	0x000000010d21b71a CPlusPlus::TranslationUnitAST::accept0(CPlusPlus::ASTVisitor*) + 74
26  libCPlusPlus.1.0.0.dylib      	0x000000010d207f1c CPlusPlus::AST::accept(CPlusPlus::ASTVisitor*) + 44
27  libCppTools.dylib             	0x000000010d1258ca CppTools::CheckSymbols::run() + 874
28  QtCore                        	0x0000000100c16696 0x100bf0000 + 157334
29  QtCore                        	0x0000000100c19e60 0x100bf0000 + 171616
30  libsystem_pthread.dylib       	0x00007fff8b8f5899 _pthread_body + 138
31  libsystem_pthread.dylib       	0x00007fff8b8f572a _pthread_start + 137
32  libsystem_pthread.dylib       	0x00007fff8b8f9fc9 thread_start + 13

Thread 25:
0   libsystem_kernel.dylib        	0x00007fff92fdde6a __workq_kernreturn + 10
1   libsystem_pthread.dylib       	0x00007fff8b8f6f08 _pthread_wqthread + 330
2   libsystem_pthread.dylib       	0x00007fff8b8f9fb9 start_wqthread + 13

Thread 24 crashed with X86 Thread State (64-bit):
  rax: 0x0000000100f17ab0  rbx: 0x00000001138bf730  rcx: 0x0000000000000001  rdx: 0x00000001138bf730
  rdi: 0x00006000011f8100  rsi: 0x0000000000000000  rbp: 0x00000001138bf720  rsp: 0x00000001138bf620
   r8: 0x0000600001bf3f00   r9: 0x0000600001bf3f00  r10: 0x000000000000001f  r11: 0x0000608002be9100
  r12: 0x0000000000000000  r13: 0x0000600007027f00  r14: 0x00006000011f8100  r15: 0x0000600001bf3f50
  rip: 0x000000010d2a16ba  rfl: 0x0000000000010202  cr2: 0x0000000000000000
  
Logical CPU:     0
Error Code:      0x00000004
Trap Number:     14


Binary Images:
       0x100000000 -        0x100013ff7 +org.qt-project.qtcreator (3.0.0 - 3.0.0) <FB006CD2-BFAA-309D-B05D-460A3FBB3F0F> /Users/USER/*/Qt Creator.app/Contents/MacOS/Qt Creator
       0x100020000 -        0x100053fff +libExtensionSystem.1.0.0.dylib (1) <C5F1163B-1C91-3878-9703-48D345801B67> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libExtensionSystem.1.0.0.dylib
       0x10006a000 -        0x10006ffff +libAggregation.1.0.0.dylib (1) <9EDD9726-3AA1-383D-8FD9-E32710A4853A> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libAggregation.1.0.0.dylib
       0x100074000 -        0x100156ff7 +libUtils.1.0.0.dylib (1) <F20C10DA-F935-3FB6-A6D0-2C865376FDA6> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libUtils.1.0.0.dylib
       0x1001d3000 -        0x100686ff7 +QtWidgets (5.2) <20511AD2-CF71-368C-9F84-6BA80814FF03> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
       0x1007ac000 -        0x100b2bff7 +QtGui (5.2) <1D90F282-6151-3035-8878-C6AFB7E54E1D> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
       0x100bf0000 -        0x1010e7fff +QtCore (5.2) <1CDDBA06-18A4-3012-93A6-C1E50440D003> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore
       0x10116b000 -        0x10126ffff +QtNetwork (5.2) <F3C37525-003D-3C90-8859-9389CAC852BD> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork
       0x1012a3000 -        0x1012a6ff7 +QtConcurrent (5.2) <FFCDB9F9-AE26-3862-991C-7F5CD60879ED> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtConcurrent.framework/Versions/5/QtConcurrent
       0x1012aa000 -        0x1012aefff  com.apple.agl (3.2.3 - AGL-3.2.3) <1B85306F-D2BF-3FE3-9915-165237B491EB> /System/Library/Frameworks/AGL.framework/Versions/A/AGL
       0x1012b5000 -        0x101439fff +QtScript (5.2) <7D4C2643-EEE0-345C-90A2-FF8663FAA019> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtScript.framework/Versions/5/QtScript
       0x10167a000 -        0x10167afeb +cl_kernels (???) <975897F6-5104-47D0-8040-BA2BC6FC3EFB> cl_kernels
       0x102883000 -        0x1028acfff +QtPrintSupport (5.2) <E54AEC0E-67DB-3D0A-B5CA-8B8AFBA0AF61> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
       0x1028cb000 -        0x1028ceff7 +libqtquick2plugin.dylib (0) <DB44F28A-F14C-3EC7-B80C-3459BB154DE0> /Users/USER/*/Qt Creator.app/Contents/Imports/qtquick2/QtQuick.2/libqtquick2plugin.dylib
       0x102c00000 -        0x102c90ff7 +libqcocoa.dylib (0) <847A2654-D22C-3B75-83F0-F0B420B72087> /Users/USER/*/Qt Creator.app/Contents/PlugIns/platforms/libqcocoa.dylib
       0x102cc2000 -        0x102cecfff +QtSql (5.2) <932FFA8A-0BFD-3D77-B3A5-77B53DE38774> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtSql.framework/Versions/5/QtSql
       0x102f00000 -        0x102f8cfff +QtHelp (5.2) <8E81879D-FE9D-3A79-BE48-7082AF7CF643> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtHelp.framework/Versions/5/QtHelp
       0x105675000 -        0x105756ff7 +QtCLucene (5.2) <8C11C869-44DF-3DAF-8C12-63D340F55A98> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtCLucene.framework/Versions/5/QtCLucene
       0x107d86000 -        0x107f2bfff +libCore.dylib (0) <4D7BDFE1-DF67-3B9B-A9B1-5DE285504FD7> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCore.dylib
       0x109039000 -        0x109113ff7 +libqsqlite.dylib (0) <3BCFE507-C6DA-3062-9A84-D7538530587F> /Users/USER/*/Qt Creator.app/Contents/PlugIns/sqldrivers/libqsqlite.dylib
       0x10b462000 -        0x10b466ffd  libFontRegistryUI.dylib (127) <57DE4E73-B65B-3712-9815-81018E72501A> /System/Library/Frameworks/ApplicationServices.framework/Frameworks/ATS.framework/Resources/libFontRegistryUI.dylib
       0x10b46d000 -        0x10b473ff7 +libqgif.dylib (0) <8AD01367-19DE-3669-ABC0-4FE98DD3B7B9> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqgif.dylib
       0x10b477000 -        0x10b47cff7 +libqico.dylib (0) <2AD7F5C9-FA28-3A97-95A2-8C5599D0A053> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqico.dylib
       0x10b480000 -        0x10b4bbff7 +libqjpeg.dylib (0) <F9115138-23FD-32C5-A915-7F801305404C> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqjpeg.dylib
       0x10b4c1000 -        0x10b4c5fff +libqsvg.dylib (0) <DD37F18F-A584-310B-A77B-5C7A466C48BF> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqsvg.dylib
       0x10b4ca000 -        0x10b4ceff7 +libqtga.dylib (0) <A5A4C61B-F8DD-37A5-9CD4-9E29D18481CB> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqtga.dylib
       0x10b4d2000 -        0x10b4d6ff7 +libqwbmp.dylib (0) <93727823-54AE-35A9-841C-8AE6455B68D9> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqwbmp.dylib
       0x10b4da000 -        0x10b4e4fff +libLanguageUtils.1.0.0.dylib (1) <78D30C11-F9DC-3549-A1BE-3C8ACF4113EC> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libLanguageUtils.1.0.0.dylib
       0x10b4eb000 -        0x10b4f6fff +libTaskList.dylib (0) <C93188C9-6D1F-33CB-8E4C-88F5E247C519> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libTaskList.dylib
       0x10b600000 -        0x10b64eff7 +libqmng.dylib (0) <4567DBE1-30DE-34BB-B1A7-33C5B51A9DBC> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqmng.dylib
       0x10b656000 -        0x10b68dff7 +QtSvg (5.2) <03531661-9BA9-3B37-B1D5-EE422B1EB00B> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtSvg.framework/Versions/5/QtSvg
       0x10b6a2000 -        0x10b6daff7 +QtXml (5.2) <95437A17-0F0C-393D-AE9C-572A5FD40A01> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtXml.framework/Versions/5/QtXml
       0x10b6ea000 -        0x10b746fff +libqtiff.dylib (0) <E9DFCFA2-002F-35F7-80C3-1193E19B7620> /Users/USER/*/Qt Creator.app/Contents/PlugIns/imageformats/libqtiff.dylib
       0x10b7d1000 -        0x10b7ecff7 +libAnalyzerBase.dylib (0) <CFD38193-7939-3176-9DD3-5EB50FEF604E> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libAnalyzerBase.dylib
       0x10c000000 -        0x10c042fff +libFind.dylib (0) <3384394B-FD62-3A4C-9B2C-0B0C9525BE37> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libFind.dylib
       0x10c06b000 -        0x10c0a3fff +libLocator.dylib (0) <420F88C6-405D-3CCF-B4FC-416AF49D6DF8> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libLocator.dylib
       0x10c0c5000 -        0x10c232fff +libTextEditor.dylib (0) <99554E23-577A-3F97-A594-0A364C49F1F2> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libTextEditor.dylib
       0x10c2de000 -        0x10c5a2ff7 +libProjectExplorer.dylib (0) <0002A0E0-31CA-3E3E-B9FA-3EF76A0FED3B> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libProjectExplorer.dylib
       0x10c6b5000 -        0x10c930ff7 +libQtcSsh.1.0.0.dylib (1) <6EC1E39E-2A27-34A1-91DB-ECCC4AD35AEF> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libQtcSsh.1.0.0.dylib
       0x10c9c1000 -        0x10cc60fff +QtQuick (5.2) <31B45427-CCBA-38A5-BC6B-CA6F003E117D> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
       0x10ccf7000 -        0x10d01cff7 +QtQml (5.2) <C5F7F865-1EA5-3F10-A60B-EAB8A87161CB> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtQml.framework/Versions/5/QtQml
       0x10d09a000 -        0x10d196fff +libCppTools.dylib (0) <CF63A3C9-7F46-3491-8306-0F97F4AE42BE> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCppTools.dylib
       0x10d204000 -        0x10d334fff +libCPlusPlus.1.0.0.dylib (1) <48D859F1-9D71-3E5D-BF7D-11215FB4FCE2> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libCPlusPlus.1.0.0.dylib
       0x10d40b000 -        0x10d502fff +libQtSupport.dylib (0) <A1787481-F14F-37C5-9324-4870C4CD98A8> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQtSupport.dylib
       0x10d54e000 -        0x10d671fff +libQmlJS.1.0.0.dylib (1) <8D83EFB0-0183-3AFC-91D0-BB3232EB1CAC> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libQmlJS.1.0.0.dylib
       0x10d6d6000 -        0x10d751fff +libQmlJSTools.dylib (0) <5A75A55A-13A7-3952-93C3-A84E3EE36EB8> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmlJSTools.dylib
       0x10d79e000 -        0x10d7e5ff7 +libDesigner.dylib (0) <D37836CA-6906-3EB5-B756-5B26DBA4E9FF> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libDesigner.dylib
       0x10d817000 -        0x10d9f9fff +QtDesignerComponents (5.2) <3DD6DECD-8ADA-3B1B-89BB-D3DF3540BE64> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtDesignerComponents.framework/Versions/5/QtDesignerComponents
       0x10da67000 -        0x10de86ff7 +QtDesigner (5.2) <21917268-0017-3891-93F1-AE5CB3DEC3A0> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtDesigner.framework/Versions/5/QtDesigner
       0x10df50000 -        0x10e07ffff +libQmakeProjectManager.dylib (0) <6622DF20-FFC8-37EF-98ED-45C87F1C24D4> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmakeProjectManager.dylib
       0x10e109000 -        0x10e1cefff +libCppEditor.dylib (0) <F6AD303C-7C04-3AEB-9129-E5296D5D4B5D> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCppEditor.dylib
       0x10e23d000 -        0x10e5b0fff +libDebugger.dylib (0) <3E170895-6DDA-3732-8E37-75785AEB9666> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libDebugger.dylib
       0x10e6a2000 -        0x10e6d1fff +libQmlDebug.1.0.0.dylib (1) <73394896-2BB8-3576-A81A-60C0B25FA60C> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libQmlDebug.1.0.0.dylib
       0x10e6e9000 -        0x10e7ecfff +libAndroid.dylib (0) <89515172-1EC2-316E-8A12-C0F28F00AEFC> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libAndroid.dylib
       0x10e84b000 -        0x10e8c5ff7 +libVcsBase.dylib (0) <1A1796B1-8773-3DC5-A2A5-1EC7EA9733F5> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libVcsBase.dylib
       0x10e90f000 -        0x10e944ff7 +libBazaar.dylib (0) <EC5B02FC-9F75-30B8-983D-E3305218C534> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libBazaar.dylib
       0x10e965000 -        0x10e982fff +libBinEditor.dylib (0) <9D2FD6F1-6E99-3051-902A-D3DE9C1DE0C4> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libBinEditor.dylib
       0x10e993000 -        0x10e9abfff +libBookmarks.dylib (0) <9057D993-7677-3F8A-B5A6-4D564C264F37> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libBookmarks.dylib
       0x10e9be000 -        0x10ea17fff +libCMakeProjectManager.dylib (0) <6ED01C0E-12A2-3F4B-BF0B-4F2145BBE39D> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCMakeProjectManager.dylib
       0x10ea54000 -        0x10ea83ff7 +libCVS.dylib (0) <18333713-364B-34B6-B98E-6A6D32216261> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCVS.dylib
       0x10ea9e000 -        0x10eac0ff7 +libClassView.dylib (0) <66ACFA6F-9418-3744-8275-C88F1D851671> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libClassView.dylib
       0x10ead2000 -        0x10eb05fff +libCodePaster.dylib (0) <7DD0CF4A-4F1A-381E-AAE1-2964D948F27D> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libCodePaster.dylib
       0x10eb1e000 -        0x10eb52ff7 +libDiffEditor.dylib (0) <152C3A7B-BEDA-3ACF-A3BE-C5A5FD873313> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libDiffEditor.dylib
       0x10eb6f000 -        0x10ebf0fff +libFakeVim.dylib (0) <F36D7BD9-EAC7-31FF-B11F-9F60EE6B8BE9> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libFakeVim.dylib
       0x10ec1a000 -        0x10ec3aff7 +libGLSLEditor.dylib (0) <CBFE6542-858B-3989-9EB8-85CCD0A22450> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libGLSLEditor.dylib
       0x10ec56000 -        0x10ec8efff +libGLSL.1.0.0.dylib (1) <54A9F9C7-658F-3BA7-92D0-B5C6BB6E3BA5> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libGLSL.1.0.0.dylib
       0x10ecab000 -        0x10ece4fff +libGenericProjectManager.dylib (0) <652459A1-5C11-3504-8DB1-3C82BDBEE960> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libGenericProjectManager.dylib
       0x10ed11000 -        0x10ee14fff +libGit.dylib (0) <F00AF81E-21E9-37CE-ADB1-19F9C6485450> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libGit.dylib
       0x10ee74000 -        0x10eee7ff7 +libHelp.dylib (0) <A6537076-846A-3B29-9634-453D351A8B73> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libHelp.dylib
       0x10ef21000 -        0x10ef4fff7 +QtWebKitWidgets (5.2) <F34E2E58-F69D-3638-8B2D-24301B8B367C> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtWebKitWidgets.framework/Versions/5/QtWebKitWidgets
       0x10ef71000 -        0x10ef85fff +QtMultimediaWidgets (5.2) <6399AA32-18CE-3977-B5EF-A2FD1A79342A> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtMultimediaWidgets.framework/Versions/5/QtMultimediaWidgets
       0x10ef93000 -        0x10f01fff7 +QtMultimedia (5.2) <91F5C349-BD6D-3E9C-B2A3-094914BF1A3E> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia
       0x10f05c000 -        0x10f093fff +QtPositioning (5.2) <ED459C06-F9A3-3559-8C6E-26443B1B6C85> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtPositioning.framework/Versions/5/QtPositioning
       0x10f0a1000 -        0x10f0e8fff +QtOpenGL (5.2) <5CCDC659-2305-35DA-95F6-997237B57E28> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtOpenGL.framework/Versions/5/QtOpenGL
       0x10f109000 -        0x1108c7fff +QtWebKit (5.2) <9BBC91A6-3969-38F0-BCE1-855A38FCD175> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtWebKit.framework/Versions/5/QtWebKit
       0x110b44000 -        0x110b64fff +QtSensors (5.2) <D03DBD19-73FB-32B1-A941-79FE9C08ED8B> /Users/USER/*/Qt Creator.app/Contents/Frameworks/QtSensors.framework/Versions/5/QtSensors
       0x110b7b000 -        0x110b8eff7 +libImageViewer.dylib (0) <B93EB71B-FE43-30F9-84FA-D507A45F9E3A> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libImageViewer.dylib
       0x110b9d000 -        0x110bf3ff7 +libIos.dylib (0) <736FBFD3-B4B9-3E44-A758-67F4C5968B0C> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libIos.dylib
       0x110c20000 -        0x110c3ffff +libMacros.dylib (0) <439BFADE-4BCF-3B88-B9E0-9F8A757009F5> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libMacros.dylib
       0x110c53000 -        0x110c84ff7 +libMercurial.dylib (0) <8B5DA87C-1DB4-3A29-AA1B-73E243E4555B> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libMercurial.dylib
       0x110ca5000 -        0x110ce1fff +libPerforce.dylib (0) <D0859252-0A5E-33F3-8B0A-09ED85C7283E> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libPerforce.dylib
       0x110d01000 -        0x110d19ff7 +libPythonEditor.dylib (0) <096A7303-C029-30C9-9A29-C7FD269EEF31> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libPythonEditor.dylib
       0x110d2f000 -        0x110dc3fff +libQmlJSEditor.dylib (0) <0FA41FE0-557F-3CE6-AC35-55CF176E7996> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmlJSEditor.dylib
       0x110e24000 -        0x110e84fff +libQmlEditorWidgets.1.0.0.dylib (1) <4BF06BCD-A71F-3B65-8E9D-A843284DA789> /Users/USER/*/Qt Creator.app/Contents/PlugIns/libQmlEditorWidgets.1.0.0.dylib
       0x110ea8000 -        0x111197ff7 +libQmlDesigner.dylib (0) <392E5FF7-E5FC-3604-A6E9-F15B63C66BDE> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmlDesigner.dylib
       0x1112a4000 -        0x111354ff7 +libQmlProfiler.dylib (0) <53DC9C24-7602-3055-ABFC-482B4EEF1ECA> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmlProfiler.dylib
       0x1113a0000 -        0x1113ddff7 +libQmlProjectManager.dylib (0) <91B843A1-0A2D-36BB-861E-51E372F3E754> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libQmlProjectManager.dylib
       0x111401000 -        0x111479ff7 +libRemoteLinux.dylib (0) <7FD9D196-E411-3DA4-BF9E-17D769308347> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libRemoteLinux.dylib
       0x1114c4000 -        0x1115ecff7 +libQnx.dylib (0) <C02BBB5A-31FD-386C-AEE1-A979E8AFF25B> /Users/USER/*/Qt Creator.app/Contents/PlugIns/BlackBerry/libQnx.dylib
       0x111676000 -        0x11169fff7 +libResourceEditor.dylib (0) <CCCA90A0-44B8-37D7-8599-F105EBD79037> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libResourceEditor.dylib
       0x1116ba000 -        0x1116e6ff7 +libSubversion.dylib (0) <E48E6225-10CE-337D-A42C-D771FBB360D5> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libSubversion.dylib
       0x111704000 -        0x1117aafff +libValgrind.dylib (0) <DA4A210B-93BB-3EE6-A118-6D89C12D4341> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libValgrind.dylib
       0x1117f7000 -        0x111804ff7 +libWelcome.dylib (0) <09D9F84A-80A7-3E5A-9692-A5BB26631342> /Users/USER/*/Qt Creator.app/Contents/PlugIns/QtProject/libWelcome.dylib
       0x111cd8000 -        0x111d8bfff +libqtquickcontrolsplugin.dylib (0) <97998CDA-BC14-33C6-9784-ADFD1FCEB5AA> /Users/USER/*/Qt Creator.app/Contents/Imports/qtquick2/QtQuick/Controls/libqtquickcontrolsplugin.dylib
       0x111db4000 -        0x111dcefff +libqquicklayoutsplugin.dylib (0) <1498259C-0003-3F0A-83E6-E604817091B9> /Users/USER/*/Qt Creator.app/Contents/Imports/qtquick2/QtQuick/Layouts/libqquicklayoutsplugin.dylib
       0x111e6b000 -        0x111e73ff7 +libqtaccessiblequick.dylib (0) <3FC88A33-4CC1-31F5-B368-E01F3CAF5022> /Users/USER/*/Qt Creator.app/Contents/PlugIns/accessible/libqtaccessiblequick.dylib
       0x111e89000 -        0x111e8cff7 +libwindowplugin.dylib (0) <B986020A-C43E-314C-9CA3-862A1A88FBDB> /Users/USER/*/Qt Creator.app/Contents/Imports/qtquick2/QtQuick/Window.2/libwindowplugin.dylib
       0x111ea1000 -        0x111ea2fe4 +cl_kernels (???) <AEA5A035-A901-40BD-8749-1B9DBA8A536F> cl_kernels
       0x111eb0000 -        0x111eb1ff9 +cl_kernels (???) <AE7216B9-72C6-4027-9AB6-DFC1F44F2B04> cl_kernels
       0x111eb3000 -        0x111ed7ff7 +libqtaccessiblewidgets.dylib (0) <B1D19700-E7FB-3CFF-A466-8FB5684E374B> /Users/USER/*/Qt Creator.app/Contents/PlugIns/accessible/libqtaccessiblewidgets.dylib
       0x11342c000 -        0x113512fef  unorm8_bgra.dylib (2.3.58) <9FF943D1-4EF7-36CA-852D-B61C2E554713> /System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries/ImageFormats/unorm8_bgra.dylib
    0x7fff6c2f8000 -     0x7fff6c32b817  dyld (239.3) <D1DFCF3F-0B0C-332A-BCC0-87A851B570FF> /usr/lib/dyld
    0x7fff874e4000 -     0x7fff8772cfff  com.apple.CoreData (107 - 481) <E5AFBA07-F73E-3B3F-9099-F51224EE8EAD> /System/Library/Frameworks/CoreData.framework/Versions/A/CoreData
    0x7fff8772d000 -     0x7fff8781eff9  libiconv.2.dylib (41) <BB44B115-AC32-3877-A0ED-AEC6232A4563> /usr/lib/libiconv.2.dylib
    0x7fff87d90000 -     0x7fff87e1cff7  com.apple.ink.framework (10.9 - 207) <8A50B893-AD03-3826-8555-A54FEAF08F47> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/Ink.framework/Versions/A/Ink
    0x7fff87e2a000 -     0x7fff87e41fff  com.apple.CFOpenDirectory (10.9 - 173.1.1) <3FB4D5FE-860B-3BDE-BAE2-3531D919EF10> /System/Library/Frameworks/OpenDirectory.framework/Versions/A/Frameworks/CFOpenDirectory.framework/Versions/A/CFOpenDirectory
    0x7fff87f08000 -     0x7fff87f12fff  libcommonCrypto.dylib (60049) <8C4F0CA0-389C-3EDC-B155-E62DD2187E1D> /usr/lib/system/libcommonCrypto.dylib
    0x7fff87f96000 -     0x7fff87fa1ff7  com.apple.DirectoryService.Framework (10.9 - 173.1.1) <F8566D1F-450F-3571-911F-75C68E45919F> /System/Library/Frameworks/DirectoryService.framework/Versions/A/DirectoryService
    0x7fff88035000 -     0x7fff8803cfff  com.apple.NetFS (6.0 - 4.0) <8E26C099-CE9D-3819-91A2-64EA929C6137> /System/Library/Frameworks/NetFS.framework/Versions/A/NetFS
    0x7fff8825c000 -     0x7fff8825cff7  libkeymgr.dylib (28) <3AA8D85D-CF00-3BD3-A5A0-E28E1A32A6D8> /usr/lib/system/libkeymgr.dylib
    0x7fff88b6c000 -     0x7fff88bd0ff9  com.apple.Heimdal (4.0 - 2.0) <E7D20A4D-4674-37E1-A949-635FFF7C439A> /System/Library/PrivateFrameworks/Heimdal.framework/Versions/A/Heimdal
    0x7fff88d05000 -     0x7fff88d35fff  com.apple.IconServices (25 - 25.17) <4751127E-FBD5-3ED5-8510-08D4E4166EFE> /System/Library/PrivateFrameworks/IconServices.framework/Versions/A/IconServices
    0x7fff88d36000 -     0x7fff88d3aff7  libGIF.dylib (1038) <C29B4323-1B9E-36B9-96C2-7CEDBAA124F0> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libGIF.dylib
    0x7fff88d3d000 -     0x7fff88d8bfff  com.apple.opencl (2.3.57 - 2.3.57) <FC03A80D-543A-3448-83FF-D399C3A240D9> /System/Library/Frameworks/OpenCL.framework/Versions/A/OpenCL
    0x7fff88dd9000 -     0x7fff88de6fff  com.apple.Sharing (132.2 - 132.2) <F983394A-226D-3244-B511-FA51FDB6ADDA> /System/Library/PrivateFrameworks/Sharing.framework/Versions/A/Sharing
    0x7fff88e9c000 -     0x7fff89038ff7  com.apple.QuartzCore (1.8 - 332.0) <994D1E0A-64B6-398C-B9A2-C362F02DE943> /System/Library/Frameworks/QuartzCore.framework/Versions/A/QuartzCore
    0x7fff89752000 -     0x7fff89781ff5  com.apple.GSS (4.0 - 2.0) <ED98D992-CC14-39F3-9ABC-8D7F986487CC> /System/Library/Frameworks/GSS.framework/Versions/A/GSS
    0x7fff897cd000 -     0x7fff8988fff1  com.apple.CoreText (352.0 - 367.15) <E5C70FC8-C861-39B8-A491-595E5B55CFC8> /System/Library/Frameworks/CoreText.framework/Versions/A/CoreText
    0x7fff89c6c000 -     0x7fff89c75ff7  libcldcpuengine.dylib (2.3.58) <A2E1ED7B-FC7E-31F6-830A-FF917689766B> /System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries/libcldcpuengine.dylib
    0x7fff89c76000 -     0x7fff89c78ff7  com.apple.securityhi (9.0 - 55005) <405E2BC6-2B6F-3B6B-B48E-2FD39214F052> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/SecurityHI.framework/Versions/A/SecurityHI
    0x7fff89c79000 -     0x7fff89c7dff7  libheimdal-asn1.dylib (323.12) <063A01C2-E547-39D9-BB42-4CC8E64ADE70> /usr/lib/libheimdal-asn1.dylib
    0x7fff89f7c000 -     0x7fff89f81fff  libmacho.dylib (845) <1D2910DF-C036-3A82-A3FD-44FF73B5FF9B> /usr/lib/system/libmacho.dylib
    0x7fff89fd5000 -     0x7fff89fdcff7  liblaunch.dylib (842.1.4) <FCBF0A02-0B06-3F97-9248-5062A9DEB32C> /usr/lib/system/liblaunch.dylib
    0x7fff89ff1000 -     0x7fff8a001ffb  libsasl2.2.dylib (170) <C8E25710-68B6-368A-BF3E-48EC7273177B> /usr/lib/libsasl2.2.dylib
    0x7fff8a06c000 -     0x7fff8a224ff3  libicucore.A.dylib (511.27) <003B6C21-CBD1-3486-9A1D-030ADF5FA061> /usr/lib/libicucore.A.dylib
    0x7fff8a29a000 -     0x7fff8a2a4ff7  com.apple.CrashReporterSupport (10.9 - 538) <B487466B-3AA1-3854-A808-A61F049FA794> /System/Library/PrivateFrameworks/CrashReporterSupport.framework/Versions/A/CrashReporterSupport
    0x7fff8a7ca000 -     0x7fff8a7cafff  com.apple.Accelerate (1.9 - Accelerate 1.9) <509BB27A-AE62-366D-86D8-0B06D217CF56> /System/Library/Frameworks/Accelerate.framework/Versions/A/Accelerate
    0x7fff8a862000 -     0x7fff8a88affb  libxslt.1.dylib (13) <C9794936-633C-3F0C-9E71-30190B9B41C1> /usr/lib/libxslt.1.dylib
    0x7fff8a8a2000 -     0x7fff8a8a4ffb  libutil.dylib (34) <DAC4A6CF-A1BB-3874-9569-A919316D30E8> /usr/lib/libutil.dylib
    0x7fff8a8a5000 -     0x7fff8a934fff  com.apple.Metadata (10.7.0 - 800.12.2) <A9F5D471-8732-3F95-A4A2-33864B92A181> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/Metadata.framework/Versions/A/Metadata
    0x7fff8a935000 -     0x7fff8a937fff  libCVMSPluginSupport.dylib (9.0.83) <E2AED858-6EEB-36C6-8C06-C3CF649A3CD5> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libCVMSPluginSupport.dylib
    0x7fff8a9bf000 -     0x7fff8a9c3fff  libpam.2.dylib (20) <B93CE8F5-DAA8-30A1-B1F6-F890509513CB> /usr/lib/libpam.2.dylib
    0x7fff8a9df000 -     0x7fff8a9eafff  libGL.dylib (9.0.83) <984A960A-C159-3AE5-8B40-E2B451F6C712> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib
    0x7fff8a9eb000 -     0x7fff8aacffff  com.apple.coreui (2.1 - 231) <432DB40C-6B7E-39C8-9FB5-B95917930056> /System/Library/PrivateFrameworks/CoreUI.framework/Versions/A/CoreUI
    0x7fff8ab5a000 -     0x7fff8ab5cfff  com.apple.EFILogin (2.0 - 2) <C360E8AF-E9BB-3BBA-9DF0-57A92CEF00D4> /System/Library/PrivateFrameworks/EFILogin.framework/Versions/A/EFILogin
    0x7fff8abe8000 -     0x7fff8abe9ffb  libremovefile.dylib (33) <3543F917-928E-3DB2-A2F4-7AB73B4970EF> /usr/lib/system/libremovefile.dylib
    0x7fff8af34000 -     0x7fff8af39ff7  libunwind.dylib (35.3) <78DCC358-2FC1-302E-B395-0155B47CB547> /usr/lib/system/libunwind.dylib
    0x7fff8af3a000 -     0x7fff8af5fff7  com.apple.ChunkingLibrary (2.0 - 155.1) <B845DC7A-D1EA-31E2-967C-D1FE0C628036> /System/Library/PrivateFrameworks/ChunkingLibrary.framework/Versions/A/ChunkingLibrary
    0x7fff8af60000 -     0x7fff8af61ff7  com.apple.print.framework.Print (9.0 - 260) <EE00FAE1-DA03-3EC2-8571-562518C46994> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/Print.framework/Versions/A/Print
    0x7fff8af65000 -     0x7fff8afb3ff9  libstdc++.6.dylib (60) <0241E6A4-1368-33BE-950B-D0A175C41F54> /usr/lib/libstdc++.6.dylib
    0x7fff8afb4000 -     0x7fff8afb5ff7  libDiagnosticMessagesClient.dylib (100) <4CDB0F7B-C0AF-3424-BC39-495696F0DB1E> /usr/lib/libDiagnosticMessagesClient.dylib
    0x7fff8afb6000 -     0x7fff8afc3ff0  libbz2.1.0.dylib (29) <0B98AC35-B138-349C-8063-2B987A75D24C> /usr/lib/libbz2.1.0.dylib
    0x7fff8afcb000 -     0x7fff8b2b5fff  com.apple.CoreServices.CarbonCore (1077.14 - 1077.14) <B00BEB34-A9F5-381F-99FD-11E405768A9A> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/CarbonCore.framework/Versions/A/CarbonCore
    0x7fff8b317000 -     0x7fff8b340ff7  libc++abi.dylib (48) <8C16158F-CBF8-3BD7-BEF4-022704B2A326> /usr/lib/libc++abi.dylib
    0x7fff8b60b000 -     0x7fff8b6f9fff  libJP2.dylib (1038) <6C8179F5-8063-3ED6-A7C2-D5603DECDF28> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libJP2.dylib
    0x7fff8b6fa000 -     0x7fff8b75eff3  com.apple.datadetectorscore (5.0 - 354.0) <9ACF24B8-3268-3134-A5BC-D72C9371A195> /System/Library/PrivateFrameworks/DataDetectorsCore.framework/Versions/A/DataDetectorsCore
    0x7fff8b7b7000 -     0x7fff8b7bafff  libCoreVMClient.dylib (58.1) <EBC36C69-C896-3C3D-8589-3E9023E7E56F> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libCoreVMClient.dylib
    0x7fff8b7cb000 -     0x7fff8b7e6ff7  libsystem_malloc.dylib (23.1.10) <FFE5C472-B23A-318A-85BF-77CDE61900D1> /usr/lib/system/libsystem_malloc.dylib
    0x7fff8b8e4000 -     0x7fff8b8ecff7  com.apple.speech.recognition.framework (4.2.4 - 4.2.4) <98BBB3E4-6239-3EF1-90B2-84EA0D3B8D61> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/SpeechRecognition.framework/Versions/A/SpeechRecognition
    0x7fff8b8ed000 -     0x7fff8b8f0ff7  libdyld.dylib (239.3) <62F4D752-4089-31A8-8B73-B95A68893B3C> /usr/lib/system/libdyld.dylib
    0x7fff8b8f4000 -     0x7fff8b8fbff7  libsystem_pthread.dylib (53.1.4) <AB498556-B555-310E-9041-F67EC9E00E2C> /usr/lib/system/libsystem_pthread.dylib
    0x7fff8b91b000 -     0x7fff8b94afff  com.apple.DebugSymbols (106 - 106) <E1BDED08-523A-36F4-B2DA-9D5C712F0AC7> /System/Library/PrivateFrameworks/DebugSymbols.framework/Versions/A/DebugSymbols
    0x7fff8b94b000 -     0x7fff8b94efff  com.apple.help (1.3.3 - 46) <AE763646-D07A-3F9A-ACD4-F5CBD734EE36> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/Help.framework/Versions/A/Help
    0x7fff8b94f000 -     0x7fff8b950fff  liblangid.dylib (117) <9546E641-F730-3AB0-B3CD-E0E2FDD173D9> /usr/lib/liblangid.dylib
    0x7fff8b9b5000 -     0x7fff8b9b9ff7  libcache.dylib (62) <BDC1E65B-72A1-3DA3-A57C-B23159CAAD0B> /usr/lib/system/libcache.dylib
    0x7fff8b9ba000 -     0x7fff8b9bdfff  com.apple.TCC (1.0 - 1) <32A075D9-47FD-3E71-95BC-BFB0D583F41C> /System/Library/PrivateFrameworks/TCC.framework/Versions/A/TCC
    0x7fff8b9be000 -     0x7fff8b9cfff7  libsystem_asl.dylib (217.1.4) <655FB343-52CF-3E2F-B14D-BEBF5AAEF94D> /usr/lib/system/libsystem_asl.dylib
    0x7fff8bde1000 -     0x7fff8becbfff  libsqlite3.dylib (158) <00269BF9-43BE-39E0-9C85-24585B9923C8> /usr/lib/libsqlite3.dylib
    0x7fff8c15e000 -     0x7fff8c16aff3  com.apple.AppleFSCompression (56 - 1.0) <5652B0D0-EB08-381F-B23A-6DCF96991FB5> /System/Library/PrivateFrameworks/AppleFSCompression.framework/Versions/A/AppleFSCompression
    0x7fff8c2fb000 -     0x7fff8c553ff1  com.apple.security (7.0 - 55471) <233831C5-C457-3AD5-AFE7-E3E2DE6929C9> /System/Library/Frameworks/Security.framework/Versions/A/Security
    0x7fff8c554000 -     0x7fff8c55dff3  libsystem_notify.dylib (121) <52571EC3-6894-37E4-946E-064B021ED44E> /usr/lib/system/libsystem_notify.dylib
    0x7fff8c55e000 -     0x7fff8c568ff7  com.apple.bsd.ServiceManagement (2.0 - 2.0) <2D27B498-BB9C-3D88-B05A-76908A8A26F3> /System/Library/Frameworks/ServiceManagement.framework/Versions/A/ServiceManagement
    0x7fff8c569000 -     0x7fff8c699ff7  com.apple.desktopservices (1.8 - 1.8) <09DC9BB8-432F-3C7A-BB08-956A2DDFC2DE> /System/Library/PrivateFrameworks/DesktopServicesPriv.framework/Versions/A/DesktopServicesPriv
    0x7fff8c69a000 -     0x7fff8c96efc7  com.apple.vImage (7.0 - 7.0) <D241DBFA-AC49-31E2-893D-EAAC31890C90> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vImage.framework/Versions/A/vImage
    0x7fff8c96f000 -     0x7fff8c9c1fff  libc++.1.dylib (120) <4F68DFC5-2077-39A8-A449-CAC5FDEE7BDE> /usr/lib/libc++.1.dylib
    0x7fff8c9c2000 -     0x7fff8c9c2ffd  libOpenScriptingUtil.dylib (157) <19F0E769-0989-3062-9AFB-8976E90E9759> /usr/lib/libOpenScriptingUtil.dylib
    0x7fff8cac7000 -     0x7fff8cad6ff8  com.apple.LangAnalysis (1.7.0 - 1.7.0) <8FE131B6-1180-3892-98F5-C9C9B79072D4> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/LangAnalysis.framework/Versions/A/LangAnalysis
    0x7fff8cad7000 -     0x7fff8cb44fff  com.apple.SearchKit (1.4.0 - 1.4.0) <B9B8D510-A27E-36B0-93E9-17146D9E9045> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/SearchKit.framework/Versions/A/SearchKit
    0x7fff8cb9b000 -     0x7fff8cc53ff7  com.apple.DiscRecording (8.0 - 8000.4.6) <CDAAAD04-A1D0-3C67-ABCC-EFC9E8D44E7E> /System/Library/Frameworks/DiscRecording.framework/Versions/A/DiscRecording
    0x7fff8cc54000 -     0x7fff8cd59fff  com.apple.ImageIO.framework (3.3.0 - 1038) <2C058216-C6D8-3380-A7EA-92A3F04520C1> /System/Library/Frameworks/ImageIO.framework/Versions/A/ImageIO
    0x7fff8cdc1000 -     0x7fff8ce71ff7  libvMisc.dylib (423.32) <049C0735-1808-39B9-943F-76CB8021744F> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/libvMisc.dylib
    0x7fff8ce90000 -     0x7fff8cf5bfff  libvDSP.dylib (423.32) <3BF732BE-DDE0-38EB-8C54-E4E3C64F77A7> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/libvDSP.dylib
    0x7fff8d0bc000 -     0x7fff8d0c1fff  com.apple.DiskArbitration (2.6 - 2.6) <F8A47F61-83D1-3F92-B7A8-A169E0D187C0> /System/Library/Frameworks/DiskArbitration.framework/Versions/A/DiskArbitration
    0x7fff8d135000 -     0x7fff8d166fff  com.apple.MediaKit (15 - 709) <23E33409-5C39-3F93-9E73-2B0E9EE8883E> /System/Library/PrivateFrameworks/MediaKit.framework/Versions/A/MediaKit
    0x7fff8d224000 -     0x7fff8d263fff  libGLU.dylib (9.0.83) <8B457205-513B-3477-AE9C-3AD979D5FE11> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
    0x7fff8d264000 -     0x7fff8d27efff  libdispatch.dylib (339.1.9) <46878A5B-4248-3057-962C-6D4A235EEF31> /usr/lib/system/libdispatch.dylib
    0x7fff8d5db000 -     0x7fff8d60ffff  libssl.0.9.8.dylib (50) <B15F967C-B002-36C2-9621-3456D8509F50> /usr/lib/libssl.0.9.8.dylib
    0x7fff8d641000 -     0x7fff8d644ff7  com.apple.LoginUICore (3.0 - 3.0) <1ECBDA90-D6ED-3333-83EB-9C8232DFAD7C> /System/Library/PrivateFrameworks/LoginUIKit.framework/Versions/A/Frameworks/LoginUICore.framework/Versions/A/LoginUICore
    0x7fff8d645000 -     0x7fff8d646ff7  libSystem.B.dylib (1197.1.1) <BFC0DC97-46C6-3BE0-9983-54A98734897A> /usr/lib/libSystem.B.dylib
    0x7fff8d647000 -     0x7fff8d726fff  libcrypto.0.9.8.dylib (50) <B95B9DBA-39D3-3EEF-AF43-44608B28894E> /usr/lib/libcrypto.0.9.8.dylib
    0x7fff8d727000 -     0x7fff8d74fffb  libRIP.A.dylib (599.7) <6F528EE3-99F8-3871-BD60-1306495C27D5> /System/Library/Frameworks/CoreGraphics.framework/Versions/A/Resources/libRIP.A.dylib
    0x7fff8e91f000 -     0x7fff8e925ff7  libCGXCoreImage.A.dylib (599.7) <AC38090E-BA96-33C0-92F3-8EF6231582C4> /System/Library/Frameworks/CoreGraphics.framework/Versions/A/Resources/libCGXCoreImage.A.dylib
    0x7fff8ea63000 -     0x7fff8ea63fff  com.apple.ApplicationServices (48 - 48) <3E3F01A8-314D-378F-835E-9CC4F8820031> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/ApplicationServices
    0x7fff8eaab000 -     0x7fff8eacffff  libxpc.dylib (300.1.17) <4554927A-9467-365C-91F1-5A116989DD7F> /usr/lib/system/libxpc.dylib
    0x7fff8ead0000 -     0x7fff8eaddff7  libxar.1.dylib (202) <5572AA71-E98D-3FE1-9402-BB4A84E0E71E> /usr/lib/libxar.1.dylib
    0x7fff8eade000 -     0x7fff8eb4dff1  com.apple.ApplicationServices.ATS (360 - 363.1) <88976B22-A9B8-3E7B-9AE6-0B8E09A968FC> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ATS.framework/Versions/A/ATS
    0x7fff8eb4e000 -     0x7fff8eb67ff7  com.apple.Kerberos (3.0 - 1) <F108AFEB-198A-3BAF-BCA5-9DFCE55EFF92> /System/Library/Frameworks/Kerberos.framework/Versions/A/Kerberos
    0x7fff8eb68000 -     0x7fff8ebcbff7  com.apple.SystemConfiguration (1.13 - 1.13) <F05F4149-981B-380B-8F50-51CE804BBB89> /System/Library/Frameworks/SystemConfiguration.framework/Versions/A/SystemConfiguration
    0x7fff8ebef000 -     0x7fff8f763ff7  com.apple.AppKit (6.9 - 1265) <0E9FC8BF-DA3C-34C5-91CC-12BC922B5F01> /System/Library/Frameworks/AppKit.framework/Versions/C/AppKit
    0x7fff8f84e000 -     0x7fff8f893ff6  com.apple.HIServices (1.22 - 466) <21807AF8-3BC7-32BB-AB96-7C35CB59D7F6> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/HIServices
    0x7fff8f894000 -     0x7fff8f8d2ff7  libGLImage.dylib (9.0.83) <C08048A7-03CC-3E40-BCDC-7791D87AC8E4> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLImage.dylib
    0x7fff8f8d3000 -     0x7fff8f95efff  libCoreStorage.dylib (380) <AE14C2F3-0EF1-3DCD-BF2B-A24D97D3B372> /usr/lib/libCoreStorage.dylib
    0x7fff8faa9000 -     0x7fff8fac4ff7  libPng.dylib (1038) <EF781AF8-C2E6-3179-B8A1-A584783070F1> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libPng.dylib
    0x7fff8fac5000 -     0x7fff8fae0ff7  libCRFSuite.dylib (34) <FFAE75FA-C54E-398B-AA97-18164CD9789D> /usr/lib/libCRFSuite.dylib
    0x7fff8fae1000 -     0x7fff8fd6ffff  com.apple.RawCamera.bundle (5.02 - 725) <4DE37ECB-24CD-38B1-B5AF-1EE911E19B80> /System/Library/CoreServices/RawCamera.bundle/Contents/MacOS/RawCamera
    0x7fff8fd70000 -     0x7fff9003eff4  com.apple.CoreImage (9.0.54) <74BB8685-69A9-3A45-8DED-EA26BD39D710> /System/Library/Frameworks/QuartzCore.framework/Versions/A/Frameworks/CoreImage.framework/Versions/A/CoreImage
    0x7fff9003f000 -     0x7fff90079ff3  com.apple.bom (12.0 - 192) <989690DB-B9CC-3DB5-89AE-B5D33EDC474E> /System/Library/PrivateFrameworks/Bom.framework/Versions/A/Bom
    0x7fff9007a000 -     0x7fff9007dffc  com.apple.IOSurface (91 - 91) <07CA8A59-1E32-3FB6-B506-18DAF58A8CE0> /System/Library/Frameworks/IOSurface.framework/Versions/A/IOSurface
    0x7fff9007e000 -     0x7fff90086ff3  libCGCMS.A.dylib (599.7) <92AA4E85-7633-36E2-BAD0-7B1A2E48E75C> /System/Library/Frameworks/CoreGraphics.framework/Versions/A/Resources/libCGCMS.A.dylib
    0x7fff90087000 -     0x7fff9008bfff  libsystem_stats.dylib (93.1.26) <B9E26A9E-FBBC-3938-B8B7-6CF7CA8C99AD> /usr/lib/system/libsystem_stats.dylib
    0x7fff9008c000 -     0x7fff900a4ff7  com.apple.GenerationalStorage (2.0 - 160.2) <79629AC7-896F-3302-8AC1-4939020F08C3> /System/Library/PrivateFrameworks/GenerationalStorage.framework/Versions/A/GenerationalStorage
    0x7fff900a5000 -     0x7fff900f2ff2  com.apple.print.framework.PrintCore (9.0 - 428) <8D8253E3-302F-3DB2-9C5C-572CB974E8B3> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/PrintCore.framework/Versions/A/PrintCore
    0x7fff900f3000 -     0x7fff90246ff7  com.apple.audio.toolbox.AudioToolbox (1.9 - 1.9) <A0B7B007-9BD8-30E2-B644-47856DA29FEE> /System/Library/Frameworks/AudioToolbox.framework/Versions/A/AudioToolbox
    0x7fff90251000 -     0x7fff90273fff  com.apple.framework.familycontrols (4.1 - 410) <4FDBCD10-CAA2-3A9C-99F2-06DCB8E81DEE> /System/Library/PrivateFrameworks/FamilyControls.framework/Versions/A/FamilyControls
    0x7fff903d5000 -     0x7fff903e7ff7  com.apple.MultitouchSupport.framework (245.13 - 245.13) <D5E7416D-45AB-3690-86C6-CC4B5FCEA2D2> /System/Library/PrivateFrameworks/MultitouchSupport.framework/Versions/A/MultitouchSupport
    0x7fff903e8000 -     0x7fff90440ff7  com.apple.Symbolication (1.4 - 129) <16D42516-7B5E-357C-898A-FAA9EE7642B3> /System/Library/PrivateFrameworks/Symbolication.framework/Versions/A/Symbolication
    0x7fff90441000 -     0x7fff90444ffa  libCGXType.A.dylib (599.7) <2FC9C2BC-B5C5-3C27-93F9-51C6C4512E9D> /System/Library/Frameworks/CoreGraphics.framework/Versions/A/Resources/libCGXType.A.dylib
    0x7fff90445000 -     0x7fff90461fff  libresolv.9.dylib (54) <11C2C826-F1C6-39C6-B4E8-6E0C41D4FA95> /usr/lib/libresolv.9.dylib
    0x7fff90607000 -     0x7fff9065afff  com.apple.ScalableUserInterface (1.0 - 1) <CF745298-7373-38D2-B3B1-727D5A569E48> /System/Library/Frameworks/QuartzCore.framework/Versions/A/Frameworks/ScalableUserInterface.framework/Versions/A/ScalableUserInterface
    0x7fff906ad000 -     0x7fff909acfff  com.apple.Foundation (6.9 - 1056) <D608EDFD-9634-3573-9B7E-081C7D085F7A> /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
    0x7fff90a2c000 -     0x7fff90a7dff3  com.apple.audio.CoreAudio (4.2.0 - 4.2.0) <BF4C2FE3-8BC8-30D1-8347-2A7221268794> /System/Library/Frameworks/CoreAudio.framework/Versions/A/CoreAudio
    0x7fff90a7e000 -     0x7fff90aa2ff7  libJPEG.dylib (1038) <86F349A8-882D-3326-A0B0-63257F68B1A7> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libJPEG.dylib
    0x7fff90aa3000 -     0x7fff90ab5fff  com.apple.ImageCapture (9.0 - 9.0) <BE0B65DA-3031-359B-8BBA-B9803D4ADBF4> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/ImageCapture.framework/Versions/A/ImageCapture
    0x7fff90b21000 -     0x7fff90b2ffff  com.apple.CommerceCore (1.0 - 42) <ACC2CE3A-913A-39E0-8344-B76F8F694EF5> /System/Library/PrivateFrameworks/CommerceKit.framework/Versions/A/Frameworks/CommerceCore.framework/Versions/A/CommerceCore
    0x7fff90b33000 -     0x7fff90b9dff7  com.apple.framework.IOKit (2.0.1 - 907.1.13) <C1E95F5C-B79B-31BE-9F2A-1B25163C1F16> /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
    0x7fff90ba4000 -     0x7fff90c75ff1  com.apple.DiskImagesFramework (10.9 - 371.1) <D456ED08-4C1D-341F-BAB8-85E34A7275C5> /System/Library/PrivateFrameworks/DiskImages.framework/Versions/A/DiskImages
    0x7fff90c76000 -     0x7fff90c8fff7  com.apple.Ubiquity (1.3 - 289) <C7F1B734-CE81-334D-BE41-8B20D95A1F9B> /System/Library/PrivateFrameworks/Ubiquity.framework/Versions/A/Ubiquity
    0x7fff90c96000 -     0x7fff90c9afff  com.apple.CommonPanels (1.2.6 - 96) <6B434AFD-50F8-37C7-9A56-162C17E375B3> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/CommonPanels.framework/Versions/A/CommonPanels
    0x7fff910bc000 -     0x7fff911abfff  libFontParser.dylib (111.1) <835A8253-6AB9-3AAB-9CBF-171440DEC486> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ATS.framework/Versions/A/Resources/libFontParser.dylib
    0x7fff911ac000 -     0x7fff91275fff  com.apple.LaunchServices (572.23 - 572.23) <8D955BDE-2C4C-3DD4-B4D7-2D916174FE1D> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/LaunchServices.framework/Versions/A/LaunchServices
    0x7fff91276000 -     0x7fff9127ffff  com.apple.speech.synthesis.framework (4.6.2 - 4.6.2) <0AAE45F0-FC6E-36B6-A6A7-73E6950A74AC> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/SpeechSynthesis.framework/Versions/A/SpeechSynthesis
    0x7fff91280000 -     0x7fff91282fff  libRadiance.dylib (1038) <55F99274-5074-3C73-BAC5-AF234E71CF38> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libRadiance.dylib
    0x7fff912c6000 -     0x7fff9130dff7  libcups.2.dylib (372) <348EED62-6C20-35D6-8EFB-E80943965100> /usr/lib/libcups.2.dylib
    0x7fff9130e000 -     0x7fff9134ffff  com.apple.PerformanceAnalysis (1.47 - 47) <784ED7B8-FAE4-36CE-8C76-B7D300316C9F> /System/Library/PrivateFrameworks/PerformanceAnalysis.framework/Versions/A/PerformanceAnalysis
    0x7fff91359000 -     0x7fff914c9ff6  com.apple.CFNetwork (673.0.3 - 673.0.3) <42CFC3DB-35C8-3652-AF37-4BCC73D8BDEF> /System/Library/Frameworks/CFNetwork.framework/Versions/A/CFNetwork
    0x7fff914ca000 -     0x7fff914d1ff3  libcopyfile.dylib (103) <5A881779-D0D6-3029-B371-E3021C2DDA5E> /usr/lib/system/libcopyfile.dylib
    0x7fff914d2000 -     0x7fff9152bfff  libTIFF.dylib (1038) <5CBFE0C2-9DD8-340B-BA63-A94CE2E476F2> /System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/libTIFF.dylib
    0x7fff9154e000 -     0x7fff9192fffe  libLAPACK.dylib (1094.5) <7E7A9B8D-1638-3914-BAE0-663B69865986> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/libLAPACK.dylib
    0x7fff91957000 -     0x7fff9197cff7  com.apple.CoreVideo (1.8 - 117.2) <4674339E-26D0-35FA-9958-422832B39B12> /System/Library/Frameworks/CoreVideo.framework/Versions/A/CoreVideo
    0x7fff9197d000 -     0x7fff91b62ff7  com.apple.CoreFoundation (6.9 - 855.11) <E22C6A1F-8996-349C-905E-96C3BBE07C2F> /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
    0x7fff91b63000 -     0x7fff91b74ff7  libz.1.dylib (53) <42E0C8C6-CA38-3CA4-8619-D24ED5DD492E> /usr/lib/libz.1.dylib
    0x7fff91be3000 -     0x7fff91beafff  libcompiler_rt.dylib (35) <4CD916B2-1B17-362A-B403-EF24A1DAC141> /usr/lib/system/libcompiler_rt.dylib
    0x7fff91beb000 -     0x7fff91c46ffb  com.apple.AE (665.5 - 665.5) <BBA230F9-144C-3CAB-A77A-0621719244CD> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/AE.framework/Versions/A/AE
    0x7fff91c47000 -     0x7fff91c8cff7  libcurl.4.dylib (78) <A722B4F0-1F6C-3E16-9CB1-4C6ADC15221E> /usr/lib/libcurl.4.dylib
    0x7fff91c8d000 -     0x7fff91cb4ffb  libsystem_info.dylib (449.1.3) <7D41A156-D285-3849-A2C3-C04ADE797D98> /usr/lib/system/libsystem_info.dylib
    0x7fff91cce000 -     0x7fff91d10ff7  libauto.dylib (185.5) <F45C36E8-B606-3886-B5B1-B6745E757CA8> /usr/lib/libauto.dylib
    0x7fff91d11000 -     0x7fff91d19fff  libsystem_dnssd.dylib (522.1.11) <270DCF6C-502D-389A-AA9F-DE4624A36FF7> /usr/lib/system/libsystem_dnssd.dylib
    0x7fff91e47000 -     0x7fff9227affb  com.apple.vision.FaceCore (3.0.0 - 3.0.0) <F42BFC9C-0B16-35EF-9A07-91B7FDAB7FC5> /System/Library/PrivateFrameworks/FaceCore.framework/Versions/A/FaceCore
    0x7fff9227b000 -     0x7fff9227bfff  com.apple.CoreServices (59 - 59) <7A697B5E-F179-30DF-93F2-8B503CEEEFD5> /System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices
    0x7fff9227c000 -     0x7fff922a5fff  com.apple.DictionaryServices (1.2 - 208) <A539A058-BA57-35EE-AA08-D0B0E835127D> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/DictionaryServices.framework/Versions/A/DictionaryServices
    0x7fff922a6000 -     0x7fff92369ff7  com.apple.backup.framework (1.5.1 - 1.5.1) <FC4E949B-B41A-3F21-8AF8-AEDB13146FEA> /System/Library/PrivateFrameworks/Backup.framework/Versions/A/Backup
    0x7fff92ac7000 -     0x7fff92ac7fff  com.apple.Cocoa (6.8 - 20) <E90E99D7-A425-3301-A025-D9E0CD11918E> /System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa
    0x7fff92ac8000 -     0x7fff92ad6fff  com.apple.opengl (9.0.83 - 9.0.83) <AF467644-7B1D-327A-AC47-CECFCAF61990> /System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL
    0x7fff92b18000 -     0x7fff92ba1fff  com.apple.ColorSync (4.9.0 - 4.9.0) <B756B908-9AD1-3F5D-83F9-7A0B068387D2> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ColorSync.framework/Versions/A/ColorSync
    0x7fff92c4e000 -     0x7fff92c4fff7  libodfde.dylib (20) <C00A4EBA-44BC-3C53-BFD0-819B03FFD462> /usr/lib/libodfde.dylib
    0x7fff92c70000 -     0x7fff92c71ff7  libsystem_sandbox.dylib (278.10) <A47E7E11-3C76-318E-B67D-98972B86F094> /usr/lib/system/libsystem_sandbox.dylib
    0x7fff92c72000 -     0x7fff92de0ff7  libBLAS.dylib (1094.5) <DE93A590-5FA5-32A2-A16C-5D7D7361769F> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/libBLAS.dylib
    0x7fff92de1000 -     0x7fff92de3ff3  libsystem_configuration.dylib (596.12) <C4F633D9-94C8-35D9-BB2D-84C5122533C7> /usr/lib/system/libsystem_configuration.dylib
    0x7fff92e16000 -     0x7fff92e21ff7  com.apple.NetAuth (5.0 - 5.0) <C811E662-9EC3-3B74-808A-A75D624F326B> /System/Library/PrivateFrameworks/NetAuth.framework/Versions/A/NetAuth
    0x7fff92e22000 -     0x7fff92e22ffd  com.apple.audio.units.AudioUnit (1.9 - 1.9) <6E89F3CB-CC41-3728-9F9A-FDFC151E8261> /System/Library/Frameworks/AudioUnit.framework/Versions/A/AudioUnit
    0x7fff92f1c000 -     0x7fff92f93fff  com.apple.CoreServices.OSServices (600.4 - 600.4) <36B2B009-C35E-3F21-824E-E0D00E7808C7> /System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/OSServices.framework/Versions/A/OSServices
    0x7fff92f94000 -     0x7fff92f9cffc  libGFXShared.dylib (9.0.83) <11A621C3-37A0-39CE-A69B-8739021BD79D> /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGFXShared.dylib
    0x7fff92fc8000 -     0x7fff92fe4ff7  libsystem_kernel.dylib (2422.1.72) <D14913DB-47F1-3591-8DAF-D4B4EF5F8818> /usr/lib/system/libsystem_kernel.dylib
    0x7fff93177000 -     0x7fff931f7fff  com.apple.CoreSymbolication (3.0 - 141) <B018335C-698B-3F87-AF1C-6115C4FA8954> /System/Library/PrivateFrameworks/CoreSymbolication.framework/Versions/A/CoreSymbolication
    0x7fff931f8000 -     0x7fff93205ff4  com.apple.Librarian (1.2 - 1) <F1A2744D-8536-32C7-8218-9972C6300DAE> /System/Library/PrivateFrameworks/Librarian.framework/Versions/A/Librarian
    0x7fff934e9000 -     0x7fff934ebff7  libquarantine.dylib (71) <7A1A2BCB-C03D-3A25-BFA4-3E569B2D2C38> /usr/lib/system/libquarantine.dylib
    0x7fff934ec000 -     0x7fff93796ffd  com.apple.HIToolbox (2.1 - 696) <1CFFF37B-C392-3088-B0A4-C08C55B2AF8F> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/HIToolbox
    0x7fff937af000 -     0x7fff937bbff7  com.apple.OpenDirectory (10.9 - 173.1.1) <6B78BD7B-5622-38E6-8FC6-86A117E3ACCA> /System/Library/Frameworks/OpenDirectory.framework/Versions/A/OpenDirectory
    0x7fff93a70000 -     0x7fff93a80fff  libbsm.0.dylib (33) <2CAC00A2-1352-302A-88FA-C567D4D69179> /usr/lib/libbsm.0.dylib
    0x7fff93b00000 -     0x7fff93b06ff7  libsystem_platform.dylib (24.1.4) <331BA4A5-55CE-3B95-99EB-44E0C89D7FB8> /usr/lib/system/libsystem_platform.dylib
    0x7fff93b1a000 -     0x7fff93b53ff7  com.apple.QD (3.50 - 298) <C1F20764-DEF0-34CF-B3AB-AB5480D64E66> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/QD.framework/Versions/A/QD
    0x7fff93b54000 -     0x7fff93b8cff7  com.apple.RemoteViewServices (2.0 - 94) <3F34D630-3DDB-3411-BC28-A56A9B55EBDA> /System/Library/PrivateFrameworks/RemoteViewServices.framework/Versions/A/RemoteViewServices
    0x7fff93b8d000 -     0x7fff93b8efff  libunc.dylib (28) <62682455-1862-36FE-8A04-7A6B91256438> /usr/lib/system/libunc.dylib
    0x7fff93ba9000 -     0x7fff93bdeffc  com.apple.LDAPFramework (2.4.28 - 194.5) <7E31A674-C6AB-33BE-BD5E-F5E3C6E22894> /System/Library/Frameworks/LDAP.framework/Versions/A/LDAP
    0x7fff93bdf000 -     0x7fff93bdffff  com.apple.Carbon (154 - 157) <45A9A40A-78FF-3EA0-8FAB-A4F81052FA55> /System/Library/Frameworks/Carbon.framework/Versions/A/Carbon
    0x7fff93be0000 -     0x7fff93beaff7  libcsfde.dylib (380) <3A54B430-EC05-3DE9-86C3-00C1BEAC7F9B> /usr/lib/libcsfde.dylib
    0x7fff93beb000 -     0x7fff93becfff  com.apple.TrustEvaluationAgent (2.0 - 25) <334A82F4-4AE4-3719-A511-86D0B0723E2B> /System/Library/PrivateFrameworks/TrustEvaluationAgent.framework/Versions/A/TrustEvaluationAgent
    0x7fff93bf6000 -     0x7fff93bf6fff  com.apple.Accelerate.vecLib (3.9 - vecLib 3.9) <F8D0CC77-98AC-3B58-9FE6-0C25421827B6> /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/vecLib
    0x7fff93bf7000 -     0x7fff93c6affb  com.apple.securityfoundation (6.0 - 55122) <119D1C53-B292-3378-AEE1-A3B1FB02F43F> /System/Library/Frameworks/SecurityFoundation.framework/Versions/A/SecurityFoundation
    0x7fff93c6b000 -     0x7fff9458705f  com.apple.CoreGraphics (1.600.0 - 599.7) <7D0FD5A7-A061-39BA-8E00-723825D2C4DD> /System/Library/Frameworks/CoreGraphics.framework/Versions/A/CoreGraphics
    0x7fff94588000 -     0x7fff945a0ff7  com.apple.openscripting (1.4 - 157) <B3B037D7-1019-31E6-9D17-08E699AF3701> /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/OpenScripting.framework/Versions/A/OpenScripting
    0x7fff945ff000 -     0x7fff94646fff  libFontRegistry.dylib (127) <A77A0480-AA5D-3CC8-8B68-69985CD546DC> /System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ATS.framework/Versions/A/Resources/libFontRegistry.dylib
    0x7fff9466e000 -     0x7fff9469dfd2  libsystem_m.dylib (3047.16) <B7F0E2E4-2777-33FC-A787-D6430B630D54> /usr/lib/system/libsystem_m.dylib
    0x7fff94776000 -     0x7fff94923f27  libobjc.A.dylib (551.1) <AD7FD984-271E-30F4-A361-6B20319EC73B> /usr/lib/libobjc.A.dylib
    0x7fff94924000 -     0x7fff9492dfff  com.apple.CommonAuth (4.0 - 2.0) <1D263127-5F27-3128-996D-7397660D0C6E> /System/Library/PrivateFrameworks/CommonAuth.framework/Versions/A/CommonAuth
    0x7fff9492e000 -     0x7fff94a15ff7  libxml2.2.dylib (26) <A1DADD11-89E5-3DE4-8802-07186225967F> /usr/lib/libxml2.2.dylib
    0x7fff94ae8000 -     0x7fff94b0fff7  libsystem_network.dylib (241.3) <8B1E1F1D-A5CC-3BAE-8B1E-ABC84337A364> /usr/lib/system/libsystem_network.dylib
    0x7fff94b10000 -     0x7fff94b3cff7  com.apple.framework.SystemAdministration (1.0 - 1.0) <36C562FF-5D91-318C-A19C-6B4453FB78B9> /System/Library/PrivateFrameworks/SystemAdministration.framework/Versions/A/SystemAdministration
    0x7fff94b3d000 -     0x7fff94b43fff  com.apple.AOSNotification (1.7.0 - 760.3) <7901B867-60F7-3645-BB3E-18C51A6FBCC6> /System/Library/PrivateFrameworks/AOSNotification.framework/Versions/A/AOSNotification
    0x7fff94b44000 -     0x7fff94b45ff7  libsystem_blocks.dylib (63) <FB856CD1-2AEA-3907-8E9B-1E54B6827F82> /usr/lib/system/libsystem_blocks.dylib
    0x7fff94bae000 -     0x7fff94c37ff7  libsystem_c.dylib (997.1.1) <61833FAA-7281-3FF9-937F-686B6F20427C> /usr/lib/system/libsystem_c.dylib
    0x7fff95087000 -     0x7fff950d5fff  libcorecrypto.dylib (161.1) <F3973C28-14B6-3006-BB2B-00DD7F09ABC7> /usr/lib/system/libcorecrypto.dylib
    0x7fff950d6000 -     0x7fff950e1fff  libkxld.dylib (2422.1.72) <C88EF3E6-B31F-3E12-BE9B-562D912BA733> /usr/lib/system/libkxld.dylib
    0x7fff95101000 -     0x7fff9512dfff  com.apple.CoreServicesInternal (184.8 - 184.8) <707E05AE-DDA8-36FD-B0FF-7F15A061B46A> /System/Library/PrivateFrameworks/CoreServicesInternal.framework/Versions/A/CoreServicesInternal

External Modification Summary:
  Calls made by other processes targeting this process:
    task_for_pid: 6
    thread_create: 0
    thread_set_state: 0
  Calls made by this process:
    task_for_pid: 0
    thread_create: 0
    thread_set_state: 0
  Calls made by all processes on this machine:
    task_for_pid: 1194433
    thread_create: 1
    thread_set_state: 68239

VM Region Summary:
ReadOnly portion of Libraries: Total=274.6M resident=231.0M(84%) swapped_out_or_unallocated=43.5M(16%)
Writable regions: Total=3.9G written=266.3M(7%) resident=350.2M(9%) swapped_out=0K(0%) unallocated=3.5G(91%)
 
REGION TYPE                        VIRTUAL
===========                        =======
CG backing stores                    18.7M
CG image                               92K
CG raster data                       1052K
CG shared images                      204K
CoreImage                               8K
Image IO                               64K
JS JIT generated code               128.3M
JS JIT generated code (reserved)      2.9G        reserved VM address space (unallocated)
JS VM register file                  8192K
JS VM register file (reserved)       4096K        reserved VM address space (unallocated)
JS garbage collector                 2752K
Kernel Alloc Once                       8K
MALLOC                              799.4M
MALLOC (admin)                         32K
Memory Tag 242                         12K
Memory Tag 251                         16K
OpenCL                                 32K
STACK GUARD                          56.1M
Stack                                19.8M
VM_ALLOCATE                          16.4M
WebKit Malloc                        6624K
__DATA                               25.0M
__IMAGE                               528K
__LINKEDIT                           85.3M
__TEXT                              189.3M
__UNICODE                             544K
mapped file                          89.4M
shared memory                           4K
===========                        =======
TOTAL                                 4.3G
TOTAL, minus reserved VM space        1.4G
 

