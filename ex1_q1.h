#define MAX_COMMAND_LEN 10
enum EXP_TYPE {ADD, SUB, MUL, DIV, BAD_EXP};
enum OPERAND_TYPE {VALUE, VAR_X, BAD_OPERAND};
enum WHOM_TO_OUTPUT {CURRENT, ALL_EXP, NONE};
typedef struct operand {
    enum OPERAND_TYPE type;
    int val; // value, valid if this is not a variable
} operand;

typedef struct exp { // binary expression
    enum EXP_TYPE type;
    struct operand oper1, oper2;
} exp;

typedef struct Node {
    struct exp* expr;
    struct Node* next;
} Node;

int handle_input(char *line, Node *head);

int is_string_includes(char *string, char i);

int get_type(char *input);

void get_operands(operand *pInt, operand *pInt1);

void push_last(Node *pNode, exp *pExp);

void print_last_expr(Node *head, int E);

void print_all_expr(Node *head, int E);

Node* return_last_node (Node *pNode);

void print_expr(exp *pExp, int E);

void print_operand(operand);

void printType(enum EXP_TYPE type);

int eval_expr(exp *pExp);

enum WHOM_TO_OUTPUT who_to_output(char *line);

void free_list(Node *head);
