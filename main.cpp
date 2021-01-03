#include <iostream>
#include <math.h>
#include <fstream>

#define LICZBA_WEZLOW 7

using namespace std;

struct DrzewoAVL{
    int liczba, wartoscWywazenia;
    DrzewoAVL *left, *right;
};

int *tablicaWezlow;

//funkcja oblicza wysokosc drzewa
int height(DrzewoAVL* wezel){

    if (wezel == NULL) {
        return 0;
    }
    return wezel->wartoscWywazenia;
}

int max(int a, int b){
    if(a>b) {
        return a;
    }
    else{
        return b;
    }
}

DrzewoAVL* singleRightRotate(DrzewoAVL* &t)
{
    if (t->left != NULL) {
        DrzewoAVL* u = t->left;
        t->left = u->right;
        u->right = t;
        t->wartoscWywazenia = max(height(t->left), height(t->right)) + 1;
        u->wartoscWywazenia = max(height(u->left), t->wartoscWywazenia) + 1;
        return u;
    }
    return t;
}

DrzewoAVL* singleLeftRotate(DrzewoAVL* &t)
{
    if (t->right != NULL) {
        DrzewoAVL* u = t->right;
        t->right = u->left;
        u->left = t;
        t->wartoscWywazenia = max(height(t->left), height(t->right)) + 1;
        u->wartoscWywazenia = max(height(t->right), t->wartoscWywazenia) + 1;
        return u;
    }
    return t;
}

