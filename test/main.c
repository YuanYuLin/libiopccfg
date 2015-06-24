#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <json.h>
#include <json_object.h>
#include "debug.h"

enum {
    SHOW_JSON=1,
    SHOW_VALUE=1,
};

static void get_value_by_obj_val(char *key_str, struct json_object *obj_val);
static void get_valueobj(struct json_object *obj_val);

static void get_valueobj(struct json_object *obj_val)
{
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        get_value_by_obj_val(tmpkey, tmpval);
    }
}

static void get_value_by_obj_val(char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    type = json_object_get_type(obj_val);
    switch(type){
    case json_type_null:
        printf("Key: %s, Val: %s\n", key_str, "NULL");
    break;
    case json_type_boolean:
        printf("Key: %s, Val: %d\n", key_str, json_object_get_boolean(obj_val));
    break;
    case json_type_double:
        printf("Key: %s, Val: %f\n", key_str, json_object_get_double(obj_val));
    break;
    case json_type_int:
        printf("Key: %s, Val: %d\n", key_str, json_object_get_int(obj_val));
    break;
    case json_type_object:
        printf("Key: %s\n", key_str);
        get_valueobj(obj_val);
    break;
    case json_type_array:
        printf("Key: %s\n", key_str);
        array_len = json_object_array_length(obj_val);
        for(i=0; i<array_len; i++) {
            ele_obj = json_object_array_get_idx(obj_val, i);
            get_value_by_obj_val("array", ele_obj);
        }
    break;
    case json_type_string:
        printf("Key: %s, Val: %s\n", key_str, json_object_get_string(obj_val));
    break;
    default:
        printf("JSON type error\n");
    break;
    }
}

static void show_json(struct json_object *obj, char* key_str)
{
    int index = 0;
    json_object_object_foreach(obj, obj_key, obj_val) {
        printf("Key at index %d is [%s] ", index, obj_key);
        get_value_by_obj_val(obj_key, obj_val);
        index++; 
    }
}


static void get_value_by_key(struct json_object *obj, char* key)
{
    json_object *obj_val;
    enum json_type type;

    obj_val = json_object_object_get(obj, key);

    if(obj_val != NULL) {
        type = json_object_get_type(obj_val);

        switch(type){
        case json_type_null:
            printf("Key: %s, Val: %s\n", key, "NULL");
        break;
        case json_type_boolean:
            printf("Key: %s, Val: %d\n", key, json_object_get_boolean(obj_val));
        break;
        case json_type_double:
            printf("Key: %s, Val: %f\n", key, json_object_get_double(obj_val));
        break;
        case json_type_int:
            printf("Key: %s, Val: %d\n", key, json_object_get_int(obj_val));
        break;
        case json_type_object:
        break;
        case json_type_array:
        break;
        case json_type_string:
            printf("Key: %s, Val: %s\n", key, json_object_get_string(obj_val));
        break;
        default:
            printf("JSON type error\n");
        break;
        }
    }

}

unsigned long parse_paramegers(int argc, char** argv, char* json_file, char* json_key)
{
    int cmd_opt = 0;
    while(1) {
        cmd_opt = getopt(argc, argv, "f:k:p:");

        if(cmd_opt == -1) {
            return 0;
        }

        switch(cmd_opt) {
        case 'k':
            json_key = optarg;
        break;
        case 'f':
            json_file = optarg;
        break;
        case 'p':
        break;
        }
    }
}

int main(int argc, char** argv)
{
    char* key;
    struct json_object *obj;
    obj = json_object_from_file("./test.json");
    //key = argv[1];
    //get_value_by_key(obj, key);
    show_json(obj, NULL);
    return 0;
}
