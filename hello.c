#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>


int x = 0;



int main() {
    int con = 1;
    Node *head = malloc(sizeof (Node));
    FILE *file = fopen ("/Users/idokah/OS-Course/HW1/in","r");
    head->expr = NULL ; head->next = NULL ;
    while (con) {
        char input[MAX_COMMAND_LEN];
        fgets(input, MAX_COMMAND_LEN, file);
        con = handle_input(input, file, head);
//        printf("\n");
    }
    return 0;
}

//returns 0 if the input is finished else 1
int handle_input(char *line, FILE *file, Node *head) {
    char operand_line[MAX_COMMAND_LEN];
    if (need_next_line(line)) {
        fgets(operand_line, MAX_COMMAND_LEN, file);
    }

    if (is_string_includes(line, 'X')) {
        sscanf(operand_line, "%d", &x);
        setbuf(stdout, 0);
        printf("X = %d\n", x);
    }

    if (is_string_includes(line, 'N')) {
        int exp_type = get_type(line);
        operand operand_a, operand_b;
        get_operands(operand_line, &operand_a, &operand_b);
        exp *new_expr = malloc (sizeof(exp));
        new_expr->type = exp_type;
        new_expr->oper1 = operand_a;
        new_expr->oper2 = operand_b;
        push_last(head, new_expr);
    }

    if (is_string_includes(line, 'P') || is_string_includes(line, 'E')) {
        int E = is_string_includes(line, 'E');
        enum WHOM_TO_OUTPUT output = who_to_output(line);
        switch (output) {
            case CURRENT:
                print_last_expr(head, E);
                break;
            case ALL_EXP:
                print_all_expr(head,E);
                break;
            case NONE:
                break;
        }
    }

    if (is_string_includes(line, 'L')){
        return 0;
    }
    return 1;
}



void print_all_expr(Node *head, int E) {
    Node *cur = head;
    while (cur != NULL){
        print_expr(cur->expr, E);
        cur = cur->next;
    }
    return;
}

void print_last_expr(Node *head, int E) {
    Node *last_node = return_last_node(head);
    print_expr(last_node->expr, E);
    return;
}

void print_expr(exp *pExp, int E) {
    print_operand(pExp->oper1);
    printType(pExp->type);
    print_operand(pExp->oper2);
    if (E){
        int result = eval_expr(pExp);
        setbuf(stdout, 0);
        printf(" = %d",result);
    }
    printf("\n");
    return;
}

int eval_expr(exp *pExp) {
    int val1, val2;
    val1 = pExp->oper1.type == VAR_X ? x : pExp->oper1.val;
    val2 = pExp->oper2.type == VAR_X ? x : pExp->oper2.val;
    //what if the type is BAD_OPERAND?
    switch (pExp->type) {
        case ADD:
            return val1+val2;
        case SUB:
            return val1-val2;
        case MUL:
            return val1*val2;
        case DIV:
            return val1/val2;
        case BAD_EXP:
            return -1; // ?
    }
}

void printType(enum EXP_TYPE type) {
    switch (type){
        case ADD:
            setbuf(stdout, 0);
            printf(" + ");
            break;
        case SUB:
            setbuf(stdout, 0);
            printf(" - ");
            break;
        case MUL:
            setbuf(stdout, 0);
            printf(" * ");
            break;
        case DIV:
            setbuf(stdout, 0);
            printf(" / ");
            break;
    }
    return;
}

void print_operand(operand op){
    if (op.type == VAR_X) {
        setbuf(stdout, 0);
        printf("X");
    } else if (op.type == VALUE) {
        setbuf(stdout, 0);
        printf("%d", op.val);
    }
    return;
}


void push_last(Node *head, exp *pExp) {
    if (head->expr == NULL ) {
        head->expr = pExp;
        head->next = NULL;
        return;
    }

    Node *new_node = malloc (sizeof (Node));
    new_node->expr = pExp;
    new_node->next = NULL;
    Node *last_node = return_last_node(head);
    last_node->next = new_node;
    return;
}

Node* return_last_node (Node *pNode) {
    Node *cur, *prev;
    cur = pNode->next;
    prev = pNode;
    while (cur != NULL){
        prev = cur;
        cur = cur->next;
    }
    return prev;
}

int need_next_line(char *line) {
    if (is_string_includes(line,'X')|| is_string_includes(line,'N')) return 1;
    return 0;
}

void get_operands(char *line, operand *operand_a, operand *operand_b) {
    char first[MAX_COMMAND_LEN],second[MAX_COMMAND_LEN];
    sscanf(line,"%s %s", first, second);
    if (strcmp(first,"X") == 0) {
        operand_a->type = VAR_X;

    } else {
        int first_val;
        sscanf(line, "%d", &first_val);
        operand_a->type = VALUE;
        operand_a->val = first_val;
    }
    if (strcmp(second,"X") == 0) {
        operand_b->type = VAR_X;
    } else {
        int second_val;
        sscanf(line, "%s %d", first, &second_val);
        operand_b->type = VALUE;
        operand_b->val = second_val;
    }
    return;
}

char* get_next_line(FILE *pFile) {
    return "";
}

int get_type(char *input) {
    if (is_string_includes(input, 'A')) return ADD;
    if (is_string_includes(input, 'S')) return SUB;
    if (is_string_includes(input, 'M')) return MUL;
    if (is_string_includes(input, 'D')) return DIV;
    return BAD_EXP;
}

int is_string_includes(char *string, char i) {
    if (strchr(string,i)!=NULL) return 1;
    return 0;
}

enum WHOM_TO_OUTPUT who_to_output(char *line) {
    if (is_string_includes(line,'C')) return CURRENT;
    if (is_string_includes(line,'T')) return ALL_EXP;
    return NONE;
}
