#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
//#include "rlutil.h"
#include <dos.h>
#include <dir.h>

void addSong();
void modSong();
void delSong();
void listSong();
void searchSong();
void Exit();
void gotoxy(int,int);
void menu();
void currentTime();
void delay(int);
void heading();
void textcolor(int);
void setColor();
void structure();
int checkExistence(char[]);
int fetch();
void songInfo(int);
int searchString(char [],char);

struct music
{
    char name[500],artist[250],genre[100],length[50],year[50],album[250];

}song,songTemp;
struct musicTmp
{
    char name[100][500],artist[100][250],genre[100][100],length[100][50],year[100][50],album[100][250];

}songTmp;
long int size = sizeof(song);
FILE *fp;

int main()
{
    fp=fopen("SONG.txt","r+");
    if(fp==NULL)
    {
        fp=fopen("SONG.txt","w+");
        if(fp==NULL)
        {
            printf("can not open file");
            exit(0);
        }
    }
    menu();
    fclose(fp);
    return 0;
}

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}
void setColor(int ForgC)
 {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void currentTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    gotoxy(20,22);
    setColor(3);
    printf ( "%s", asctime (timeinfo) );
    setColor(0);

}

void delay(int number_of_seconds)
{
    int milli_seconds = 75 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int checkExistence(char nameCheck[500]) //Sai nai chl raha abi
{
    int lim=fetch();
    int i=0;
    while(i<=lim)
    {
        if(strcmpi(nameCheck,songTmp.name[i])==0) return 1;
        i++;
    }
    return 0;
}

int fetch()
{
    int i=0;
    rewind(fp);
    while(fread(&songTemp,size,1,fp)==1)
    {
        strcpy(songTmp.name[i],songTemp.name);
        strcpy(songTmp.album[i],songTemp.album);
        strcpy(songTmp.artist[i],songTemp.artist);
        strcpy(songTmp.genre[i],songTemp.genre);
        strcpy(songTmp.length[i],songTemp.length);
        strcpy(songTmp.year[i],songTemp.year);
        i++;
    }
    return i-1;
}

void songInfo(int choice)
{
    system("cls");
    structure();
    gotoxy(15,4);
    printf("%s",songTmp.name[choice]);
    gotoxy(10,6);
    printf("album: %s",songTmp.album[choice]);
    gotoxy(10,8);
    printf("artist: %s",songTmp.artist[choice]);
    gotoxy(10,10);
    printf("genre: %s",songTmp.genre[choice]);
    gotoxy(10,12);
    printf("length: %s",songTmp.length[choice]);
    gotoxy(10,14);
    printf("year: %s",songTmp.year[choice]);
    gotoxy(10,16);
    printf("press enter to continue");
    getch();

}

void heading()
{
    gotoxy(15,2);
    setColor(3);
    printf("Database Management System for Music Playlist");
    setColor(0);
}

int stringSearch(char check[500],char ch)
{
    int lim=fetch();
    int i=0;
    while(i<=lim)
    {
        switch(ch)
        {
        case '1':   //for name
            if(strcmp(check,songTmp.name[i])==0)
                return i;
            break;

        case '2':   //for artist
            if(strcmp(check,songTmp.artist[i])==0)
                return i;
            break;

        case '3':   //for album
            if(strcmp(check,songTmp.album[i])==0)
                return i;
            break;

        case '4':   //for genre
            if(strcmp(check,songTmp.genre[i])==0)
                return i;
            break;

        case '5':   //for length
            if(strcmp(check,songTmp.length[i])==0)
                return i;
            break;

        case '6':   //for year
            if(strcmp(check,songTmp.year[i])==0)
                return i;
            break;
        }
        i++;
    }
    return 0;

}

void structure()
{
    int i;
    setColor(4);
    for(i=0;i<24;i++)
    {
        gotoxy(0,i);
        printf("||");
    }
    for(i=2;i<76;i++)
    {
        gotoxy(i,0);
        printf("||");
    }
    /*for(i=2;i<76;i++)
    {
        gotoxy(i,1);
        printf("_");
    }*/
    for(i=0;i<24;i++)
    {
        gotoxy(77,i);
        printf("||");
    }
    for(i=2;i<76;i++)
    {
        gotoxy(i,23);
        printf("||");
    }
    setColor(0);
    delay(1);
    heading();
    delay(1);
    currentTime();
}

void menu()
{
    int choice;
    while(1)
    {
        char really;
        system("cls");
        structure();
        gotoxy(10,4);
        delay(1);
        setColor(3);
        printf("Enter the number corresponding the option you want to select");
        setColor(0);
        gotoxy(10,6);
        delay(1);
        printf("1. Add Song");
        gotoxy(10,8);
        delay(1);
        printf("2. Modify Song");
        gotoxy(10,10);
        delay(1);
        printf("3. Delete Song");
        gotoxy(10,12);
        delay(1);
        printf("4. List Song");
        gotoxy(10,14);
        delay(1);
        printf("5. Search Song");
        gotoxy(10,16);
        delay(1);
        printf("0. Exit");
        gotoxy(10,18);
        delay(1);
        printf("Enter your choice: ");
        fflush(stdin);
        choice = getche();
        switch(choice)
        {
        case '1':
            gotoxy(10,20);
            printf("Do you REALLY want to add song? (Y/N)");
             really=getche();
             if(really=='y'||really=='Y')
             {
                fseek(fp,0,SEEK_END);
                addSong();
             }
             else
                menu();
            break;
        case '2':
            delSong();
            fp=fopen("SONG.txt","r+");
            if(fp==NULL)
            {
            fp=fopen("SONG.txt","w+");
            if(fp==NULL)
            {
                printf("can not open file");
                exit(0);
            }
            }
            addSong();
            break;
        case '3':
            delSong();
            fp=fopen("SONG.txt","r+");
            if(fp==NULL)
            {
            fp=fopen("SONG.txt","w+");
            if(fp==NULL)
            {
                printf("can not open file");
                exit(0);
            }
            }
            break;
        case '4':
            listSong();
            break;
        case '5':
            searchSong();
            break;
        case '0':
            Exit();
            break;
        default:
            gotoxy(10,20);
            printf("Please Enter from the options in the menu");
            gotoxy(10,21);
            printf("Press enter to continue");
            getch();
            menu();
        }
    }
}

void addSong()
{
    char another='y';
    while(another=='y')
    {
        system("cls");
        structure();
        gotoxy(15,4);
        delay(1);
        setColor(3);
        printf("Enter information regarding song");
        setColor(0);
        gotoxy(10,6);
        delay(1);
        printf("Enter name: ");
        gets(song.name);
        gotoxy(10,8);
        delay(1);
        printf("Enter artist name: ");
        gets(song.artist);
        gotoxy(10,10);
        delay(1);
        printf("Enter album name: ");
        gets(song.album);
        gotoxy(10,12);
        delay(1);
        printf("Enter genre of song: ");
        gets(song.genre);
        gotoxy(10,14);
        delay(1);
        printf("Enter track length: ");
        gets(song.length);
        gotoxy(10,16);
        delay(1);
        printf("Enter year of release: ");
        gets(song.year);
        char songName[500];
        strcpy(songName,song.name);
        if(checkExistence(songName))
        {
            gotoxy(10,18);
            delay(1);
            printf("Your song already exist!");
        }
        else
        {
            fwrite(&song,size,1,fp);
            gotoxy(10,18);
            delay(1);
            printf("Your song was successfully added!");
        }
        fflush(stdin);
        gotoxy(10,20);
        delay(1);
        printf("do you want to add another song(y/n)?");
        another=getche();

    }
}

void listSong()
{
    system("cls");
    structure();
    int i=0,choice=0,lim;
    gotoxy(10,4);
    delay(1);
    setColor(3);
    printf("Enter the number corresponding the option you want to select");
    setColor(0);
    delay(1);
    lim=fetch();
    while(i<=lim)
    {
        gotoxy(10,6+i);
        printf("%d. %s",i+1,songTmp.name[i]);
        i++;
        delay(1);
    }
    gotoxy(10,i+10);
    printf("Press 0 to go back");
    gotoxy(10,i+7);
    printf("your choice: ");
    fflush(stdin);
    scanf("%d",&choice);
    if(choice==0)
    {
        menu();
    }
    else
    {
        choice--;
        songInfo(choice);
    }
}

void modSong()
{
    /*
    char another='y';
    while(another=='y')
    {
        int flag=1;
        system("cls");
        structure();
        gotoxy(10,4);
        printf("Enter song name you want to modify: ");
        gets(songTemp.name);
        rewind(fp);
        while(fread(&song,size,1,fp)==1)
        {
            if(strcmpi(songTemp.name,song.name)==0)
            {
                gotoxy(10,6);
                printf("Enter Info");
                gotoxy(10,8);
                printf("Enter name: ");
                gets(song.name);
                gotoxy(10,10);
                printf("Enter album: ");
                gets(song.album);
                gotoxy(10,12);
                printf("Enter artist: ");
                gets(song.artist);
                gotoxy(10,14);
                printf("Enter genre: ");
                gets(song.genre);
                gotoxy(10,16);
                printf("Enter track length: ");
                gets(song.length);
                gotoxy(10,18);
                printf("Enter year of relese: ");
                gets(song.year);
                if(checkExistence(song.name))
                {
                    gotoxy(10,6);
                    printf("This song already exist!");
                }
                else
                {
                    fseek(fp,-size,SEEK_CUR);
                    fwrite(&song,size,1,fp);
                    gotoxy(10,6);
                    printf("Your song was successfully changed");
                }
                flag=0;
                break;
            }
        }
        if(flag)
        {
            gotoxy(10,6);
            printf("This song do not exist in the play list!");
        }
        gotoxy(10,20);
        printf("Do you want to modify another song(Y/N)?");
        another=getche();
    }*/
}

void delSong()
{
    char ch[10];
    system("cls");
    structure();
    int lim=fetch();
    int i=0,choice;
    static char tmp[500];
    FILE *ft;
    ft=fopen("TEMP.txt","w");
    gotoxy(10,4);
    delay(1);
    setColor(3);
    printf("Enter the number corresponding the option you want to select");
    setColor(0);
        while(i<=lim)
        {
            gotoxy(10,i+6);
            printf("%d. %s",i+1,songTmp.name[i]);
            i++;
        }
        gotoxy(10,i+10);
        printf("Press 0 to go back");
        gotoxy(10,i+8);
        printf("your choice: ");
        gets(ch);
        choice=atoi(ch);
        if(choice==0)
        {
            menu();
        }
        else if(choice>lim)
        {
            gotoxy(10,i+9);
            printf("Please select a valid option");
            gotoxy(10,i+10);
            printf("Press enter to continue");
            getch();
            delSong();
        }
        else
        {
            strcpy(tmp,songTmp.name[choice-1]);
            rewind(fp);
            while(fread(&song,size,1,fp)==1)
            {
                if(strcmpi(tmp,song.name)!=0)
                    fwrite(&song,size,1,ft);
            }
            fclose(fp);
            fclose(ft);
            remove("SONG.txt");
            rename("TEMP.txt","SONG.txt");
        }

}
void searchSong()
{
    system("cls");
    structure();
    char ch;
    static char tmp[500];
    gotoxy(10,4);
    delay(1);
    setColor(3);
    printf("Enter the number corresponding the option you want to select");
    setColor(0);
    gotoxy(10,6);
    printf("1. by Name");
    gotoxy(10,8);
    printf("2. by Artist");
    gotoxy(10,10);
    printf("3. by Album");
    gotoxy(10,12);
    printf("4. by Track length");
    gotoxy(10,14);
    printf("5. by Genre");
    gotoxy(10,16);
    printf("6. by Year of release");
    gotoxy(10,18);
    printf("your choice: ");
    ch=getche();
    system("cls");
    structure();
    gotoxy(10,4);
    printf("Enter: ");
    gets(tmp);
    int choice;
    switch(ch)
    {
    case '1':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;

        case '2':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;

        case '3':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;

        case '4':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;

        case '5':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;

        case '6':
        gotoxy(10,6);
        choice=stringSearch(tmp,ch);
        if(choice)
        {
            songInfo(choice);
        }
        else
        {
            printf("This song does not exist");
        }
        break;
    }



}
void Exit()
{
    system("cls");
    printf("Good Bye!");
    exit(0);
}
