//in your header somewhere
typedef bool gboolean;
typedef char gchar;
enum GSpawnFlags {G_SPAWN_SEARCH_PATH};
typedef void* gpointer;
typedef int(*GSpawnChildSetupFunc)(gpointer);
typedef int GPid;
typedef int GError;
#define NULL 0
gboolean g_spawn_async  (const gchar *working_directory,
                         gchar **argv,
                         gchar **envp,
                         GSpawnFlags flags,
                         GSpawnChildSetupFunc child_setup,
                         gpointer user_data,
                         GPid *child_pid,
                         GError **error)
{}


//THESE VARIABLES ARE COMPLETELY IGNORED
//THEY ARE LITTLE MORE THAN DOCUMENTATION
const gchar *working_directory;
gchar **argv;
gchar **envp;
GSpawnFlags flags;
GSpawnChildSetupFunc child_setup;
gpointer user_data;
GPid *child_pid;
GError **error;

//below here is real stuff

int main() {
    gchar **new_argv = NULL;
    
    g_spawn_async(NULL, new_argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
    
    g_spawn_async(working_directory=NULL,
              argv=new_argv,
              envp=NULL,
              flags=G_SPAWN_SEARCH_PATH,
              child_setup=NULL,
              user_data=NULL,
              child_pid=NULL,
              error=NULL);
}