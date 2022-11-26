#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 50000

typedef struct H_item H_item;
typedef struct H_table H_table;

struct H_item {
  char* key;
  char* val;
 };

struct H_table {
  H_item** items;
  int size;
  int count;
};

H_item* create_item(char* key, char* val) {
  H_item* item = (H_item*) malloc(sizeof(H_item)); 
  item->key = (char*) malloc(strlen(key)+1);
  item->val = (char*) malloc(strlen(val)+1);

  strcpy(item->key, key);
  strcpy(item->val, val);
  
  return item;
}

void free_item(H_item* item) {
  free(item->key);
  free(item->val);
  free(item);
}

H_table* create_table(int size) {
  H_table* table = (H_table*) malloc(sizeof(H_table));
  table->size = size;
  table->count = 0;
  table->items = (H_item**) calloc(table->size, sizeof(H_item*));

  return table;
}

void free_table(H_table* table) {

  for(int i = 0; i < table->size; i++) {
    H_item* item = table->items[i]; 
    if (item != NULL) {
      free_item(item);
    }
  } 

  free(table->items);
  free(table);
}

unsigned long hash_function(char* str) {
  unsigned long val = 0;
  for (int i = 0; str[i]; i++) {
    val += str[i];
  }
  return val % CAPACITY;
}

void handle_collision(H_table* table, unsigned long index, H_item* item) {

}

void h_insert(H_table* table, char* key, char* val) {
  H_item* item = create_item(key, val);
  unsigned long index = hash_function(key);

  H_item* curItem = table->items[index];

  if(curItem == NULL) {
    if (table->count == table->size) {
      printf("Insertion error, hash table full\n");
      free_item(item);
      return;
    }
    table->items[index] = item;
    table->count++;
  } else {
    if (strcmp(curItem->key, key) == 0) {
      strcpy(table->items[index]->val, val);
      return;
    } else {
      handle_collision(table, index, item);
      return;
    }
  }
}

char* h_search(H_table* table, char* key) {
  int index = hash_function(key);
  H_item* item = table->items[index];

  if (item != NULL) {
    if (strcmp(item->key, key) == 0) {
      return item->val;
    }
  }
  return NULL;
}

void print_table(H_table* table) {
  printf("\nYour lovely hash table\n----------------\n");
  for (int i = 0; i < table->size; i++) {
    if (table->items[i]) {
      printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->val);
    }
  }
  printf("-------------------\n\n");
}

int main(int argc, char** argv) {
  H_table* ht = create_table(CAPACITY);
  h_insert(ht, "user", "cool");
  h_insert(ht, "ghoul", "1000-7");
  print_table(ht);
  free_table(ht);
}
