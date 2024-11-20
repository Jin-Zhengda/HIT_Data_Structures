#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 以下部分是提供给学生的 */
typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;

/* 创建交叉列表 */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a和b后面若干结点值相同
    // beforeCross1为跳过的a中的个数，从第beforeCross1 + 1个结点开始相交
    // beforeCross2为跳过的b中的个数，从第beforeCross2 + 1个结点开始相交
    // 相交方法是将b中的前一结点指向a中的首个相交结点
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //销毁野指针结点
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

/* 程序结束后销毁交叉列表 */
void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode){
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode){
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode){
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* 打印单个结点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }
}

/** 以下部分是需要学生自己实现的 **/
/** 打印整个列表 **/
void outputStudentLinkedList(StudentLinkedListNode* head){
    // 用于单个节点输出的函数printLinkedListNode已提供
    // 请你实现遍历链表的逻辑
	// TODO
}

/** 新建一个链表node并返回 **/
StudentLinkedListNode* createStudentLinkedList(char student_id[], int grade) {
    //tips:malloc的时候记得为转化为结构体指针
	//TODO
}

/** 按照降序插入学生的成绩情况,并返回链表头指针 **/
StudentLinkedListNode* addStudentLinkedList(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    //TODO
}

/** 反转链表 **/
StudentLinkedListNode* reverseStudentLinkedList(StudentLinkedListNode*head)
{
    //TODO
}

/** 找到相交的第一个结点 **/
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
    // class1和class2在后一部分完全重合（结点的内存地址相同），请找出并返回开始相交的第一个结点。
    // 请不要简单地通过结点结构体的成员来判断。
    // TODO
}

int main()
{
    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    // 读取两个班级的人数
    scanf("%d%d", &num1, &num2);
    class1 = class2 = NULL;
    // 读取班级1的成绩
    for(i = 0;i < num1;i++){
        scanf("%s%d", student_id, &grade);
        node = createStudentLinkedList(student_id, grade);
        class1 = addStudentLinkedList(class1, node);
    }
    // 读取班级2的成绩
    for(i = 0;i < num2;i++){
        scanf("%s%d", student_id, &grade);
        node = createStudentLinkedList(student_id, grade);
        class2 = addStudentLinkedList(class2, node);
    }
    // 读取链表交叉之前的结点个数
    scanf("%d%d",&beforeCross1,&beforeCross2);

    // 输出1：存储列表结果
    printf("Store Linkedlist\n");
    outputStudentLinkedList(class1);
    outputStudentLinkedList(class2);

    // 执行反转链表操作
    class1 = reverseStudentLinkedList(class1);
    class2 = reverseStudentLinkedList(class2);

    // 输出2：反转列表结果
    printf("Reverse Linkedlist\n");
    outputStudentLinkedList(class1);
    outputStudentLinkedList(class2);

    // 创建交叉链表并找到第一个交点
    createCrossLink(class1, class2, beforeCross1, beforeCross2);
    node = findCrossBeginNode(class1, class2);

    // 输出3：链表交点
    printf("Cross node\n");
    printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

    // 销毁交叉链表
    destroyCrossLink(class1, class2, node);

    return 0;
}
