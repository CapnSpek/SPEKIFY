/*Copyright (c) 2022, Bhaskar Sharma
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree. */


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
//for the default color of the program
char b='0',t='b';
//Whenever err is set to 1, the system prints invalid choice and asks the value user to enter again
int err=0;
//Struct to store album information
typedef struct albumdata
{
    int year;
    char* name;
    char** artist;
    int noartist;
    double rating;
    char* genre;
    char** mood;
    int nomoods;
} albumdata;

typedef struct tree
{
    albumdata album;
    struct tree *left, *right;
} tree;

typedef tree* treeptr;

//Logo function (prints logo)
void logo();
//The function that handles the main menu
void mainmenu();
//The function that catches and returns the user entered value
int menucatch();
//clears screen
void clear();
//Loads the database
void load();
//function handles the choice enetered by the user in the main menu
int main2sub(int c);
//Function prints the main menu
void pmainmenu();
//Function prints the theme menu
void ptheme();
//Function handles the theme menu
void theme();
//Function used to pick and execute the input of the theme menu
int pictheme(int x);
//Prints invalid choice
void invalidchoice();
//Prints custom theme menu
void pcusttheme();
//Handles custom theme manu
int custtheme();
//View database option
void vdb();
//Prints view database option
void pvdb();
//view database choice
int vdbchoice(int x);
//If view entire database option is selected
void vedb();
//Prints the menu
void pvedb();
//If view a section of database is selected
void vsdb();
//Prints the menu
void pvsdb();
//If search option is selected
void search();
//Makes choice in the view entire database menu
int vedbchoice(int x);
//Makes choice in the view a section of database menu
int vsdbchoice(int x);
//Used for the sort by genre option
void vbwsdb(int x);
int vbwsdbchoice(int x, int g);
void pvbwsdb();
void pickgenre();
int pickgenrechoice(int x);
void ppickgenre();
//This function takes the address of an array of strings, and a string, and address of an integers, and breaks the words down in
//that string and stores them in an array of strings
void filenames(char*** filenamearr, char* x, int* size);
//This function is used to build a tree as per a particular criteria
treeptr buildtree(char* x, int type, int sptype, int sp1, int sp2, char* sp3);
//This function is used to breakdown a string into words separated by '|'
void breakdown(char*** filenamearr, char* x, int* size);
//This function is used to add node after comparing a certain thing based on the int type
treeptr addnode(treeptr root , albumdata data, int type);
//This function is called to print a tree by the printree function
void printtree(treeptr root);
//This function is used to compare 2 names of albums in a case insensitive manner
int comparename(char* a, char* b);
//This function is used to compare artist names in a case insensitive manner
int compareartist(char* a, char* b);
//This function is used to compare 2 genres in a case insensitive manner
int comparegenre(char* a, char* b);
//This function is called to print a tree but it further calls printtree function. It only clears the screen and prints "No results" if the tree is empty, and returns void.
void printree(treeptr v);
//This function is used when used wants to display an year, or a year range in the daabase
void yoyr();
//This function is used to print previous one's menu
void pyoyr();
//This function inputs the choice, and calls other functions for the year or year choice menu
int yoyrchoice(int x);
//This function is called when user wishes to see albums in an year range
void eyr();
//THis function is called when user wishes to see albums in a particular year
void ey();
//This one is used to print the sort by menu after user picks an year or year range
void pysortby();
//This one picks how the user wants to sort it
void ysortby(int y1, int y2);
//This function inputs initial year and final year and the sort type, and acts accordingly
int ysortbychoice(int y1, int y2, int x);
//This function is used if the user wishes to see a particular artist
void vart();
//This is its sort by menu
void vartsortby(char * x);
//This prints the menu
void pvartsortby();
int vartchoice(char* aname, int x);
//For the search option
void dosearch(char* aname);
//Prints its menu
void pdosearch();
//The sort by menu
int dosearchchoice(char * aname, int x);
//Create profile option
void createit(char * name);
//The function called when create option is selected, the parameter is the name of the profile
void create();
//worst function
int customscan(char**text, int size);
//The function used to load a profile (the parameter is the name of the profile)
void loadit(char* name);
//Prints the menu
void ploadit();
//Sort by choice in the load it option
int loaditchoice(char* name, int x);
//Suggest option
void suggest();
//Prints the menu
void psuggest();
//Picks up your genre choice
int suggestchoice(int x);
//Suggests
void suggestit(char* ads, char* file);
//The adjectives and the filename of the final file are sent to this function
int pickadjec(char** adjecs, char* filename);
//This one finally prints a suggested album
void sugg(int size, int * choices, char** adjecs, char* filename);
//Deletes a tree
treeptr delete(treeptr root);

int main()
{
    //Default color of the program.
    system("color 0b");
    //Calls the main menu.
    mainmenu();
    clear();
    return 0;
}

int menucatch()
{
    int a;
    fflush(stdin);
    if(scanf("%d", &a)==1)
    {
        return a;
    }
    return -1;
}

