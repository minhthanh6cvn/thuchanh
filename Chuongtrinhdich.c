#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define maxx 1000
///
typedef struct node{
  char *word;
  int icount;
  int *line;
  int size;
  struct node *next;
}node;

node *new_node(char *str){
        node *new;
        new = (node*)malloc(sizeof(node));
        new->icount = 1;
        new->size = 1;
        new->word = (char*)malloc(strlen(str)*sizeof(char));
        new->line = (int*)malloc(sizeof(int));
        if(new->word == NULL||new->line == NULL)
        {
         printf("Loi cap phat bo nho trong new_node\n");
         free(new);
         return NULL;
        }
        else
        {
         strcpy(new->word,str);
         return new;
        }
}
node *add_line(node *n,int line)
{
        int i,sign;
        sign = 0;
        for(i = 0;i < n->size;i ++)
        {
         if(n->line[i] == line)
         {
         sign = 1;
         break;
         }        
        }
        if(sign == 0)
        {
         n->line = (int*)realloc(n->line,(n->size)*sizeof(int));
         if(n->line == NULL)
         {
         printf("Loi cap phat lai bo nho trong add_line");
         }
         else
         {
         n->line[n->size - 1] = line;
         n->size ++;
         }
        }
        return n;
}
node *insert_node(node *root,char *str,int line)
{
        node *tmp,*prev,*new;
        int sign;
        if(root == NULL)
        {
         root = new_node(str);
         root = add_line(root,line);
        }
        else
        {
         sign = 0;
         for(tmp = root;tmp != NULL;tmp = tmp -> next)
         if(strcmp(str,tmp -> word) == 0)
         {
                sign = 1;
                break;
         }
         if(sign == 1)
         {
         tmp -> icount ++;
         tmp = add_line(tmp,line);
         }
         else
         {
         if(strcmp(str,root -> word) < 0)
                {
                 new = new_node(str);
                 new = add_line(new,line);
                 new -> next = root;
                 root = new;
                }
         else
                {
                 tmp = root;
                 while(tmp != NULL&& strcmp(str,tmp -> word) > 0)
                 {
                 prev = tmp;
                 tmp = tmp -> next;
                 }
                 new = new_node(str);
                 new = add_line(new,line);
                 prev -> next = new;
                 new -> next = tmp;
                }
         }
        }
        return root;
}
void print_list(node *root)
{
        int i;
        node *tmp;
        for(tmp = root;tmp != NULL;tmp = tmp -> next)
        {
         printf("word: %20s count: %5d line:",tmp->word,tmp->icount);
         for(i = 0;i < tmp->size -1 ;i ++)
         {
         printf("%3d",tmp->line[i]);
         }
         printf("\n");
        }
}
///////
typedef struct stopw{
  char *word;
}stopw;

int readfile_stopw(stopw Arr[])
{
  FILE *f;
  char str[100];
  int icount,i;
  stopw *tmp;
  f = fopen("stopw.txt","r");
  if(f == NULL)
    {
      printf("Khong mo dk file stopw.txt");
      return 0;
    }
  tmp = Arr;
  icount = 0;
  while(1)
    {
      fgets(str,100,f);
      if(feof(f) != 0) break;
      str[strlen(str) - 1] = '\0';
      Arr[icount].word = (char*)malloc(strlen(str)*sizeof(char));
      strcpy(Arr[icount].word,str);
      icount ++;
    }
  fclose(f);
  return icount;
}
///
char *strlwr(char *tmp)
{
  int i;
  for(i = 0;i < strlen(tmp);i ++)
    if(isupper(tmp[i])) tmp[i] = tolower(tmp[i]);
  return tmp;
}
node *readfile_source(node *root,stopw Arr[],int size )
{
  FILE *f;
  char str[100],c,s,t, *tmp;
  int i,line,sign;
  f = fopen("vanban.txt","r");
  if(f == NULL)
    {
      printf("Khong mo duoc file vanban.txt");
      return;
    }
  line = 1;
  while(1)
    {
      fscanf(f,"%s",str);
      if(feof(f) != 0) break;
      s = str[strlen(str) - 1];
      tmp = strtok(str," \t.,\":;+=-*&^%$#@!~|{}()/[]?><\\");
      if(c == '\n') line ++;
      else if(c == ' '&&t != '.'&&isupper(tmp[0]))//Phat hien danh tu
        {
         sign = 1;
        }
      else sign = 0;
      if(sign == 0) {
        tmp = strlwr(tmp);
        sign = 0;
        for(i = 0;i < size;i ++)
         if(strcmp(Arr[i].word,tmp) == 0)
         {
         sign = 1;
         break;
         }

        if(sign == 0)
         {
         //printf("%s\t%d\n",tmp,line);
         root = insert_node(root,tmp,line);
         }
      }
      t = s;
      c = fgetc(f);
    }
  fclose(f);
  return root;
}

int main()
{
  node *root;
  stopw Arr[maxx];
  int size;
  root = NULL;
  size = readfile_stopw(Arr);
  root = readfile_source(root,Arr,size);
  print_list(root);
  return 0;
}
