// Brian Murphy R00189335
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node * getInformation(); // inatlising some functions needed
struct Parameter * makeParameterStack();
void printNodes(struct Parameter* head);
void studentStack(struct Parameter*, struct Node*);
bool studentValidCheck(struct Parameter* p);
int fileSize();


struct Student{ // student structure
    char name[20];
    char inital;
    char surname[20];
    int year;
    char courseName[20];
    char group;
    int average;
    };

    struct Node { // node apart of the student linked list
    struct Student* student;
    struct Node* next;
    };

    struct Parameter{ // passed to the fscanf function. stores the data in the correct type, stores character representing data type in dataType varible, points to the next Parameter in the list
        char strings[21];
        int numbers;
        char character;
        char dataType;
        struct Parameter* next;
    };
void myfscanf(char formatString[],FILE* , struct Parameter*); // initalising myfscanf
int main()
{
    char fileAddress[150];// user inputted file address storage
    printf("Please enter file address ");
    scanf("%[^'\n']s",fileAddress);
    char formatString[] = "%s (%c) %s %d %s %c %d";// premade format string for the student database

    struct Node* top;
    top = (struct Node*)malloc(sizeof(struct Node));
    top->next=NULL;

    int fileLength = fileSize(fileAddress); // stores the amount of lines in the file
    FILE * f;
    f=fopen(fileAddress,"r");

    for(int i =0; i<fileLength;i++){
        struct Parameter* p;
        p = (struct Parameter*)malloc(sizeof(struct Parameter));
        p=makeParameterStack(p);
        myfscanf(formatString,f,p);
        printP(p);// used to show the data read from the file a stored in the paramiters
        studentStack(p,top);// an attempt to get the data stored in the paramiter linked list into nodes containing students and link them


    }
printStudentNode(top);
//
}
void myfscanf(char formatString[], FILE * f,struct Parameter *currentNode)
{
    char c; // character where the fgetc data is going
    int length;
    length = strlen(formatString); // length of the format string
    if(c=='\n'){ // if the file is a new line take out the character and put it back
        c=fgetc(f);
        ungetc(c,f);
    }

    while(c != '\n' || c != EOF){

        if (c =='\n'){// for some reason the while statement wouldnt stop on the newline
            break;
        }
        c=fgetc(f);// grab a character

        for(int i=0;i <= length ;i++){// iterate from 0 to the length of the format string
            if(formatString[i]=='s'){// if the current position in the format string is an s we look for a string
                int index =0; // start the index of the string we are gonna store the characters at 0
                char strings[20];// string where we are gonna store the characters
                while (c <'a' || c >'z' ){// while its not a letter keep grabbing characters till one is a letter
                        c=fgetc(f);
                    }

                while(c >='a' && c <='z'){// keep grabbing characters as long as they are characters
                    strings[index]=c;// put the got character in the next index spot
                    index++;// increment the index
                    c=fgetc(f);// grab a character
                }
                strings[index]='\0';// put a null at the end of the string
                strcpy(currentNode->strings, strings);// copy the data into the string varible of the current node
                currentNode->dataType='s';// record the dataType of s in the node we are writing too
                currentNode = currentNode->next;// go to the next node since this one is written

            }
            else if(formatString[i]=='c'){// if format string is c

                    while (c <'a' || c >'z' ){// keep going untill we get a character
                        c=fgetc(f);
                    }
                currentNode->character=c;// once we got a character write it to the current node
                currentNode->dataType='c';// recorded the dataType as c in the current node

                currentNode = currentNode->next;// go to the next node
                c=fgetc(f);// go to the next character

            }
            else if (formatString[i] =='d'){// if the format string is a d
               while (c <'0' || c >'9' ){// keep going untill we get a number
                        c=fgetc(f);
                    }
                    int number =0;// start our number off at 0
                    int digit;// this is where we are gonna store the numbers as they come in

                    while(c >='0' && c <='9' ){// while we keep getting numbers
                        digit = c -'0';// turn it from an assci character into a number
                        number = number *10;// times the current count by 10
                        number = number+ digit;// add the new number
                        c=fgetc(f);// get a new number
                    }
                    currentNode->numbers=number;// write the number to the current node
                    currentNode->dataType='d';// record the dataType as d
                    currentNode = currentNode->next;// go to the next node
            }
        }

}
};

struct Parameter* makeParameterStack(){// it can accept any size of preformed stack of perameter nodes. this function is to quickly make a stack of 7 as that is the numebr our student database needs
    struct Parameter* head;
    head = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n2;
    n2 = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n3;
    n3 = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n4;
    n4 = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n5;
    n5 = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n6;
    n6 = (struct Parameter*)malloc(sizeof(struct Parameter));

