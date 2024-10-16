#include <stdio.h>
#include <stdlib.h>

// define our object type
typedef struct obj1 {
    int a, b, c;
    int (*add_ab) (struct obj1 *);


// define your function prototypes here

} OBJ1;

// define a couple different add functions
int my_add_ab (OBJ1 *obj) {
    return (obj->a + obj->b);
}

int bad_add_ab (OBJ1 *obj) {
    return(obj->a - obj->b);
}



// define your functions here



int main(int argc, char **argv) {

    OBJ1 *myobj;
    myobj = (OBJ1 *) malloc(sizeof(OBJ1));
    myobj->a = 1;
    myobj->b = 2;
    myobj->c = 3;
    myobj->add_ab = my_add_ab;
    printf("add ab result %d\n",myobj->add_ab(myobj));
   
    myobj->add_ab = bad_add_ab;
    printf("add ab result %d\n",myobj->add_ab(myobj));


// set up the function pointers here for use below


    myobj->set_a(myobj, 20);
    myobj->set_b(myobj, 5);
    myobj->set_c(myobj, 12);
    printf("sum_all result %d\n",myobj->sum_all(myobj));
}