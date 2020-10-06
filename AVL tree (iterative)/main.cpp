// AVL tree data structure

#include <iostream>
#include <fstream>

using namespace std;

#define NULL 0

class node
{
public:
    int data;
    int height;
    node* lchild;
    node* rchild;
    node* parent;
    node()
    {
        height= 1;
        data = 0;
        lchild = rchild = parent = NULL;
    }
};

node* root = new node;

void create(int in)
{
    root->data = in;
}

int maxh(int a, int b)
{
    return (a>b)? a:b;
}

int get_height(node* ptr)
{
    if(ptr==NULL)
    {
        return 0;
    }
    else
    {
        return maxh(get_height(ptr->lchild),get_height(ptr->rchild))+1;
    }
}

int get_balance(node* ptr)
{
    if (ptr==NULL)
    {
        return 0;
    }
    else
    {
        return get_height(ptr->lchild)- get_height(ptr->rchild);
    }
}

node* get_unbalanced_node(node* ptr)
{
    if(get_balance(ptr)>1 || get_balance(ptr)<-1)
    {
        return ptr;
    }
    else
    {
        if(ptr->parent!=NULL)
        {
            return get_unbalanced_node(ptr->parent);
        }
        else
        {
            return NULL;
        }
    }
}

void update_heights(node* ptr)
{
    if(ptr==NULL){}
    else
    {
        ptr->height = get_height(ptr);
        update_heights(ptr->parent);
    }
}

int assign_heights(node* ptr)
{
    if(ptr!=NULL)
    {
        assign_heights(ptr->lchild);
        ptr->height = get_height(ptr);
        assign_heights(ptr->rchild);
    }
}

void display(node* );

void left_rotate(node* a, node* b)
{
    node* temp = b->lchild;
    b->parent = a->parent;
    b->lchild = a;
    a->rchild = temp;
    a->parent = b;
    if(temp!=NULL)
    {
        temp->parent = a;
    }
    if(b->parent!=NULL)
    {
        if(b->parent->data > b->data)
        {
            b->parent->lchild = b;
        }
        else
        {
            b->parent->rchild = b;
        }
    }
    else
    {
        root = b;
    }
    assign_heights(root);
}

void right_rotate(node* a, node* b)
{
    node* temp = b->rchild;
    b->parent = a->parent;
    b->rchild = a;
    a->lchild = temp;
    a->parent = b;
    if(temp!=NULL)
    {
        temp->parent = a;
    }
    if(b->parent!=NULL)
    {
        if(b->parent->data > b->data)
        {
            b->parent->lchild = b;
        }
        else
        {
            b->parent->rchild = b;
        }
    }
    else
    {
        root = b;
    }
    assign_heights(root);
}

void add_ele(int in)
{
    node* ptr = root;
    while(ptr!=NULL)
    {
        if(ptr->data>in)
        {
            if(ptr->lchild==NULL)
            {
                node* temp = new node;
                temp->parent = ptr;
                temp->data = in;
                ptr->lchild = temp;
                update_heights(ptr);
                break;
            }
            ptr = ptr->lchild;
        }
        else if(ptr->data<in)
        {
            if(ptr->rchild==NULL)
            {
                node* temp = new node;
                temp->data = in;
                temp->parent = ptr;
                ptr->rchild = temp;
                update_heights(ptr);
                break;
            }
            ptr = ptr->rchild;
        }
        else
        {
            cout<<"\n***Duplicate elements are not allowed***"<<endl;
            break;
        }
        ptr->height = get_height(ptr);
    }
    node* u_node = get_unbalanced_node(ptr);
    if (u_node!=NULL)
    {
        int balance = get_balance(u_node);
        if (balance==2)
        {
            //LL & LR
            //z = u_node
            node* y = u_node->lchild;
            if(get_height(y->lchild)>get_height(y->rchild))
            {
                //LL   (node* x = y->lchild;)
                //cout<<"\t\t\nLL\n";
                right_rotate(u_node,y);
            }
            else
            {
                //LR
                node* x = y->rchild;
                //cout<<"\t\t\nLR\n";
                left_rotate(y,x);
                right_rotate(u_node,x);
            }
        }
        else if(balance==-2)
        {
            //RR & RL
            node* y = u_node->rchild;
            if(get_height(y->lchild)>get_height(y->rchild))
            {
                //RL
                node* x = y->lchild;
                //cout<<"\t\t\nRL\n";
                right_rotate(y,x);
                left_rotate(u_node,x);
            }
            else
            {
                //RR (node* x = y->rchild;)
                //cout<<"\t\t\nRR\n";
                left_rotate(u_node,y);
            }
        }
    }
}

