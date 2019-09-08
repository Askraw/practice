#include<iostream>
#include<algorithm>
using namespace std;

class ListNode{
    public:
    int val;
    ListNode* next;
    ListNode(int x):val(x){}
};

class solution{
public:
    ListNode* mergeSortList(ListNode* head){
        if(!head || head->next == NULL)
            return head;
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast->next != NULL && fast->next->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
        fast = mergeSortList(head);
        slow = mergeSortList(slow);
        return merge(fast, slow);
    }
    ListNode* merge(ListNode* head1, ListNode* head2){
        if(head1 == NULL) return head2;
        if(head2 == NULL) return head1;
        ListNode *res;
        ListNode *p;
        if(head1->val < head2->val){
            res = head1;
            head1 = head1->next;
        }else {
            res = head2;
            head2 = head2->next;
        }
        p = res;

        while(head1 != NULL && head2 != NULL){
            if(head1->val < head2->val){
                p->next = head1;
                head1 =  head1->next;
            }else{
                p->next = head2;
                head2 =  head2->next;
            }
            p = p->next;
        }
        if(head1 == NULL)
            p->next = head2;
        else 
            p->next  = head1;
        return res;
    }
};