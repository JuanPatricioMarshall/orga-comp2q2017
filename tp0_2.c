#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

int N = 100;

typedef struct {
  char *array;
  size_t used;
  size_t size;
} WordArray;

void init_array(WordArray *a, size_t initial_size){
    a->array = (char*)malloc(sizeof(char*)*initial_size);
    a->used = 0;
    a->size = initial_size;
}

void insert_char(WordArray *a, char c){
    if (a->used == a->size){
        size_t new_size = a->size*2;
        a->array = (char*)realloc(a->array, sizeof(char*)*new_size);
        a->size = new_size;
    }
    a->array[a->used]=c;
    a->array[a->used+1]='\0';
    a->used++;
}

void free_array(WordArray *a){
    free(a->array);
    a->array = NULL;
    a->size = a->used = 0;
}

/* imprimir el uso de tp0 */
void print_usage() {
    printf("Usage: tp0 -i [input_file] -o [output_file]\n");
}

/* imprimir la pagina de ayuda */

void print_help() {
    printf("\tUsage:\n"
    	"\t\ttp0 -h\n"
    	"\t\ttp0 -V\n"
    	"\t\ttp0 [options]\n"
    	"\tOptions:\n"
    	"\t\t-V, --version\tPrint version and quit.\n"
    	"\t\t-h, --help\tPrint this information.\n"
    	"\t\t-i, --input\tLocation of the input file.\n"
    	"\t\t-o, --output\tLocation of the output file.\n"
    	"\tExamples:\n"
    	"\t\ttp0 -i ~/input -o ~/output\n");
}

/* imprimir la version del programa */
void print_version(){
    printf("tp0 1.0\n");
}

/* funcion para determinar si una palabra es capicua o no */
int es_capicua(char *palabra){

    size_t len = strlen(palabra); //  hay que ver si se puede usar strlen

    int capicua = 1;
    int i=0;
    while (capicua && i < (len / 2)){
        if (tolower(palabra[i]) != tolower(palabra[len - i - 1])){
            return 0;
        }
        i++;
    }
    return 1;
}

/* Lee la palabra de un archivo y la devuelve en word */
int read_word (FILE *f, char *word) {
    return fscanf(f, " %99s", word);
}

int main(int argc, char *argv[]) {

    int opt= 0;

    int help = -1;
    int version = -1;
    int input = -1;
    int output =-1;

    char *input_filename = NULL;
    char *output_filename = NULL;

    // especificacion de las opciones
    static struct option long_options[] = {
        {"help",     no_argument,       0,  'h' },
        {"version",  no_argument,       0,  'V' },
        {"input",    required_argument, 0,  'i' },
        {"output",   required_argument, 0,  'o' },
        {0,          0,                 0,  0   }
    };

    int long_index = 0;

    // evaluacion de los parametros enviados al programa
    while ((opt = getopt_long(argc, argv,"hVui:o:", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
            case 'h' :
                help = 0;
                break;
            case 'V' :
                version = 0;
                break;
            case 'i' :
                input = 0;
                input_filename = optarg; 
                break;
            case 'o' :
                output = 0;
                output_filename = optarg;
                break;
            case '?':
            	exit(1);
            default:
                print_usage(); 
                exit(EXIT_FAILURE);
        }
    }

    // procesamiento de los parametros
    if (help == 0) {
        print_help();
        exit(0);
    }
    else if (version == 0) {
        print_version();
        exit(0);
    }

    /* Si no se recibe parametro de ayuda o version se ejecuta el programa */

    // estableciendo los archivos de entrada y salida
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    
    if (input == 0){
        input_file = fopen(input_filename,"r");
        if (input_file == NULL) {
            printf ("can't open input file, errno = %d\n", errno);
            return 1;
        }
    }
    if (output == 0){
        output_file = fopen(output_filename,"w");
        if (output_file == NULL) {
            printf ("Can't open output file, errno = %d\n", errno);
            return 1;
        }
    }

    /* ejecucion del programa */
    printf("A\n");
    /*char *word = malloc(sizeof(char *) * N);
    int i = read_word(input_file, word);
    while (i == 1){
        if (es_capicua(word)){
        	fprintf(output_file,"%s\n", word);
        }
		i = read_word(input_file, word);
    }
    free(word);*/

    printf("Hola\n");
    WordArray a;
    init_array(&a, 1);
    insert_char(&a, 'a');
    insert_char(&a, 'a');
    insert_char(&a, 'a');
    insert_char(&a, 'a');
    printf("%zd\n", a.size);
    printf("%s\n", a.array);
    free_array(&a);


    // cierro los archivos
    
    if (input == 0){
        fclose(input_file);
    }
    if (output == 0){
        fclose(output_file);
    }

    return 0;
}
