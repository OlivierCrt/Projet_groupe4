#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_process.h"

/**
 * @mainpage Traitement d'image
 *
 * @section intro Introduction
 * Cette partie de code permet de detecter des pixels dans differentes plages de couleurs RGB.    
 * Elle permet aussi de savoir si ces pixels détectés forment des objets et ainsi les utiliser dans les autres partie du pfr1.
 *
 * @section usage Usage
 * - Inclure le header image_process.h dans votre projet.
 * - Utiliser les differentes fonctions de traitement.
 *
 * @section features Fonctionnalités
 * - Detection d'objets de couleurs orange,bleu ou jaune dans une image.
 * - Groupement et manipulation de pixels en utilisant la detection de couleur.
 * - Trouver le centre d'objet dans une image.
 * - Trouver le nombre d'objet dans une image.(1 par couleur)
 * - Trouver le rayon d'un objet.
 * - Ecrire dans un nouveau fichier texte les matrices des plages detectés.
 *
 * @section example Example
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "image_process.h"
 *
 * int main() {
 *     // code
 *     return 0;
 * }
 * @endcode
 */

/**
 * @file
 * @brief Ce fichier rassemble les fonctions concernant la detection d'objet dans une image.
 * 
 * 
*/

/**
 * @defgroup Groupe_pixel
 * @{
*/
/**
 * 
 * 
 *  
 * @brief Structure d'un groupe de pixel.
 * @struct Groupe_Pixel_s
 * 
 */
struct Groupe_Pixel_s {
    int nbpixel_g ;/**<Nombre de pixels correspondant au groupe.  */
    int ** matrice_associe ;/**<Matrice de la taille de l'image de l'entrée standart, composée de 0 et de 1, 1 pour un pixel dans la plage.  */
    char* couleur ;/**<Couleur du groupe.*/
    
};

//Allocation pixel
/**
 * @brief Fonction d'allocation pour un pointeur vers un groupe de pixels.
 * @param nbp Nombre de pixel du groupe.
 * @param matrice_ass_param Tableau à deux dimensions concernant la couleur.
 * @param couleur Chaîne de caractère correspondant à la couleur du groupe.
 * @return Pointeur vers un groupe de pixel.
 * */
Groupe_Pixel_ptr alloc_Groupe_Pixel(int nbp , int** matrice_ass_param,char * couleur){
    Groupe_Pixel_ptr res = malloc(sizeof(struct Groupe_Pixel_s)) ;
    res->nbpixel_g = nbp ;
    res->matrice_associe = matrice_ass_param ;
    res->couleur = couleur ;
    return res ;
}



//Detection de plage de couleur

/**
 * @brief Fonction de detection de pixel dans la plage de couleur Jaune , utilisation de seuil RGB avec valeur min et max.
 * @param matriceR Tableau à deux dimension correspondant à la matrice initiale du Rouge.
 * @param matriceG Tableau à deux dimension correspondant à la matrice initiale du Vert.
 * @param matriceB Tableau à deux dimension correspondant à la matrice initiale du Bleu.
 * @param hauteur Hauteur de l'image iniatiale/tableau.
 * @param largeur Largeur de l'image initaiale/tableau.
 * @return Pointeur vers un groupe de pixel, on ne peut pas encore dissocier le groupe d'un objet @see isObjet()
*/

Groupe_Pixel_ptr detecterPixelsJaune(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }






    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 200;
    int seuilRougeMax = 255;
    int seuilVertMin = 180;
    int seuilVertMax = 255;
    int seuilBleuMin = 0;
    int seuilBleuMax = 100;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }

    // si nbpixel trop élevé dire que ce n est pas un objet mais un arriere plan sinon dfs et regroupement 
    




    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Jaune"));
}
Groupe_Pixel_ptr detecterPixelsBleu(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }
    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 0;
    int seuilRougeMax = 10;
    int seuilVertMin = 21;
    int seuilVertMax = 94;
    int seuilBleuMin = 48;
    int seuilBleuMax = 255;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }
    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Bleu"));
}
Groupe_Pixel_ptr detecterPixelsOrange(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }
    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 136;
    int seuilRougeMax = 250;
    int seuilVertMin = 27;
    int seuilVertMax = 56;
    int seuilBleuMin = 0;
    int seuilBleuMax = 10;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }
    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Orange"));
}
/**@}*/


