// Command-line interface to the Student DB ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Record.h"
#include "StudentDb.h"

#define MAX 8192

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progName);
static void showWelcomeMessage(void);
static bool getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runInsertRecord(StudentDb db, int argc, char *argv[]);
static void runListByZid(StudentDb db, int argc, char *argv[]);
static void runListByName(StudentDb db, int argc, char *argv[]);
static void runDeleteByZid(StudentDb db, int argc, char *argv[]);
static void runFindByZid(StudentDb db, int argc, char *argv[]);
static void runFindByName(StudentDb db, int argc, char *argv[]);
static void showCmdHelp(void);

static void showRecordList(List l);

////////////////////////////////////////////////////////////////////////

typedef struct command {
    char  *code;
    void (*fn)(StudentDb, int, char **);
    char  *argHint;
    char  *helpMsg;
} Command;

static Command COMMANDS[] = {
    {"+",  runInsertRecord, "<zid> <family name> <given name>",
                            "add a student record"},
    {"lz", runListByZid,    "",
                            "list all records in order of zid"},
    {"ln", runListByName,   "",
                            "list all records in order of name"},
    {"d",  runDeleteByZid,  "<zid>",
                            "delete a student record"},
    {"fz", runFindByZid,    "<zid>",
                            "find a student record by zid"},
    {"fn", runFindByName,   "<family name> <given name>",
                            "find student records by name"},
    
    // Meta-commands
    {"?",  NULL,            "", "show this message"},
    {"q",  NULL,            "", "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool echo = false;
static Command *currCommand = NULL;

int main(int argc, char *argv[]) {
    processOptions(argc, argv);
    showWelcomeMessage();

    StudentDb db = DbNew();
    bool done = false;
    char cmd[MAX + 1] = {0};

    while (!done && getCommand(cmd)) {
        if (echo) {
            printf("%s", cmd);
        }

        int ntokens = 0;
        char **tokens = tokenize(cmd, &ntokens);
        if (ntokens == 0) {
            free(tokens);
            continue;
        }
        
        char *cmdName = tokens[0];

        // Meta-commands
        if (strcmp(cmdName, "?") == 0) {
            showHelp();
        } else if (strcmp(cmdName, "q") == 0) {
            done = true;
        
        // Actual commands
        } else {
            bool validCommand = false;

            int numCommands = sizeof(COMMANDS) / sizeof(Command);
            for (int i = 0; i < numCommands; i++) {
                if (strcmp(cmdName, COMMANDS[i].code) == 0) {
                    validCommand = true;
                    currCommand = &COMMANDS[i];
                    COMMANDS[i].fn(db, ntokens, tokens);
                }
            }

            if (!validCommand) {
                printf("Unknown command '%s'\n", cmdName);
            }
        }
        freeTokens(tokens);
    }

    DbFree(db);
}

static void processOptions(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            showUsage(argv[0]);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-e") == 0) {
            echo = true;
        }
    }
}

static void showUsage(char *progName) {
    printf("Usage: %s [options]...\n"
           "Options:\n"
           "    -h      show this help message\n"
           "    -e      echo - echo all commands\n",
           progName);
}

static void showWelcomeMessage(void) {
    printf("StudentDb v1.0\n");
    printf("Enter ? to see the list of commands.\n");
}

static bool getCommand(char *buf) {
    printf("> ");
    if (fgets(buf, MAX, stdin) != NULL) {
        int len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            buf[len] = '\n';
            buf[len + 1] = '\0';
        }
        return true;
    } else {
        return false;
    }
}

static char **tokenize(char *s, int *ntokens) {
    char *separators = " \t\r\n";
    *ntokens = 0;

    char **tokens = calloc((strlen(s) + 1), sizeof(*tokens));
    assert(tokens != NULL);

    while (*s != '\0') {
        s += strspn(s, separators);

        if (*s == '\0') {
            break;
        }

        size_t length = strcspn(s, separators);

        char *token = strndup(s, length);
        assert(token != NULL);
        s += length;

        tokens[*ntokens] = token;
        (*ntokens)++;
    }

    tokens[*ntokens] = NULL;

    tokens = realloc(tokens, (*ntokens + 1) * sizeof(*tokens));
    assert(tokens != NULL);

    return tokens;
}

static void freeTokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

static void showHelp(void) {
    printf("Commands:\n");
    int numCommands = sizeof(COMMANDS) / sizeof(Command);
    for (int i = 0; i < numCommands; i++) {
        printf("%5s %-18s %s\n", COMMANDS[i].code, COMMANDS[i].argHint,
                                 COMMANDS[i].helpMsg);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////
// Commands

static void runInsertRecord(StudentDb db, int argc, char *argv[]) {
    if (argc != 4) {
        showCmdHelp();
        return;
    }

    char *zidStr = argv[1];
    char *familyName = argv[2];
    char *givenName = argv[3];

    int zid = atoi(zidStr);
    if (zid == 0 || zid < MIN_ZID || zid > MAX_ZID) {
        printf("Error: Invalid zid '%s'\n", zidStr);
        return;
    }

    Record r = RecordNew(zid, familyName, givenName);
    if (r == NULL) {
        return;
    }

    if (DbInsertRecord(db, r)) {
        printf("Successfully inserted record!\n");
    } else {
        printf("There is already a record with zid '%d'\n", zid);
        RecordFree(r);
    }
}

static void runListByZid(StudentDb db, int argc, char *argv[]) {
    if (argc != 1) {
        showCmdHelp();
        return;
    }

    DbListByZid(db);
}

static void runListByName(StudentDb db, int argc, char *argv[]) {
    if (argc != 1) {
        showCmdHelp();
        return;
    }

    DbListByName(db);
}

static void runDeleteByZid(StudentDb db, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *zidStr = argv[1];

    int zid = atoi(zidStr);
    if (zid == 0 || zid < MIN_ZID || zid > MAX_ZID) {
        printf("Error: Invalid zid '%s'\n", zidStr);
        return;
    }

    if (DbDeleteByZid(db, zid)) {
        printf("Successfully deleted record!\n");
    } else {
        printf("Could not find a record with zid '%d' to delete\n", zid);
    }
}

static void runFindByZid(StudentDb db, int argc, char *argv[]) {
    if (argc != 2) {
        showCmdHelp();
        return;
    }

    char *zidStr = argv[1];

    int zid = atoi(zidStr);
    if (zid == 0 || zid < MIN_ZID || zid > MAX_ZID) {
        printf("Error: Invalid zid '%s'\n", zidStr);
        return;
    }

    Record r = DbFindByZid(db, zid);
    if (r == NULL) {
        printf("No records with zid '%d'\n", zid);
    } else {
        printf("Found a record:\n");
        RecordShow(r);
        printf("\n");
    }
}

static void runFindByName(StudentDb db, int argc, char *argv[]) {
    if (argc != 3) {
        showCmdHelp();
        return;
    }

    char *familyName = argv[1];
    char *givenName = argv[2];

    List l = DbFindByName(db, familyName, givenName);
    if (ListSize(l) == 0) {
        printf("No records found\n");
    } else {
        printf("Found records:\n");
        showRecordList(l);
    }
    ListFree(l);
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

static void showRecordList(List l) {
    ListIterator it = ListItNew(l);
    while (ListItHasNext(it)) {
        RecordShow(ListItNext(it));
        printf("\n");
    }
    ListItFree(it);
}
