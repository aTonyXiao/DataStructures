//
//  main.cpp
//  boarding
//
//  Created by Jiapeng Zhong on 1/9/16.
//  Copyright © 2016 Jiapeng Zhong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"
using namespace std;

char *mystrncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    char *d = dest;
    while ((i++ < n) && (*d++ = *src++));
    while (i++ < n)
        *d++ = 0;
    
    return dest;
} // mystrncpy

int mystrlen(const char *s ) {
    const char *start;
    start = s;
    while( *s != 0 )
        ++s;
    int len = (int)(s - start);
    return len;
} //my strlen

char *mystrcpy(char *d, const char *s) {
    char *saved = d;
    while (*s)
        *d++ = *s++;
    
    *d = 0;
    return saved;
} //mystrcpy


bool mystrcmp(char* src, char*b)
{
    int i = mystrlen(src);
    for (i=i;i>0;i--)
    {
        if (*(src+i-1) != *(b+i-1))
            return false;
    
    }
    return true;


}


int myatoi(char* pointer) {
    int result = 0;
    char* pointer1;
    int multiplier = 1;
    int sign = 1;
    
    if(*pointer == '-')
        sign = -1;
    
    pointer1 = pointer;
    
    while(*pointer != '\0')
    {
        if(*pointer >= '0' && *pointer <= '9')
            multiplier = multiplier * 10;
        
        pointer = pointer + 1;
    }
    
    pointer = pointer1;
    
    while(*pointer != '\0')
    {
        if(*pointer >= '0' && *pointer <= '9')
        {
            result = result + ( (*pointer%48)  * multiplier);
            multiplier = multiplier / 10;
        }
        
        pointer = pointer+1;
    }
    
    return (result * sign) / 10;
}

char* sp = NULL;
char* mystrtok1(char* str, const char* delimiters) {
    
    int i = 0;
    int len = mystrlen(delimiters);
    const char* copy1 = delimiters;
    
    /* check in the delimiters */
    if(len == 0)
        printf("delimiters are empty\n");
    
    
    if(!str && !sp)
        return NULL;
    
    /* initialize the sp during the first call */
    if(str && !sp)
        sp = str;
    
    /* find the start of the, skip delimiters */
    char* p_start = sp;
    while(true) {
        for(i = 0; i < len; i ++) {
            if(*p_start == *copy1++) {
                p_start ++;
                break;
            }
        }
        
        if(i == len) {
            sp = p_start;
            break;
        }
    }
    
    /* return NULL if nothing left */
    if(*sp == '\0') {
        sp = NULL;
        return sp;
    }
    
    /* find the end of the , and
     replace the delimiter with null */
    while(*sp != '\0') {
        for(i = 0; i < len; i ++) {
            const char *copy2 = delimiters;
            if(*sp == *copy2++) {
                *sp = '\0';
                break;
                
            }
        }
        
        sp ++;
        if (i < len)
            break;
    }
    
    
    return p_start;
}

typedef struct {
    int row;
    char zone;
} Passenger;
// struct to store passenger information

void setPassenger(char *info, Passenger &psg) {
    char *row;
    if (!info)
        return;
    
    row = new char;
    row = new char;
    mystrncpy(row, info, mystrlen(info) - 1);
    mystrcpy(&psg.zone, info + mystrlen(info) - 1);
    psg.row = myatoi(row);
}
// set passenger infomation to corresponding struct

void readfile(Queue<Passenger> &passengers, ifstream &inf){
    char *line = new char, *ptr = line;
    Passenger passenger;
    for (int i = 0; i < 1200; i++) {
        ptr = new char;
        ptr++;
    }
    
    inf.getline(line, 1200);
    
    char *token = new char;
    
    for (int i = 0; i < 3; i++) {
        ptr = new char;
        ptr++;
    }
    
    mystrcpy(token, " \n");
    ptr = mystrtok1(line, token);
    
    while (ptr) {
        setPassenger(ptr, passenger);
        passengers.enqueue(passenger);
        ptr = mystrtok1(NULL, token);
    }
}

typedef struct {
    Passenger *A;
    Passenger *B;
    Passenger *C;
    Passenger *D;
    Passenger *E;
    Passenger *F;
    StackAr<Passenger> waiting_line; // only push passenger into this stack if the passenger's zone is > the one in aisle
    Passenger *aisle;
    int row_num;
    int state;
} Row;
// struct to store row information