void mainmenu()
{
    do
    {
        clear();
        logo();
        pmainmenu();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(main2sub(menucatch())!=6);
    return;
}

void pmainmenu()
{
    printf("E N T E R   Y O U R   C H O I C E : -\n\n");
    printf("1.) View the database.\n");
    printf("2.) Create a profile.\n");
    printf("3.) Load a profile.\n");
    printf("4.) Album suggester.\n");
    printf("5.) Theme.\n");
    printf("6.) Exit.\n\n");
    return;
}

int main2sub(int c)
{
    switch(c)
    { 
        case 1:
        vdb();
        break;
        case 2:
        create();
        break;
        case 3:
        load();
        break;
        case 4:
        suggest();
        break;
        case 5:
        theme();
        break;
        case 6:
        ;        
        break;
        default:
        err=1;
    }
    return c;
}

void suggest()
{
    do
    {
        clear();
        logo();
        psuggest();
        if(err==1)
        {
            invalidchoice();
            err=0;
        }
    }while(suggestchoice(menucatch())!=4);
    return;
}

void psuggest()
{
    printf("S U G G E S T : -\n\n");
    printf("Pick a genre.\n");
    printf("1.) Jazz\n");
    printf("2.) Indie Pop.\n");
    printf("3.) Hip Hop.\n");
    printf("4.) Reurn to the main menu\n\n");
    return;
}

int suggestchoice(int x)
{
    switch(x)
    {
    case 1:
     suggestit("jazz adjectives.txt", "jazz.txt");
     break;
     case 2:
     suggestit("indie pop adjectives.txt", "indiepop.txt");
     break;
     case 3:
     suggestit("hiphopadjectives.txt", "hiphop.txt");
     break;
     case 4:
     break;
     default:
     err = 1;
     return x;
    }
    return x;
}

void suggestit(char* ads, char* file)
{
    char **adjectives = (char**)malloc(20*sizeof(char*));
    for(int i=0;i<20;i++)
    {
        adjectives[i] = (char*)malloc(20*sizeof(char));
    }
    FILE* adj;
    adj = fopen(ads, "r");
    printf("%s", ads);
    if(adj==NULL)
    {
        printf("Could not open file...\n");
        getch();
        return;
    }
    int i=0;
    int j=0;
    char c;
    for(i=0;i<20;i++)
    {
        fgets(adjectives[i], 20, adj);
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            if(adjectives[i][j]=='\n')
            {
                adjectives[i][j]='\0';
            }
        }
    }

    do
    {
        
        clear();
        logo();
        printf("Pick adjectives:-\n\n");
        for(int i=1;i<=20;i++)
        {
          printf("%d.) %s\n", i, adjectives[i-1]);
        }
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
        int temp;
        printf("Enter 3 choices. Enter same index twice if you would like to narrow it down. To go back enter \"0 0 0\". (you can enter same number twice).\n");
    }
    while(pickadjec(adjectives, file)!=0);
    for(int i=0;i<20;i++)
    {
        free(adjectives[i]);
    }
    free(adjectives);
    fclose(adj);
    return;
}

int pickadjec(char** adjecs, char* filename)
{
    int j = 0;
    int* n = (int*)malloc(3*sizeof(int));
    fflush(stdin);
    do
    {
        if(err==1)
        {
            printf("Enter valid values\n");
            err = 0;
        }
        fflush(stdin);
        scanf("%d %d %d", &n[0], &n[1], &n[2]);
        if(n[0]==0||n[1]==0||n[2]==0)
        {
            return 0;
        }
        else if(n[0]<1||n[1]<1||n[2]<1||n[0]>20||n[1]>20||n[2]>20)
        {
            err = 1;
            continue;
        }
        --n[0];
        --n[1];
        --n[2];
    }while(err==1);
    sugg(3, n, adjecs, filename);
    free(n);
    return 0;
}

void sugg(int size, int * choices, char** adjecs, char* filename)
{
    albumdata* temparr;
    albumdata* sure=NULL;
    FILE * fil = fopen(filename, "r");
    if(fil==NULL)
    {
        printf("Could not open file...\n");
        return;
    }
    albumdata temp;
    char tempartist[100];
    char tempmood[300];
    char tempname[100];
    char tempgenre[20];
    int j = 0;
    while(fscanf(fil, "%[^;];%[^;];%[^;];%d;%lf;%[^\n]\n", tempgenre, tempartist, tempname, &temp.year, &temp.rating, tempmood)==6)
    {
        temp.name = malloc((strlen(tempname)+1)*sizeof(char));
        strcpy(temp.name, tempname);
        temp.genre = malloc((strlen(tempgenre)+1)*sizeof(char));
        strcpy(temp.genre, tempgenre);
        temp.genre[strlen(tempgenre)]='\0';
        temp.name[strlen(tempname)] = '\0';
        breakdown(&temp.artist, tempartist, &temp.noartist);
        breakdown(&temp.mood, tempmood, &temp.nomoods);
        temparr = malloc((j+1)*sizeof(albumdata));
        for(int i = 0; i < j; i++)
        {
            temparr[i] = sure[i];
        }
        temparr[j] = temp;
        free(sure);
        sure = temparr;
        j++;
    }
    int max=0; int maxcount=0;
    for(int i = 0; i<j; i++)
    {
        int count = 0;
        for(int k = 0;k<temparr[i].nomoods;k++)
        {
            for(int l = 0;l<size;l++)
            {
                if(strcmp(temparr[i].mood[k],adjecs[choices[l]])==0)
                {
                    count++;
                }
            }
        }
        if(count>maxcount)
        {
            maxcount = count;
            max = i;
        }
        if(count==maxcount)
        {
            if(temparr[i].rating>temparr[max].rating)
            {
                max = i;
            }
        }
    }   
    clear();
    logo();
    printf("Suggested album:-\n");
    printf("%s\nYear - %d\nGenre - %s\n\n", temparr[max].name, temparr[max].year, temparr[max].genre);
    getch();
    free(temp.name);
    free(temp.genre);
    free(temparr);
    fclose(fil);
    return;
}

