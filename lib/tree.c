#define _XOPEN_SOURCE // include support for strptime(3)
#include "tree.h"
#include "tree_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Tree* tree_create(const char* sp, tree_state st, const char* d)
{
  Tree* new_tree = malloc(sizeof(Tree));
  tree_set_species(new_tree, sp);
  tree_set_status(new_tree, st);
  new_tree->day_planted = NULL;
  tree_set_day_planted(new_tree, d);

  return new_tree;
}

void tree_free(Tree* t)
{
  free(t->day_planted);
  free(t->species);
  free(t);
}

const char* tree_get_species(const Tree* t)
{
  return t->species;
}

tree_state tree_get_status(const Tree* t)
{
  return t->status;
}

struct tm* tree_get_day_planted(const Tree* t)
{
  return t->day_planted;
}

void tree_set_species(Tree* t, const char* sp)
{
  if ((t->str_size = strlen(sp)) > 0) {
    t->species = calloc(t->str_size, sizeof(char));
    strncpy(t->species, sp, t->str_size);
  } else {
    t->str_size = 0;
    t->species = NULL;
  }
}

void tree_set_status(Tree* t, tree_state st)
{
  t->status = st;
}

void tree_set_day_planted(Tree* t, const char* d)
{
  if (tree_get_status(t) == DEAD) {
    t->day_planted = NULL;
  } else {
    if (!t->day_planted) { // handle the case when day_planted haven't allocated
      // with memory
      t->day_planted = malloc(sizeof(struct tm));
    }

    strptime(d, "%F", t->day_planted);
  }
}

void tree_serialise(Tree* t, char* buf)
{
  char* date = malloc(11);
  strftime(date, 11, "%F", t->day_planted);
  sprintf(buf, "%s,%u,%s", t->species, t->status, date);
}

Tree* tree_deserialise(char* s)
{
  char* species = malloc(1024);
  tree_state status;
  char* date = malloc(11);
  sscanf(s, "%[^,],%u,%[^,]", species, &status, date);

  Tree* t = tree_create(species, status, date);

  free(species);
  free(date);
  return t;
}
