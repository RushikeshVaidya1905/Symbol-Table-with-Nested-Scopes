#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Structure for a symbol
typedef struct Symbol 
{
    char name[50];
    int value;
    struct Symbol* next;
}Symbol;

// Structure for a scope
typedef struct Scope 
{
    Symbol* table[TABLE_SIZE];
    struct Scope* parent;
} Scope;

// Hash function
unsigned int hash(const char* name) 
{
    unsigned int hash = 0;
    while (*name) 
    {
        hash = (hash * 31) + *name++;
    }
    return hash % TABLE_SIZE;
}

// Create a new scope
Scope* create_scope(Scope* parent) 
{
    Scope* new_scope = (Scope*)malloc(sizeof(Scope));
    if (!new_scope) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        new_scope->table[i] = NULL;
    }
    new_scope->parent = parent;
    return new_scope;
}

// Insert a variable in the current scope
void insert(Scope* scope, const char* name, int value) 
{
    unsigned int index = hash(name);
    if (!scope) {
        printf("No active scope so cannot assign variable '%s' \n", name);
        return;
    }

    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
    if (!new_symbol) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(new_symbol->name, name);
    new_symbol->value = value;
    new_symbol->next = scope->table[index];
    scope->table[index] = new_symbol;
}

// Lookup a variable in the current and surrounding scopes
int lookup(Scope* scope, const char* name) 
{
    unsigned int index = hash(name);
    if (!scope) {
        printf("No active scope so cannot print variable '%s' \n", name);
        return -1;
    }
    Scope* current_scope = scope;
    while (current_scope) 
    {
        Symbol* entry = current_scope->table[index];
        while (entry) 
        {
            if (strcmp(entry->name, name) == 0) 
            {
                return entry->value;
            }
            entry = entry->next;
        }
        current_scope = current_scope->parent;
    }
    printf("Variable %s not found!\n", name);
    return -1;
}

int main() {
    FILE *file = fopen("file.txt", "r");
    if (!file) 
    {
        printf("Error opening file!\n");
        return 1;
    }

    Scope* current_scope = NULL;
    char command[50], var[50];
    int value;
    
    while (fscanf(file, "%s", command) != EOF) 
    {
        if (strcmp(command, "begin") == 0) 
        {
            current_scope = create_scope(current_scope);
        } 
        else if (strcmp(command, "assign") == 0) 
        {
            fscanf(file, "%s %d", var, &value);
            insert(current_scope, var, value);
        } 
        else if (strcmp(command, "print") == 0) 
        {
            fscanf(file, "%s", var);
            printf("%s = %d\n", var, lookup(current_scope, var));
        } 
        else if (strcmp(command, "end") == 0) 
        {
            if (current_scope) 
            {
                Scope* temp = current_scope;
                current_scope = current_scope->parent;
                free(current_scope->table);
                free(current_scope);
            }
            else
            {
                printf("No current active Scope\n");
            }
        }
    }
    fclose(file);
    return 0;
}
