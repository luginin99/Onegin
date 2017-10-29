#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <cctype>
#include <cstring>

#define DEBUG



const int in_file   = 1 ;
const int on_screen = 0;

struct Mystr
{
    char* line;
    int length;
};

int read_file (char* name_file, char** buf, Mystr** text, int* nLines);
int compare (const void * a, const void* b);
void write_on_screen (Mystr* text,int nLines);
int line_to_lines (char** buf,Mystr** text);
void write_in_file (Mystr* text, int nLines);
int reverse_compare (const void* a, const void* b);



int main ()
{
    setlocale (LC_CTYPE, "Russian");
    char*  buf    = 0;
    Mystr* text   = 0;
    int    nLines = 0,  f_or_s = 0;

    if ((read_file ("onegin.txt", &buf, &text, &nLines)) == 0)
    {
        printf ("Error read file\n");
        return 0;
    }

    qsort  (text, nLines, sizeof (text[0]), reverse_compare);


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

int read_file (char* name_file, char** buf, Mystr** text, int* nLines)
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

int line_to_lines (char** buf,Mystr** text)
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

    (*text) = (Mystr*) calloc(num_of_lines, sizeof (Mystr));

    (*text)[i].line = *buf;

    for (j = 1; j < num_of_lines; j++)
    {
        while ((*buf)[i] != 0)
            i++;
        i++;

        (*text)[j].line = (char*)(int(*buf)+i);
    }

    for (j = 0; j < num_of_lines- 1; j++)
    {
        (*text)[j].length = (*text)[j+1].line - (*text)[j].line;
    }

    (*text)[num_of_lines-1].length = strlen((*text)[num_of_lines-1].line);

    return num_of_lines;
}

int compare(const void* a, const void* b)
{
    Mystr c = *(Mystr*)a;
    Mystr d = *(Mystr*)b;

    while ((ispunct (*c.line)) || (isspace (*c.line)) )
        c.line++;

    while ((ispunct (*d.line)) || (isspace (*d.line)) )
        d.line++;

    return strcmp (c.line, d.line);
}

int reverse_compare (const void* a, const void* b)
{
    Mystr c = *(Mystr*)a;
    Mystr d = *(Mystr*)b;
    char tmp = 0;

    char* position1   = c.line + c.length - 2;
    char* position2   = d.line + d.length - 2;

    while (ispunct(*position1) || isspace(*position1)) position1--;
    while (ispunct(*position2) || isspace(*position2)) position2--;

    int counter = 0;

    while ((position1 - counter >= c.line) && (position2 - counter >= d.line))
    {
        int result    = *(position1 - counter) - *(position2 - counter);
        if (result != 0) return result;
        counter++;
    }
    return 0;

}

void write_on_screen (Mystr* text,int nLines)
{
    for (int i = 0; i<nLines; ++i)
    {
         printf ("%s\n", text[i].line);
    }

}

void write_in_file (Mystr* text, int nLines)
{
    char name[40];

    printf ("Enter the name of file:");
    scanf ("%s", name);

    FILE* out_ptr = fopen (name, "w");

    for (int i = 0; i < nLines; i++)
    {
        fprintf (out_ptr, "%s\n", text[i].line);
    }
}





