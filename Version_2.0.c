#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct Player_Data
{
    char Name[30];
    char *Word;
    char *Word_Completion;
    char *Guess;
    char *Guessed_Letters;
    char **Guessed_Words;
    short int Length;
    short int Tries;
    short int Result;
};

void Assign_Player(int, struct Player_Data*);

int main()
{
    int n;
    struct Player_Data *Players = NULL;
    printf("Enter Number of Players: ");
    scanf("%d", &n);
    fflush(stdin);
    Players = (struct Player_Data *) calloc(n, sizeof(struct Player_Data));
    Assign_Player(n, Players);

}

void Assign_Player(int n, struct Player_Data *Players)
{
    for(int i = 0; i < n; i++)
    {
        srand(time(0));
        printf("\n\tEnter Player %d Name: ", i+1);
        scanf("%s", Players[i].Name);
        fflush(stdin);
        Players[i].Tries = 6, Players[i].Result = 0, Players[i].Length = (rand()%8)+4;

        Players[i].Word = (char*) calloc(n+1, sizeof(char));
        for (int j = 0; j < Players[i].Length; j++)
            *(Players[i].Word + j) = (char)((rand() % 26) + 65);
        *(Players[i].Word + Players[i].Length) = '\0';

        Players[i].Word_Completion = (char*) calloc(n+1, sizeof(char));
        for (int j = 0; j < Players[i].Length; Players[i].Word_Completion[j++] = '_');
        Players[i].Word_Completion[Players[i].Length] = '\0';

        Players[i].Guessed_Letters = (char *) calloc(Players[i].Length+10, sizeof(char));

        Players[i].Guessed_Words = (char **) malloc(sizeof(char));
        for (int j = 0; j < 10; Players[i].Guessed_Words[j++] = (char *) calloc(Players[i].Length+1, sizeof(char)));
    }
}