Adds the number head1 to head2 using high precision algorithms.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    /**
     * 
     * @param head1 ListNode类 
     * @param head2 ListNode类 
     * @return ListNode类
     */
    ListNode* ReverseList(ListNode* pHead) {
        if (pHead == NULL) return NULL;
        ListNode *prev = pHead, *now= pHead->next, *temp;
        pHead->next = NULL;
        while(now != NULL)
        {
            temp = now->next;
            now->next = prev;
            prev = now;
            now = temp;
        }
        return prev;
    }
    
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        ListNode *ans = new ListNode(0);
        if(head1 == NULL && head2 == NULL) return ans;
        if(head1 == NULL) return head2;
        if(head2 == NULL) return head1;
        int n=0, m=0;
        ListNode *now1(head1), *now2(head2);
        while(now1 != NULL)
        {
            ++n;
            now1 = now1->next;
        }
        while(now2 != NULL)
        {
            ++m;
            now2 = now2->next;
        }
        if(n < m)
        {
            swap(head1, head2);
            swap(n,m);
        }
        now1 = head1; now2 = head2;
        head1 = ReverseList(now1); head2 = ReverseList(now2);
        ListNode *now = ans, *prev = ans;
        ListNode *reverse_head1 = NULL, reverse_head2 = NULL;
        now1 = head1;
        for(int i=0; i<n; ++i)
        {
            now->val = now1->val;
            now->next = new ListNode(0);
            now = now->next;
            now1 = now1->next;
        }
        now2 = head2; now = ans;
        for(int i=0; i<m; ++i)
        {
            now->val += now2->val;
            if(now->val >= 10)
            {
                int t = now->val;
                now->val = t%10;
                now->next->val ++;
            }
            now = now->next;
            now2 = now2->next;
        }
        if(now->val >= 10)
        {
             int t = now->val;
             now->val = t%10;
             now->next->val ++;
        }
        ans = ReverseList(ans);
        if(ans->val == 0) ans=ans->next;
        return ans;
    }
};