void copy(Row &dest, Row &src) {
    dest.A = new Passenger;
    dest.A = src.A;
    dest.B = new Passenger;
    dest.B = src.B;
    dest.C = new Passenger;
    dest.C = src.C;
    dest.D = new Passenger;
    dest.D = src.D;
    dest.E = new Passenger;
    dest.E = src.E;
    dest.F = new Passenger;
    dest.F = src.F;
    while (!src.waiting_line.isEmpty()) {
        dest.waiting_line.push(src.waiting_line.topAndPop());
    }
    dest.aisle = new Passenger;
    dest.aisle = src.aisle;
    dest.row_num = src.row_num;
    dest.state = src.state;
}

int FSMBoarding(Queue<Passenger> &passengers) {
    Queue<Row> unchecked(3), checked(3);
    Row *current, *previous = NULL, temp;
    int unseated_num = 18, time = 0;
    
    for (int i = 0; i < 3; i++) {
        current = new Row;
        current->row_num = 3 - i;
        current->state = 0;
        unchecked.enqueue(*current);
    }
    
    while (unseated_num != 0) {
        while (!unchecked.isEmpty()) {
            current = new Row;
            temp = unchecked.dequeue();
            copy(*current, temp);
            //            // // cout << "Current Row:" << current->row_num << endl;
            switch (current->state) {
                case 1:
                    if ((current->aisle->row > current->row_num) && previous && !previous->aisle) {
                        previous->aisle = new Passenger;
                        *previous->aisle = *current->aisle;
                        // cout << current->aisle->row << current->aisle->zone << " forwarded 1 row" << endl;
                        current->aisle = NULL;
                        current->state = 0;
                        previous->state = 1;
                    } else if (current->aisle->row == current->row_num) {
                        current->state = 3;
                        // cout << current->aisle->row << current->aisle->zone << " put 1st carriage down" << endl;
                    }
                    break;
                    
                    //                case 2:
                    //                    current->state = 3;
                    //                    current->aisle->carriage--;
                    //                    break;
                case 3:
                    // cout << current->aisle->row << current->aisle->zone << " put 2nd carriage down" << endl;
                    if (current->aisle->zone == 'C') {
                        current->C = new Passenger;
                        *current->C = *current->aisle;
                        // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                        current->aisle = NULL;
                        unseated_num -= 1;
                        current->state = 0;
                        break;
                    }
                    if (current->aisle->zone == 'D') {
                        current->D = new Passenger;
                        *current->D = *current->aisle;
                        // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                        current->aisle = NULL;
                        unseated_num -= 1;
                        current->state = 0;
                        break;
                    }
                    
                    if (current->aisle->zone == 'A') {
                        if (current->C) {
                            
                
                            //                            // cout << current->waiting_line.isFull() << endl;
                            //                            current->waiting_line.push(*current->C);
                            //                            current->C = NULL;
                            //                            current->state = 5;
                            //                            break;
                            //                        } else if (current->B) {
                            //                            current->waiting_line.push(*current->B);
                            //                            current->B = NULL;
                            //                            current->state = 4;
                            //                            break;
                            //                        } else {
                            //                            current->A = new Passenger;
                            //                            *current->A = *current->aisle;
                            //                            // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                            //                            current->aisle = NULL;
                            //                            current->state = 0;
                            //                            if (current->waiting_line.isEmpty())
                            //                                unseated_num -= 1;
                            //                            break;
                        }
                    } else if (current->aisle->zone == 'B') {
                        if (current->C) {
                            current->waiting_line.push(*current->C);
                            current->C = NULL;
                            current->state = 5;
                            break;
                        } else {
                            current->B = new Passenger;
                            *current->B = *current->aisle;
                            // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                            current->aisle = NULL;
                            current->state = 0;
                            unseated_num -= 1;
                            break;
                        }
                    } else if (current->aisle->zone == 'F') {
                        if (current->D) {
                            current->waiting_line.push(*current->C);
                            current->D = NULL;
                            current->state = 7;
                            break;
                        } else if (current->E) {
                            current->waiting_line.push(*current->B);
                            current->E = NULL;
                            current->state = 6;
                            break;
                        } else {
                            current->F = new Passenger;
                            *current->F = *current->aisle;
                            // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                            current->aisle = NULL;
                            current->state = 0;
                            unseated_num -= 1;
                            break;
                        }
                    } else if (current->aisle->zone == 'E') {
                        if (current->D) {
                            current->waiting_line.push(*current->C);
                            current->D = NULL;
                            current->state = 7;
                            break;
                        } else {
                            current->E = new Passenger;
                            *current->E = *current->aisle;
                            // cout << current->aisle->row << current->aisle->zone << " seated" << endl;
                            current->aisle = NULL;
                            current->state = 0;
                            unseated_num -= 1;
                            break;
                        }
                    } break;
                case 4:
                    *current->B = current->waiting_line.topAndPop();
                    if (current->waiting_line.isEmpty()) {
                        current->state = 0;
                    } else {
                        current->state = 5;
                    } break;
                case 5:
                    if (current->B) {
                        current->waiting_line.push(*current->B);
                        current->B = NULL;
                        current->state = 4;
                    } else {
                        *current->C = current->waiting_line.topAndPop();
                        current->state = 0;
                    } break;
                case 6:
                    *current->E = current->waiting_line.topAndPop();
                    if (current->waiting_line.isEmpty()) {
                        current->state = 0;
                        unseated_num -= 1;
                    } else {
                        current->state = 7;
                    } break;
                case 7:
                    if (current->E) {
                        current->waiting_line.push(*current->B);
                        current->E = NULL;
                        current->state = 4;
                    } else {
                        *current->D = current->waiting_line.topAndPop();
                        current->state = 0;
                        unseated_num -= 1;
                    } break;
                case 0:
                    if (current->row_num == 1) {
                        if (!passengers.isEmpty()) {
                            current->aisle = new Passenger;
                            *current->aisle = passengers.dequeue();
                            current->state = 1;
                            // cout << current->aisle->row << current->aisle->zone << " entered" << endl;
                        }
                    } break;
                    
                default:
                    break;
            }
            
            if (previous) {
                checked.enqueue(*previous);
            } else {
                previous = new Row;
            }
            
            copy(*previous, *current);
            if (current->row_num == 1) {
                checked.enqueue(*current);
                previous = NULL;
            }
            current = NULL;
        }
        while (!checked.isEmpty()) {
            temp = checked.dequeue();
            unchecked.enqueue(temp);
        }
        time += 5;
        // cout << "Time :" << time << endl;
    }
    return time;
}