int delete_ele(int in)
{
    node* ptr = root;
    while(ptr!=NULL)
    {
        if(ptr->data == in)
        {
            node* r = ptr->rchild;
            node* l = ptr->lchild;
            if(l==NULL && r==NULL)
            {
                if(ptr->parent->data > in)
                {
                    ptr->parent->lchild = NULL;
                }
                else
                {
                    ptr->parent->rchild = NULL;
                }
                break;
            }
            else if(l==NULL && r!=NULL)
            {
                r->parent = ptr->parent;
                if(ptr->parent==NULL)
                {
                    root = r;
                }
                else
                {
                    if(ptr->parent->data > in)
                    {
                        ptr->parent->lchild = r;
                    }
                    else
                    {
                        ptr->parent->rchild = r;
                    }
                }
                break;
            }
            else if(l!=NULL && r==NULL)
            {
                l->parent = ptr->parent;
                if(ptr->parent==NULL)
                {
                    root = l;
                }
                else
                {
                    if(ptr->parent->data > in)
                    {
                        ptr->parent->lchild = l;
                    }
                    else
                    {
                        ptr->parent->rchild = l;
                    }
                }
                break;
            }
            else
            {
                if(r->lchild==NULL)
                {
                    r->parent=ptr->parent;
                    if(ptr->parent==NULL)
                    {
                        root=r;
                    }
                    r->lchild=ptr->lchild;
                    r->lchild->parent=r;
                    if(ptr->parent!=NULL)
                    {
                        if(ptr->parent->data > r->data)
                        {
                            ptr->parent->lchild = r;
                        }
                        else
                        {
                            ptr->parent->rchild = r;
                        }
                    }
                    break;
                }
                else
                {
                    node* temp = r;
                    while(temp->lchild!=NULL)
                    {
                        temp = temp->lchild;
                    }
                    temp->parent->lchild = temp->rchild;
                    if(temp->rchild!=NULL)
                    {
                        temp->rchild->parent=temp->parent;
                    }
                    temp->parent = ptr->parent;
                    if (temp->parent==NULL)
                    {
                        root = temp;
                    }
                    temp->lchild = ptr->lchild;
                    temp->rchild = ptr->rchild;
                    ptr->lchild->parent = temp;
                    ptr->rchild->parent = temp;
                    if(ptr->parent!=NULL)
                    {
                        if(ptr->parent->data > temp->data)
                        {
                            ptr->parent->lchild = temp;
                        }
                        else
                        {
                            ptr->parent->rchild = temp;
                        }
                    }
                    break;
                }
            }
        }
        else if(ptr->data > in)
        {
            if (ptr->lchild!=NULL)
            {
                ptr = ptr->lchild;
            }
            else
            {
                cout<<"\n***Element doesn't exist in tree***\n";
                return 1;
            }
        }
        else if(ptr->data < in)
        {
            if (ptr->rchild!=NULL)
            {
                ptr = ptr->rchild;
            }
            else
            {
                cout<<"\n***Element doesn't exist in tree***\n";
                return 1;
            }
        }
    }
    node* st = ptr;
    assign_heights(root);
    node* u_node;
    while(st!=NULL)
    {
        u_node = get_unbalanced_node(st);
        node* y;
        node* x;
        if (u_node != NULL)
        {
            //cout<<"Data: "<<u_node->data<<"  Balance: "<<get_balance(u_node)<<endl;
            int balance = get_balance(u_node);
            if(get_height(u_node->rchild)>=get_height(u_node->lchild)) //equal to?
            {
                y = u_node->rchild;
            }
            else
            {
                y = u_node->lchild;
            }
            if(get_height(y->rchild)>get_height(y->lchild)) //equal to?
            {
                x = y->rchild;
            }
            else
            {
                x = y->lchild;
            }
            if(balance==2)
            {
                //LL & LR

                if(x==y->lchild)
                {
                    //LL
                    right_rotate(u_node,y);
                }
                else
                {
                    //LR
                    left_rotate(y,x);
                    right_rotate(u_node,x);
                }
            }
            else if(balance==-2)
            {
                //RR & RL

                if(x==y->lchild)
                {
                    //RL
                    right_rotate(y,x);
                    left_rotate(u_node,x);
                }
                else
                {
                    //RR
                    left_rotate(u_node,y);
                }
            }
        }
        else
        {
            break;
        }
    }
    delete(ptr);
    return 0;
}

bool search_ele(int in)
{
    node* ptr = root;
    while(ptr!=NULL)
    {
        if(ptr->data == in)
        {
            return true;
        }
        else if(ptr->data>in)
        {
            ptr = ptr->lchild;
        }
        else
        {
            ptr = ptr->rchild;
        }
    }
    return false;
}

void display(node* ptr)
{
    if(ptr!=NULL)
    {
        display(ptr->lchild);
        cout<<" "<<ptr->data<<" ("<<ptr->height<<")\n";
        display(ptr->rchild);
    }
}

int main()
{
    cout<<"AVL Tree implementation by Nishanth.G\n\n";
    int i, n, ele;
    cout<<"Enter the no of elements: ";
    cin>>n;
    cout<<"Enter the elements: \n";
    cin>>ele;
    create(ele);
    for(i=0;i<n-1;i++)
    {
        cin>>ele;
        add_ele(ele);
    }
    cout<<"\n\t\t\t\t***AVL tree constructed***";
    while(1)
    {
        cout<<"\n\nChoose action:\n1)Add element\n2)Delete element\n3)Search element\n4)Display\n5)Exit\n\t(1/2/3/4/5): ";
        int resp;
        cin>>resp;
        if (resp==1)
        {
            cout<<"Enter element : ";
            cin>>ele;
            add_ele(ele);
            //display(root);
        }
        else if(resp==2)
        {
            cout<<"Enter element : ";
            cin>>ele;
            delete_ele(ele);
            //display(root);
        }
        else if(resp==3)
        {
            cout<<"Enter element : ";
            cin>>ele;
            if(search_ele(ele))
            {
                cout<<"*** Element found in Dictionary ***";
            }
            else
            {
                cout<<"*** Element not found in Dictionary ***";
            }
            //display(root);
        }
        else if(resp==4)
        {
            display(root);
        }
        else
        {
            break;
        }
    }
    return 0;
}
