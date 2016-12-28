/**
 * @file     zndkjansson.c
 * @brief    jansson, json c libary test
 *
 * @note     ** Jansson — C library for working with JSON data
 *           http://www.digip.org/jansson/
 *
 * @date     2016-12-23
 * @author   zundoko
 */

#include <stdio.h>              /* printf()      */
#include <stdlib.h>             /* EXIT_SUCCESS  */
#include <string.h>             /* memcpy()      */

#include <jansson.h>            /* json c lib    */

/**
 * main()
 * @brief    main routine for jansson test
 *
 * @param    [in]   argc        int ::= # of args
 * @param    [in]  *argv[]     char ::= entity of args
 * @return          stat            ::= process termination (EXIT_)
 */
int
main(int argc, char *argv[])
{
    int           stat     = EXIT_SUCCESS;
    char         *filepath = "./zndkjansson.json";
    json_t       *obj;
    json_error_t  err;

    obj = json_load_file(filepath, 0, &err);
    if (obj == NULL) {
        printf(" %s():[L%4d] json_loads() error, %s.\n",
               __func__, __LINE__, err.text);
    }

    {
        json_t *json = json_object_get(obj, "firstName");
        printf( " <firstname>  : %s\n", json_string_value( json ) );
    }

    {
        json_t *is_alive = json_object_get(obj, "isAlive");
        printf( " <isAlive>    : %d", json_boolean_value(is_alive));
        if (json_is_boolean( is_alive )) {
            printf(" (true)\n");
        } else {
            printf(" (false)\n");
        }
    }

    {
        json_t *address = json_object_get(obj, "address");
        {
            json_t *st      = json_object_get(address, "streetAddress");
            json_t *city    = json_object_get(address, "city"         );
            json_t *state   = json_object_get(address, "state"        );
            json_t *pcode   = json_object_get(address, "postalCode"   );
            printf(" streetAddress: %s\n", json_string_value(st   ));
            printf(" city         : %s\n", json_string_value(city ));
            printf(" state        : %s\n", json_string_value(state));
            printf(" postalCode   : %s\n", json_string_value(pcode));
        }
    }

    {
        int age = json_integer_value( json_object_get(obj, "age") );
        printf( " <age>        : %d\n", age);
    }

    {
        int     i;
        json_t *phonetbl = json_object_get(obj, "phoneNumbers");
        json_t *attr;

        json_array_foreach(phonetbl, i, attr) {
            printf(" <%10s> :%s\n",
                   json_string_value( json_object_get(attr, "type") ),
                   json_string_value( json_object_get(attr, "number" ) ) );
        }
    }
    {
        json_t *lastname = json_object_get(obj, "lastName");
        json_t *spouse   = json_object_get(obj, "spouse"  );

        if (json_is_null(lastname) == 0) printf(" lastName is not null\n");
        else                             printf(" lastName is     null\n");

        if (json_is_null(spouse  ) == 0) printf(" spouse   is not null\n");
        else                             printf(" spouse   is     null\n");
    }

    json_decref(obj);           /* destroys json obj */
 
    return  stat;
}

/* end */
