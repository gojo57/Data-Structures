#include<bits/stdc++.h>
#define ll long long
using namespace std;

class Node{
    public:
    int data;
    Node *next; //Contains address of the next node

    Node(int data){
        this->data = data;
        next = NULL;
    }
};

void print(Node *head){
    Node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}

int length(Node *head){
    Node *temp = head;
    int count = 0;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

int lengthRecursion(Node *head){
    if(head==NULL) return 0;
    return 1+lengthRecursion(head->next);
}

void printithNode(Node *head, int i){ //Returns head of ith node
    if(i<0) {cout<<-1<<endl; return;}
    for(int j = 0; j<i; j++){
        if(head!=NULL){
            head = head->next;
        }
        else{
            cout<<-1<<endl;
            break;
        }
    }
    cout<<head->data<<endl;
}

bool isPresent(Node *head, int data){
    Node *cur = head;
    while(cur!=NULL){
        if(cur->data == data) return true;
        cur = cur->next;
    }
    return false;
}

bool isPresentRecursion(Node *head, int data){
    if(head==NULL) return false;
    if(head->data == data) return true;
    return isPresentRecursion(head->next, data);
}

Node* insertAtIthPos(Node *head, int i, int data){
    
    if(i<0) return head;
    if(i==0){
        Node *n = new Node(data);
        n->next = head;
        head = n;
        return head;
    }
    Node *copyHead = head;
    int count = 1;
    while(count<=i-1 && head!=NULL){
        head = head->next;
        count++;
    }
    if(head){
        Node *n = new Node(data);
        Node *temp = head->next;
        head->next = n;
        n->next = temp;
        // n->next = head->next;
        // head->next = n;
        return copyHead;
    }
    return copyHead;
}

Node* deleteIthNode(Node *head, int i){ //This method had memory leak, but now it doesn't have that
    if(i<0) return head;
    if(i==0 && head){
        Node* NewHead = head->next;
        head->next = NULL;
        delete head;
        return NewHead;
    }
    else{
        Node *cur = head;
        int count = 1;
        while(count<=i-1 && head!=NULL){
            cur = cur->next;
            count++;
        }
        if(cur && cur->next){//cur->next because we have to check for cur->next->next, hence cur->next should also exist
            Node *temp = cur->next;
            cur->next = temp->next;
            temp->next = NULL;
            delete temp;
            return head;
        }
        return head;
    }
}

Node* removeNthNodeFrmEnd(Node *head, int k){
    Node *one = head; Node *two = head;
    while(k--){
        two = two->next;
    }
    if(two==NULL){
        return one->next;
    }
    while(two->next!=NULL){
        one = one->next;
        two = two->next;
    }
    one->next = one->next->next;
    return head;
}

Node* mergeTwoLL(Node *head1, Node *head2){
    if(head1==NULL) return head2; 
    if(head2==NULL) return head1; 

    Node *finalHead=NULL; //head of the list to return
    if(head1->data<head2->data){
        finalHead = head1;
        head1 = head1->next;
    }
    else{
        finalHead = head2;
        head2 = head2->next;
    }
    Node *p = finalHead; // pointer to form new LL
    while(head1 && head2){
        if(head1->data<head2->data){
            p->next = head1;
            head1 = head1->next;
        }
        else{
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if(head1) p->next = head1;
    else p->next = head2;
    return finalHead;
}

Node* mergeSortLL(Node *head){
    if(head==NULL || head->next==NULL) return head;
    // break list into two halves
    Node* slow = head; Node* fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* n =  slow->next;
    slow->next = NULL;
    Node* a = mergeSortLL(head);
    Node* b = mergeSortLL(n);

    head = mergeTwoLL(a, b);
    return head;
}

Node* takeInput(){  //Node* because it will return head 
    int data; cin>>data;
    Node *head = NULL; //LL is initially empty
    Node *tail = NULL; //LL is initially empty
    while(data!=-1){
        //Creating LL
        Node *n = new Node(data);
        //1st node
        if(head==NULL){
            head = n;
            tail = n;
        }
        else{
            tail->next = n; //Inserting at tail
            tail = n;
        }
        cin>>data;
    }
    return head;
}

Node* findMid(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    if(fast) return slow->next; //even length
    return slow; //odd length
}

Node *reverseLL(Node *head){
    Node *curr = head;
    Node *prev = NULL;
    while(curr!=NULL){
        Node *n = curr->next;
        curr->next = prev;
        prev = curr;
        curr = n;
    }
    return prev;
}

Node* takeInputRev(){  //Node* because it will return head 
    int data; cin>>data;
    Node *head = NULL; //LL is initially empty
    Node *tail = NULL; //LL is initially empty
    while(data!=-1){
        //Creating LL
        Node *n = new Node(data);
        //1st node
        if(head==NULL){
            head = n;
            tail = n;
        }
        else{
            n->next = head; //Inserting at head
            head = n;
        }
        cin>>data;
    }
    return head;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Statically
    // Node n1(1);
    // Node *head = &n1;

    // Node n2(2);
    // Node n3(3);
    // Node n4(4);
    // Node n5(5);

    // n1.next = &n2;
    // n2.next = &n3;
    // n3.next = &n4;
    // n4.next = &n5;
    Node *head1 = takeInput(); //Inserting at tail
    // Node *head2 = takeInput(); //Inserting at tail
    print(head1); 
    Node* head = mergeSortLL(head1);
    print(head);
    // print(head2); 
    // Node* head = mergeTwoLL(head1, head2);
    // print(head);
    // head = removeNthNodeFrmEnd(head, 3);
    // head = reverseLL(head);
    // print(head); 
    // Node *temp = findMid(head);
    // cout<<temp->data;
    // int data; cin>>data;
    // cout<<isPresentRecursion(head, data);
    // cout<<lengthRecursion(head);
    // int i, data; cin>>i>>data;
    // head = insertAtIthPos(head, i, data);
    // int i; cin>>i;
    // head = deleteIthNode(head, i);
    // print(head);

    // printithNode(head, 4);
    // Node *head2 = takeInputRev(); //Inserting at head
    // cout<<length(head)<<endl;
    // print(head2);
    
    //Creating objects statically
    // Node n1(1);
    // Node n2(2);

    // n1.next = &n2;
    // cout<<n1.data<<" "<<n2.data<<endl;

    // Node *head = &n1;
    // cout<<head->data<<endl;

    // //Dynamically
    // Node *n3 = new Node(3);
    // Node *n4 = new Node(4);
    // n3->next = n4;

    return 0;
}