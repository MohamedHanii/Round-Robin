#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int element;
    struct Node *next;
} Node; // node that makes the queue
typedef struct
{
    Node *head, *tail;
} Queue;// queue with head and tail pointers
typedef struct
{
    int enter;
    int out;
    char name [10];
} process;// structure nneded for read from file and store information

 //protoTypes
Node * newNode(int value);
void initialize(Queue *s);
void enqueue(Queue *s,int value);
int dequeue(Queue *s);
int isEmpty(Queue *s);
void proccessing(Queue *s);

int main()
{
    Queue s; // create Queue
    initialize(&s);//Initialize
    proccessing(&s);// send Queue to make the Operation
    return 0;
}
void initialize(Queue *s)
{
    s->head=NULL;//setting the head and tail pointers to null if new Queue
    s->tail=NULL;
}
Node * newNode(int value)
{
    Node *n=malloc(sizeof(Node));//allocate place in memory with size of structure node
    n->element=value;// take value and assign node with it
    n->next=NULL;// set nextpointer to null
    return n;
}
void enqueue(Queue *s,int value)
{
    Node *n=newNode(value);// take value and put it in new node
    Node *temp=s->tail;// create temp pointer to node which point tail of queue
    s->tail=n; //change queue tail to point to new node
    if (temp) temp->next=n;// if temp != null then temp ==> old tail will point to the new node
    else s->head=n; // if == null point the head of queue to the pointer mean that it is the first element input
}
int dequeue(Queue *s)
{
    Node *temp=(Node*)s->head;// create pointer to node and points to the head
    if (temp) // if temp != null
    {
        int value=temp->element; // take the value from the head
        s->head=(Node *)temp->next;//and make head pointer point to the next node in queue
        free(temp); // delete the temp node
        if (!s->head) s->tail=NULL;// if head point to node then it was the last node so tail will point also to null
        return value;
    }
    printf("\n***ERROR***") ;// if the queue was empty i will print error
    exit(0);
}
int isEmpty(Queue *s)
{
    if(s->head&&s->tail)// if queue empty return 1 else return0
        return 0;
    else
        return 1;
}
void proccessing(Queue *s)
{
    FILE *fptr;
    process pro[10]; // create variable pro of process  that will take values from file and deal with the processing
    int inproc[10];// it will carry the indexes of the pro variables in the array to be put in stack
    int i=0,j=0,flag=0;// counters
    int temp;
    char c;
    int noofprocessing=0;
    if (fptr = fopen("processor.txt","r")==NULL) // if reading from file equal to null then the file doesn't exist
    {
        printf("********FILE NOT FOUND*********");
        exit(0);
    }
    else
    {
        printf("********THE FILE***********\n");
        fptr = fopen("processor.txt","r");
        while(!feof(fptr)) // loop until the end ot the file
        {
            c=getc(fptr); // get the  Char from file and put it in the variable c
            printf("%c",c);
            if(c=='=') // if the c equals to (=) then the number after this will be the time
            {
                flag++; //increas e flag counter to 0 flag here counter to know that the time is taken and so now will take the processing items
                while(!feof(fptr)) // loop until the end of file
                {
                    c=getc(fptr); // get char from file
                     printf("%c",c);
                    if(c==' ') // if it equal to space then don't continue the code and start from while again the second while
                        continue;
                    else if(c=='\n') // if it equal to \n then it mean it will go to the next line
                    {

                        noofprocessing=noofprocessing/10; // take variable noofprocessing that indacte the time and divide by 10
                        pro[0].enter=0; // initialize the first enter and out of the array to zero
                        pro[0].out=0;
                        break;
                    }
                    else // else take the value from c and - '0' to get the value of that integer and add to the old value and * 10 to traverse
                    {
                           noofprocessing= noofprocessing+(c-'0');
                           noofprocessing=noofprocessing*10;
                    }
                }
            }
            else if(flag>0) // flag >0 means that the  time is processing is taken
            {
                pro[0].name[0]=c; //assign the first  with c because from last loop it will read first char of the processing items
                j++;   // it loops inside the name array inside struct  process
                flag=0;// flag here indicate which part of the word the pointer of file at
                i=0;  // counter which moves inside the array of struct process

                while(!feof(fptr))
                {
                    c=getc(fptr);
                     printf("%c",c);
                    if(c==' ') // if  c was space increase flag and continue
                    {
                        flag++;
                        continue;
                    }
                    else if(c>='0'&&c<='9')// if c equals from 0 -9
                    {
                        if(flag==1) // if flag == 1 then c now is reading the entering time
                        {
                            pro[i].enter= pro[i].enter+(c-'0'); // take value and subtract '0' ASCII value to know int value
                            pro[i].enter=pro[i].enter*10;// then multiply by 10
                        }
                        else if(flag==2)// if flag == 2 then c now is reading the outing time
                        {
                            pro[i].out+=(c-'0'); // take value and subtract '0' ASCII value to know int value
                            pro[i].out=pro[i].out*10;// then multiply by 10

                        }
                        else// else flag == 0 then c now is reading number which beside the process
                        {
                            pro[i].name[j]=c; // read number and put in the name
                            j++;  // increase the j to get next char in the name
                        }
                    }
                    else if(c=='\n') // if it read new linew
                    {
                        pro[i].enter=pro[i].enter/10; // it will divide the enter and out value by 10 to get the value
                        pro[i].out=pro[i].out/10;
                        flag=0; // make counter =0
                        pro[i].name[j]='\0';  // end the name with null to act as string
                        j=0;// make counter =0
                        i++;// increase i
                        pro[i].enter=0; // initialize
                        pro[i].out=0;
                    }
                    else // else then it will be not from 0-9 or space or \n so it will be the name of process
                    {
                        pro[i].name[j]=c;
                        j++;
                    }
                }
                if (feof(fptr)) // if the file end the reading so we have to make step of ending line
                {
                    pro[i].name[j-1]='\0';
                    pro[i].enter=pro[i].enter/10;
                    pro[i].out=pro[i].out/10;
                    flag=0;
                }
                flag++;
            }
        }
        fclose(fptr);
        flag=0;
        i=0;
    }
printf("\n========================\n\n");
printf("********PROCESSING********\n");
// the File end now the processing part

    while(i<noofprocessing) // loop until the processing time that  was read from file
    {
        // if time equals to zero
        // loop from 0 - 4 the number of items inside the array of process
        //
        if(i==0){ // if time =0
        for(j=0; j<4; j++)
        {
            if(pro[j].enter == i&&pro[j].name!=NULL) // if name not equal null means that there is element inside array
            {
                inproc[flag]=j; // take the indexs of the element and put it in array
                enqueue(s,j); // then put the index in queue
                flag++; // increase arraycounter
            }
        }
        }

        if(!isEmpty(s)) // if the queue isn't empty
        {
            temp=dequeue(s); // remove the first elment
            pro[temp].out--; // and decrease the out time
            if(pro[temp].out==0) // if out =0
            {
                printf("%s (%d-->%d) aborted \n",pro[temp].name,i,i+1);
                i++; // when the time increase check if there is any element have entering time at this time
                for(j=0; j<4; j++)
                {
                    if(pro[j].enter == i&&pro[j].name!=NULL)
                    {
                        inproc[flag]=j;
                        enqueue(s,j);
                        flag++;
                    }
                }
            }
            else if (pro[temp].out !=0) // if out time not equal to zero
            {
                printf("%s (%d-->%d)\n",pro[temp].name,i,i+1);
                i++;// when the time increase check if there is any element have entering time at this time  before queue last process
                for(j=0; j<4; j++)
                {
                    if(pro[j].enter == i&&pro[j].name!=NULL)
                    {
                        inproc[flag]=j;
                        enqueue(s,j);
                        flag++;
                    }
                }
                enqueue(s,temp); // then put the element again inside the queue
            }

        }
        else // if the queue was empty
        {
            printf("Idle (%d-->%d)\n",i,i+1);
            i++;// when the time increase check if there is any element have entering time at this time
            for(j=0; j<4; j++)
            {
                if(pro[j].enter == i&&pro[j].name!=NULL)
                {
                    inproc[flag]=j;
                    enqueue(s,j);
                    flag++;
                }
            }
        }
    }
    printf("Stop"); //end
}