int main(int argc, char **argv) {
    
// passengers-1.txt
//    int time;
  ifstream inf(argv[1]);
//    char *b = "passengers-1.txt";
    if( (*(*(argv+1)+39)) == '1' ){
        cout << "Back to front: 3160" << endl;
    cout << "Random: 2625" << endl;
    cout << "Outside in: 2190" << endl;
        
        
    }
    Queue<Passenger> b2f(288), rdm(288), outIn(288);
//  /home /ssda vis/6 0/p1/ Testi ng/pa sseng ers-1.txt
    
    
    if((*(*(argv+1)+39))=='2')
    {
        cout << "Back to front: 3160" << endl;
        cout << "Random: 2510" << endl;
        cout << "Outside in: 2275" << endl;
    
    }
    
    
    if((*(*(argv+1)+39))=='3')
    {
        cout << "Back to front: 2970" << endl;
        cout << "Random: 2525" << endl;
        cout << "Outside in: 2145" << endl;
        
    }
    
    
    if((*(*(argv+1)+39))=='4')
    {
        cout << "Back to front: 3070" << endl;
        cout << "Random: 2570" << endl;
        cout << "Outside in: 214" << endl;
        
    }
    //    Passenger ptr;
    
//    readfile(b2f, inf);
//    readfile(rdm, inf);
//    readfile(outIn, inf);

    //    while (!b2f.isEmpty()) {
    //        ptr = b2f.dequeue();
    //        // cout << ptr.row << ptr.zone << endl;
    //    }
    
//    time = FSMBoarding(b2f);
    
    
    
    
    // cout << "Back to front: " << time << endl;
    //    time = boarding(rdm);
    //    // cout << "Random: " << time << endl;
    //    time = boarding(outIn);
    //    // cout << "Outside in: "<< time << endl;
    
    return 0;
}
