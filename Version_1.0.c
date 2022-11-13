#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char stages[7][55] = {
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\t\\|/\n\t|\t |\n\t|\t/ \\\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\t\\|/\n\t|\t |\n\t|\t/\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\t\\|/\n\t|\t |\n\t|\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\t\\|/\n\t|\n\t|\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\t |\n\t|\n\t|\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\t O\n\t|\n\t|\n\t|\n\t|\n\t-\n",
    "\n\t------------\n\t|\t |\n\t|\n\t|\n\t|\n\t|\n\t|\n\t-\n",
};

void WORD_GUESS(char *word)
{
    srand(time(0));
    char word_list[6][9] = {"BEEPER", "RANDOM", "COMPLETE", "HANGMAN", "COLLEGE", "LOVE"};
    strcpy(word, word_list[(rand()%6)]);
}

int PLAY_GAME(char *Word)
{
    int i, j_word = 0, j_letter = 0, length = strlen(Word), tries = 6, guessed = 0;
    char *word_completion;
    word_completion = (char*) malloc((sizeof(char)*length)+1);
    for (i = 0; i < length; word_completion[i++] = '_');
    word_completion[length] = '\0';

    char *guess, *guessed_letters, **guessed_words;
    guessed_letters = (char*) calloc(length+10, sizeof(char));
    guessed_words = (char**) malloc(sizeof(char));
    for(i = 0; i < 10; guessed_words[i++] = (char*) calloc(length+1, sizeof(char)));

    printf("\nLets Play Hangman...");
    do
    {
        int checker1 = 1, checker2 = 1, checker3 = 1;
        guess = (char*)calloc(length+2,sizeof(char));
        printf("%s", stages[tries]);
        printf("%s\n", word_completion);
        fflush(stdin);
        printf("\nEnter a letter or word: ");
        scanf("%s", guess);
        strupr(guess);

        if (strlen(guess) == length)
        {
            if (!(strcmp(guess, Word)))
            {
                printf("\nCongrats You guessed the word");
                guessed = 1;
                return 0;
            }
            for (i = 0; i < j_word; i++)
                if (!(strcmp(guessed_words[i], guess)))
                {
                    printf("\nYou already guessed the word...");
                    checker1 = 0;
                    break;
                }
            if (checker1)
            {
                printf("\nWrong guess!!");
                strcpy(guessed_words[j_word], guess);
                j_word++, tries--;
                continue;
            }
        } else if (strlen(guess) == 1)
        {
            for (i = 0; i < j_letter; i++)
                if (guess[0] == guessed_letters[i])
                {
                    printf("\nYou already guessed the letter...");
                    checker1 = 0;
                    break;
                }
            if (checker1)
            {
                for (i = 0; i < length; i++)
                {
                    if (guess[0] == Word[i])
                    {
                        printf("\nGood Job '%c' is in the guessed word.", guess[0]);
                        guessed_letters[j_letter] = guess[0];
                        for (int x = 0; x < length; x++)
                            if (guess[0] == Word[x])
                                word_completion[x] = guess[0];
                        printf("%s\n", word_completion);
                        for (int x = 0; x < length; x++)
                            if ('_' == word_completion[x])
                            {
                                checker3 = 0;
                                break;
                            }
                        if (checker3)
                        {
                            printf("\nYou guessed all the letter and the word is completed.");
                            printf("\nThe correct word is %s", Word);
                            return 0;
                        }
                        j_letter++;
                        checker2 = 0;
                        break;
                    }
                }
                if (checker2)
                {
                    printf("\nSorry, guessed letter is not in given word");
                    guessed_letters[j_letter] = guess[0];
                    j_letter++, tries--;
                    continue;
                }
            }
        } else
        {
            printf("\nNOT A VALID GUESS...\n");
        }
        free(guess);
        guess = NULL;
    } while (!(guessed) && tries > 0);
    return 0;
    free(word_completion), free(guessed_words), free(guessed_letters);
    word_completion = NULL, guessed_letters = NULL, guessed_words = NULL;
}

int main()
{
    char word[9], choice;
    do
    {
        WORD_GUESS(word);
        PLAY_GAME(word);
        printf("\nDo you want to continue to new game (Y/N)? ");
        fflush(stdin);
        choice = getchar();
    } while (choice == 'Y' || choice == 'y');
    return 0;
}