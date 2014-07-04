#include "stdio.h"

#include "apr_general.h"

#include "block_utils.h"

typedef struct person {
    const char *name;
    int age;
} person_t;

int main(void) {
    apr_initialize();
    
    bu_with_pool(^{
        person_t *person = bu_alloc(sizeof(person_t));
        person->name = "Derek";
        person->age = 20;
        puts(bu_format("name: %s; age: %d", person->name, person->age));
    });

    apr_terminate();
    return 0;
}

