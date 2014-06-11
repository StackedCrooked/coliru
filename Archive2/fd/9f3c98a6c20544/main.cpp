bool found = false;
string portName = "testing:";
RegistryKey PrinterPort = Registry.LocalMachine.OpenSubKey("SYSTEM\\ControlSet001\\Control\\Print\\Monitors\\Redirected Port\\Ports\\"+portName, true);
if (PrinterPort != null)
{
    PrinterPort.SetValue(@"Arguments", "@C:\\gs\\pdfwrite.txt -sOutputFile=\"d:\\hello.pdf\" -c .setpdfwrite -f -");
    PrinterPort.SetValue(@"Command", "c:\\gs\\bin\\gswin32c.exe");
    PrinterPort.SetValue(@"Delay", 0x12c);
    PrinterPort.SetValue(@"LogFileDebug", 0x0);
    PrinterPort.SetValue(@"LogFileName", "");
    PrinterPort.SetValue(@"LogFileUse", 0x0);
    PrinterPort.SetValue(@"Output", 0x0);
    PrinterPort.SetValue(@"Printer", "Send To Cool Printer");
    PrinterPort.SetValue(@"PrintError", 0x0);
    PrinterPort.SetValue(@"RunUser", 0x0);
    PrinterPort.SetValue(@"ShowWindow", 0x0);
    PrinterPort.Close();
}