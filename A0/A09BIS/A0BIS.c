#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <csv.h>

#define BUFFER_SIZE 1024

typedef struct {
    char **headers;
    char ***rows;
    int num_columns;
    int num_rows;
    int is_header_row;
} CsvData;

// Fonction de rappel pour gérer les champs CSV
void field_callback(void *s, size_t len, void *data) {
    CsvData *csv_data = (CsvData *)data;

    if (csv_data->num_rows == 0) {
        // Gérer les en-têtes
        csv_data->headers = realloc(csv_data->headers, (csv_data->num_columns + 1) * sizeof(char *));
        if (!csv_data->headers) {
            perror("Erreur de réallocation pour les en-têtes");
            exit(EXIT_FAILURE);
        }
        csv_data->headers[csv_data->num_columns] = strndup(s, len);
        if (!csv_data->headers[csv_data->num_columns]) {
            perror("Erreur d'allocation pour l'en-tête");
            exit(EXIT_FAILURE);
        }
        csv_data->num_columns++;
    } else {
        // Initialisation des lignes si nécessaire
        if (csv_data->num_columns == 0) {
            csv_data->rows = realloc(csv_data->rows, (csv_data->num_rows + 1) * sizeof(char **));
            if (!csv_data->rows) {
                perror("Erreur de réallocation pour les lignes");
                exit(EXIT_FAILURE);
            }
            csv_data->rows[csv_data->num_rows] = NULL;
        }

        // Gérer les lignes de données
        csv_data->rows[csv_data->num_rows - 1] = realloc(csv_data->rows[csv_data->num_rows - 1], (csv_data->num_columns + 1) * sizeof(char *));
        if (!csv_data->rows[csv_data->num_rows - 1]) {
            perror("Erreur de réallocation pour une ligne de données");
            exit(EXIT_FAILURE);
        }

        csv_data->rows[csv_data->num_rows - 1][csv_data->num_columns - 1] = strndup(s, len);
        if (!csv_data->rows[csv_data->num_rows - 1][csv_data->num_columns - 1]) {
            perror("Erreur d'allocation pour une cellule de données");
            exit(EXIT_FAILURE);
        }
    }
}

// Fonction de rappel pour gérer les lignes CSV
void row_callback(int c, void *data) {
    CsvData *csv_data = (CsvData *)data;

    // Ajouter une nouvelle ligne (sauf pour la première ligne, qui est l'en-tête)
    if (csv_data->num_rows > 0 || csv_data->num_columns > 0) {
        csv_data->num_rows++;
        char ***new_rows = realloc(csv_data->rows, csv_data->num_rows * sizeof(char **));
        if (!new_rows) {
            perror("Erreur de réallocation pour les lignes");
            exit(EXIT_FAILURE);
        }
        csv_data->rows = new_rows;
        csv_data->rows[csv_data->num_rows - 1] = NULL; // Initialiser la nouvelle ligne à NULL
    }
    // Réinitialiser le nombre de colonnes après chaque ligne
    csv_data->num_columns = 0;
}

// Fonction pour convertir en majuscules
void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// Fonction pour convertir en minuscules
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

// Fonction pour afficher les données CSV
void print_csv(CsvData *csv_data, int uppercase, int lowercase, int sort_columns) {
    int *column_order = malloc(csv_data->num_columns * sizeof(int));
    if (!column_order) {
        perror("Erreur d'allocation mémoire pour l'ordre des colonnes");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < csv_data->num_columns; i++) {
        column_order[i] = i;
    }

    if (sort_columns) {
        // Tri des en-têtes si nécessaire
        for (int i = 0; i < csv_data->num_columns - 1; i++) {
            for (int j = i + 1; j < csv_data->num_columns; j++) {
                if (strcmp(csv_data->headers[column_order[i]], csv_data->headers[column_order[j]]) > 0) {
                    int temp = column_order[i];
                    column_order[i] = column_order[j];
                    column_order[j] = temp;
                }
            }
        }
    }

    // Affichage des en-têtes
    printf("Data:\n");
    for (int i = 0; i < csv_data->num_columns; i++) {
        char *header = csv_data->headers[column_order[i]];
        if (uppercase) to_uppercase(header);
        if (lowercase) to_lowercase(header);
        printf("%s\t", header);
    }
    printf("\n");

    // Affichage des lignes de données
    for (int i = 0; i < csv_data->num_rows; i++) {
        for (int j = 0; j < csv_data->num_columns; j++) {
            char *field = csv_data->rows[i][column_order[j]];
            if (uppercase) to_uppercase(field);
            if (lowercase) to_lowercase(field);
            printf("%s\t", field);
        }
        printf("\n");
    }

    free(column_order);
}

// Fonction principale
int main(int argc, char *argv[]) {
    FILE *fp = fopen("measurements.csv", "r");
    if (!fp) {
        perror("Unable to open file!");
        return EXIT_FAILURE;
    }

    CsvData csv_data = {NULL, NULL, 0, 0, 1};  // Initialisation correcte

    struct csv_parser parser;
    csv_init(&parser, 0);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        if (csv_parse(&parser, buffer, bytes_read, field_callback, row_callback, &csv_data) != bytes_read) {
            fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&parser)));
            return EXIT_FAILURE;
        }
    }

    csv_fini(&parser, field_callback, row_callback, &csv_data);
    csv_free(&parser);
    fclose(fp);

    // Gestion des arguments pour les options d'affichage
    int uppercase = 0, lowercase = 0, sort_columns = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--uppercase") == 0) uppercase = 1;
        if (strcmp(argv[i], "--lowercase") == 0) lowercase = 1;
        if (strcmp(argv[i], "--sort") == 0) sort_columns = 1;
    }

    print_csv(&csv_data, uppercase, lowercase, sort_columns);

    // Libération de la mémoire
for (int i = 0; i < csv_data.num_columns; i++) {
    if (csv_data.headers[i]) {
        free(csv_data.headers[i]); // Libérer chaque en-tête
    }
}
free(csv_data.headers); // Libérer le tableau des en-têtes

for (int i = 0; i < csv_data.num_rows; i++) {
    for (int j = 0; j < csv_data.num_columns; j++) {
        if (csv_data.rows[i][j]) {
            free(csv_data.rows[i][j]); // Libérer chaque cellule
        }
    }
    free(csv_data.rows[i]); // Libérer chaque ligne
}
free(csv_data.rows); // Libérer le tableau des lignes

    return 0;
}