    struct Parameter* n7;
    n7 = (struct Parameter*)malloc(sizeof(struct Parameter));
    head->next=n2;
    n2->next=n3;
    n3->next=n4;
    n4->next=n5;
    n5->next=n6;
    n6->next=n7;
    n7->next=NULL;
    return head;
};

void studentStack(struct Parameter* parameters,struct Node* head){// this function takes a linked list of full parameters and makes a student and a node with that student
    int count=0;// used to store the count of the linked list paramiters
    count = linkedListLength(parameters);// i assume the student database only wants full students so i am testing if there is the correct about of peramiters in the linked list to make a student
    bool isValid= studentValidCheck(parameters);// this checks that the data types of the paramiters are in the correct order to form a student %s (%c) %s %d %s %c %d
    if(count ==7 && isValid){// if there is 7 in the paramiter linked list and the dataType order is correct we can make a student
        struct Node *last = head;
        struct Node* n;// make a new node
        n = (struct Node*)malloc(sizeof(struct Node));

        struct Student* s;// make a new student
        s = (struct Student*)malloc(sizeof(struct Student));

        strcpy(s->name,parameters->strings);// copy the first paramiter in the linked list to the name of the student
        parameters = parameters->next;

        s->inital = parameters->character;// copy the second paramiter in the linked list to the inital of the studetnt etc
        parameters = parameters->next;

        strcpy(s->surname,parameters->strings);
        parameters = parameters->next;

        s->year = parameters->numbers;
        parameters = parameters->next;

        strcpy(s->courseName,parameters->strings);
        parameters = parameters->next;

        s->group = parameters->character;
        parameters = parameters->next;

        s->average = parameters->character;

        n->student=s;// assign the student to the node we created

        /*while (last->next != NULL){ // THIS IS THE PART OF MY CODE THAT DOSNT WORK
            last = last->next;// this is supposed to iterate thoug the linked list to find the last spot, i cant figure it out but for some reason this is an infinate loop
        }// without this working i cant make a working linked list even though everything else should be perfect


        head->next = n;// make the node we were given in the function peramiters to point to the newly created node
        */

    }
}

int linkedListLength(struct Parameter* head){// used to find the length of a linked list
    int count = 0;//start the count at 0
    while (head != NULL)// while there is data
    {
        count++;// increment the count
        head = head->next;// go to the next node in the linked list
    }
    return count;// return the count
}

bool studentValidCheck(struct Parameter* p){// checks if the linked list dataTypes are the correct order to form a studetnt %s (%c) %s %d %s %c %d
    bool res = 0;
    if(p->dataType=='s'){
            p= p->next;
        if(p->dataType=='c'){
            p= p->next;
                if(p->dataType=='s'){
                    p= p->next;
                    if(p->dataType=='d'){
                        p= p->next;
                        if(p->dataType=='s'){
                            p= p->next;
                                if(p->dataType=='c'){
                                    p= p->next;
                                    if(p->dataType=='d'){
                                        res = 1;
}

}

}


}

}

}
}
return res;
}

int fileSize(char fileAddress[]){// return the amount of lines inside a file
    int length=0;// start the count at 0
    FILE * f;
    char c;
    f=fopen(fileAddress,"r");
    c=fgetc(f);
    while (c != EOF){// while we havent hit the end of the file
        if(c=='\n'){// if there is a newline
            length++;// increase the count
        }
        c=fgetc(f);// get the next character
    }
    fclose(f);// close the file
    return length;// return the count
}
void printP(struct Parameter* p){// not part of the goals of the assignment but used for testing, if given a head of a paramiter linked list it would iterate though the linked listand print out the data
    printf("Student Name %s \n",p->strings);
    p = p->next;
    printf("Student Initial %c \n",p->character);
    p = p->next;
    printf("Student Surname %s \n",p->strings);
    p = p->next;
    printf("Student year %d \n",p->numbers);
    p = p->next;
    printf("Student course name %s \n",p->strings);
    p = p->next;
    printf("Student group %c \n",p->character);
    p = p->next;
    printf("Student average %d \n \n",p->numbers);
}

void printStudentNode(struct Node* n){// if given a head of a linked list of nodes containing students would print out the student values and go to the next node untill the linked list is empty
    while(n=! NULL){
            printf("NEXT ONE ");
    printf("Student Name %s \n",n->student->name);
    printf("Student Initial %c \n",n->student->inital);
    printf("Student Surname %s \n",n->student->surname);
    printf("Student Year %d \n",n->student->year);
    printf("Student Course Name %s \n",n->student->courseName);
    printf("Student group %c \n",n->student->group);
    printf("Student average %d \n\n",n->student->average);
    n= n->next;
    }
}

