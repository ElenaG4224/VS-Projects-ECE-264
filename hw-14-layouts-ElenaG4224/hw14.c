#include <stdio.h>
#include <stdlib.h>
#include "hw14.h"

static void print_layoutHelp(struct DOMNode *root, FILE *target, float left, float top, float right, float bottom);

void layout(struct DOMNode *root, float width, float height, FILE *target) {
 // TODO: fill this in, recursive calls, write to file.
 fprintf(target, "%.2f %.2f\n", width, height);
 print_layoutHelp(root, target, 0, 0, width, height);

 return;
}

static void print_layoutHelp(struct DOMNode *root, FILE *target, float left, float top, float right, float bottom)
{
 if (root == NULL)
 {
   return;
 }
 int childCount = 0;
 struct DOMNodeList *list = root->children;
 struct DOMNodeList *counter_list = root->children;
 while (counter_list != NULL)
 {
   childCount++;
   counter_list = counter_list->next;
 }

 //file print current node.(use fprintf to format)
 fprintf(target, "%d %.2f %.2f %.2f %.2f\n", root->id, left, top, right, bottom);

 if (childCount == 0)
 {
   return;
 }

 float margin = root-> margin;
 float horzDiff = (right - left) * margin / 2;
 float vertDiff = (bottom - top) * margin / 2;

 float leftMargin = left + horzDiff;
 float rightMargin = right - horzDiff;
 float topMargin = top + vertDiff;
 float bottomMargin = bottom - vertDiff;

 for (int i = 0; i < childCount; i++)
 {
   struct DOMNode * child = list->node;

   if (root->layout_direction == LAYOUT_HORIZ)
   {
     //use lefts and rights
     float width = (rightMargin - leftMargin) / childCount;
     float leftCurr = leftMargin + (i * width);
     float rightCurr = leftCurr + width;
     
     print_layoutHelp(child, target, leftCurr, topMargin, rightCurr, bottomMargin);
   }
   else if (root->layout_direction == LAYOUT_VERT)
   {
     // use top and bottom
     float height = (bottomMargin - topMargin) / childCount;
     float topCurr = topMargin + (i * height);
     float bottomCurr = topCurr + height;
     print_layoutHelp(child, target, leftMargin, topCurr, rightMargin, bottomCurr);
     
   }
   else if (root->layout_direction == LAYOUT_NONE)
   {
     print_layoutHelp(child, target, leftMargin, topMargin, rightMargin, bottomMargin);
   }

   list = list->next;

 }
 
 return;
}

void free_DOMTree(struct DOMNode *root) {
 // TODO: fill this in
 if (root == NULL)
 {
   return;
 }

 struct DOMNodeList * listCurr = root->children;
 
 while (listCurr != NULL)
 {
   struct DOMNodeList * listNext = listCurr->next;
   free_DOMTree(listCurr->node);//access children
   free(listCurr);
   listCurr = listNext;//advance to next child
 }
 free(root);
 return;
}