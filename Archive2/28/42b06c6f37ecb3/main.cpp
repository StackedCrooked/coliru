//
// moon.c
// 'Moon: Remix RPG Adventure' packer - PSX
// (c) CUE 2011
//

#include <stdio.h>
#include <stdlib.h>

#define ELFNAME    "SLPS_010.31"
#define OFFSET     0x04E7A8
#define NUMFILES   195
#define DATNAME    "MOON.DAT"

#define ELFNAMENEW "SLPS_010.31.new"
#define DATNAMENEW "MOON.DAT.new"

#define FOLDERNAME "MOON"
#define SECTORLEN  0x800

#define EXIT(text) { printf(text); exit(-1); }

void  Extract(void);
void  Insert(void);
char *Load(char *filename, int *length);
void  Save(char *filename, char *buffer, int length);
void  Folder(char *path);

int main(int argc, char **argv) {
  printf("\nMOON - (c) CUE 2011\n'Moon: Remix RPG Adventure' packer - PSX\n\n");

  if (argc != 2) EXIT("Usage: MOON -e|-i\n"
                      "\n"
                      "-e ... extrayez tous les fichiers dans '"DATNAME"'/'"ELFNAME"' à '"FOLDERNAME"\\'\n"
                      "-i ... insérez tous les fichiers dans '"FOLDERNAME"\\' à '"DATNAMENEW"'/'"ELFNAMENEW"'\n"
                     );

  if      (!strcmpi(argv[1], "-e")) Extract();
  else if (!strcmpi(argv[1], "-i")) Insert();
  else                              EXIT("Paramètre inconnue\n");

  printf("Terminer\n");

  return(0);
}

void Extract(void) {
  unsigned char *elf, *dat;
  unsigned int  *table;
  unsigned int   elflen, datlen, len, lba;
  unsigned char  filename[256];
  unsigned int   i;

  elf = Load(ELFNAME, &elflen);
  dat = Load(DATNAME, &datlen);

  Folder(FOLDERNAME);

  table = (unsigned int *)(elf + OFFSET);
  for (i = 0; i < NUMFILES; i++) {
    len = *table++;
    lba = *table++;

// VAB files -> VH/VB/SEQ (SEQ in 0048, 0052, 0064, 0078, 0080)

    switch (*(unsigned int *)(dat + lba * SECTORLEN)) {
      case 0x56414270: sprintf(filename, "%s/%04d.VAB", FOLDERNAME, i); break;
      case 0x00000010: sprintf(filename, "%s/%04d.TIM", FOLDERNAME, i); break;
      default:         sprintf(filename, "%s/%04d.BIN", FOLDERNAME, i); break;
    }

    printf("- en cours d'extraction %s\n", filename);

    Save(filename, dat + lba * SECTORLEN, len);
  }
  printf("\n");

  free(dat);
  free(elf);
}

void Insert(void) {
  FILE *fp;
  unsigned char *elf, *dat, *new;
  unsigned int  *table;
  unsigned int   elflen, datlen, len, lba;
  unsigned char  filename[256];
  unsigned int   i, j;

  elf = Load(ELFNAME, &elflen);
  dat = Load(DATNAME, &datlen);

  if ((fp = fopen(DATNAMENEW, "w+b")) == NULL) EXIT("Créez une erreur\n");

  table = (unsigned int *)(elf + OFFSET);
  for (i = 0; i < NUMFILES; i++) {
    len = *table++;
    lba = *table++;

    switch (*(unsigned int *)(dat + lba * SECTORLEN)) {
      case 0x56414270: sprintf(filename, "%s/%04d.VAB", FOLDERNAME, i); break;
      case 0x00000010: sprintf(filename, "%s/%04d.TIM", FOLDERNAME, i); break;
      default:         sprintf(filename, "%s/%04d.BIN", FOLDERNAME, i); break;
    }

    printf("- en cours d'insertion %s\n", filename);

    new = Load(filename, &len);
    *(table-2) = len;
    *(table-1) = ftell(fp) / SECTORLEN;
    if (fwrite(new, 1, len, fp) != len) EXIT("Ecrire une erreur\n");
    free(new);

    len = ((len + SECTORLEN) & -SECTORLEN) - len; // stupid alignment
    if (len) {
      if ((new = (char *) malloc(len)) == NULL) EXIT("Erreur de mémoire\n");
      for (j = 0; j < len; j++) new[j] = 0xFF;
      if (fwrite(new, 1, len, fp) != len) EXIT("Ecrire une erreur\n");
      free(new);
    }
  }
  printf("\n");

  if (fclose(fp) == EOF) EXIT("Annuler une erreur\n");

  Save(ELFNAMENEW, elf, elflen);

  free(dat);
  free(elf);
}

char *Load(char *filename, int *length) {
  FILE *fp;
  int   fs;
  char *fb;

  if ((fp = fopen(filename, "rb")) == NULL) EXIT("Ouvrir une erreur\n");
  fs = filelength(fileno(fp));
  if ((fb = (char *) malloc(fs)) == NULL) EXIT("Erreur de mémoire\n");
  if (fread(fb, 1, fs, fp) != fs) EXIT("Lire une erreur\n");
  if (fclose(fp) == EOF) EXIT("Annuler une erreur\n");

  *length = fs;

  return(fb);
}

void Save(char *filename, char *buffer, int length) {
  FILE *fp;

  if ((fp = fopen(filename, "wb")) == NULL) EXIT("Créer une erreur\n");
  if (fwrite(buffer, 1, length, fp) != length) EXIT("Ecrire une erreur\n");
  if (fclose(fp) == EOF) EXIT("Annuler une erreur\n");
}

void Folder(char *path) {
  int i;

  for (i = 0; path[i]; i++) {
    if ((path[i] == '/') || (path[i] == '\\')) {
      path[i] = 0;
      if (mkdir(path) > 0) EXIT("Erreur de dossier\n");
      path[i] = '/';
    }
  }
  if (mkdir(path) > 0) EXIT("Erreur de dossier\n");
}
return 0;