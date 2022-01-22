#include <bits/stdc++.h>

using namespace std;

char position[10][10], ordi[10][10], jeu[10][10], noms[5]={'A','B','C','D','E'};
/**
 * Position = position des navires du joueurs
 * Ordi = Position des navires de l'ia
 * Jeu = Cadre ennemi du joueur
 */

int sizes[5]={5,4,3,3,2};
string pseudos[5]={"Porte-avion","Croiseur","Contre-torpilleur","Sous-marin","Torpilleur"};
void alea(){
    int x,y,z,index(0),s;bool ok;char a;
	while(index < 5){
		s=sizes[index];
		a=noms[index];
		do{
			ok = true;
			z = rand() % 2 +1; //Verticale ou horizontale
			if(x==1){x = rand() % 10 -(s-1);y = rand() % 10;}
			else{y = rand() % 10 -(s-1);x = rand() % 10;}
			for(int i(0);i<s;i++){ //Deja un bateau ?
				if(z==2){if(ordi[x][y+i] != ' '){ok = false;i+=30;}}
				else{if(ordi[x+i][y] != ' '){ok = false;i+=30;}}
			}
		}while(ok == false);
		for(int i(0);i<s;i++){
			if(z==1){ordi[x+i][y] = a;}
			else{ordi[x][y+i] = a;}
                }
		index++;
	}
}

void navire(int s, char a){ //Entrer des coordon�es des navires du joueur
    int x,y,z, index(0);bool ok;
    do{
        ok = true;
        cout<<endl;
        cout<< "Coordonees : ";
        cin>>x>>y>>z;
        if(index > 3){system("cls");cout<<"Abandonnes t'es vraiment trop con...";}
        if(x>=10-s && z==1 || y>=10){ok = false;cout<<"Bateau hors zone !";}
        if(x>=10 || y>=10-s && z==2){ok = false;cout<<"Bateau hors zone !";}
        if(z!= 1 && z!= 2){ok = false;cout<<"Horizontal ou vertical !";}
        if(ok == true){
            for(int i(0);i<s;i++){
                if(z==2){if(position[x-1][y-1+i] != ' '){cout<<"Il y a deja un bateau !";ok = false;i+=30;}}
                else{if(position[x-1+i][y-1] != ' '){cout<<"Il y a deja un bateau !";ok = false;i+=30;}}
            }
        }
        index++;
    }while(ok == false);
    for(int i(0);i<s;i++){
        if(z==1){position[x-1+i][y-1] = a;}
        else{position[x-1][y-1+i] = a;}
        }
}
void affichage(char positionleau[10][10]){
    cout<<setw(10)<<1;
    for(int i(1);i<10;i++){cout<<setw(5)<<i+1;}
    cout<<endl;
    for(int i(0);i<10;i++){
        cout<<setw(5)<<i+1;
        for(int j(0);j<10;j++){cout<<setw(5)<<positionleau[i][j];}
        cout<<endl;
    }
}
int score(int tab[5]){int x(0);for(int i(0);i<5;i++)x+=tab[i];return x;}

struct coo{int x,y;};
int main()
{
    int x(0), y(0);
    for(int i(0);i<10;i++){for(int j(0);j<10;j++){position[i][j]=' ';jeu[i][j]=' ';ordi[i][j]=' ';}}
    alea();
    cout<<"Les navires doivent etre entre de la maniere suivante : X Y Z"<<endl;
    cout<<"Le z etant le position 1 pour verticale et 2 horizontale"<<endl;
    for(int i(0);i<5;i++){cout<<pseudos[i]<<" :";navire(sizes[i],noms[i]);system("cls");affichage(position);}
    getchar();

    system("cls");
    printf("Jouons ! \n");
    int players[5]={5,4,3,3,2};
    int ia[5]={5,4,3,3,2};
    list<coo> played;
    bool hit=false, ok;//balises d'ia
    while(score(players)!=0 && score(ia)!=0 ){
        if(x!=0 && y!=0){
            if(position[x-1][y-1] != ' '){
            cout<<"Score :"<<score(players)<<" TOUCHE ! ";
            int *temp = new int;
            *temp=position[x-1][y-1]-65;
            cout << pseudos[*temp]<<endl;
            players[*temp]--;
            if(players[*temp] == 0){cout<<"Navire abattu !"<<endl;}
            jeu[x-1][y-1]='T';
            delete temp;
            }
            else{
                cout<<"Score :"<<score(players)<<" A l'eau"<<endl;
                jeu[x-1][y-1]='X';
            }
        }
        affichage(jeu);
        //IA
        coo temp;
        do{
            ok=true;
            temp.x = rand()%10;temp.y = rand()%10;
            for(list<coo>::iterator it= played.begin();it!=played.end();it++){
                    if((*it).x == temp.x && (*it).y == temp.y){ok=false;}
            }
        }while(ok == false);
        played.push_back(temp); //mise en mémoire de la position tiré
        // Annonces
        if(position[temp.x][temp.y] == ' '){
            printf("Score : %d Tire a l'eau pour l'IA ! %d %d \n",score(ia), temp.x+1, temp.y+1);
            position[temp.x][temp.y]='0';
        }else{
            printf("Score : %d L'IA vous a touche ! %d %d \n",score(ia), temp.x +1, temp.y+1);
            position[temp.x][temp.y]='X';hit=true;
        }
        affichage(position);
        do{cout << "Coordonnees : ";cin>>x>>y;}while(x<0 || x>10 || y<0 || y>10 );system("cls");

    }
    return 0;
}
