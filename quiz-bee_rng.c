/*

Task #4
Quiz Bee
[A]EASY - 3pts total. 3 questions total??? or 1 points each???
[B]Average - 5pts total.
[C]Difficult - 10pts each. Identification lol
[D]EXIT

*/


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

void cli_menu(int choice, int score, bool qdone[]){
    system("cls");
    printf("\033[90;1mcontrols:(w,s),(%c,%c),(spacebar, enter) Task#4 Quiz Bee\n",24, 25);
    printf("choice: %d Score: %d / 48\n\033[0m", choice, score);
    printf("   1.[A] \033[32;4mEASY\033[0m - 1pts each\n");
    printf("   2.[B] \033[34;4mAverage\033[0m - 5pts each\n");
    printf("   3.[C] \033[31;4mDifficult\033[0m - 10pts each\n");
    printf("   4.[D] EXIT\n");
    printf("   5. Show previous users\n---------------------------------\n\033[s");
    printf("\033[90mqdone[i]:{ ");
    for (int i = 0; i < 8; i++){printf("%d,", qdone[i]);}printf("%d }\n", qdone[8]);
}

int movement(int choice, int *score){
    
char key;

    while(1){ 
        printf("\033[2;8H %d\033[2;17H %d\033[%dH-> ",choice, *score, choice + 2);
         key = getch();
         printf("\033[%dH   ",choice + 2);
        if (key == 'w' && choice > 1 || key == 72 && choice > 1 ) {choice--;} 
        else if (key == 's' && choice < 5 || key == 80 && choice < 5 ) {choice++;}
            else if (key >= '1' && key <= '5') { choice = key - '0'; }
            else if (key >= 97 && key <= 100) {choice = key - 96; }
        else if (key == '\r'|| key == ' ') { break;}
    }

return choice;
}

int movementchoice(int choice){
    
char key;

    while(1){ 
        printf("\033[%dH-> ", choice + 2);
         key = getch();
         printf("\033[%dH   ",choice + 2);
        if (key == 'w' && choice > 1 || key == 72 && choice > 1 ) {choice--;} 
        else if (key == 's' && choice < 4 || key == 80 && choice < 4 ) {choice++;}
            else if (key >= '1' && key <= '4'){ choice = key - '0'; }
            else if (key >= 97 && key <= 100){ if((key == 'a' && choice == 1)|| 
                                                    (key == 'b' && choice == 2)||
                                                    (key == 'c' && choice == 3)||
                                                    (key == 'd' && choice == 4)){ break;}
                                                    choice = key - 96; }
        else if (key == '\r'|| key == ' ') { break;}
    }

return choice;
}

char ansconverter(int choice) {
    return 'a' + (choice - 1);
}

void anschecker(int pluspoint, int startofindex, char useranswer[], char correctans[], bool qdone[], int random, int *score){

        if (strcmp(useranswer, correctans) == 0){
        qdone[random - startofindex] = 1;
        (*score) += pluspoint;
        printf("   +%d\n   current score: %d", pluspoint, *score);
        } else {
            qdone[random - startofindex] = 1;
            printf(" %s  wrong\n   Correct answer: \"%s\"\n   current score: %d", useranswer,correctans ,*score);
                }
}

void txtformatter(char question[420]){

    for (int i = 0; question[i] != '\0'; i++) { 
        if (question[i] == '|') { printf("\n");
    } else { 
        putchar(question[i]);
        }
    }
}

void txtfileextractor(int random, char *question, int q_size, char *correctans, int a_size, FILE *questionfile, FILE *answerfile){
        for (int i = 1; i <= random; i++){
        fgets(question, q_size, questionfile);
        fgets(correctans, a_size, answerfile);
        }   
        question[strcspn(question, "\n")] = 0;
        correctans[strcspn(correctans, "\n")] = 0;
}


