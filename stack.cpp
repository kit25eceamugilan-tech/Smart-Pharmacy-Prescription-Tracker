#define _CRT_SECURE_NO_WARNINGS   // disables unsafe warnings in Visual Studio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Prescription {
    char patient[50];
    char medicine[50];
    char dosage[20];
    int duration;
};

struct Stack {
    struct Prescription items[MAX];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, struct Prescription p) {
    if (isFull(s)) {
        printf("Stack Overflow! Cannot add more prescriptions.\n");
    }
    else {
        s->items[++s->top] = p;
        printf("Prescription for %s added successfully.\n", p.patient);
    }
}

struct Prescription pop(struct Stack* s) {
    struct Prescription empty = { "", "", "", 0 };
    if (isEmpty(s)) {
        printf("Stack Underflow! No prescriptions to remove.\n");
        return empty;
    }
    else {
        return s->items[s->top--];
    }
}

struct Prescription peek(struct Stack* s) {
    struct Prescription empty = { "", "", "", 0 };
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return empty;
    }
    else {
        return s->items[s->top];
    }
}

void display(struct Stack* s) {
    if (isEmpty(s)) {
        printf("No prescriptions recorded.\n");
    }
    else {
        printf("\n--- Prescription Records ---\n");
        for (int i = 0; i <= s->top; i++) {
            printf("Patient: %s | Medicine: %s | Dosage: %s | Duration: %d days\n",
                s->items[i].patient,
                s->items[i].medicine,
                s->items[i].dosage,
                s->items[i].duration);
        }
        printf("----------------------------\n");
    }
}

int main() {
    struct Stack s;
    initStack(&s);

    int choice;
    do {
        printf("\nSmart Pharmacy Prescription Tracker\n");
        printf("1. Add Prescription\n");
        printf("2. Remove Last Prescription\n");
        printf("3. View Latest Prescription\n");
        printf("4. Display All Prescriptions\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            struct Prescription p;

            printf("Enter Patient Name: ");
            fgets(p.patient, sizeof(p.patient), stdin);
            p.patient[strcspn(p.patient, "\n")] = 0;

            printf("Enter Medicine Name: ");
            fgets(p.medicine, sizeof(p.medicine), stdin);
            p.medicine[strcspn(p.medicine, "\n")] = 0;

            printf("Enter Dosage: ");
            fgets(p.dosage, sizeof(p.dosage), stdin);
            p.dosage[strcspn(p.dosage, "\n")] = 0;

            printf("Enter Duration (days): ");
            scanf("%d", &p.duration);
            getchar(); // clear newline

            push(&s, p);
        }
        else if (choice == 2) {
            struct Prescription removed = pop(&s);
            if (strlen(removed.patient) > 0) {
                printf("Removed prescription for %s.\n", removed.patient);
            }
        }
        else if (choice == 3) {
            struct Prescription latest = peek(&s);
            if (strlen(latest.patient) > 0) {
                printf("Latest Prescription → Patient: %s | Medicine: %s | Dosage: %s | Duration: %d days\n",
                    latest.patient, latest.medicine, latest.dosage, latest.duration);
            }
        }
        else if (choice == 4) {
            display(&s);
        }
        else if (choice == 5) {
            printf("Exiting... Thank you!\n");
        }
        else {
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
}
