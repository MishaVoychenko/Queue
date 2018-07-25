#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
const int quantity = 5;

enum PRIORIRIES {
	LOWEST,
	LOW,
	MEDIUM,
	HIGH,
	HIGHEST
};

struct queue
{
	int priority;
	char *message;
	struct queue *next;
};

void dequeue(struct queue **root)
{
	if (*root == NULL) printf("delete_root: we have not root\n");
	else
	{
		struct queue *temp = *root;
		*root = (*root)->next;
		free(temp);
	}
}

void enqueue(struct queue **root, char *message, int priority)
{
	struct queue *duplicate, *duplicate_past;
	int number = 1;
	duplicate = *root;
	duplicate_past = NULL;
	if (*root != NULL)
	{
		while (duplicate->next != NULL)
		{
			number++;
			duplicate_past = duplicate;
			duplicate = duplicate->next;
		}
		if (number == quantity)
		{
			if (duplicate->priority < priority)
			{
				duplicate_past->next = NULL;
				free(duplicate);
			}
			else return;
		}
	}

	struct queue *temp;
	temp = (struct queue*)malloc(sizeof(struct queue));
	temp->priority = priority;
	temp->message = message;
	temp->next = NULL;
	if ((*root) == NULL) *root = temp;
	else
	{
		duplicate = *root;
		duplicate_past = NULL;
		while (duplicate != NULL && duplicate->priority >= priority)
		{
			duplicate_past = duplicate;
			duplicate = duplicate->next;
		}
		temp->next = duplicate;
		if (duplicate_past != NULL) duplicate_past->next = temp;
		else *root = temp;
	}
}

void queue_print(struct queue *root)
{
	struct queue *duplicate;
	duplicate = root;
	if (root == NULL) printf("turn_print: we have not root");
	else
		do {
			printf("priority %d: %s\n", duplicate->priority, duplicate->message);
			duplicate = duplicate->next;
		} while (duplicate != NULL);
}

int main()
{
	struct queue *root = NULL;
	enqueue(&root, "message 1", LOW);
	enqueue(&root, "message 2", HIGH);
	dequeue(&root);
	enqueue(&root, "message 3", HIGH);
	enqueue(&root, "message 4", HIGHEST);
	enqueue(&root, "message 5", LOW);
	enqueue(&root, "message 6", LOWEST);
	enqueue(&root, "message 7", LOWEST);
	queue_print(root);
	getchar();
	return 0;
}