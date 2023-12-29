#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//1 ci dessous les 2 structures candidats et des administrateurs, aprés j ai créé deux listes chainées pour enrigistrer tout les candidats et les administrateurs 
struct Candidat{
    char nom[20];
    char prenom[20];
    int age;
    char email[145];
    char numero_telephone[8];
    char classe[6];
    char appartenance[20];
    char numero_cin[8];
    int nombre_de_vote;
    int code;
    struct Candidat *suivant;};
struct Administrateur{
    char nom[20];
    char prenom[20];
    char numero_cin[8];
    char poste[20];
    struct Administrateur *suivant;};

struct Candidat*ajouterCandidat(struct Candidat*tete,struct Candidat*candidat){
    candidat->suivant=tete;
    return candidat;}

struct Administrateur*ajouterAdministrateur(struct Administrateur*tete,struct Administrateur*admin){
    admin->suivant=tete;
    return admin;}

void libererCandidats(struct Candidat*tete){
    struct Candidat*actuel=tete;
    struct Candidat*suivant;

    while (actuel!= NULL){
        suivant=actuel->suivant;
        free(actuel);
        actuel=suivant;}}

void libererAdministrateurs(struct Administrateur*tete){
    struct Administrateur*actuel=tete;
    struct Administrateur*suivant;
    while (actuel!=NULL){
        suivant=actuel->suivant;
        free(actuel);
        actuel=suivant;
    }
}

int main(){
    struct Candidat *teteCandidats = NULL;
    struct Administrateur *teteAdmins = NULL;
    int n,m;
    printf("Entrez le nombre de candidats:");
    scanf("%d",&n);
    int nombre_de_vote[n];

    for (int i=0;i<n;i++){
        struct Candidat*candidat=(struct Candidat*)malloc(sizeof(struct Candidat));
        if (candidat==NULL){
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);}
        printf("\nCandidat%d:\n",i+1);
        printf("Nom:");
        scanf("%s",candidat->nom);
        printf("Prénom:");
        scanf("%s",candidat->prenom);
        printf("Age:");
        scanf("%d",&candidat->age);
        printf("Email:");
        scanf("%s",candidat->email);
        printf("Numéro de téléphone:");
        scanf("%s",candidat->numero_telephone);
        printf("Classe:");
        scanf("%s",candidat->classe);
        printf("Appartenance:");
        scanf("%s",candidat->appartenance);
        printf("Numéro de CIN:");
        scanf("%s",candidat->numero_cin);
        printf("\nVous êtes candidat numéro %d:\n", i);
        nombre_de_vote[i]=0;

        teteCandidats=ajouterCandidat(teteCandidats,candidat);}

    printf("\nEntrez le nombre d'administrateurs:");
    scanf("%d",&m);
    char mdp_admin[m][20];
    for (int i=0;i< m;i++){
        struct Administrateur*admin=(struct Administrateur *)malloc(sizeof(struct Administrateur));
        if(admin == NULL){
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);}

        printf("\nAdministrateur %d:\n",i+1);
        printf("Nom:");
        scanf("%s",admin->nom);
        printf("Prénom:");
        scanf("%s", admin->prenom);
        printf("Numéro de CIN:");
        scanf("%s", admin->numero_cin);
        printf("Poste:");
        scanf("%s", admin->poste);
        printf("\nVous êtes admin numéro %d:\n",i);
        printf("Entrez votre mot de passe:");
        scanf("%s",mdp_admin[i]);
        teteAdmins = ajouterAdministrateur(teteAdmins, admin);}
        // chaque administrateurs va avoir un code et il va etre demander de saisir un mot de passe
        //c est la 2eme partie ou les administrateurs vont modifier les nombres de votes de chaque candidats  
    for (int i=0;i<m;i++) {
        char a[20];
        printf("écrivez votre numero\n");
        int l;
        scanf("%d",&l);
        printf("écrivez votre mot de passe s'il te plaît \n");
        scanf("%s",a);
        if (strcmp(mdp_admin[l],a)==0){
            for (int j=0;j<n;j++) {
                int b;
                printf("\ndonnez les nombre de vote de candidat %d:\n",j);
                scanf("%d", &b);
                nombre_de_vote[j]+=b;
            }
        }else{
            printf("mdp incorrect!!!!\n");
        }
    }
    for (int i=0;i<n;i++) {
        struct Candidat*candidat=(struct Candidat*)malloc(sizeof(struct Candidat));
        if (candidat==NULL){
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }

        candidat->nombre_de_vote = nombre_de_vote[i];
        teteCandidats = ajouterCandidat(teteCandidats,candidat);
    }
    //c est la 3eme partie ou je veux parcourir la liste des candidats et trouver le gagnant et apres l afficher 
    struct Candidat*gagnant=teteCandidats;
    struct Candidat *courantCandidat = teteCandidats->suivant;
    while (courantCandidat != NULL) {
        if (courantCandidat->nombre_de_vote>gagnant->nombre_de_vote) {
            gagnant=courantCandidat;}
        courantCandidat=courantCandidat->suivant;}
    printf("\nLe candidat gagnant est:%s %s\n",gagnant->nom, gagnant->prenom);
    printf("Nombre de votes: %d\n",gagnant->nombre_de_vote);
    // 4eme partie: pour gérer les anciennes elections comme il est demandé dans l énoncée, je veux mettre tous les informations de chaque election dans un fichier pour etre enregistrer 

    FILE *fichier = fopen("resultats.txt", "w");
    if (fichier==NULL){
        fprintf(stderr,"Impossible d'ouvrir le fichier pour écriture.\n");
        exit(EXIT_FAILURE);}

    struct Candidat*candidatCourant=teteCandidats;
    while(candidatCourant!=NULL){
        fprintf(fichier,"Candidat:\n");
        fprintf(fichier,"Nom: %s\n", candidatCourant->nom);
        fprintf(fichier,"Prénom: %s\n",candidatCourant->prenom);
               fprintf(fichier,"Nombre de votes: %d\n",candidatCourant->nombre_de_vote);
        fprintf(fichier,"\n");
        candidatCourant = candidatCourant->suivant;}
    struct Administrateur *adminCourant = teteAdmins;
    while (adminCourant!=NULL){
        fprintf(fichier, "Administrateur:\n");
        fprintf(fichier, "Nom: %s\n", adminCourant->nom);
        fprintf(fichier, "Prénom: %s\n", adminCourant->prenom);
        fprintf(fichier, "Poste: %s\n", adminCourant->poste);
        fprintf(fichier, "\n");
        adminCourant = adminCourant->suivant;
    }

    fprintf(fichier, "Gagnant:\n");
    fprintf(fichier, "Nom: %s\n", gagnant->nom);
    fprintf(fichier, "Prénom: %s\n", gagnant->prenom);
    fprintf(fichier, "Nombre de votes: %d\n", gagnant->nombre_de_vote);

    fclose(fichier);

    return 0;
}