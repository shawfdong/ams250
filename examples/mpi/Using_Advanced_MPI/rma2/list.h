typedef struct _listelm {
    struct _listelm *next;
    char *key, *value; } ListElm;

/* Initial head element:
ListElm headval = { 0, 0, 0 };
static ListElm *head = &headval;
*/
