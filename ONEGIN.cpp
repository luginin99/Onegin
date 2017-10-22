#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <cctype>
#include <cstring>

#define DEBUG

const int in_file   = 1 ;
const int on_screen = 0;

int read_file (char* name_file, char** buf, char*** text, int* nLines);
int compare (const void * a, const void* b);
void write_on_screen (char** text,int nLines);
int line_to_lines (char** buf,char*** text);
void write_in_file (char ** text, int nLines);


int main ()
{
    setlocale (LC_CTYPE, "Russian");
    char*  buf    = 0;
    char** text   = 0;
    int    nLines = 0,  f_or_s = 0;

    if ((read_file ("onegin.txt", &buf, &text, &nLines)) == 0)
    {
        printf ("Error read file\n");
        return 0;
    }

    qsort  (text, nLines, sizeof (text[0]), compare);


    printf ("Do you want to write in file or on screen (1/0)\n");
    scanf  ("%d", &f_or_s);

    switch (f_or_s)
    {
    case on_screen :
        write_on_screen (text,nLines);
        break;

    case in_file :
        write_in_file (text, nLines);
        break;
    }

    return 0;
}

int read_file (char* name_file, char** buf, char*** text, int* nLines)
{
    int i = 0 , j = 1;
    int num_symb = 0;

    FILE* file_ptr = fopen (name_file, "rb");

    fseek (file_ptr, 0, SEEK_END);
    num_symb = ftell (file_ptr);
    rewind (file_ptr);

    *buf = (char *) calloc (num_symb + 1, sizeof (char));

    fread ( *buf, sizeof (char), num_symb, file_ptr);

    *nLines = line_to_lines (buf, text);

    return 1;
}

int compare(const void* a, const void* b)
{
    char* c = *(char**)a;
    char* d = *(char**)b;
    int i = 0;

    while ((ispunct (c[i])) || (isspace (c[i])) )
        i++;
    (c)+=i;

    i = 0;

    while ((ispunct (d[i])) || (isspace (d[i])))
        i++;

    (d)+=i;
    return strcmp (c, d);
}

void write_on_screen (char** text,int nLines)
{
    for (int i = 0; i<nLines; ++i)
    {
         printf ("%s\n", text [i]);
    }

}

void write_in_file (char ** text, int nLines)
{
    char name[40];

    printf ("Enter the name of file:");
    scanf ("%s", name);

    FILE* out_ptr = fopen (name, "w");

    for (int i = 0; i < nLines; i++)
    {
        fprintf (out_ptr, "%s\n", text [i]);
    }
}

int line_to_lines (char** buf,char*** text)
{
    int num_of_lines = 0;
    int i = 0;
    int j = 0;

    while ((*buf)[i] != 0)
    {

        if ((*buf) [i] == '\n')
        {
            (*buf) [i] = '\0';
            num_of_lines++;
        }
        if ((*buf) [i]=='¨')
            (*buf) [i] = 'Å';
        if ((*buf) [i] == '¸')
            (*buf) [i] = 'å';
        i++;
    }
    i=0;

    (*text) = (char **) calloc(num_of_lines, sizeof (char*));

    (*text) [i] = *buf;

    for (j = 1; j < num_of_lines; j++)
    {
        while ((*buf)[i] != 0)
            i++;
        i++;

        (*text) [j] = (char*)(int(*buf)+i);
    }

    return num_of_lines;
}