// Fonctions de renvoi pour l'intégration
/**
 * @defgroup Fonctions_utiles
 * @{
*/
/**
 * @brief Fonction pour trouver le milieu d'un objet, ne donne le milieu uniquement si le groupe est un objet @see isObjet().
 *
 * @param groupe Pointeur vers le groupe de pixels.
 * @param largeur Largeur de l'image.
 * @param hauteur Hauteur de l'image.
 * @return Tableau d'entiers contenant les coordonnées du milieu [hauteur, largeur].Vide si impossible.
 */
int * trouver_milieu(Groupe_Pixel_ptr groupe, int largeur , int hauteur){//null si pas un objet
    int * res =malloc(2*sizeof(int));
    if (!isObjet(groupe)){
        return(res);//liste 
    }
    int imin_h=60000 ;
    int jmin_l = 60000;
    int imax_h,jmax_l ;
    for (int i =0 ; i<hauteur ; i++){
        for(int j = 0 ; j<largeur ; j++){
            if (groupe->matrice_associe[i][j] == 1 && imin_h> i){
                imin_h = i ;
            }
            if (groupe->matrice_associe[i][j] == 1){
                imax_h =i;
            }
        }
    }

    for (int j = 0 ; j<largeur ; j++){
        for(int i =0 ; i<hauteur ; i++){
            if (groupe->matrice_associe[i][j] == 1 && jmin_l> j){
                jmin_l = j ;
            }
            if (groupe->matrice_associe[i][j] == 1){
                jmax_l =j;
            }
        }
    }
    res[0] =jmin_l+(jmax_l-jmin_l)/2 ; //hauteur
    res[1] = imin_h+(imax_h-imin_h)/2 ;
    if(groupe->couleur == "Bleu"){
        printf("Le milieu de l'objet \x1B[34m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);

    }
    else if(groupe->couleur == "Jaune"){
        printf("Le milieu de l'objet \x1B[33m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);
    }
    else{
        printf("Le milieu de l'objet \x1B[38;5;208m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);
    }
    return (res);

}
/**
 * @brief Fonction de calcul de rayon d'un objet .
 * @param objet Objet de couleur.La fonction effectue un controle pour verifier que c'est bien un objet.
 * @param largeur Largeur de l'image.
 * @param hauteur Hauteur de l'image.
 * @return Entier correspondant au rayon.-1 si impossible.
*/
int  trouver_rayon(Groupe_Pixel_ptr objet, int largeur , int hauteur){
    if (!isObjet(objet)){
        return(-1);
    }
    int imin_h=60000 ;
    int jmin_l = 60000;
    int imax_h,jmax_l ;
    for (int i =0 ; i<hauteur ; i++){
        for(int j = 0 ; j<largeur ; j++){
            if (objet->matrice_associe[i][j] == 1 && imin_h> i){
                imin_h = i ;
            }
            if (objet->matrice_associe[i][j] == 1){
                imax_h =i;
            }
        }
    }
    for (int j = 0 ; j<largeur ; j++){
        for(int i =0 ; i<hauteur ; i++){
            if (objet->matrice_associe[i][j] == 1 && jmin_l> j){
                jmin_l = j ;
            }
            if (objet->matrice_associe[i][j] == 1){
                jmax_l =j;
            }
        }
    }
    int maxres = jmax_l-jmin_l ;
    if ((imax_h-imin_h)>maxres){
        maxres = imax_h-imin_h ;
    }

    if(objet->couleur == "Bleu"){
        printf("Le rayon de l'objet de couleur \x1B[34m%s\x1B[0m est : %d\n",objet->couleur,maxres);

    }
    else if (objet->couleur == "Jaune"){
        printf("Le rayon de l'objet de couleur \x1B[33m%s\x1B[0m est : %d\n",objet->couleur,maxres);

    }
    else {
        printf("Le rayon de l'objet de couleur \x1B[38;5;208m%s\x1B[0m est : %d\n",objet->couleur,maxres);
        
    }
    
    return maxres;





}
/**
 * @brief Fonction getter de la couleur d'un groupe de pixel.
 * @param groupe Groupe de pixel.
 * @return Chaîne de caractère correspondant à la couleur du groupe.
 * 
*/
char* get_couleur(Groupe_Pixel_ptr groupe){
    return(groupe->couleur);

}
/**
 * @brief Fonction pour connaitre si un groupe de pixel est un objet.
 * @return Booleen.
*/
bool isObjet (Groupe_Pixel_ptr groupe){
    return (groupe->nbpixel_g>30 );

}
/**
 * @}
*/

//Pas demandé dans le dossier mais pratique pour visualiser les plages detectées en noir et blanc
/**
 * @defgroup Hors_spec
 * @{
*/
/**
 * @brief Fonction d'écriture dans un nouveau fichier texte une image en noir et blanc correspondant à une couleur.
 * @param groupePixel Groupe de pixel de couleur.
 * @param hauteur Hauteur de l'image.
 * @param largeur Largeur de l'image.
 * @param nomfichier Nom du fichier avec extension.(.dat)
*/
void ecrireMatriceDansFichier(Groupe_Pixel_ptr groupePixel, int hauteur, int largeur,char*nomfichier) {
    FILE *fichier = fopen(nomfichier, "w"); // Ouvre un fichier en écriture

    if (fichier == NULL || !isObjet(groupePixel)) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(fichier,"%d  ",hauteur);
    fprintf(fichier,"%d  ",largeur);
    fprintf(fichier,"%d\n",3);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fprintf(fichier, "%d ", groupePixel->matrice_associe[i][j]); // Écrit la valeur dans le fichier
        }
        fprintf(fichier, "\n"); // Passage à la ligne suivante dans le fichier
    }

    fclose(fichier); // Ferme le fichier
}
/**
 * @brief Fonction de parcours en profondeur ( Deep First Search) récursive.
 * @param matrice_p Matrice à explorer.( Avec : matrice[hauteur][largeur]).
 * @param hauteur Hauteur de l'image/matrice.
 * @param largeur Largeur de l'image/matrice.
 * @param deb_i Indice de la hauteur du début du dfs.
 * @param deb_j Indice de la largeur du début du dfs.
 * @param visite Matrice des élements deja visité, marqués par un 1.
*/
int dfs (int ** matrice_p , int hauteur , int largeur , int deb_i , int deb_j ,int ** visite){
    if (deb_i < 0 || deb_i >= hauteur || deb_j < 0 || deb_j >= largeur || visite[deb_i][deb_j] == 1 || matrice_p[deb_i][deb_j] == 0) {
        // Conditions d'arrêt (coordonnées invalides, déjà visité, ou pixel non marqué)
        return 0;
    }
    visite[deb_i][deb_j] = 1 ;
    int taille = 1 ;

    //parcours voisins

    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i +1 , deb_j , visite) ;
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i -1 , deb_j , visite);
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i , deb_j+1 , visite);
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i  , deb_j-1 , visite);
    return taille ;


}
/**
 * @brief Fonction qui repère et isole le plus gros groupe de pixel dans une image. C'est en fait une fonction d'elimination de bruit. 
 * @param matrice Tableau d'entier de 0 et de 1 correspondant à une couleur. Le traitement s'effectue sur cette matrice.
 * @param hauteur Hauteur de l'image/matrice.
 * @param largeur Largeur de l'image/matrice.
 * 
*/
void trouverLePlusGros (int ** matrice , int hauteur, int largeur){
    int ** visite = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
    
        visite[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            visite[i][j] = 0 ;
        }
    }
    int taillemax = 0 ;
    int lpg_deb_i = -1 ;
    int lpg_deb_j =-1 ;


    for (int i =0 ; i<hauteur ; i++){
        for(int j =0 ; j<largeur ; j++){
            if (matrice[i][j] == 1 && visite[i][j] == 0){
                int taille_actuelle = dfs(matrice , hauteur, largeur,i , j ,visite);
                if (taille_actuelle > taillemax){
                    taillemax = taille_actuelle ;
                    lpg_deb_i = i ;
                    lpg_deb_j = j ;
                }
            }
        }
    }
    //maj de la matrice et garder lpg
    for (int i=0; i<hauteur ; i++){
        for(int j =0 ; j<largeur ; j++){
            if (matrice[i][j] == 1 && (i!= lpg_deb_i ||j!= lpg_deb_j)){
                matrice[i][j] = 0 ;
            }
        }
    }








}
/**
 *  @}
*/
void main_it(int *rayon_bleu, int *rayon_jaune, int *rayon_orange,int **milieu_bleu, int **milieu_jaune, int **milieu_orange){

int largeur,hauteur,nbcompo ;
scanf("%d",&largeur) ;
scanf("%d",&hauteur) ;
scanf ("%d", &nbcompo) ;
printf("\n\n");
printf("\x1B[1m---------------TRAITEMENT D'IMAGE--------------\x1B[0m\n\n");
printf("\x1B[4mCARACTERISTIQUES IMAGE:\x1B[0m\n\n");
printf("Largeur : %d\n",largeur);
printf("Hauteur : %d\n",hauteur);
printf("Nbcompo : %d\n",nbcompo);
printf("\n");
//Matrice initiales
int ** matrice_init_red =malloc(hauteur*sizeof(int*));
int ** matrice_init_green =malloc(hauteur*sizeof(int*));
int ** matrice_init_blue =malloc(hauteur*sizeof(int*));
//Allocations
for (int p = 0; p < hauteur; p++) {
        matrice_init_red[p] = malloc(largeur * sizeof(int));
        matrice_init_green[p] = malloc(largeur * sizeof(int));
        matrice_init_blue[p] = malloc(largeur * sizeof(int));
    }
//R
for (int i=0 ;i<hauteur ; i++){
    for(int j=0 ; j<largeur ; j++){
        scanf("%d",&matrice_init_red[i][j]);
    }
}
//G
int x,y ;
for (x=0 ;x<hauteur ; x++){
    for(y=0 ; y<largeur ; y++){
        scanf("%d",&matrice_init_green[x][y]);
    }
}
//B
int a,b ;
for (a=0 ;a<hauteur ; a++){
    for(b=0 ; b<largeur ; b++){
        scanf("%d",&matrice_init_blue[a][b]);
    }
}
Groupe_Pixel_ptr objet_poss_bleu = detecterPixelsBleu(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_jaune = detecterPixelsJaune(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_Orange = detecterPixelsOrange(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
//dfs et lpg
//trouverLePlusGros(objet_poss_Orange->matrice_associe ,hauteur , largeur );
//dETECTION
printf("\x1B[4mDETECTIONS DES OBJETS :\x1B[0m\n\n");
if(isObjet(objet_poss_bleu)){printf("Objet de couleur \x1B[34mBleu\x1B[0m détecté!\n");}
if(isObjet(objet_poss_jaune)){printf("Objet de couleur \x1B[33mJaune\x1B[0m détecté!\n");}
if(isObjet(objet_poss_Orange)){printf("Objet de couleur \x1B[38;5;208mOrange\x1B[0m détecté!\n");}
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mAucun objet détecté!\x1B[0m\n");
}
//Milieux
printf("\n\x1B[4mCALCULS DES MILIEUX :\x1B[0m\n\n");
*milieu_bleu = trouver_milieu(objet_poss_bleu, largeur, hauteur);
*milieu_jaune = trouver_milieu(objet_poss_jaune, largeur, hauteur);
*milieu_orange = trouver_milieu(objet_poss_Orange, largeur, hauteur);
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mCalcul des milieux impossible il n'y a pas d'objet!\x1B[0m\n");
}
printf("\n\x1B[4mRAYON DES OBJETS\x1B[0m\n\n");
//rayons
*rayon_bleu = trouver_rayon(objet_poss_bleu, largeur, hauteur);
*rayon_jaune = trouver_rayon(objet_poss_jaune, largeur, hauteur);
*rayon_orange = trouver_rayon(objet_poss_Orange, largeur, hauteur);
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mCalcul des rayons impossible il n'y a pas d'objet!\x1B[0m\n");
}
printf("-----------------------------------------------\n\n\n\n");
//Fichier txt avec les matrices des plages de la forme vue en TP, j'utilise le script de M.Ferrané afin de les visualiser par la suite
if (isObjet(objet_poss_bleu))  { ecrireMatriceDansFichier(objet_poss_bleu,hauteur,largeur,"obj_bleu.dat"); };

if (isObjet(objet_poss_jaune))  { ecrireMatriceDansFichier(objet_poss_jaune,hauteur,largeur,"obj_jaune.dat"); };

if (isObjet(objet_poss_Orange))  { ecrireMatriceDansFichier(objet_poss_Orange,hauteur,largeur,"obj_orange.dat"); };

return;
}



int main() {
    // Déclaration des variables pour les rayons et milieux
    int rayon_bleu, rayon_jaune, rayon_orange;//-1 si pas de rayon
    int *milieu_bleu, *milieu_jaune, *milieu_orange;//liste vide si existe pas
    main_it(&rayon_bleu, &rayon_jaune, &rayon_orange,&milieu_bleu, &milieu_jaune, &milieu_orange);


    return 0;
}
