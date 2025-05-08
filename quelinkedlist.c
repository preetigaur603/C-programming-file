#include <stdio.h>
#include <stdlib.h>

typedef struct que {
    int data;
    struct que *next;
} q;

q*enque(q*);

int main()
{
    q*f=NULL,*r=NULL;
    int ch;
    do{
        case 1:
        r=enque(q);
        if(f==NULL)
        f=r;
        break;
    }while(ch<=1);
}

q*enque(q* r)
{
    int x;
    q*p=NULL;
    p=(q*)malloc(sizeof(q));
    if(p==NULL)
    {
        printf("memory is not allocated!");
    }
    else{
        printf("enter the data: ");
        scanf("%d",&x);
        p->data=x;
        if(r==NULL)
        {
            r=p;
        }
        else{
            r->next=p;
            r=p;
        }
        r->next=NULL;
    }
    return (r);
}