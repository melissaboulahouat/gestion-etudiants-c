#include <stdio.h>
#include <string.h>

#define MAX_ETUDIANTS 50   /* nombre maximum d'étudiants */
#define NB_NOTES 3         /* nombre de notes par étudiant */

/* Structure qui représente un étudiant */
struct Etudiant {
    char nom[30];
    char prenom[30];
    int matricule;
    float notes[NB_NOTES];
};

/* Calcul de la moyenne d'un étudiant */
float moyenne(struct Etudiant e) {
    float somme = 0;
    int i;

    for (i = 0; i < NB_NOTES; i++) {
        somme = somme + e.notes[i];
    }
    return somme / NB_NOTES;
}

/* Vérifie si un matricule existe déjà */
/* Retourne la position de l'étudiant, ou -1 s'il n'existe pas */
int trouver(struct Etudiant tab[], int nb, int matricule) {
    int i;

    for (i = 0; i < nb; i++) {
        if (tab[i].matricule == matricule) {
            return i;
        }
    }
    return -1;
}

/* 1. Ajouter un étudiant */
void ajouter(struct Etudiant tab[], int *nb) {
    struct Etudiant e;
    int i;

    if (*nb >= MAX_ETUDIANTS) {
        printf("\nLa liste est pleine. \n");
        return;
    }

    printf("\n--- Ajout d'un etudiant ---\n");
    printf("Nom : ");
    scanf("%s", e.nom);
    printf("Prenom : ");
    scanf("%s", e.prenom);
    printf("Matricule : ");
    scanf("%d", &e.matricule);

    /* On refuse deux étudiants avec le même matricule */
    if (trouver(tab, *nb, e.matricule) != -1) {
        printf("\nCe matricule existe deja .\n");
        return;
    }

    /* Saisir les trois notes */
    for (i = 0; i < NB_NOTES; i++) {
        do {
            printf("Note %d (sur 20) : ", i + 1);
            scanf("%f", &e.notes[i]);

            /* Verifier que la note est entre 0 et 20 */
            if (e.notes[i] < 0 || e.notes[i] > 20) {
                printf("Note invalide , Entrez une note entre 0 et 20.\n");
            }

        } while (e.notes[i] < 0 || e.notes[i] > 20);
    }

    tab[*nb] = e;   /* on place l'étudiant dans le tableau */
    *nb = *nb + 1;  /* on augmente le nombre d'étudiants */

    printf("\nEtudiant ajoute avec succes.\n");
}

/* 2. Afficher la liste des étudiants */
void liste(struct Etudiant tab[], int nb) {
    int i;

    if (nb == 0) {
        printf("\nAucun etudiant enregistre.\n");
        return;
    }

    printf("\n--- Liste des etudiants ---\n");
    for (i = 0; i < nb; i++) {
        printf("%d. %s %s (Matricule : %d)\n",
               i + 1, tab[i].nom, tab[i].prenom, tab[i].matricule);
    }
}

/* 3. Rechercher un étudiant par matricule */
void chercher(struct Etudiant tab[], int nb) {
    int matricule, pos, i;

    printf("\nMatricule a rechercher : ");
    scanf("%d", &matricule);

    pos = trouver(tab, nb, matricule);

    if (pos == -1) {
        printf("Aucun etudiant avec ce matricule.\n");
    } else {
        printf("\nEtudiant trouve :\n");
        printf("Nom : %s\n", tab[pos].nom);
        printf("Prenom : %s\n", tab[pos].prenom);
        printf("Matricule : %d\n", tab[pos].matricule);
        for (i = 0; i < NB_NOTES; i++) {
            printf("Note %d : %.2f\n", i + 1, tab[pos].notes[i]);
        }
    }
}

/* 4. Afficher la moyenne d'un étudiant */
void moy(struct Etudiant tab[], int nb) {
    int matricule, pos;

    printf("\nMatricule de l'etudiant : ");
    scanf("%d", &matricule);

    pos = trouver(tab, nb, matricule);

    if (pos == -1) {
        printf("Aucun etudiant avec ce matricule.\n");
    } else {
        printf("Moyenne de %s %s : %.2f / 20\n",
               tab[pos].nom, tab[pos].prenom, moyenne(tab[pos]));
    }
}

/* 5. Afficher les résultats */
void resultats(struct Etudiant tab[], int nb) {
    int i;
    float m;

    if (nb == 0) {
        printf("\nAucun resultat a afficher.\n");
        return;
    }

    printf("\n--- Resultats ---\n");
    for (i = 0; i < nb; i++) {
        m = moyenne(tab[i]);
        printf("%s %s : %.2f / 20 -> ", tab[i].nom, tab[i].prenom, m);

        if (m >= 10) {
            printf("Admis\n");
        } else {
            printf("Ajourne\n");
        }
    }
}

/* Programme principal */
int main() {
    struct Etudiant etudiants[MAX_ETUDIANTS];
    int nbEtudiants = 0;
    int choix;

    do {
        printf("\n===== GESTION DES ETUDIANTS =====\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste des etudiants\n");
        printf("3. Rechercher un etudiant par matricule\n");
        printf("4. Calculer la moyenne d'un etudiant\n");
        printf("5. Afficher les resultats et quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter(etudiants, &nbEtudiants);
                break;
            case 2:
                liste(etudiants, nbEtudiants);
                break;
            case 3:
                chercher(etudiants, nbEtudiants);
                break;
            case 4:
                moy(etudiants, nbEtudiants);
                break;
            case 5:
                resultats(etudiants, nbEtudiants);
                printf("\nAu revoir !\n");
                break;
            default:
                printf("\nChoix invalide, reessayez.\n");
        }
    } while (choix != 5);

    return 0;
}
