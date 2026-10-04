#ifndef HW14
#define HW14

#include <stdio.h>

enum dir { LAYOUT_HORIZ, LAYOUT_VERT, LAYOUT_NONE };

struct DOMNode;
struct DOMNodeList {
  struct DOMNode *node;//points to node info
  struct DOMNodeList *next;//points to child
};

struct DOMNode {
  int id; //unique per element
  float margin;
  enum dir layout_direction; //how children are placed/oriented
  struct DOMNodeList *children;//points to child
};

void layout(struct DOMNode *root, float width, float height, FILE *target);
void free_DOMTree(struct DOMNode *root);

// UTILITY STUFF HERE
// DO NOT MODIFY
struct stream {
  char *text;
  size_t pos;
  size_t length;
};

struct DOMNode *load_tree(struct stream *s);

#endif // HW14