int main(){

char question[420], correctans[69], useranswer[100] = {0};
int choice = 1 , totalquestions = 0, score = 0, counter = 0;
int random = 0, aldone = 0;
bool qdone[9] = {0};
 
srand(time(NULL));

      FILE *questionfile = fopen("txtfiles/questions.txt", "r");
        if(questionfile == NULL){printf("questions.txt gone wrong");return 1;}
        totalquestions = 0;
        while(fgets(question, sizeof(question), questionfile)){ totalquestions++;}

      FILE *answerfile = fopen("txtfiles/answers.txt", "r");
        if(answerfile == NULL){printf("answers.txt gone wrong");return 1;}

      FILE *userrecords = fopen("txtfiles/userrecords.txt", "r+");
        if(userrecords == NULL){printf("userrecords.txt gone wrong");return 1;}
        
            rewind(questionfile);
            rewind(answerfile);
 while(1){
    aldone = 0;
    
    memset(useranswer, 0, sizeof(useranswer));

    for (int i = 0; i < 9; i++ ){ aldone += qdone[i]; }
    if (aldone == 9){
        system("cls");
        printf("\033[0mFINAL SCORE: %d / 48\nPlease enter your name (ATLEAST 3 CHARACTER)\n: ", score);
        fgets(useranswer, sizeof(useranswer), stdin);

        rewind(userrecords);
        counter = 1;

        if (strlen(useranswer) >= 4){
            while(fgets(question, 100, userrecords)){ counter++;}
            fprintf(userrecords, "%d.) [%2d / 48] %s", counter, score,useranswer);
            }else{printf("didn't save\n");}

        fclose(userrecords);
        fclose(answerfile);
        fclose(questionfile);
        printf("[program done...]");
        getch();
        return 0;
        }


    cli_menu(choice, score, qdone);
    choice = movement(choice, &score);
    printf("\033[1;35m\033[%dH ->\033[0m\033[u",choice + 2);



switch (choice){

    case 1:  // easy

        while(1){
            system("cls");
                random = 0;
                aldone = 0;

            for (int i = 0; i < 3; i++ ){ aldone += qdone[i]; }
            if (aldone == 3){printf("your already done here"); break;}
            do{random = rand() % 3 + 2;}while(qdone[random - 2] == 1);

             txtfileextractor(random, question, sizeof(question), correctans, sizeof(correctans), questionfile, answerfile);
             txtformatter(question);
             printf("\n\033[s"); 

            choice = movementchoice(choice);
            printf("\033[u");
            useranswer[0] = ansconverter(choice);

            anschecker(1, 2, useranswer, correctans, qdone, random, &score);
            rewind(questionfile);
            rewind(answerfile);
            getch();
        }
        break;


    case 2: // normal

        while(1){
        system("cls");

             random = 0;
             aldone = 0;

            for (int i = 3; i < 6; i++ ){aldone += qdone[i];}
            if (aldone == 3){printf("your already done here"); break;}
            do{random = rand() % 3 + 7;}while(qdone[random - 4] == 1);

             txtfileextractor(random, question, sizeof(question), correctans, sizeof(correctans), questionfile, answerfile);
             txtformatter(question);
             printf("\n\033[s"); 

            choice = movementchoice(choice);
            printf("\033[u");
            useranswer[0] = ansconverter(choice);

            anschecker(5, 4, useranswer, correctans, qdone, random, &score);
            rewind(questionfile);
            rewind(answerfile);
            getch();
        }
        break;

         
    case 3: // hard

        while(1){
        system("cls");

             random = 0;
             aldone = 0;

            for (int i = 6; i < 9; i++ ){aldone += qdone[i];}
            if (aldone == 3){printf("your already done here"); break;}
            do{random = rand() % 3 + 12;}while(qdone[random - 6] == 1);

                
             txtfileextractor(random, question, sizeof(question), correctans, sizeof(correctans), questionfile, answerfile);
             txtformatter(question);
             printf("\n\033[s"); 

             printf("\033[u");
             fgets(useranswer, sizeof(useranswer), stdin);
             useranswer[strcspn(useranswer, "\n")] = 0;

            anschecker(10, 6, useranswer, correctans, qdone, random, &score);
            rewind(questionfile);
            rewind(answerfile);
            getch();
        }
        break;

    case 5: // show previous users

        system("cls");
            rewind(userrecords);
            int counter = 1; 
            printf("User Records :\n");
            while(fgets(question, sizeof(question), userrecords)){  
                 printf("%s", question);

                counter++;}
            break;

    default:

         printf("\nconfirm? (y/n): ");
         useranswer[0] = getch();
         if (useranswer[0] == 'y' || useranswer[0] == 'y') {  
         printf("Exited...");  
         getch();
         fclose(questionfile);
         fclose(answerfile);
         fclose(userrecords);
         return 0;}else {break;}
                }

    printf("\n...press any key to continue...");
    getch();

        }



    // your not supposed to be here
    return 1;
}