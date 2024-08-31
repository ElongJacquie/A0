#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

// Funktion zur Anzeige der Benutzungsanweisung
void print_usage();

int main(int argc, char *argv[])
{
    int opt;
    char* date_str = NULL;
    struct tm date_tm = {0}; // Struktur für Datum und Uhrzeit initialisieren
    time_t date_time;
    char weekday[10];

    // Verarbeite die Befehlszeilenoptionen
    while((opt = getopt(argc, argv, "t:")) != -1) {
        switch(opt) {
            case 't':
                date_str = optarg; // Speichere das Datum als String
                break;
            default:
                print_usage(); // Zeige Benutzungsanweisung an
                exit(EXIT_FAILURE); // Beende das Programm bei ungültiger Option
        }
    }

    // Überprüfe, ob ein Datum angegeben wurde
    if(date_str == NULL) {
        print_usage(); // Zeige Benutzungsanweisung an
        exit(EXIT_FAILURE); // Beende das Programm bei fehlendem Datum
    }

    // Initialisiere die Struktur für das Mindestdatum
    struct tm min_tm1 = {0};

    // Setze das Mindestdatum auf den 01.01.1900
    if (strptime("1900-01-01", "%Y-%m-%d", &min_tm1) == NULL) {
        fprintf(stderr, "Error initializing minimum date.\n");
        exit(EXIT_FAILURE);
    }

    // Setze die Struktur für das Eingabedatum
    if (strptime(date_str, "%Y-%m-%d", &date_tm) == NULL) {
        fprintf(stderr, "Invalid date format. Please use YYYY-MM-DD.\n");
        exit(EXIT_FAILURE); // Beende das Programm bei ungültigem Datum
    }

    // Überprüfe, ob das Datum nach dem 01.01.2024 liegt
    if (difftime(mktime(&date_tm), mktime(&min_tm1)) < 0) {
        fprintf(stderr, "Date must be after 2024-01-01.\n");
        exit(EXIT_FAILURE); // Beende das Programm, wenn das Datum nicht gültig ist
    }

    // Konvertiere die Struktur tm in time_t
    date_time = mktime(&date_tm);
    if (date_time == -1) {
        fprintf(stderr, "Failed to convert date to time_t.\n");
        exit(EXIT_FAILURE);
    }

    // Bestimme den Wochentag des eingegebenen Datums
    strftime(weekday, sizeof(weekday), "%A", &date_tm);

    // Gebe den Wochentag aus
    printf("The day of the week for %s is %s.\n", date_str, weekday);

    return 0;
}

// Funktion zur Anzeige der Benutzungsanweisung
void print_usage() {
   printf("Usage: ./a07_1 -t YYYY-MM-DD\n"); // Zeigt die korrekte Verwendung des Programms an
}
