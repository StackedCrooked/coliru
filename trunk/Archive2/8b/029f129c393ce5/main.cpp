#include <stdio.h>
int main(void)
{
double salaire_horaire; /* Salaire horaire de l’employé. */
int nb_heures; /* Nombre d’heures travaillées. */
/* On saisit le salaire horaire. */
printf("Veuillez entrer le salaire horaire : ");
scanf("%lf", &salaire_horaire);
/* On saisit le nombre d’heures travaillées. */
printf("Veuillez entrer le nombre d’heures de travail : ");
scanf("%i", &nb_heures);
/* On affiche le salaire à verser à l’employé. */
printf("Le salaire à verser est : %.2f$\n",
nb_heures * salaire_horaire);
return 0;
}