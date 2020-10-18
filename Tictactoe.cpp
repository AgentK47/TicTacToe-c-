#include <iostream>

using namespace std;

class jeux//classe tictactoe
{
private:int T[9];//declaration de tableau de 9 cases
public:
	jeux()
	{//initialisation du jeu
		 T[0] = 0;
		 T[1] = 0;
		 T[2] = 0;
		 T[3] = 0;
		 T[4] = 0;
		 T[5] = 0;
		 T[6] = 0;
		 T[7] = 0;
		 T[8] = 0;
	}
	char corresp(int i);//correspondre les numeros au 'X' et au 'O'
	void affichage();//affichage du jeu
	int gagne();//verifie si le joueur ou l'ordinateur a gagné
	int minmax(int player);//fonction minmax
	void computerMove();//coup de l'ordinateur
	void playerMove(); //coup du joueur
	void jouer();
};

char jeux::corresp(int x)
{  
	int i=T[x];
	
	switch(i) 
	{
        case -1:
            return 'X';//attribut X aux cases -1
        case 0:
			return NULL ;//retour null;
        case 1:
            return 'O';//attribut O aux cases 1
    }
}

void jeux::affichage()//affiche le jeu
{
	cout<<corresp(0)<<" | "<<corresp(1)<<" | "<<corresp(2)<<endl;
	cout<<"--+---+--"<<endl;
	cout<<corresp(3)<<" | "<<corresp(4)<<" | "<<corresp(5)<<endl;
	cout<<"--+---+--"<<endl;
	cout<<corresp(6)<<" | "<<corresp(7)<<" | "<<corresp(8)<<endl;
}

int jeux::gagne()//verifie si l'un des joueurs a gagné
{
	int wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};//les états de solutions possibles 
	for(int i = 0; i < 8; ++i) 
	{
        if(T[wins[i][0]] != 0 && T[wins[i][0]] == T[wins[i][1]] && T[wins[i][0]] == T[wins[i][2]])
            return T[wins[i][2]];//retourne le joueur gagnant si l'un des états est atteint
    }
    return 0;//retourne 0 si aucun état final atteint
}

int jeux::minmax(int joueur) //fonction minmax
{
	int gagnant = gagne(); 
    if(gagnant != 0) return gagnant*joueur;
	int move = -1;
    int score = -2;
    
    for(int i = 0; i < 9; i++) //pour tous les noeuds 
	{
        if(T[i] == 0) //si vide
		{
            T[i] = joueur;//on essaie de positionner
            int thisScore = -minmax(joueur*-1);
            if(thisScore > score) //minimiser
			{
                score = thisScore;
                move = i;
            }//Prendre celui qui n'avantage pas l'adversaire
            T[i] = 0;//Remettre la case vide
        }
    }
    if(move == -1) return 0;
    return score;
}

void jeux::computerMove()
{
	int move = -1;
    int score = -2;
    for(int i = 0; i < 9; i++) //parcourir tous les noeuds
	{
        if(T[i] == 0) //si vide
		{
            T[i] = 1;//positionner pour vérifier l'éficacité
            int tempScore = -minmax(-1); //appelle de minmax
            T[i] = 0;
            if(tempScore > score) //maximiser
			{
                score = tempScore;
                move = i;
            }
        }

    }
    //retourne un score basé sur minmax tree .
    T[move] = 1;
}
void jeux::playerMove()//fonction de l'adversaire
{
	int move = 0;
    do 
	{
        cout<<"\nChoix ([0..8]): ";
        cin>>move;//position du joueur
        cout<<endl;
    } while ((move >= 9 || move < 0) && T[move] == 0); //repeter tant qu'on a pas terminé
    T[move] = -1;//adversaire joue
}
void jeux::jouer()
{
    cout<<"Ordinateur: O, Vous: X\n jouer (1)er ou (2)eme ? "<<endl;
    int joueur=0;
    cin>>joueur;//decide quel joueur commence
    cout<<endl;
    for(int tour = 0; tour < 9 && gagne() == 0; tour++) //parcour les cases et verifie si un joueur a gagné
	{
        if((tour+joueur) % 2 == 0)//determine le tour de l'ordinateur
            computerMove();
        else 
		{
            affichage();//affiche les cases
            playerMove();//le tour du joueur
        }
    }
    switch(gagne())
	{
        case 0://retourne 0 pour un match nul
			affichage();
            cout<<"Match Nul."<<endl;
            break;
        case 1://retourne 1 si l ordinateur gagne
            affichage();
            cout<<"Vous avez perdu."<<endl;
            break;
        case -1://retourne -1 si le joueur gagne
			affichage();
            cout<<"Vous avez gagne. Incroyable!"<<endl;
            break;
    }
}

int main()
{
	jeux j;
	j.jouer();

	return 0;
}