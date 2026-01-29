/*
 * A simple example of json string parsing with json-c.
 *
 * clang -Wall -g -I/usr/include/json-c/ -o json_parser json_parser.c -ljson-c
 */
#include <json.h>
#include <stdio.h>
#include <string.h>

#include "../utils/utils.h"
#include "../earthquake.h"

int main() {

	char *url = "https://cse.unl.edu/~cbourke/example.json";
	char *str = getContent(url);

	struct json_object *object;
	object = json_tokener_parse(str);

	printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(object, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));

	char *val_type_str;
	int val_type;

	// key and val don't exist outside of this bloc
	json_object_object_foreach(object, key, val) {
		printf("key: \"%s\", type of val: ", key);
		val_type = json_object_get_type(val);

		switch (val_type) {
			case json_type_null:
				val_type_str = "val is NULL";
				break;

			case json_type_boolean:
				val_type_str = "val is a boolean";
				break;

			case json_type_double:
				val_type_str = "val is a double";
				break;

			case json_type_int:
				val_type_str = "val is an integer";
				break;

			case json_type_string:
				val_type_str = "val is a string";
				str = (char *) json_object_get_string(val);
				break;

			case json_type_object:
				val_type_str = "val is an object";
				break;

			case json_type_array:
				val_type_str = "val is an array";
				break;
		}

		printf("%s", val_type_str);

		if (str)
			printf("\t->\t\"%s\"", str);

		printf("\n");
		str = NULL;
	}

	//get a subobject:
	// Get the json_object associated to the "student" key
	struct json_object *student;
	json_object_object_get_ex(object, "student", &student);

	json_object_object_foreach(student, key2, val2) {
		str = (char *) json_object_get_string(val2);
		printf("key: \"%s\" -> %s \n", key2, str);

		if(strcmp(key2, "id") == 0) {
			//nope, val2 is a macro and a json_object*:
			// int x = atoi(val2);
			int y = json_object_get_int(val2);
			printf("y = %d\n", y);
		}
	}

	return 0;
}