void load()
{
    char *name = (char*)malloc(51*sizeof(char));
    for(int i=0;i<51;i++)
    {
        name[i]='\0';
    }
    do
    {
        clear();
        logo();
        printf("L O A D : -\n\n");
        if(err==1)
        {
            printf("Enter valid name.\n");
            err = 0;
        }
        printf("Enter the name of the profile, or enter 0 to return to the main menu.\n\n");
        if(customscan(&name, 51)!=1)
        {
            err = 1;
            continue;
        }
        if(strcmp(name, "0")==0)
        {
            return;
        }
        int l = strlen(name);
        name = realloc(name, (l+5)*sizeof(char));
        name[l] = '.';
        name[l+1] = 't';
        name[l+2] = 'x';
        name[l+3] = 't';
        name[l+4] = '\0';
        printf("%s\n", name);
        loadit(name);
        free(name);
    }while(err==1);
    free(name);
    return;
}

void loadit(char* name)
{
    do
    {
        clear();
        logo();
        ploadit();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(loaditchoice(name, menucatch())!=5);
    return;
}

int loaditchoice(char* name, int x)
{
    if(x<1||x>4)
    {
        if(x!=5)
        {
            err=1;
        }
        return x;
    }
    treeptr newtree = buildtree(name, x, 0, 0, 0, NULL);
    printree(newtree);
    newtree = delete(newtree);
    free(newtree);
    return x;
}

void ploadit()
{
    
    printf("L O A D\t\tS O R T E D\tB Y : -\n\n");
    printf("1.) Sorted by artist name.\n");
    printf("2.) Sorted by release year.\n");
    printf("3.) Sorted by album name.\n");
    printf("4.) Sorted by genre.\n");
    printf("5.) Return to the previous menu.\n\n");
    return;
}

void create()
{
    char *name = (char*)malloc(51*sizeof(char));
    for(int i=0;i<51;i++)
    {
        name[i]='\0';
    }
    do
    {
        clear();
        logo();
        printf("C R E A T E : -\n\n");
        if(err==1)
        {
            printf("Enter valid name.\n");
            err = 0;
        }
        printf("Enter the name of the profile, or enter 0 to return to the main menu.\n\n");
        if(customscan(&name, 51)!=1)
        {
            err = 1;
            continue;
        }
        if(strcmp(name, "0")==0)
        {
            return;
        }
        int l = strlen(name);
        name = realloc(name, (l+5)*sizeof(char));
        name[l] = '.';
        name[l+1] = 't';
        name[l+2] = 'x';
        name[l+3] = 't';
        name[l+4] = '\0';
        printf("%s\n", name);
        createit(name);
    }while(err==1);
    free(name);
    return;
}

void createit(char * name)
{
    FILE * fp;
    char c;
    clear();
    logo();
    fp = fopen(name, "a");
    if(fp==NULL)
    {
        printf("Unable to open file\n");
        return;
    }
    char tempartist[51];
    char tempname[101]; 
    char tempmood[301];
    char genre[51]; 
    int year;
    float rate;
    int l;
    printf("C R E A T E : -\n\n");
    int exit = 0;
    do{
    printf("At any stage of entering, you can enter 0 to terminate entering\n");
    printf("Enter the artist names, separated by '|', at most 50 characters\n");
    int test;
    scanf("%[^\n]", tempartist);
    fflush(stdin);

    if(strcmp(tempartist, "0")==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }

    printf("Enter the album name, at most 50 characters\n");
    scanf("%[^\n]", tempname);
    fflush(stdin);
    
    if(strcmp(tempname, "0")==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }

    printf("Enter the year the album was released in\n");
    scanf("%d", &year);
    fflush(stdin);
    if(year==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }

    printf("Enter the genre of the album (at most 50 characters)\n");
    scanf("%[^\n]", genre);
    fflush(stdin);
    if(strcmp(genre, "0")==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }

    printf("Enter what would you rate the album (out of 5, upto 2 decimal places):-\n");
    scanf("%f", &rate);
    fflush(stdin);
    if(rate==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }


    printf("Enter a few moods (separated by '|') to identify the album, at most 200 characters\n");
    scanf("%[^\n]", tempmood);
    fflush(stdin);
    
    if(strcmp(tempmood, "0")==0)
    {
        fclose(fp);
        exit = 1;
        continue;
    }
    fflush(stdin);
    printf("Adding entry...\n");
    fprintf(fp, "%s;%s;", genre, tempartist);
    int i = 0;
    while(i<50 && tempartist[i]!='\0')
    {
        if(tempartist[i]=='|')
        {
            fprintf(fp, " & ");
        }
        else
        {
            fprintf(fp, "%c", tempartist[i]);
        }
        i++;
    }
    fprintf(fp, " - %s ( %d );%d;%.2f;%s\n", tempname, year, year, rate, tempmood);
    }
    while(exit==0);
    return;
}

int customscan(char**text, int size)
{
    char *a=(char*)malloc(sizeof(size));
    char c;
    fflush(stdin);
    int i = 0;
    do
    {
        scanf("%c", &c);
        if(c=='\n')
        {
            a[i] = '\0';
            break;
        }
        a[i] = c;
        i++;
    }while(i<size-1);
    a[i] = '\0';
    strcpy(*text, a);
    if(a[0]='\0')
    {
        return 0;
    }
    return 1;
}

void theme()
{
    do
    {
        ptheme();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    } while (pictheme(menucatch())!=7);
    return;
}

void ptheme()
{
    clear();
    logo();
    printf("P I C K\t\tA\tT H E M E : -\n");
    printf("1.) Default - Aqua-Dark.\n");
    printf("2.) Yellow-Red.\n");
    printf("3.) BIOS like (White-Blue).\n");
    printf("4.) Classic Dos.\n");
    printf("5.) Light (Purple-White).\n");
    printf("6.) Custom.\n");
    printf("7.) Return to main menu.\n\n");
    return;
}

int pictheme(int x)
{
    switch(x)
    {
        case 1:
        b='0';
        t='b';
        break;
        case 2:
        b='4';
        t='e';
        break;
        case 3:
        b='1';
        t='f';
        break;
        case 4:
        b='0';
        t='f';
        break;
        case 5:
        b='f';
        t='5';
        break;
        case 6:
        do
        {
            if(err==1)
            {
                ptheme();
            }
            pcusttheme();
            if(err==1)
            {
                invalidchoice();
                err=0;
            }
        }while(custtheme()!=1);
        break;
        case 7:
        break;
        default:
        err = 1;
    }
    char a[8];
    strcpy(a, "color 00");
    a[7] = b;
    a[8] = t;
    system(a);
    return x;
}

void vdb()
{
    do
    {
        pvdb();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while (vdbchoice(menucatch())!=4);
    return;
}

int vdbchoice(int x)
{
    switch(x)
    {
        case 1:
        vedb();
        break;
        case 2:
        vsdb();
        break;
        case 3:
        search();
        break;
        case 4:
        break;
        default:
        err = 1;
    }
    return x;
}

void search()
{
    char aname[300];
    do
    {
        clear();
        logo();
        printf("S E A R C H\t\tA N\tA L B U M : -\n\n");
        printf("Enter all the information you know about the album separated by spaces, or enter 0 to return to the previous menu.\n");
        fflush(stdin);
        if(err==1)
        {
            printf("Enter valid values.\n");
            err = 0;
        }
        if(scanf("%[^\n]", aname)!=1)
        {
            err=1;
            continue;
        }
        fflush(stdin);
        if(strcmp(aname, "0")==0)
        {
            continue;
        }
        dosearch(aname);
    }while(err==1);
    return;
}

void dosearch(char* aname)
{
    do
    {
        clear();
        logo();
        pdosearch();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(dosearchchoice(aname, menucatch())!=5);
}

int dosearchchoice(char* aname, int x)
{
    char name[50] = "jazz.txt indiepop.txt hiphop.txt";
    if(x<1 || x>4)
    {
        if(x!=5)
        {
            err = 1;
        }
        return x;
    }
    treeptr newtree = buildtree(name, x, 3, 0, 0, aname);
    printree(newtree);
    newtree=delete(newtree);
    free(newtree);
    return x;
}

void pdosearch()
{
    printf("S E A R C H : -\n\n");
    printf("1.) Sorted by artist name.\n");
    printf("2.) Sorted by release year.\n");
    printf("3.) Sorted by album name.\n");
    printf("4.) Sorted by genre.\n");
    printf("5.) Return to the previous menu.\n");
    return;
}

void vedb()
{
    do
    {
        pvedb();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while (vedbchoice(menucatch())!=5);
    return;
}

void vsdb()
{
    do
    {
        pvsdb();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while (vsdbchoice(menucatch())!=4);
}

void pvsdb()
{
    clear();
    logo();
    printf("V I E W\t\tA\tS E C T I O N : -\n\n");
    printf("1.) View a genre.\n");
    printf("2.) View an year (or an year range).\n");
    printf("3.) View an artist.\n");
    printf("4.) Return to the previous menu.\n");
}

int vsdbchoice(int x)
{
    switch(x)
    {
        case 1:
        pickgenre();
        break;
        case 2:
        yoyr();
        break;
        case 3:
        vart();
        break;
        case 4:
        break;
        default:
        err = 1;
    }
    return x;
}

void vart()
{
    char aname[50];
    do
    {
        clear();
        logo();
        printf("V I E W\t\tA N\tA R T I S T : -\n\n");
        printf("Enter an artist name, or 0 to go back.\n");
        if(err==1)
        {
            printf("Not a valid name.\n\n");
            err = 0;
        }
        fflush(stdin);
        if(scanf("%[^\n]", aname)!=1)
        {
            err=1;
            continue;
        }
        int i = 0;
        while(aname[i]!='\0')
        {
            aname[i] = tolower(aname[i]);
            i++;
        }
        fflush(stdin);
        if(strcmp(aname, "0")==0)
        {
            continue;
        }
        vartsortby(aname);
    }while(err==1);
    return;
}

void vartsortby(char * x)
{
    do
    {
        clear();
        logo();
        pvartsortby();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(vartchoice(x, menucatch())!=4);
    return;
}

int vartchoice(char* aname, int x)
{
    char name[50] = "jazz.txt indiepop.txt hiphop.txt";
    x = x+1;
    if(x<2 || x>3)
    {
        if(x!=4)
        {
            err=1;
        }
        return x;
    }
    treeptr newtree = buildtree(name, x, 2, 0, 0, aname);
    printree(newtree);
    newtree=delete(newtree);
    free(newtree);
    return x;
}

void pvartsortby()
{
    printf("S O R T\t\tB Y : -\n\n");
    printf("1.) Sort by release year.\n");
    printf("2.) Sort by album name.\n");
    printf("3.) Return to the previous menu.\n\n");
    return;
}

void yoyr()
{
    do
    {
        clear();
        logo();
        pyoyr();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(yoyrchoice(menucatch())!=3);
    return;
}

void pyoyr()
{
    printf("Y O Y R:-\n\n");
    printf("1.) Year.\n");
    printf("2.) Year range.\n");
    printf("3.) Return to the previous menu.\n\n");
    return;
}

int yoyrchoice(int x)
{
    int y1;
    switch(x)
    {
        case 1:
        ey();
        break;
        case 2:
        eyr();
        break;
        case 3:
        break;
        default:
        err = 1;
    }
    return x;
}

void eyr()
{
    do
    {
        clear();
        logo();
        printf("E Y R : -\n\n");
        if(err==1)
        {
            printf("Enter a valid year range.\n");
            err = 0;
        }
        printf("Enter initial year, or 0 to go back.\n");
        int y1;
        y1 = menucatch();
        if(y1==0)
        continue;
        if(y1<0)
        {
            err = 1;
            continue;
        }
        printf("Enter the ending year, or 0 to go back.\n");
        int y2;
        y2 = menucatch();
        if(y2==0)
        continue;
        if(y2<0)
        {
            err = 1;
            continue;
        }
        if(y2<y1)
        {
            int temp = y2;
            y2 = y1;
            y1 = temp;
        }
        ysortby(y1, y2);
    } while (err==1);
    return;
}

void ysortby(int y1, int y2)
{
    do
    {
        clear();
        logo();
        pysortby();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    } while(ysortbychoice(y1, y2, menucatch())!=5);
    return;
}

void pysortby()
{
    printf("1.) Sorted by artist name.\n");
    printf("2.) Sorted by release year.\n");
    printf("3.) Sorted by album name.\n");
    printf("4.) Sorted by genre.\n");
    printf("5.) Return to the last menu.\n\n");
}

int ysortbychoice(int y1, int y2, int x)
{
    treeptr newtree;
    char name[100] = "jazz.txt indiepop.txt hiphop.txt";
    if(x>0 && x<5)
    {
        newtree = buildtree(name, x, 1, y1, y2, NULL);
    }
    else
    {
        if(x!=5)
        {
            err = 1;
        }
        return x;
    }
    printree(newtree);
    newtree=delete(newtree);
    free(newtree);
    return x;
}

void ey()
{
    do
    {
        clear();
        logo();
        printf("E Y : -\n\n");
        printf("Enter the year, or 0 to go back\n");
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
        int y;
        y = menucatch();
        if(y==0)
        continue;
        if(y<0)
        {
            err = 1;
            continue;
        }
        ysortby(y, y);
    }while(err==1);
    return;
}

void pickgenre()
{
    do
    {
        ppickgenre();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while(pickgenrechoice(menucatch())!=4);
    return;
}

int pickgenrechoice(int x)
{
    if(x==4)
    {
        return x;
    }
    if(x<1 || x>4)
    {
        err = 1;
        return x;
    }
    vbwsdb(x);
    return x;
}

void ppickgenre()
{
    clear();
    logo();
    printf("P I C K\t\tG E N R E\n\n");
    printf("1.) Jazz.\n");
    printf("2.) Indie Pop\n");
    printf("3.) Hip Hop.\n");
    printf("4.) Return to the previous menu.\n\n");
    return;
}

int vedbchoice(int x)
{
    char name[200] = "jazz.txt indiepop.txt hiphop.txt";
    if(x<1 || x>4)
    {
        if(x!=5)
        {
            err=1;
        }
        return x;
    }
    treeptr newtree = buildtree(name, x, 0, 0, 0, NULL);
    printree(newtree);
    newtree=delete(newtree);
    free(newtree);
    return x;
}

void printree(treeptr v)
{
    clear();
    logo();
    if(v==NULL)
    {
        printf("No results found.\n\n");
    }
    printtree(v);
    printf("Press any key to go back...");
    getch();
    return;
}

void pvedb()
{
    clear();
    logo();
    printf("V I E W\t\tT H E\t E N T I R E\tD A T A B A S E : -\n\n");
    printf("1.) Sorted by artist name.\n");
    printf("2.) Sorted by release year.\n");
    printf("3.) Sorted by album name.\n");
    printf("4.) Sorted by genre.\n");
    printf("5.) Return to the last menu.\n\n");
    return;
}

void pvdb()
{
    clear();
    logo();
    printf("P I C K\t\tA\tC H O I C E : -\n\n");
    printf("1.) View the entire database (sorted as per a criteria).\n");
    printf("2.) View a section of a database based on a criteria.\n");
    printf("3.) Search an album.\n");
    printf("4.) Return to the main menu.\n\n");
    return;
}

void vbwsdb(int x)
{
    do
    {
        pvbwsdb();
        if(err==1)
        {
            invalidchoice();
            err = 0;
        }
    }while (vbwsdbchoice(menucatch(), x)!=4);
    return;
}

int vbwsdbchoice(int x, int g)
{
    char *name;
    switch(g)
    {
        case 1:
        name = malloc((8+1)*sizeof(char));
        strcpy(name, "jazz.txt");
        break;
        case 2:
        name = malloc((8+1)*sizeof(char));
        strcpy(name, "indiepop.txt");
        break;
        case 3:
        name = malloc((10+1)*sizeof(char));
        strcpy(name, "hiphop.txt");
    }
    if(x<1 || x>3)
    {
        if(x!=4)
        {
            err = 1;
        }
        return x;
    }
    treeptr newtree = buildtree(name, x, 0, 0, 0, NULL);
    printree(newtree);
    newtree=delete(newtree);
    free(newtree);
    free(name);
    return x;
}

treeptr addnode(treeptr root , albumdata data, int type)
{
    if(root==NULL)
    {
        root = (treeptr)malloc(sizeof(tree));
        root->album = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else
    {
        switch(type)
        {
            case 1:
            if(compareartist(data.name, root->album.name)<=0)
            {
                root->left = addnode(root->left, data, type);
            }
            else
            {
                root->right = addnode(root->right, data, type);
            }
            break;
            case 2:
            if(data.year <= root->album.year)
            {
                root->left = addnode(root->left, data, type);
            }
            else
            {
                root->right = addnode(root->right, data, type);
            }
            break;
            case 3:
            if(comparename(data.name, root->album.name)<=0)
            {
                root->left = addnode(root->left, data, type);
            }
            else
            {
                root->right = addnode(root->right, data, type);
            }
            break;
            case 4:
            if(comparegenre(data.genre, root->album.genre)<=0)
            {
                root->left = addnode(root->left, data, type);
            }
            else
            {
                root->right = addnode(root->right, data, type);
            }
            break;
        }
    }
    return root;
}

int comparename(char* a, char* b)
{
    char tempa[50];
    char tempb[50];
    int i=-1;
    int check = 0;
    int j=0;
    while(a[j]!='(')
    {
        if(check==1)
        {
            ++i;
            tempa[i]=tolower(a[j]);
        }
        if(a[j]=='-')
        {
            check=1;
            j++;
        }
        j++;
    }
    tempa[i] = '\0';

    i = -1;
    check = 0;
    j = 0;
    while(b[j]!='(')
    {
        if(check==1)
        {
            i++;
            tempb[i]=tolower(b[j]);
        }
        if(b[j]=='-')
        {
            check=1;
            j++;
        }
        j++;
    }
    tempb[i] = '\0';
    int x = strcmp(tempa, tempb);
    return x;
}

int compareartist(char* a, char* b)
{
    char tempa[50];
    char tempb[50];
    int i=-1;
    int j=0;
    while(a[j]!='-')
    {
        ++i;
        tempa[i] = a[j];
        j++;
    }   
    tempa[i] = '\0';

    i = -1;
    j = 0;
    while(b[j]!='-')
    {
        ++i;
        tempb[i] = b[j];
        j++;
    }
    tempb[i] = '\0';
    int x = strcmp(tempa, tempb);
    return x;
}

int comparegenre(char* a, char* b)
{
    char tempa[50];
    char tempb[50];
    int i=0;
    while(a[i]!='\0')
    {
        tempa[i] = tolower(a[i]);
        i++;
    }
    tempa[i] = '\0';

    i=0;
    while(b[i]!='\0')
    {
        tempb[i] = tolower(b[i]);
        i++;
    }
    tempb[i] = '\0';
    int x = strcmp(tempa, tempb);
    return x;
}

treeptr buildtree(char* x, int type, int sptype, int sp1, int sp2, char* sp3)
{
    char** files;
    int filenumbers;
    filenames(&files, x, &filenumbers);
    int fn = filenumbers;
    treeptr v=NULL;
    FILE** fp = (FILE**)malloc(filenumbers*sizeof(FILE*));
    for(int i=0; i<filenumbers; i++)
    {
        fp[i] = fopen(files[i], "r");
        if(fp[i]==NULL)
        {
            printf("Could not load file...\n");
            getch();
            return v;
        }
        if(fp[i]==NULL)
        {
            clear();
            logo();
            printf("No such profile found...\nPress any key to continue.\n\n");
            getch();
            break;
        }
        albumdata temp;
        char tempartist[100];
        char tempmood[300];
        char tempname[100];
        char tempgenre[20];
        while(fscanf(fp[i], "%[^;];%[^;];%[^;];%d;%lf;%[^\n]\n", tempgenre, tempartist, tempname, &temp.year, &temp.rating, tempmood)==6)
        {
            temp.name = malloc((strlen(tempname)+1)*sizeof(char));
            strcpy(temp.name, tempname);
            temp.genre = malloc((strlen(tempgenre)+1)*sizeof(char));
            strcpy(temp.genre, tempgenre);
            temp.genre[strlen(tempgenre)]='\0';
            temp.name[strlen(tempname)] = '\0';
            breakdown(&temp.artist, tempartist, &temp.noartist);
            breakdown(&temp.mood, tempmood, &temp.nomoods);
            if(sptype == 0)
            {
                v = addnode(v, temp, type);
            }
            else
            {
                switch(sptype)
                {
                    case 1:
                    if(sp1 <= temp.year && sp2 >= temp.year)
                    {
                        v = addnode(v, temp, type);
                    }
                    break;
                    case 2:
                    for(int j=0;j<temp.noartist;j++)
                    {
                        if(strcmp(temp.artist[j], sp3)==0)
                        {
                            v = addnode(v, temp, type);
                        }
                    }
                    break;
                    case 3:;
                    char ** keywords;
                    int keysize;
                    char ** orgwords;
                    int orgsize;
                    filenames(&keywords, sp3, &keysize);
                    filenames(&orgwords, temp.name, &orgsize);

                    for(int l=0;l<keysize;l++)
                    {
                        int o=0;
                        while(keywords[l][o]!='\0')
                        {
                            keywords[l][o] = tolower(keywords[l][o]);
                            o++;
                        }
                    }

                    for(int l=0;l<orgsize;l++)
                    {
                        int o=0;
                        while(orgwords[l][o]!='\0')
                        {
                            orgwords[l][o] = tolower(orgwords[l][o]);
                            o++;
                        }
                    }
                    int similarities=0;
                    for(int j = 0;j<keysize;j++)
                    {
                        for(int k=0;k<orgsize;k++)
                        {
                            if(strcmp(keywords[j], orgwords[k])==0)
                            {
                                similarities++;
                                if(similarities==keysize)
                                {
                                    v=addnode(v, temp, type);
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }


    }
    for(int i=0;i<filenumbers;i++)
    fclose(fp[i]);
    return v;
}

void printtree(treeptr root)
{
    if(root==NULL)
    {
        return;
    }
    printtree(root->left);
    printf("%s\nYear - %d\nGenre - %s\n\n", root->album.name, root->album.year, root->album.genre);
    for(int i=0;i<root->album.noartist;i++)
    printtree(root->right);
    return;
}

void breakdown(char*** filenamearr, char* x, int* size)
{
    int i = 1;
    int n = 0;
    while(x[n]!='\0')
    {
        if(x[n]=='|')
        i++;
        n++;
    }
    char** names = (char**)malloc(i*sizeof(char*));
    int* ind = (int*)malloc((i+1)*sizeof(int));
    ind[0] = -1;
    ind[i] = n;
    n = 0; int j = 1;
    while(x[n]!='\0')
    {
        if(x[n]=='|')
        {
            ind[j] = n;
            j++;
        }
        n++;
    }
    for(j=0;j<i;j++)
    {
        names[j] = (char*)malloc((ind[j+1]-ind[j])*sizeof(char));
    }
    int k = 0;
    for(j=0;j<i;j++)
    {
        int z = 0;
        while(ind[j]<k && ind[j+1]>k)
        {
            names[j][z] = tolower(x[k]);
            z++;
            k++;
            if(k==ind[j+1])
            {
                k++;
            }
        }
        names[j][z] = '\0';
    }
    *filenamearr = names;
    *size = i;
}

void filenames(char*** filenamearr, char* x, int* size)
{
    
    int i = 1;
    int n = 0;
    while(x[n]!='\0')
    {
        if(x[n]==' ')
        i++;
        n++;
    }
    char** names = (char**)malloc(i*sizeof(char*));
    int* ind = (int*)malloc((i+1)*sizeof(int));
    ind[0] = -1;
    ind[i] = n;
    n = 0; int j = 1;
    while(x[n]!='\0')
    {
        if(x[n]==' ')
        {
            ind[j] = n;
            j++;
        }
        n++;
    }
    for(j=0;j<i;j++)
    {
        names[j] = (char*)malloc((ind[j+1]-ind[j])*sizeof(char));
    }
    int k = 0;
    for(j=0;j<i;j++)
    {
        int z = 0;
        while(ind[j]<k && ind[j+1]>k)
        {
            names[j][z] = x[k];
            z++;
            k++;
            if(k==ind[j+1])
            {
                k++;
            }
        }
        names[j][z] = '\0';
    }
    *filenamearr = names;
    *size = i;
}

void pvbwsdb()
{
    clear();
    logo();
    printf("V I E W\t\tS O R T E D\tB Y\n\n");
    printf("1.) Sorted by artist name.\n");
    printf("2.) Sorted by release year.\n");
    printf("3.) Sorted by album name.\n");
    printf("4.) Return to the previous menu.\n\n");
}

int custtheme()
{
    char x,y;
    printf("Enter the code of the background color first. Enter 'X' to retain the color.\n");
    scanf(" %c", &x);
    fflush(stdin);
    x = tolower(x);

    if(((x<'a' || x>'f') && (x<'0' || x>'9') && x!='x'))
    {
        err = 1;
        return 0;
    }
    printf("Enter the code of the text color. Enter 'X' to retain the color.\n");
    scanf("%c", &y);
    fflush(stdin);
    y = tolower(y);
    if(((y<'a' || y>'f') && (y<'0' || y>'9') && y!='x'))
    {
        err = 1;
        return 0;
    }
    if(x!='x')
    {
        b=x;
    }
    if(y!='x')
    {
        t=y;
    }
    return 1;

}

void pcusttheme()
{
    printf("Codes for different colors:-\n");
    printf("\t0 - Black\t8 - Gray\n");
    printf("\t1 - Blue\t9 - Light Blue\n");
    printf("\t2 - Green\tA - Light Green\n");
    printf("\t3 - Aqua\tB - Light Aqua\n");
    printf("\t4 - Red\t\tC - Light Red\n");
    printf("\t5 - Purple\tD - Light Purple\n");
    printf("\t6 - Yellow\tE - Light Yellow\n");
    printf("\t7 - White\tF - Bright White\n");
    printf("\tX - Retain the color\n\nNOTE: It does not work for same background and text color.\n\n");
    return;
}

void invalidchoice()
{
    printf("Invalid choice. Enter again\n\n");
    return;
}
void clear()
{
    system("cls");
    return;
}

void logo()
{
    char sp[] = {"  "};
    char s[] = {"S "};
    char p[] = {"P "};
    char e[] = {"E "};
    char k[] = {"K "};
    char ii[] = {"I "};
    char f[] = {"F "};
    char y[] = {"Y "};
    int c=-4;
    for(int i=0;i<=8;i++)
    {
        for(int j=1;j<=121;j+=2)
        {
            if(i==0)
            {
                if(j>=3 && j<=13)
                {
                    printf("%s", s);
                }
                else if(j>=21 && j<=33)
                {
                    printf("%s", p);
                }
                else if(j>=41 && j<=53)
                {
                    printf("%s", e);
                }
                else if(j==61 || j==73)
                {
                    printf("%s", k);
                }
                else if(j==81)
                {
                    printf("%s", ii);
                }
                else if(j>=89 && j<=101)
                {
                    printf("%s", f);
                }
                else if(j==109 || j==121)
                {
                    printf("%s", y);
                }
                else
                {
                    printf("%s", sp);
                }
            }
            else if(i>=1 && i<=3)
            {
                if(j==1)
                {
                    printf("%s", s);
                }
                else if(j==21 || j==35)
                {
                    printf("%s", p);
                }
                else if(j==41)
                {
                    printf("%s", e);
                }
                else if(j==61 || j==(73-2*i))
                {
                    printf("%s", k);
                }
                else if(j==81)
                {
                    printf("%s", ii);
                }
                else if(j==89)
                {
                    printf("%s", f);
                }
                else if(j==109+(i*2) || j==121-(i*2))
                {
                    printf("%s", y);
                }
                else
                {
                    printf("%s", sp);
                }
            }
            else if(i==4)
            {
                if(j>=3 && j<=11)
                {
                    printf("%s", s);
                }
                else if(j>=21 && j<=33)
                {
                    printf("%s", p);
                }
                else if(j>=41 && j<=53)
                {
                    printf("%s", e);
                }
                else if(j>=61 && j<=65)
                {
                    printf("%s", k);
                }
                else if(j==81)
                {
                    printf("%s", ii);
                }
                else if(j>=89 && j<=101)
                {
                    printf("%s", f);
                }
                else if(j==115)
                {
                    printf("%s", y);
                }
                else
                {
                    printf("%s", sp);
                }
            }
            else if(i>=5 && i<=7)
            {
                if(j==13)
                {
                    printf("%s", s);
                }
                else if(j==21)
                {
                    printf("%s", p);
                }
                else if(j==41)
                {
                    printf("%s", e);
                }
                else if(j==61 || j==65+(c*2))
                {
                    printf("%s", k);
                }
                else if(j==81)
                {
                    printf("%s", ii);
                }
                else if(j==89)
                {
                    printf("%s", f);
                }
                else if(j==115)
                {
                    printf("%s", y);
                }
                else
                {
                    printf("%s", sp);
                }
            }
            else if(i==8)
            {
                if(j>=1 && j<=11)
                {
                    printf("%s", s);
                }
                else if(j==21)
                {
                    printf("%s", p);
                }
                else if(j>=41 && j<=53)
                {
                    printf("%s", e);
                }
                else if(j==61 || j==65+(c*2))
                {
                    printf("%s", k);
                }
                else if(j==81)
                {
                    printf("%s", ii);
                }
                else if(j==89)
                {
                    printf("%s", f);
                }
                else if(j==115)
                {
                    printf("%s", y);
                }
                else
                {
                    printf("%s", sp);
                }
            }
        }
        c++;
        printf("\n");
    }
    printf("\n");
    return;
}

treeptr delete(treeptr root)
{
    if(root==NULL)
    {
        return root;
    }
    root->left = delete(root->left);
    root->right = delete(root->right);
    free(root);
    root = NULL;
    return root;
}