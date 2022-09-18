// runQueue.c - a command-line interface to the Queue ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"

#define MAX 64

static void processOptions(int argc, char *argv[]);
static void showUsage(char *progname);
static void showWelcomeMessage(void);
static int getCommand(char *buf);
static char **tokenize(char *s, int *ntokens);
static void freeTokens(char **tokens);
static void showHelp(void);

static void runEnqueue(Queue q, int argc, char *argv[]);
static void runDequeue(Queue q, int argc, char *argv[]);
static void runFront(Queue q, int argc, char *argv[]);
static void runSize(Queue q, int argc, char *argv[]);
static void runDebug(Queue q, int argc, char *argv[]);
static void showCmdHelp(void);

////////////////////////////////////////////////////////////////////////

typedef struct command {
	char  *code;
	void (*fn)(Queue, int, char **);
	char  *argHint;
	char  *helpMsg;
} Command;

static Command COMMANDS[] = {
	{"+", runEnqueue, "<num>", "enqueue an element"},
	{"-", runDequeue, "",      "dequeue an element"},
	{"f", runFront,   "",      "get the front element"},
	{"s", runSize,    "",      "get the queue size"},
	{"d", runDebug,   "",      "call QueueDebugPrint"},
	{"?", NULL,       "",      "show this message"},
	{"q", NULL,       "",      "quit"},
};

////////////////////////////////////////////////////////////////////////

static bool ECHO = false;
static Command *currCommand = NULL;

int main(int argc, char *argv[]) {
	processOptions(argc, argv);
	showWelcomeMessage();

	Queue q = QueueNew();
	bool done = false;
	char cmd[MAX + 1] = {0};

	while (!done && getCommand(cmd)) {
		if (ECHO) {
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
					COMMANDS[i].fn(q, ntokens, tokens);
				}
			}

			if (!validCommand) {
				printf("Unknown command '%s'\n", cmdName);
			}
		}
		freeTokens(tokens);
	}

	QueueFree(q);
}

static void processOptions(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-e") == 0) {
			ECHO = true;
		} else {
			showUsage(argv[0]);
			exit(EXIT_FAILURE);
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
	printf("Interactive Queue Tester\n");
	printf("Enter ? to see the list of commands.\n");
}

static int getCommand(char *buf) {
	printf("> ");
	if (fgets(buf, MAX, stdin) != NULL) {
		int len = strlen(buf);
		if (len > 0 && buf[len - 1] != '\n') {
			buf[len] = '\n';
			buf[len + 1] = '\0';
		}
		return 1;
	} else {
		return 0;
	}
}

static char **tokenize(char *s, int *ntokens) {
	char *separators = " \t\n";
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

static void runEnqueue(Queue q, int argc, char *argv[]) {
	if (argc != 2) {
		showCmdHelp();
		return;
	}

	int elem = 0;
	char c;
	if (sscanf(argv[1], "%d%c", &elem, &c) != 1) {
		showCmdHelp();
		return;
	}

	QueueEnqueue(q, elem);
	printf("Enqueued %d\n", elem);
}

static void runDequeue(Queue q, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (QueueIsEmpty(q)) {
		printf("Error: The queue is empty!\n");
		return;
	}

	int elem = QueueDequeue(q);
	printf("Dequeued %d\n", elem);
}

static void runFront(Queue q, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	if (QueueIsEmpty(q)) {
		printf("Error: The queue is empty!\n");
		return;
	}

	int elem = QueueFront(q);
	printf("Front element is %d\n", elem);
}

static void runSize(Queue q, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	int size = QueueSize(q);
	printf("Queue size is %d\n", size);
}

static void runDebug(Queue q, int argc, char *argv[]) {
	if (argc != 1) {
		showCmdHelp();
		return;
	}

	QueueDebugPrint(q);
}

static void showCmdHelp(void) {
    printf("Usage: %s %s\n", currCommand->code, currCommand->argHint);
}

////////////////////////////////////////////////////////////////////////

