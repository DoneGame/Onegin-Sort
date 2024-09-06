#include <stdio.h>
#include <string.h>

int  my_strcmp (const char *s1, const char *s2);
void print_str (const char str_name[], const char *string);

int main () {
    const char s1[] = "cat";
    const char s2[] = "catee";

    print_str ("s1", s1);
    print_str ("s2", s2);

    printf ("\nmy_diff = %d\n", my_strcmp (s1, s2));
    printf ("\nstd_diff = %d\n", strcmp (s1, s2));

    return 0;
}

int my_strcmp (const char *string1, const char *string2) {
    int i = 0;
    for (; string1[i] != '\0' && string1[i] == string2[i]; i++) {}; 
    
    return string1[i] - string2[i];
}

void print_str (const char str_name[], const char *string) {
    printf ("%s = ", str_name);
    for (unsigned i = 0; i < strlen(string); i++)
        printf ("%c(%3d) ", string[i], string[i]);
    printf ("\n");
}
