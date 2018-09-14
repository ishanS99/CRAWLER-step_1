
//crawler in cpp
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>

#define pname "crawler"
#define site "chitkara"

using namespace std;

int testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 ) 
  {
    /*fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    exit(1);*/
    return 0;
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) ) 
  {
    /*fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    exit(1);*/
    return 0;
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
  {
    /*fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);*/
    return 0;
  }
  return 1;
}

int isSubstring(char s1[],char s2[])
{
    int M = strlen(s1);
    int N = strlen(s2);
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;
		/* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return 1;
    }
    return 0;
}

int verify_command(int argc, char* argv[])
{
	if(argc!=5)
		return 0;
	if(strcmp(argv[1],pname)!=0)
		return 0;
	if(isSubstring(site,argv[2])==0)
		return 0;
	if(argv[3][0]<'0' || argv[3][0]>'9')
		return 0;
	if(testDir(argv[4])==0)
		return 0;
	return 1;

}

int validate_url_wGet(char str[])
{
	char s1[100] = "wget --spider ";
	strcat(s1,str);
	if(!system(s1))
		return 1;
	return 0;
}

int main(int argc,char* argv[])
{
	int k = verify_command(argc,argv);
	if(k==0)
	{
		cout<<"Command invalid\n";
		return 0;
	}
	if(validate_url_wGet(argv[2])==0)
	{
		cout<<"WEBSITE NOT FOUND\n";
		return 0;
	}
	cout<<"GOOD\n";
	return 0;
}