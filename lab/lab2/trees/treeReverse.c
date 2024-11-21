#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
   int id;
   int val;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode {
   struct TreeNode *node; // ���е�ֵ�����������ڵ�ָ��
   struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue {
   ListNodePtr dummyHead;
   ListNodePtr tail;
   int size;
} *QueuePtr;

// ���������Ľڵ�
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next) {
   ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
   curr->node = node;
   curr->next = next;
   return curr;
}

// �������Ľڵ�
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {
   TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
   curr->id = TreeId++;
   curr->val = val;
   curr->left = left;
   curr->right = right;
   return curr;
}

// ���������г�ʼ��
QueuePtr InitQueue() {
   QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
   TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
   queue->size = 0;
   queue->dummyHead = createListNode(dummyTreeNode, NULL);
   queue->tail = queue->dummyHead;
   return queue;
}

// �� queue ��β������һ��Ԫ�صĸ���
void EnQueue(QueuePtr queue, TreeNodePtr node) {
   ListNodePtr curr = createListNode(node, NULL);
   queue->tail->next = curr;
   queue->tail = queue->tail->next;
   queue->size++;
}

// ɾ�� queue �еĵ�һ��Ԫ��
void DeQueue(QueuePtr queue) {
   if (queue->size == 0) {
       perror("error! the size of queue is zero when call DeQueue().");
       return;
   }
   ListNodePtr head = queue->dummyHead->next;
   queue->dummyHead->next = head->next;
   queue->size--;
   if (queue->size == 0) queue->tail = queue->dummyHead;
   free(head);
}

// ��� queue ��û��Ԫ��, ���� true
bool QueueEmpty(QueuePtr queue) {
   return queue->size == 0;
}

// ���� queue �е�һ��Ԫ�ص�����
TreeNodePtr GetHead(QueuePtr queue) {
   if (QueueEmpty(queue)) {
       perror("error! the size of queue is zero when call front().");
       return NULL;
   } else {
       return queue->dummyHead->next->node;
   }
}

int max(int a, int b) {
   return (a >= b) ? a : b;
}

// ������ת��Ϊ����
void getDigits(char *buff, int *data) {
   int len = strlen(buff);
   int index = 0;
   for (int i = 0; i < len; i++) {
       int num = 0;
       if (buff[i] == '#') {
           num = -1;
           i++;
       } else {
           while (buff[i] != ' ' && buff[i] != '\0') {
               num = num * 10 + (buff[i++] - '0');
           }
       }
       data[index++] = num;
   }
}

// ���� dot ���ӻ��ļ�
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize) {
   FILE *fp = fopen(filename, "w");    // �ļ�ָ��
   if (fp == NULL) {   // ΪNULL�򷵻�
       printf("File cannot open!");
       exit(0);
   }
   fprintf(fp, "digraph G {\n");   // ��ͷ
   // ���ò�α�������
   QueuePtr queue = InitQueue();
   EnQueue(queue, root);
   int id = 1;
   while (!QueueEmpty(queue)) { // �����в��գ��������������򣬱�������
       TreeNodePtr curr = GetHead(queue);
       DeQueue(queue);
       if (curr == NULL) continue;
       fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr->id, curr->val);
       if (curr->left != NULL) { // ��������ӣ��������
           EnQueue(queue, curr->left);
           fprintf(fp, "%d->%d;\n", curr->id, curr->left->id);
       }
       id++;
       // �м�����ڵ�
       fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
       fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr->id, id);
       if (curr->right != NULL) { // ������Һ��ӣ��Һ������
           EnQueue(queue, curr->right);
           fprintf(fp, "%d->%d;\n", curr->id, curr->right->id);
       }
       id++;
   }
   fprintf(fp, "}\n"); // ��β
   fclose(fp); // �ر�IO
}


// ���ƶ�����ͼƬ,���� createDotFile ��ʹ�� system ִ������
void plot(TreeNodePtr tree_root, int i, int size, char *name) {
   char tree_filename[50], paint_tree[100];
   sprintf(tree_filename, "./%s_%d.dot", name, i);
   createDotFile(tree_filename, tree_root, size);
   sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
   // puts(paint_tree);
   system(paint_tree);
}


// ɾ��������
void destoryTree(TreeNodePtr root) {
   if (!root) return;
   if (root->left) {
       destoryTree(root->left);
       root->left = NULL;
   }
   if (root->right) {
       destoryTree(root->right);
       root->right = NULL;
   }
   free(root);
}


void inOrderTraverse(TreeNodePtr root) {
   if (root == NULL) {
       return;
   }
   inOrderTraverse(root->left);
   if (root->val != -1) {
       printf(" %d", root->val);
   }
   inOrderTraverse(root->right);
}

TreeNodePtr createTreeWithLevelOrder(int *data, int size) {
   QueuePtr qPtr = InitQueue();
   TreeNodePtr root = NULL;
   int i = 0;

   if (data[i] == -1) {
       return root;
   }
   root = createTreeNode(data[i], NULL, NULL);
   EnQueue(qPtr, root);

   while (!QueueEmpty(qPtr) && i < size) {
       TreeNodePtr T = GetHead(qPtr);
       DeQueue(qPtr);

       i++;
       int leftData;
       if (i >= size) {
           leftData = -1;
       }else {
           leftData = data[i];
       }
       T->left = createTreeNode(leftData, NULL, NULL);
       EnQueue(qPtr, T->left);
       i++;
       int rightData;
       if (i >= size) {
           rightData = -1;
       } else {
           rightData = data[i];
       }
       T->right = createTreeNode(rightData, NULL, NULL);
       EnQueue(qPtr, T->right);

   }
   return root;
}


/** TODO: ����� ͨ���ݹ���ȡ�����ľ��񣬼���ת�ö����� */
TreeNodePtr invertTree(TreeNodePtr root) {
   if (root == NULL) {
       return NULL;
   }
   if (root->left != NULL && root->right != NULL) {
       TreeNodePtr p = root->left;
       root->left = root->right;
       root->right = p;
       invertTree(root->left);
       invertTree(root->right);
       return root;
   }
}

int main() {
   int SIZE = 128;
   int MAX_NUM = 10;
   char buff[SIZE];
   int num;
   bool use_graphviz = false;


   int i = 0;
   while (scanf("%d\n", &num) == 1) {
       fgets(buff, SIZE, stdin);
       char *pos = strchr(buff, '\n');          //���һ��з�
       if (pos)                            //���find��Ϊ��ָ��
           *pos = '\0';                    //�Ͱ�һ�����ַ���������

       // Mac/Linux �滻\r
       pos = strchr(buff, '\r');
       if (pos)
           *pos = '\0';


       int size = num;
       int data[size];
       getDigits(buff, data);

       TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);

       /** ����� */
       TreeNodePtr invert_tree_root = invertTree(tree_root);
       printf("inOrderTraverse of invert trees is:");
       inOrderTraverse(invert_tree_root);
   }
}