#include<iostream>
#include<algorithm>
using namespace std;

class ListNode{
public:
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode* mergeSort(ListNode* head){
    if(head == NULL || head->next == NULL) return head;
    ListNode *fast = head, *slow = head;
    while(fast->next && fast->next->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;
    head = mergeSort(head);
    fast = mergeSort(fast);
    head = mergeList(head, fast);
    return head;
}

ListNode* mergeList(ListNode* head1, ListNode* head2){
    if(head1 == NULL) return head2;
    if(head2 == NULL) return head1;

}