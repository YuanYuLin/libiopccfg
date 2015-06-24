#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "iopccfg.h"

static void parse_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val);

static void parse_value_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    char tmp_str[STR_LEN]={0};
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);

        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0){
            query_json_obj->isFound = 1;
            query_json_obj->obj = tmpval;
            query_json_obj->type = json_object_get_type(tmpval);
            strcpy(query_json_obj->key_str, tmp_str);
            return;
        }
        parse_json_obj_by_query_obj(query_json_obj, tmp_str, tmpval);
    }
}

static void parse_value_array_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0){
            query_json_obj->isFound = 1;
            query_json_obj->obj = ele_obj;
            query_json_obj->type = json_object_get_type(ele_obj);
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_json_obj_by_query_obj(query_json_obj, tmp_str, ele_obj);
        if(query_json_obj->isFound)
            return ;
    }
}

static void parse_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    char tmp_str[STR_LEN]={0};
    type = json_object_get_type(obj_val);

    switch(type){
    case json_type_null:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_null;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_boolean:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_boolean;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_double:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_double;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_int:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_int;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_object:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_object;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_value_obj_by_query_obj(query_json_obj, key_str, obj_val);
    break;
    case json_type_array:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_array;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_value_array_by_query_obj(query_json_obj, key_str, obj_val);
    break;
    case json_type_string:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_string;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    default:
        query_json_obj->isFound = 0;
        query_json_obj->obj = NULL;
        query_json_obj->type = json_type_null;
        strcpy(query_json_obj->key_str, "error");
    break;
    }
}

void get_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, struct json_object *json_obj)
{
    json_object_object_foreach(json_obj, obj_key, obj_val) {
        parse_json_obj_by_query_obj(query_json_obj, obj_key, obj_val);
        if(query_json_obj->isFound)
            break;
    }
}

