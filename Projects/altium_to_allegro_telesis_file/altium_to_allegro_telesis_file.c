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
	char org_file_name[50] = {"a.txt\0"};
	char new_file_name[50] = {"b.txt\0"};
	FILE* p_orgin_file = NULL;
	FILE* p_new_file = NULL;
	int i,j;
	char str_org[100] = {'\0'};
	char str_sym[100] = {'\0'};
	char str_dev[100] = {'\0'};
	char str_val[100] = {'\0'};
	char str_ref[100] = {'\0'};
	char str_new[100] = {'\0'};
	int  file_position = FILE_POSITION_UNKOWN;

	puts("!!!Hello World, modify telesis file for allegro!!!"); /* prints !!!Hello World!!! */

	p_orgin_file = fopen(org_file_name, "r");
	if ( p_orgin_file == NULL ){
	  printf("%s dose not exist.\n", org_file_name);
	  printf("Please change the name of orginal file to %s\n", org_file_name);
	  printf("Press enter to exit...");
	  getchar();
	  goto exit;
	}

    p_new_file = fopen(new_file_name, "w+");
	if ( p_new_file == NULL ){
	  printf("%s can not be created. Byebye.\n", new_file_name);
	  goto exit;
	}

	while ((fgets(str_org, 100, p_orgin_file)) != NULL){

		if ( strcmp (str_org, "$PACKAGES\n") == 0 ){
			file_position = FILE_POSITION_PACKAGES;
			fputs(str_org, p_new_file);
			continue;
		}
		if ( strcmp (str_org, "$NETS\n") == 0 ){
		    file_position = FILE_POSITION_NETS;
		    fputs(str_org, p_new_file);
		    continue;
		}
		if ( strcmp (str_org, "$End\n") == 0 ){
		    file_position = FILE_POSITION_END;
		    fputs(str_org, p_new_file);
		    continue;
		}

		if ( file_position == FILE_POSITION_PACKAGES ){
            i = 0;
			// get SYM_NAME
		    while ( str_org[i] != '!' ){
               i++;
			}
		    strncpy (str_sym, str_org, i);
		    str_sym[i] = '\0';

			// get COMP_VALUE
			j = 0;
			while ( str_org[i+j+2] != ';' ){   // 2 is ' ' + '!' in str_org
			   j++;
		    }
		    strncpy (str_val, str_org+i+2, j);
			str_val[j] = '\0';

			// get REFDES
			strcpy (str_ref, str_org+i+j+2+2);  // 2 is ' ' + ';' in str_org

			// combine into new string
            strcpy (str_new, str_sym);   // SYM_NAME
            strcat (str_new, "!");
            strcat (str_new, " ");
            strcat (str_new, str_sym);   // DEVICE_TYPE
            strcat (str_new, "!");
            strcat (str_new, " ");
			strcat (str_new, "\'");
			strcat (str_new, str_val);   // COMP_VALUE
			strcat (str_new, "\'");
			strcat (str_new, ";");
            strcat (str_new, " ");
			strcat (str_new, str_ref);
		    fputs( str_new, p_new_file );
		    continue;
		}

		fputs( str_org, p_new_file );
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
