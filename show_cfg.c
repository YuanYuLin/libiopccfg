#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "iopccfg.h"

static void parse_json_obj(char *key_str, struct json_object *obj_val);

static void parse_value_obj(char*key_str, struct json_object *obj_val)
{
    char tmp_str[STR_LEN]={0};
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);
        parse_json_obj(tmp_str, tmpval);
    }
}

static void parse_value_array(char *key_str, struct json_object *obj_val)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        parse_json_obj(tmp_str, ele_obj);
    }
}

static void parse_json_obj(char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    type = json_object_get_type(obj_val);

    switch(type){
    case json_type_null:
        printf("%s=%s\n", key_str, "NULL");
    break;
    case json_type_boolean:
        printf("%s=%d\n", key_str, json_object_get_boolean(obj_val));
    break;
    case json_type_double:
        printf("%s=%f\n", key_str, json_object_get_double(obj_val));
    break;
    case json_type_int:
        printf("%s=%d\n", key_str, json_object_get_int(obj_val));
    break;
    case json_type_object:
        parse_value_obj(key_str, obj_val);
    break;
    case json_type_array:
        parse_value_array(key_str, obj_val);
    break;
    case json_type_string:
        printf("%s=%s\n", key_str, json_object_get_string(obj_val));
    break;
    default:
        printf("JSON type error\n");
    break;
    }
}

void show_json(struct json_object *json_obj)
{
    json_object_object_foreach(json_obj, obj_key, obj_val) {
        parse_json_obj(obj_key, obj_val);
    }
}

