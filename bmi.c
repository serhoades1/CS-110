#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmi.h"

///////////////////////////////////////////////////////////////
// helper functions

Person *createPerson(char *first, char *last, int height, int weight, Person *nextHeight, Person *nextWeight)
{
    Person *ptr=malloc(sizeof(Person));
    ptr->first=malloc(strlen(first)+1);
    strcpy(ptr->first, first);
    ptr->last=malloc(strlen(last)+1);
    strcpy(ptr->last, last);

    ptr->height=height;
    ptr->weight=weight;

    ptr->nextHeight=nextHeight;
    ptr->nextWeight=nextWeight;

    return ptr;
}

int compareHeight(Person *pNew, Person *pExisting) {
    if (pNew->height == pExisting->height) {
        if (pNew->weight == pExisting->weight) {
            return 1;
        }
        else if (pNew->weight > pExisting->weight) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else if (pNew->height > pExisting->height) {
        return -1;
    }
    else {
        return 1;
    }
    return -1; //Unreachable
}

int compareWeight(Person *pNew, Person *pExisting) {
    if (pNew->weight == pExisting->weight) {
        if (pNew->height == pExisting->height) {
            return 1;
        }
        else if (pNew->height < pExisting->height) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else if (pNew->weight < pExisting->weight) {
        return -1;
    }
    else {
        return 1;
    }
    return -1; //Unreachable
}

Person *addToHeightList(Person *head, Person *pNew) {
	if (head == NULL) {
        return pNew;
    }
	// printf("After if-statement in addHeight\n");

    if (compareHeight(pNew, head) < 0) {
        pNew->nextHeight = head;
        return pNew;
    }

    for (Person *cur = head; cur != NULL; cur = cur->nextHeight) {
        if (cur->nextHeight == NULL) { // Case #3: d is the smallest, add at the end
		// printf("Case #3 in addHeight\n");
            cur->nextHeight = pNew;
            return head;
        }

        if (compareHeight(pNew, cur->nextHeight) < 0) { // Case #4: insert between cur and cur->next
		// printf("Case #4 in addHeight\n");
            pNew->nextHeight = cur->nextHeight;
            cur->nextHeight = pNew;
            return head;
        }
    }
    // if (cur->nextHeight == NULL) {
    //     cur->nextHeight = pNew;
    //     return list;
    // }

    // if (compareHeight(pNew, cur->nextHeight) < 0) {
    //     pNew->nextHeight = cur->nextHeight;
    //     cur->nextHeight = pNew;
    //     return list;
    // }


	return NULL;
}

Person *addToWeightList(Person *head, Person *pNew) {
	if (head == NULL) {
        return pNew;
    }
	// printf("After if-statement in addWeight\n");

    if (compareWeight(pNew, head) < 0) {
        pNew->nextWeight = head;
        return pNew;
    }

    for (Person *cur = head; cur != NULL; cur = cur->nextWeight) {
        if (cur->nextWeight == NULL) { // Case #3: d is the smallest, add at the end
		// printf("Case #3 in addWeight\n");
            cur->nextWeight = pNew;
            return head;
        }

        if (compareWeight(pNew, cur->nextWeight) < 0) { // Case #4: insert between cur and cur->next
		// printf("Case #4 in addWeight\n");
            pNew->nextWeight = cur->nextWeight;
            cur->nextWeight = pNew;
            return head;
        }
    }
	// for (Person *cur = list->headWeightList; cur != NULL; cur = cur->nextWeight) {
    //     if (cur->nextWeight == NULL) {
    //         cur->nextWeight = pNew;
    //         return list;
    //     }

    //     if (compareWeight(pNew, cur->nextWeight) < 0) {
    //         pNew->nextWeight = cur->nextWeight;
    //         cur->nextWeight = pNew;
    //         return list;
    //     }
    // }

	return NULL; //Unreachable
}

///////////////////////////////////////////////////////////////

// Old add function

// PersonList *add(PersonList *list, char *first, char *last, int height, int weight) {
// 	// make sure it does not already exist
// 	Person *ptr=search(list, first, last);
// 	if (ptr!=NULL) {
// 		printf("Error: %s %s already exists in the list\n", first, last);
// 		return list;
// 	}

// 	// allocate a new node
// 	Person *pNew=createPerson(first, last, height, weight, NULL, NULL);

// 	// add it to "headHeightList"
// 	pNew->nextHeight=list->headHeightList;
// 	list->headHeightList=pNew; 

// 	// add it to "headWeightList"
// 	pNew->nextWeight=list->headWeightList;
// 	list->headWeightList=pNew; 

// 	return list;
// }

PersonList *add(PersonList *list, char *first, char *last, int height, int weight) {
	// make sure it does not already exist
	Person *ptr=search(list, first, last);
	if (ptr!=NULL) {
		printf("Error: %s %s already exists in the list\n", first, last);
		return list;
	}

	// allocate a new node
	Person *pNew=createPerson(first, last, height, weight, NULL, NULL);

	// add it to "headHeightList"
    list->headHeightList = addToHeightList(list->headHeightList, pNew);


    // else if ( > head->degree) {
    //     return createTerm(c, d, head);
    // }
    // else {
    //     head->next = addOrdered(head->next, c, d);
    //     return head;
    // }

	// Person *ptr = list->headHeightList;
	// Person *ptr1 = list->headHeightList;

	// // while (ptr != NULL) {
	// 	if (ptr == NULL && ptr1 == NULL) {
	// 		pNew->nextHeight = list->headHeightList;
	// 		list->headHeightList = pNew;

	// 		pNew->nextWeight = list->headWeightList;
	// 		list->headWeightList = pNew;

	// 		return list;
	// 	}

	// 	if (compareHeight(pNew, list->headHeightList) < 0) {
	// 		pNew->height = list->headHeightList;
	// 		return pNew;
	// 	}

	// 	for (Person *cur = list; cur != NULL; cur = cur->nextHeight) {
	// 		if (cur->nextHeight == NULL) {
	// 			cur->nextHeight = pNew;
	// 			return list;
	// 		}

	// 		if (compareHeight(pNew, cur) < 0) {
	// 			pNew->nextHeight = cur->nextHeight;
	// 			cur->nextHeight = pNew;
	// 			return list;
	// 		}
	// 	}
	// // }
	
	
	// while (1) {
	// 	if (ptr->height <= ptr->nextHeight->height && ptr->nextHeight != NULL) {
	// 		ptr = ptr->nextHeight;
	// 	}
	// 	else {
	// 		pNew->nextHeight=list->headHeightList;
	// 		list->headHeightList=pNew;
	// 	}
		
	// }
	



	// add it to "headWeightList"

	list->headWeightList = addToWeightList(list->headWeightList, pNew);

	// while (1) {
	// 	if (ptr->weight <= ptr->nextWeight->weight && ptr->nextWeight != NULL) {
	// 		ptr = ptr->nextWeight;
	// 	}
	// 	else {
	// 		pNew->nextWeight=list->headWeightList;
	// 		list->headWeightList=pNew;
	// 	}
	// }
	 

	return list;
}

int size(PersonList *list) {
	int count=0;
	Person *ptr = list->headHeightList;
	// Person *ptr2 = NULL;

	while (1) {
        if (ptr == NULL) {
			return count;
		}
		else {
			ptr = ptr->nextHeight;
			count++;
		}
    }
	return count;
}

void printByHeight(PersonList *list) {
    Person *ptr = list->headHeightList;
	// Person *ptr2 = NULL;

	while (1) {
		if (ptr == NULL) {
			printf("\n");
			return;
		}
		else {
			printf("%s %s: height = %d, weight = %d\n", ptr->first, ptr->last, ptr->height, ptr->weight);
		}
		ptr = ptr->nextHeight;
	}
}

void printByWeight(PersonList *list) {
	Person *ptr = list->headWeightList;

	while (1) {
		if (ptr == NULL) {
			printf("\n");
			return;
		}
		else {
			printf("%s %s: height = %d, weight = %d\n", ptr->first, ptr->last, ptr->height, ptr->weight);
		}
		ptr = ptr->nextWeight;
	}
}

Person *search(PersonList *list, char *first, char *last) {
	Person *ptr = list->headHeightList;
	
	while (ptr != NULL) {
        if (ptr->first != NULL && ptr->last != NULL) {
			if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
				return ptr;
			}
		}
		ptr = ptr->nextHeight;
	}

	// if (ptr->first == NULL || ptr->last == NULL || (ptr->first == NULL && ptr->last == NULL)) {
	// 	return NULL;
	// }
	// else if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
	// 	return ptr;
	// }
	// else {
	// 	return search(ptr->nextHeight, first, last);
	// }
	
	return NULL;
}

void updateName(PersonList *list, char *first, char *last, char *newFirst, char *newLast) { 
	Person *ptr = search(list, first, last);

	if (ptr == NULL) {
		printf("Error: person does not exist\n");
	}

	if (ptr != NULL) {
		strcpy(ptr->first, newFirst);
		strcpy(ptr->last, newLast);
	}
}

PersonList *removePerson(PersonList *list, char *first, char *last) {
	Person *head = search(list, first, last);
	if (head == NULL) {
		printf("Error: person does not exist\n");
		return NULL;
	}
	head = list->headHeightList;
    Person *temp = head;
	Person *prev = NULL;
    
	if ((head != NULL) && (strcmp(head->first, first) == 0) && (strcmp(head->last, last) == 0)) {
        list->headHeightList = head->nextHeight;
        // free(head);
        // return list;
    }
	else {
		while ((temp != NULL) && (strcmp(temp->first, first) != 0) && (strcmp(temp->last, last) != 0)) {
			prev = temp;
			temp = temp->nextHeight;
		}
		// if (temp == NULL) {
		// 	return list;
		// }
		prev->nextHeight = temp->nextHeight;
		// free(temp);
	}

	head = list->headWeightList;
    temp = head;
	prev = NULL;
	if ((head != NULL) && (strcmp(head->first, first) == 0) && (strcmp(head->last, last) == 0)) {
        list->headWeightList = head->nextWeight;
        // free(head);
        // return list;
    }
	else {
		while ((temp != NULL) && (strcmp(temp->first, first) != 0) && (strcmp(temp->last, last) != 0)) {
			prev = temp;
			temp = temp->nextWeight;
		}
		// if (temp == NULL) {
		// 	return list;
		// }
		prev->nextWeight = temp->nextWeight;
		free(temp);
	}
	

	



	// if ((strcmp(head->first, first) == 0) && (strcmp(head->last, last) == 0)) {
    //     Person *pDel = head;
    //     head = head->nextHeight;
    //     free(pDel);
    //     return list;
    // }

    // for (Person *cur = head; cur != NULL; cur = cur->nextHeight) {
    //     if (cur->nextHeight == head->nextHeight) {
    //         Person *pDel = cur->nextHeight;
    //         cur->nextHeight = cur->nextHeight->nextHeight;
    //         free(pDel);
    //         return list;
    //     }
    // }
	// for (Person *cur = head; cur != NULL; cur = cur->nextWeight) {
    //     if (cur->nextWeight == head->nextWeight) {
    //         Person *pDel = cur->nextWeight;
    //         cur->nextWeight = cur->nextWeight->nextWeight;
    //         free(pDel);
    //         return list;
    //     }
    // }

    // return list; // Unreachable



    // else {
    //     head->nextHeight = removePerson(head->nextHeight, first, last);
		
    //     return head;
    // }

	return list;
}

PersonList *updateHeight(PersonList *list, char *first, char *last, int height)
{ 
	Person *ptr = search(list, first, last);

	if (ptr == NULL) {
		printf("Error: person does not exist\n");
	}

	if (ptr != NULL) {
		int weight = ptr->weight;
		list = removePerson(list, first, last);
		list = add(list, first, last, height, weight);
	}

	return list;
}

PersonList *updateWeight(PersonList *list, char *first, char *last, int weight)
{ 
    Person *ptr = search(list, first, last);

	if (ptr == NULL) {
		printf("Error: person does not exist\n");
	}

	if (ptr != NULL) {
		int height = ptr->height;
		list = removePerson(list, first, last);
		list = add(list, first, last, height, weight);
	}
	
	return list;
}