DrzewoAVL* doubleLeftRotate(DrzewoAVL* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

DrzewoAVL* doubleRightRotate(DrzewoAVL* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

// Funkcja szuka w drzewie BST węzła o zadanym kluczu. Jeśli go znajdzie, zwraca jego wskazanie. Jeżeli nie, to zwraca wskazanie puste.
DrzewoAVL * szukajWezel ( DrzewoAVL * root, int wartosc ){

    if(root){
        if(wartosc == root->liczba){
            return root;
        }
        else if(wartosc < root->liczba){
            szukajWezel(root->left, wartosc);
        }
        else if(wartosc > root->liczba ){
            szukajWezel(root->right, wartosc);
        }
    }
    else{
        return NULL;
    }
}

//funkcja znajduje najmniejsza wartosc
DrzewoAVL* znajdzNajmniejszy(DrzewoAVL* root){
    if(root){
        if(root->left){
            return znajdzNajmniejszy(root->left);
        }
        else{
            return root;
        }
    }
}

DrzewoAVL* szukajIUsunWezel ( DrzewoAVL * root, int liczba ){

    if(root){
        if(root!=NULL && liczba == root->liczba){
            delete root;
            root=NULL;
            return root;
        }
        else if(root->right!=NULL && liczba != root->right->liczba){
            szukajIUsunWezel(root->right, liczba);
        }
        else if(root->left!=NULL && liczba != root->left->liczba){
            szukajIUsunWezel(root->left, liczba);
        }
    }
    else{
        return NULL;
    }
}

DrzewoAVL* usuwanieWezlaPoWartosc(DrzewoAVL *root, int wartosc){
    DrzewoAVL *tmp;
    if(root==NULL){
        return NULL;
    }
    else if(wartosc < root->liczba){
        root->left=usuwanieWezlaPoWartosc(root->left,wartosc);
    }
    else if(wartosc > root->liczba){
        root->right=usuwanieWezlaPoWartosc(root->right, wartosc);
    }
    else {
        //jesli ma dwoje dzieci
        if (root->left && root->right) {
            tmp = znajdzNajmniejszy(root->right);
//                cout<<"Najmniejsza wartosc w prawm poddrzewie: "<<tmp->liczba<<endl;
            root->liczba = tmp->liczba;
//                szukajIUsunWezel(root->right, tmp->liczba);
            root->right = usuwanieWezlaPoWartosc(root->right, tmp->liczba);
        }
            //jesli ma jedno dziecko albo nie ma dziecka
        else {
            //jesli nie ma lewego dziecka
            if (root->left == NULL) {
                root = root->right;
            }
                //jesli nie ma prawego dziecka
            else if (root->right == NULL) {
                root = root->left;
            }
//                delete tmp;
        }
    }
    if(root==NULL){
        return root;
    }

    root->wartoscWywazenia=max(height(root->left), height(root->right))+1;

    if(height(root->left)-height(root->right)==-2){
        //prawo prawo
        if(height(root->right->right)-height(root->right->left)==1){
            return singleLeftRotate(root);
        }
        else{
            return doubleLeftRotate(root);
        }
    }
    else if(height(root->right)-height(root->left)==2){
        //lewo lewo
        if(height(root->left->left)-height(root->left->left)==1){
            return singleRightRotate(root);
        }
        else{
            return doubleRightRotate(root);
        }
    }
    return root;
}

void inOrder (DrzewoAVL *&liczba){
    if(liczba){
        inOrder(liczba->left);
        cout<<liczba->liczba<<",";
        inOrder(liczba->right);
    }
}

void postOrder (DrzewoAVL *&liczba){
    if(liczba){
        postOrder(liczba->left);
        postOrder(liczba->right);
        cout<<liczba->liczba<<",";
    }
}

void preOrder (DrzewoAVL *&liczba){
    if(liczba){
        cout<<liczba->liczba<<",";
        preOrder(liczba->left);
        preOrder(liczba->right);
    }
}

////funkcja dodajaca elementy drzewa do tablicy
//void dodajDoTablicy(DrzewoAVL *&root){
//    DrzewoAVL* lewo=NULL;
//    DrzewoAVL* prawo=NULL;
//    lewo=root;
//    prawo=root;
//    int i=0;
//
//    tablicaWezlow[i]=root->liczba;
//    i++;
//
//    if (lewo->left != NULL) {
//        tablicaWezlow[i] = lewo->left->liczba;
//        i++;
//    }
//    if (prawo->right != NULL) {
//        tablicaWezlow[i] = prawo->right->liczba;
//        i++;
//    }
//    while(lewo->liczba!=NULL || prawo->liczba!=NULL) {
//
//        if (lewo->left != NULL && lewo->left->left != NULL) {
//            tablicaWezlow[i] = lewo->left->left->liczba;
//            i++;
//        }
//        if (lewo->left != NULL && lewo->left->right != NULL) {
//            tablicaWezlow[i] = lewo->left->right->liczba;
//            i++;
//        }
//        if (lewo->left->right != NULL && lewo->left->left != NULL ||
//            lewo->left->right == NULL && lewo->left->left != NULL ||
//            lewo->left->right != NULL && lewo->left->left == NULL) {
//            lewo = lewo->left;
//        }
//        if (prawo->right != NULL && prawo->right->left != NULL) {
//            tablicaWezlow[i] = prawo->right->left->liczba;
//            i++;
//        }
//        if (prawo->right != NULL && prawo->right->right != NULL) {
//            tablicaWezlow[i] = prawo->right->right->liczba;
//            i++;
//        }
//        if (prawo->right!=NULL &&prawo->right->left != NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left == NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left != NULL && prawo->right->right == NULL) {
//            prawo = prawo->right;
//        } else {
//            if (lewo->left->right == NULL && lewo->left->left == NULL) {
//                break;
//            }
//        }
//    }
//}

//void rysowanieDrzewa(){
//    int k=1;
//    int liczaElemntow=1;
//    string odstep=" ";
//    string odstep2="    ";
//    string odstep3=" ";
//    cout<<odstep2+odstep+odstep<<tablicaWezlow[0]<<endl;
//    cout<<odstep2+odstep3<<"/  \\"<<endl;
//    for(int j=1; j<LICZBA_WEZLOW; j++){
//        if(liczaElemntow==pow(2,k)) {
//            k++;
//            cout <<odstep2<< tablicaWezlow[j];
//            odstep2=odstep2.substr(0,odstep2.length()-2);
//            cout<<endl;
//            for(int i=0; i<liczaElemntow; i++) {
//                cout << odstep2 << "/  \\";
//            }
//            cout<<endl;
//            liczaElemntow=1;
//        }
//        else {
////            if(liczaElemntow==1 && tablicaWezlow[j]>=tablicaWezlow[j-1]){
////                cout <<odstep2+odstep2+odstep2+odstep2+odstep2+odstep2<< tablicaWezlow[j];
////            }
////            if(liczaElemntow==1 && tablicaWezlow[j]<tablicaWezlow[j-1]){
////                if(tablicaWezlow[j]>=tablicaWezlow[j-2]){
////                    cout <<odstep2+odstep2+odstep2+odstep2+odstep2<< tablicaWezlow[j];
////                }
////            }
//            cout <<odstep2<< tablicaWezlow[j];
//            liczaElemntow++;
//        }
//    }
//    cout<<endl;
//}

int wysokosc(DrzewoAVL* wezel){

    if ( !wezel ) {
        return 0;
    }
    return 1 + max( wysokosc( wezel->left ), wysokosc( wezel->right ) );
}

//funkcja dodaje do tablic wyjsciowych kolejne wezel, odleglosci i ukosniki
void rysujWezel( string wyjscie[], string polaczenieWyzej[], DrzewoAVL* wezel, int level, int rozmiar, char polaczenieZnak){

    //sprawdzenie czy drzewo nie jest puste, jesli jest to funkcja sie konczy
    if (!wezel) {
        return;
    }

    rozmiar = max( rozmiar, 0 );

    // zapelnia wszystko po lewej stronie
    if ( wezel->left ){
        //wywolanie rekurencyjne funkcji rysujWezel
        rysujWezel( wyjscie, polaczenieWyzej, wezel->left, level + 1, rozmiar - to_string( wezel->left->liczba ).size() - 2, '/');
        //ustalenie, ktora z podanych liczb jest wieksza i zapisanie jej do zmiennej rozmiar
        rozmiar = max( rozmiar, (int)wyjscie[level+1].size() );
    }

    int space = rozmiar - wyjscie[level].size();

    if ( space > 0 ){
        //dodanie spacji, czyli odleglosci pomiedzy wezlami
        wyjscie[level] += string( space, ' ' );
    }
    //zapisanie do tablicy wyjscie dwoch znakow odstepu oraz aktualnego wezla w postaci stringa
    wyjscie[level] += ' ' + to_string( wezel->liczba) + ' ';

    //warunek sprawdzajacy czy ukosnik zostal juz dodany
    if ( polaczenieZnak == '/' ) {
        rozmiar = wyjscie[level].size() - 1;
    }
    //ustalenie wolnej przestrzeni
    space = rozmiar - polaczenieWyzej[level].size();

    if ( space > 0 ){
        //dodanie do tablicy polaczenieWyzej odstepow
        polaczenieWyzej[level] += string( space, ' ' );
    }
    //dodanie ukosnika
    polaczenieWyzej[level] += polaczenieZnak;

    // uzuepelnia po prawej stronie
    rozmiar = wyjscie[level].size();
    rysujWezel( wyjscie, polaczenieWyzej, wezel->right, level + 1, rozmiar, '\\');
}

//funkcja wyswietla w konsoli drzewo
void draw(DrzewoAVL *&root){

    if(root!=NULL) {
        int h = wysokosc(root);
        string wyjscie[h];
        string polaczeniePowyzej[h];

        rysujWezel(wyjscie, polaczeniePowyzej, root, 0, 0, ' ');

        for (int i = 0; i < h; i++) {
            if (i) {
                cout << polaczeniePowyzej[i] << '\n';
            }
            cout << wyjscie[i] << '\n';
        }
    }
    else{
        cout<<"Drzewo jest puste"<<endl;
    }
}

void wyswietlenieTablicy(int rozmiar){
    cout<<endl<<"wartosc tablicy: "<<endl;
    for(int i=0; i<rozmiar; i++){
        cout<<tablicaWezlow[i]<<",";
    }
}

////funkcja dodajaca elementy drzewa do tablicy
//void dodajDoTablicy(DrzewoAVL *&root, int *tablicaWezlow){
//    DrzewoAVL* lewo=NULL;
//    DrzewoAVL* prawo=NULL;
//    lewo=root;
//    prawo=root;
//    int i=0;
//
//    //dodanie korzenia do tablicy
//    tablicaWezlow[i]=root->liczba;
//    i++;
//
//    if (lewo->left != NULL) {
//        tablicaWezlow[i] = lewo->left->liczba;
//        i++;
//    }
//    if (prawo->right != NULL) {
//        tablicaWezlow[i] = prawo->right->liczba;
//        i++;
//    }
//    while(lewo->liczba!=NULL || prawo->liczba!=NULL) {
//
//        if (lewo->left != NULL && lewo->left->left != NULL) {
//            tablicaWezlow[i] = lewo->left->left->liczba;
//            i++;
//        }
//        if (lewo->left != NULL && lewo->left->right != NULL) {
//            tablicaWezlow[i] = lewo->left->right->liczba;
//            i++;
//        }
//        if (lewo->left!= NULL && lewo->left->right != NULL && lewo->left->left != NULL ||
//            lewo->left!= NULL && lewo->left->right == NULL && lewo->left->left != NULL ||
//            lewo->left!= NULL && lewo->left->right != NULL && lewo->left->left == NULL){
//            lewo = lewo->left;
//        }
//
//        if (prawo->right != NULL && prawo->right->left != NULL) {
//            tablicaWezlow[i] = prawo->right->left->liczba;
//            i++;
//        }
//        if (prawo->right != NULL && prawo->right->right != NULL) {
//            tablicaWezlow[i] = prawo->right->right->liczba;
//            i++;
//        }
//        if (prawo->right!=NULL &&prawo->right->left != NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left == NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left != NULL && prawo->right->right == NULL) {
//            prawo = prawo->right;   //przesuniecie o jeden poziom nizej
//        }
//        else {
//            if (lewo->left==NULL || lewo->left->right == NULL && lewo->left->left == NULL) {
//                break;
//            }
//        }
//        if (lewo->right != NULL && lewo->right->right != NULL) {
//            tablicaWezlow[i] = lewo->right->right->liczba;
//            i++;
//        }
//        if (lewo->right != NULL && lewo->right->left != NULL) {
//            tablicaWezlow[i] = lewo->right->left->liczba;
//            i++;
//        }
//        if (lewo->left != NULL && lewo->left->left != NULL) {
//            tablicaWezlow[i] = lewo->left->left->liczba;
//            i++;
//        }
//        if (lewo->left != NULL && lewo->left->right != NULL) {
//            tablicaWezlow[i] = lewo->left->right->liczba;
//            i++;
//        }
//        if (prawo->left != NULL && prawo->left->right != NULL) {
//            tablicaWezlow[i] = prawo->left->right->liczba;
//            i++;
//        }
//        if (prawo->left != NULL && prawo->left->left != NULL) {
//            tablicaWezlow[i] = prawo->left->left->liczba;
//            i++;
//        }
//
//    }
//}

void zapisDoPliku(int *tablicaWezlow, int ileLiczb){
    fstream plik;
    plik.open("wy.txt", ios::out);
    int wartoscPliku=tablicaWezlow[0];
    int i=1;
    int k=1;
    int liczaElementow=1;
    cout<<endl;
    if(!plik.good()){
        cout<<"Nie uzyskano dostepu do pliku"<<endl;
    }
    else{
        for(int i=1; i<=ileLiczb; i++){
            //sprawdzenie czy w danym poziomie wszytskie wezly juz zostaly zapisane
            if(liczaElementow==pow(2,k)) {
                k++;
                plik<<endl;
            }
            cout<<wartoscPliku<<",";
            plik<<wartoscPliku<<",";
            wartoscPliku=tablicaWezlow[i];
            liczaElementow++;
        }
    }
}


//void zapisDoPliku(){
//    fstream plik;
//    plik.open("wy.txt", ios::out);
//    int wartoscPliku=tablicaWezlow[0];
//    int i=1;
//    int k=1;
//    int liczaElementow=1;
//    cout<<endl;
//    if(!plik.good()){
//        cout<<"Nie uzyskano dostepu do pliku"<<endl;
//    }
//    else{
//        while(wartoscPliku!=NULL){
//
//            if(liczaElementow==pow(2,k)) {
//                k++;
//                plik<<endl;
//            }
////            cout<<"zapisywana do pliku wartosc: "<<wartoscPliku<<endl;
//            plik<<wartoscPliku<<",";
//            wartoscPliku=tablicaWezlow[i];
//            liczaElementow++;
//            i++;
//        }
//    }
//}

DrzewoAVL* insert(int wartosc, DrzewoAVL *&tmp){

    int balans;

    if(tmp==NULL){
        tmp=new DrzewoAVL;
        tmp->left=NULL;
        tmp->right=NULL;
        tmp->liczba=wartosc;
        tmp->wartoscWywazenia=1;
        return tmp;
    }
    else if(wartosc<tmp->liczba){
        tmp->left=insert(wartosc, tmp->left);
//        tmp->left->wartoscWywazenia=1+max(height((tmp->left)), height(tmp->right));
        if(height(tmp->left)-height(tmp->right)==2){
            if(wartosc<tmp->left->liczba){
                tmp=singleRightRotate(tmp);
            }
            else{
                tmp=doubleRightRotate(tmp);
            }
        }
    }
    else if(wartosc>=tmp->liczba){
        tmp->right=insert(wartosc, tmp->right);
//        tmp->right->wartoscWywazenia=1+max(height((tmp->left)), height(tmp->right));
        if(height(tmp->left)-height(tmp->right)==-2){
            if(wartosc>tmp->right->liczba){
                tmp=singleLeftRotate(tmp);
            }
            else{
                tmp=doubleLeftRotate(tmp);
            }
        }
    }

    tmp->wartoscWywazenia=1+max(height(tmp->left), height(tmp->right));
    return tmp;
}

//void insertAVL(DrzewoAVL *&root, int klucz){
//    DrzewoAVL *tmp;
//    DrzewoAVL *wezel;
//    DrzewoAVL *r;
//    bool t;
//
//    wezel=new DrzewoAVL;
//    wezel->left = wezel->right = wezel->up = NULL;
//    wezel->liczba=klucz;
//    wezel->wartoscWywazenia=0;
//
//    //wstawienei wezla do drzewa
//
//    tmp=root;
//
//    if(!tmp){
//        root=wezel;
//    }
//    else{
//        while (true){
//            if(klucz < tmp->liczba){
//                if(!tmp->left){
//                    tmp->left=wezel;
//                    break;
//                }
//                tmp=tmp->left;
//            }
//            else{
//                if(!tmp->right){
//                    tmp->right=wezel;
//                    break;
//                }
//                tmp=tmp->right;
//            }
//        }
//        //ojciec wezla jest tmp;
//        wezel->up=tmp;
//
//        //równowazenie drzewa
//        if(tmp->wartoscWywazenia){
//            tmp->wartoscWywazenia=0;
//        }
//        else{
//            if(tmp->left==wezel){
//                tmp->wartoscWywazenia=1;
//            }
//            else{
//                tmp->wartoscWywazenia=-1;
//            }
//            r=tmp->up;
//
//            t=false;
//
//            while(r){
//                if(r->wartoscWywazenia){
//                    t=true;
//                    break;
//                }
//                if(r->right==tmp){
//                    r->wartoscWywazenia=1;
//                }
//                else{
//                    r->wartoscWywazenia=-1;
//                }
//                tmp=r;
//                r=r->up;
//            }
//            if(t){
//                if(tmp->wartoscWywazenia==1){
//                    if(r->right==tmp){
//                        r->wartoscWywazenia=0;
//                    }
//                    else if(tmp->wartoscWywazenia==-1){
//                        rotacjaLR(root, r);
//                    }
//                    else{
//                       rotacjaLL(root,r);
//                    }
//                }
//                else{
//                    if(r->left==tmp){
//                        r->wartoscWywazenia=0;
//                    }
//                    else if(tmp->wartoscWywazenia==1){
//                        rotacjaRL(root,r);
//                    }
//                    else{
//                        rotacjaRR(root, r);
//                    }
//                }
//            }
//        }
//    }
//}

//funkcja dodajaca elementy drzewa do tablicy
void dodajDoTablicy(DrzewoAVL *&root, int *tablicaWezlow){
    DrzewoAVL* lewo=NULL;
    DrzewoAVL* prawo=NULL;
    int i=0;

    //dodanie korzenia do tablicy
    tablicaWezlow[i]=root->liczba;
    i++;

    if (root->left != NULL) {
        tablicaWezlow[i] = root->left->liczba;
        i++;
    }
    if (root->right != NULL) {
        tablicaWezlow[i] = root->right->liczba;
        i++;
    }

    if (root->left != NULL && root->left->left != NULL) {
        tablicaWezlow[i] = root->left->left->liczba;
        i++;
    }
    if (root->left != NULL && root->left->right != NULL) {
        tablicaWezlow[i] = root->left->right->liczba;
        i++;
    }
    if (root->right != NULL && root->right->left != NULL) {
        tablicaWezlow[i] = root->right->left->liczba;
        i++;
    }
    if (root->right != NULL && root->right->right != NULL) {
        tablicaWezlow[i] = root->right->right->liczba;
        i++;
    }

    lewo=root;
    prawo=root;
    lewo=lewo->left;
    prawo=prawo->right;

    while(lewo->left!=NULL || lewo->right!=NULL || prawo->left!=NULL || prawo->right!=NULL) {

        if (lewo->left != NULL && lewo->left->left != NULL) {
            tablicaWezlow[i] = lewo->left->left->liczba;
            i++;
        }
        if (lewo->left != NULL && lewo->left->right != NULL) {
            tablicaWezlow[i] = lewo->left->right->liczba;
            i++;
        }
        if (lewo->right != NULL && lewo->right->left != NULL) {
            tablicaWezlow[i] = lewo->right->left->liczba;
            i++;
        }
        if (lewo->right != NULL && lewo->right->right != NULL) {
            tablicaWezlow[i] = lewo->right->right->liczba;
            i++;
        }
        if (prawo->left != NULL && prawo->left->left != NULL) {
            tablicaWezlow[i] = prawo->left->left->liczba;
            i++;
        }
        if (prawo->left != NULL && prawo->left->right != NULL) {
            tablicaWezlow[i] = prawo->left->right->liczba;
            i++;
        }
        if (prawo->right != NULL && prawo->right->left != NULL) {
            tablicaWezlow[i] = prawo->right->left->liczba;
            i++;
        }
        if (prawo->right != NULL && prawo->right->right != NULL) {
            tablicaWezlow[i] = prawo->right->right->liczba;
            i++;
        }

//        if (lewo->left!= NULL && lewo->left->right != NULL && lewo->left->left != NULL ||
//            lewo->left!= NULL && lewo->left->right == NULL && lewo->left->left != NULL ||
//            lewo->left!= NULL && lewo->left->right != NULL && lewo->left->left == NULL){
        prawo = prawo->right;
        lewo = lewo->left;
//        }

//        if (prawo->left != NULL && prawo->left->left != NULL) {
//            tablicaWezlow[i] = prawo->left->left->liczba;
//            i++;
//        }
//        if (prawo->left != NULL && prawo->left->right != NULL) {
//            tablicaWezlow[i] = prawo->left->right->liczba;
//            i++;
//        }
//        if (prawo->right != NULL && prawo->right->left != NULL) {
//            tablicaWezlow[i] = prawo->right->left->liczba;
//            i++;
//        }
//        if (prawo->right != NULL && prawo->right->right != NULL) {
//            tablicaWezlow[i] = prawo->right->right->liczba;
//            i++;
//        }


//        if (prawo->right!=NULL &&prawo->right->left != NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left == NULL && prawo->right->right != NULL ||
//            prawo->right!=NULL && prawo->right->left != NULL && prawo->right->right == NULL) {
//            prawo = prawo->right;   //przesuniecie o jeden poziom nizej
//        }
//        else {
//            if (lewo->left==NULL || lewo->left->right == NULL && lewo->left->left == NULL) {
//                break;
//            }
//        }

//        if (lewo->left != NULL && lewo->left->left != NULL) {
//            tablicaWezlow[i] = lewo->left->left->liczba;
//            i++;
//        }
//        if (lewo->left != NULL && lewo->left->right != NULL) {
//            tablicaWezlow[i] = lewo->left->right->liczba;
//            i++;
//        }

    }
}

void dodajTab(DrzewoAVL *&root, int *tablicaWezlow){

}

int main() {

    DrzewoAVL *root=NULL;
    int key;
    char wybor;
    int ileLiczb=0, i=0, liczba, usuwany, wyborKolejnosciWyswietlania;


    cout<<"Wybierz sposob wczytania danych"<<endl<<"\"k\"-klawiatura, \"p\"-plik"<<endl;
    cin>>wybor;

    switch(wybor){
        case 'k':
            cout<<"Ile ma byc liczb w drzewie?"; cin>>ileLiczb;
            cout<<"Podaj liczby jakie chcesz wstawic do drzewa"<<endl;
            for(int i=0; i<ileLiczb; i++) {
                insert(key, root);
                cin>>key;
            }
            cout<<endl<<endl;
            draw(root);
            break;
        case 'p':
            fstream plik;
            plik.open("we.txt", ios::in);
            if(!plik.good()){
                cout<<"blad podczas wczytywania danych z pliku"<<endl;
            }
            else{
                while (!plik.eof()) {
                    plik >> key;
                    insert(key, root);
                    ileLiczb++;
                }
                plik.close();
            }
            draw(root);
            break;
    }

    cout<<"Nacisnij:"<<endl<<"\"d\" jesli chcesz dodac wezel"<<endl<<
        "\"u\" jesli chcesz usuanc wezel"<<endl<<
        "\"q\" jesli zadne z powyzszych"<<endl;
    cin>>wybor;
    switch (wybor) {
        case 'd':
            cout<<"Wprowadz liczbe"<<endl;
            cin>>liczba;
            insert(liczba, root);
            ileLiczb++;
            break;
        case 'u':
            cout<<"Wprowadz numer wezla, ktory chcesz usunac";
            cin>>usuwany;
            usuwanieWezlaPoWartosc(root, usuwany);
            ileLiczb--;
            break;
        case 'q':
            break;
        default:
            cout<<"Podano nieprawidlowa wartosc"<<endl;
    }
    cout<<"Nacisnij: "<<endl<<"\"r\"-jesli drzewao ma zostac narysowane"<<endl<<"\"w\"-jesli wezly moja zostac wypisane w kolejnosci przechodzenia,"<<endl<<
        "\"q\"-wyjscie"<<endl;
    cin>>wybor;

    switch (wybor) {
        case 'r':
            draw(root);
            break;
        case 'w':
            cout<<endl<<"inorder"<<endl;
            inOrder(root);
            cout<<endl<<"postorder"<<endl;
            postOrder(root);
            cout<<endl<<"preorder"<<endl;
            preOrder(root);
//            cout << "Wybierz w jakiej kolejnosci maja zostac wypisane wezly" << endl
//                 << "\"1\"-VLR, \"2\"-LVR, \"3\"-LRV"<<"  ";
//            cin >> wyborKolejnosciWyswietlania;
//            if (wyborKolejnosciWyswietlania == 1) {
//                cout<<"preorder"<<endl;
//                preOrder(root);
//                break;
//            }
//            if (wyborKolejnosciWyswietlania == 2) {
//                cout<<"inorder"<<endl;
//                inOrder(root);
//                break;
//            }
//            if (wyborKolejnosciWyswietlania == 3) {
//                cout<<"postorder"<<endl;
//                postOrder(root);
//                break;
//            }
            break;
        case 'q':
            break;
        default:
            cout << "Podano nieprawidlowa wartosc" << endl;
    }
    tablicaWezlow = new int[ileLiczb];
    dodajDoTablicy(root, tablicaWezlow);

    zapisDoPliku(tablicaWezlow, ileLiczb);
    wyswietlenieTablicy(ileLiczb);

    cout<<endl<<"Czy chcesz usunac Drzewo? "<<endl<<"\"t\" - Tak, \"n\" - Nie ";
    cin>>wybor;

    switch(wybor){
        case 't':
            root=NULL;
            draw(root);
            break;
        case 'n':
            break;
        default:
            cout << "Podano nieprawidlowa wartosc" << endl;
    }

    return 0;
}
