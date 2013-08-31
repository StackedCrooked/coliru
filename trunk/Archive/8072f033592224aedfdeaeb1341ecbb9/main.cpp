int execute_command(const command &command,
                    string &string_cout,
                    string &/*string_cerr*/)
{
  // Create pipes for redirected output
  int cout_pipe[2];
  int cerr_pipe[2];
  if(pipe(cout_pipe) || pipe(cerr_pipe))
    throw error("pipe returned an error.");

  int exit_code;
  pid_t pid = fork();
  switch(pid)
  {
    case -1:
      throw error("fork failed.");
    case 0:
      debug(debug::command_exec) << "unix::execute_command::Doing pipe stuff.\n";
      // Close read end in the child
      //close(cout_pipe[0]);
      //close(cout_pipe[0]);
      // Redirect stdout and stderr
      dup2(cout_pipe[1],1);
      dup2(cerr_pipe[1],2);
      // Close unneeded file descriptors
      //close(cout_pipe[1]);
      //close(cerr_pipe[1]);
      // execute child program
      execvp(command.program.c_str(), &command.arguments[0]);
      throw error("execlp failed to execute command: " + command.program + ".");
      break;
    default:
      if(waitpid(pid, &exit_code, 0) != -1)
        debug(debug::command_exec) << "unix::execute_command::Child exited with status " << exit_code << ".\n";
      else
        throw error("waitpid failed.");

      // Close pipes
      close(cout_pipe[1]);
      close(cerr_pipe[1]);
      // Read from pipes
      const size_t buffer_size = 1024;
      string buffer;
      buffer.resize(buffer_size);
      ssize_t bytes_read = read(cout_pipe[0], &buffer[0], buffer_size);
      while(bytes_read > 0)
      {
        string_cout.append(buffer.substr(0, static_cast<size_t>(bytes_read)+1));
        bytes_read = read(cout_pipe[0], &buffer[0], buffer_size);
        if(bytes_read == -1)
          throw error("Failure reading from stdout pipe.");
      }
  }
  return exit_code;