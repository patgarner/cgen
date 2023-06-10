#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

static const char *cgen_makefile_string = 
"<makefile>";

static const char *makefile_boiler_plate = 
"CC=gcc\n"
"CFLAGS=-I.\n"
"\n"
"TARGET=%s\n"
"\n"
"%%.o: %%.c\n"
"\t$(CC) -c -o $@ $< $(CFLAGS)\n"
"\n"
"$(TARGET): main.o\n"
"\t$(CC) -o $(TARGET) main.o\n"
"\n"
"run: $(TARGET)\n"
"\t./$(TARGET)\n"
"\n"
"install: $(TARGET)\n"
"\tinstall ./$(TARGET) /usr/local/bin/\n"
"\n"
"clean:\n"
"\trm -f *.o $(TARGET)\n"
"\n"
".PHONY: all run install clean\n";

const char *cgen_source = 
"<source_code>";

static const char *c_source_boiler_plate = "\
#include <stdio.h>			    \n\
#include <stdlib.h>			    \n\
  					    \n\
int main(int argc, char **argv) {\n\
  printf(\"Hello, World!\\n\");\n\
  return EXIT_SUCCESS;		\n\
}\n\
";

void print_usage() {
  printf("Usage: cgen program_name\n");
  exit(EXIT_FAILURE);
}

typedef struct _Args {
  char *program_name;
} Args;

Args parse_arguments(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
  }

  return (Args){.program_name = argv[1]};

  #if 0
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'n':
	break;
      default:
	print_usage();
      }
    }
  }
  #endif
}

bool make_program_directory(const char *program_name) {
  if (!program_name || !strlen(program_name))
    return false;

  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    strcat(cwd, "/");
    strcat(cwd, program_name); // Append the new directory to the cwd
  } else {
    perror("getcwd() error");
    return false;
  }

  struct stat st = {0};
  if (stat(cwd, &st) != -1) {
    perror("Directory already exists!");
    printf("%s\n", cwd);
    return false;
  }
  
  // The 0777 is the file permission for the new directory
  if (mkdir(cwd, 0777) == -1) {
    perror("Error creating directory!");
    return false;
  }

  printf("directory created: %s\n", cwd);

  return true;
}

bool write_file(const char *filename, const char *path, const char *contents) {
  char output_path[PATH_MAX];
  strcpy(output_path, path);
  strcat(output_path, "/");
  strcat(output_path, filename);

  printf("output_path = %s\n", output_path);

  struct stat st = {0};
  if (stat(output_path, &st) != -1) {
    perror("File already exists!");
    printf("%s\n", output_path);
    return false;
  }
    
  FILE *file = fopen(output_path, "w+");

  if (file == NULL) {
    char errorString[256];
    int someValue = 5;  // Some value you want to include in the error message

    sprintf(errorString, "Error %d opening file %s", someValue, output_path);
    perror(errorString);

    return false;
  }

  fwrite(contents, sizeof(char), strlen(contents), file);

  fclose(file);
  return true;
}

char* str_replace(const char* original, const char* pattern, const char* replacement) {
    size_t i, count = 0;
    size_t patlen = strlen(pattern);
    size_t replen = strlen(replacement);
    for (i = 0; original[i] != '\0'; i++) {
        if (!memcmp(&original[i], pattern, patlen)) {
            count++;
        }
    }
    char* result = malloc(i + count * (replen - patlen) + 1);
    if (!result) {
        return NULL;
    }
    char* retptr = result;
    for (i = 0; original[i] != '\0'; i++) {
        if (!memcmp(&original[i], pattern, patlen)) {
            memcpy(retptr, replacement, replen);
            retptr += replen;
            i += patlen - 1;
        } else {
            *retptr++ = original[i];
        }
    }
    *retptr = '\0';
    return result;
}

void writefiles(const char *path, const char *makefile, const char *sourcefile) {
    write_file("Makefile", path, makefile);
    write_file("main.c", path, sourcefile);
}

int main(int argc, char **argv) {
  Args args = parse_arguments(argc, argv);

  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    strcat(cwd, "/");
    strcat(cwd, args.program_name); // Append the new directory to the cwd
  } else {
    perror("getcwd() error");
    return EXIT_FAILURE;
  }

  if (!make_program_directory(args.program_name))
    return EXIT_FAILURE;

  if (strcmp(args.program_name, "cgen") == 0) {
    writefiles(cwd, cgen_makefile_string, cgen_source);
  } else {
    char makefile[1024];
    snprintf(makefile, sizeof(makefile), makefile_boiler_plate, args.program_name);
    writefiles(cwd, makefile, c_source_boiler_plate);
  }
  
  return EXIT_SUCCESS;
}
