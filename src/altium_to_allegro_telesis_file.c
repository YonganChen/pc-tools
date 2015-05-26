/*
 ============================================================================
 Name        : pc_tools.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_POSITION_UNKOWN    (0)
#define FILE_POSITION_PACKAGES  (1)
#define FILE_POSITION_NETS      (2)
#define FILE_POSITION_END       (3)

int main(void) {
	char org_file_name[50] = {"orgin_file.txt\0"};
	char new_file_name[50] = {"new_file.txt\0"};
	FILE* p_orgin_file = NULL;
	FILE* p_new_file = NULL;
	char i,j;
	char str[100] = {'\0'};
	char str2[100] = {'\0'};
	char str3[100] = {'\0'};
	char str4[100] = {'\0'};
	int  file_position = FILE_POSITION_UNKOWN;

	puts("!!!Hello World, modify telesis file for allegro!!!"); /* prints !!!Hello World!!! */

	p_orgin_file = fopen(org_file_name, "r");
	if ( p_orgin_file == NULL ){
	  printf("%s dose not exist. Byebye.\n", org_file_name);
	  goto exit;
	}

    p_new_file = fopen(new_file_name, "w+");
	if ( p_new_file == NULL ){
	  printf("%s can not be created. Byebye.\n", new_file_name);
	  goto exit;
	}

	while ((fgets(str, 100, p_orgin_file)) != NULL){

		if ( strcmp (str, "$PACKAGES\n") == 0 ){
			file_position = FILE_POSITION_PACKAGES;
			fputs(str, p_new_file);
			continue;
		}
		if ( strcmp (str, "$NETS\n") == 0 ){
		    file_position = FILE_POSITION_NETS;
		    fputs(str, p_new_file);
		    continue;
		}
		if ( strcmp (str, "$End\n") == 0 ){
		    file_position = FILE_POSITION_END;
		    fputs(str, p_new_file);
		    continue;
		}

		if ( file_position == FILE_POSITION_PACKAGES ){
            i = 0;
		    while ( str[i] != '!' ){
               i++;
			}
		    strncpy (str2, str, i);
		    str2[i] = '\0';
			while ( str[i] != ';' ){
			   i++;
		    }
		    strcpy (str3, str+i);

            strcpy (str4, str2);
            strcat (str4, "!");
            strcat (str4, " ");
            strcat (str4, str2);
            strcat (str4, str3);
		    fputs( str4, p_new_file );
		    continue;
		}
		fputs( str, p_new_file );
	}

	printf("%s is created. Goodbye.\n", new_file_name);

	exit:
	if ( p_orgin_file != NULL ){
	fclose(p_orgin_file);
	}
	if ( p_new_file != NULL ){
	fclose(p_new_file);
	}
	return EXIT_SUCCESS;
}
