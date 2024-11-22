/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
void reverse(ListNode *s,ListNode *e){
   
     ListNode *p=NULL,*c=s,*n=s->next;
     while(p!=e){
         c->next=p;
         p=c;
         c=n;
         if(n!=NULL)n=n->next;
     }
}
    ListNode* reverseBetween(ListNode* head, int left, int right) {
         if(head==NULL || head->next == NULL)return head;
       
       ListNode *dummy=new ListNode(-1);
       dummy->next=head;
       ListNode *temp=dummy;
       
       int i=1;
       while(i<left){
           temp=temp->next;
           i++;
       }
       ListNode *s=temp->next,*e=head;
       i=1;
       while(i<right){
           e=e->next;
           i++;
       }
       ListNode *beforeS=temp,*afterE=e->next;
       reverse(s,e);
       beforeS->next=e;
       s->next=afterE;

       return dummy->next;



        

    }
};