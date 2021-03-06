// 最优解
/**
 * 设链表长度为L，起点到环入口长度为X，入口到相遇点距离为A，则
 * X+A=nR + L-X ==> X = NR + L-X-A, 其中L-X-A为相遇点到环入口的距离，
 * 所以当到达相遇点时，用两个指针，一个从链表头，一个在相遇点，同时单步移动，
 * 直到相遇，此相遇点即为环入口。
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    typedef struct ListNode ListNode;

    ListNode *pNode1 = head, *pNode2 = head;
    while (pNode2 && pNode2->next) {
        pNode1 = pNode1->next;
        pNode2 = pNode2->next->next;

        if (pNode1 == pNode2) {
            pNode1 = head;
            while (pNode1 != pNode2) {
                pNode1 = pNode1->next;
                pNode2 = pNode2->next;
            }
            return pNode1;
        }
    }

    return NULL;
}

// 次优解
#include <stdio.h>

struct ListNode {
    ListNode *m_pNext;
    int m_nValue;
};

ListNode *MeetingNode(ListNode *pHead)
{
    if (pHead == NULL) return NULL;

    ListNode *pSlow = pHead->m_pNext;
    if (pSlow == NULL) return NULL;

    ListNode *pFast = pSlow->m_pNext;
    while (pFast != NULL && pSlow != NULL) {
        if (pFast == pSlow) return pFast;
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
        if (pFast != NULL) 
            pFast = pFast->m_pNext;
    }

    return NULL;
}

ListNode *EntryNodeOfLoop(ListNode *pHead)
{
    ListNode *meetingNode = MeetingNode(pHead);
    if (meetingNode == NULL) return NULL;

    // get the number of nodes in loop
    int nodesInLoop = 1;
    ListNode *pNode1 = meetingNode;
    while (pNode1->m_pNext != meetingNode) {
        ++nodesInLoop;
        pNode1 = pNode1->m_pNext;
    }

    pNode1 = pHead;
    for (int i = 0; i < nodesInLoop; ++i)
        pNode1 = pNode1->m_pNext;

    ListNode *pNode2 = pHead;
    while (pNode1 != pNode2) {
        pNode1 = pNode1->m_pNext;
        pNode2 = pNode2->m_pNext;
    }

    return pNode1;
}

// ==================== Test Code ====================
ListNode *CreateListNode(int value) 
{
    ListNode *pNode = new ListNode();
    pNode->m_nValue = value;

    return pNode;
}

void DestroyList(ListNode *pHead) 
{
    if (pHead == NULL) return;

    ListNode *pNode = NULL;
    while (pHead != NULL) {
        pNode = pHead->m_pNext;
        delete pHead;
        pHead = pNode;
    }
}

void ConnectListNodes(ListNode *pHead1, ListNode *pHead2) 
{
    if (pHead1 == NULL || pHead2 == NULL) return;

    ListNode *pNode = pHead1;
    while (pNode->m_pNext != NULL) {
        pNode = pNode->m_pNext;
    }

    pNode->m_pNext = pHead2;
}

void Test(char* testName, ListNode* pHead, ListNode* entryNode)
{
    if(testName != NULL)
        printf("%s begins: ", testName);

    if(EntryNodeOfLoop(pHead) == entryNode)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);

    Test("Test1", pNode1, NULL);

    DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ConnectListNodes(pNode1, pNode1);

    Test("Test2", pNode1, pNode1);

    delete pNode1;
    pNode1 = NULL;
}

// A list has multiple nodes, with a loop 
void Test3()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode3);

    Test("Test3", pNode1, pNode3);

    delete pNode1;
    pNode1 = NULL;
    delete pNode2;
    pNode2 = NULL;
    delete pNode3;
    pNode3 = NULL;
    delete pNode4;
    pNode4 = NULL;
    delete pNode5;
    pNode5 = NULL;
}

// A list has multiple nodes, with a loop 
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode1);

    Test("Test4", pNode1, pNode1);

    delete pNode1;
    pNode1 = NULL;
    delete pNode2;
    pNode2 = NULL;
    delete pNode3;
    pNode3 = NULL;
    delete pNode4;
    pNode4 = NULL;
    delete pNode5;
    pNode5 = NULL;
}

// A list has multiple nodes, with a loop 
void Test5()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode5);

    Test("Test5", pNode1, pNode5);

    delete pNode1;
    pNode1 = NULL;
    delete pNode2;
    pNode2 = NULL;
    delete pNode3;
    pNode3 = NULL;
    delete pNode4;
    pNode4 = NULL;
    delete pNode5;
    pNode5 = NULL;
}

// A list has multiple nodes, without a loop 
void Test6()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test("Test6", pNode1, NULL);

    DestroyList(pNode1);
}

// Empty list
void Test7()
{
    Test("Test7", NULL, NULL);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}
