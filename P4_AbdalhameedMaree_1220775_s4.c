// -*---------------------------------------------*- //

/*
          ABDALHAMEED MAREE - 1220775 - SEC: 4
                      PROJECT NUM: 4
            SORTING GRAPHS USING DIJKSTRA'S
            ALGORITHM AND TOPOLOGICAL SORT
*/

// -*---------------------------------------------*- //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  The following two structures are used for storing courses and thier prerequisits
*/
typedef struct PreRequisit
{
  char CourseName[50];
  struct PreRequisit *Next;
} PreRequisit;

typedef struct TopoGraph
{
  char CourseName[50];
  struct PreRequisit *PreRequisits;
  struct TopoGraph *Next;
} TopoGraph;

/*
  The following structure are used to make a queue wich is used to store the courses correctly
  to applay FIFO Algorithm (First in First Out), wich will be used in the Topological sort.
*/
typedef struct Queue
{
  char string[50];
  struct Queue *Next;
} Queue;

struct Queue *Front = NULL;
struct Queue *Rear = NULL;

/*
  The following two structures are used for storing buildings and the distinations
*/
typedef struct Distination
{
  char DistinationName[50];
  int weight;
  struct Distination *Next;
} Distination;

typedef struct Buildings
{
  char BuildingName[50];
  char preBuilding[50];
  struct Distination *NextBuilding;
  struct Buildings *Next;
  int visited;
  int distance;
} Buildings;

/*
  The following two structures are used to make the heap , where the heap will be used
  in the Dijkstra's algorithm to maintain the buildings and store them correctly
*/
typedef struct HeapNode
{
  char BuildingName[50];
  int distance;
} HeapNode;

typedef struct MinHeap
{
  HeapNode *data[1000];
  int size;
} MinHeap;

/*
 The following Two function are used to handle the queue
 by adding(Enqueue) or removing(Dequeue) data.
*/
void Enqueue(char *string);
char *Dequeue();

/*
  The following function are used for courses to applay some operations on them
*/
TopoGraph *LoadInputFile(TopoGraph *head);            // Load data from input file and store them in the graph
TopoGraph *InsertCourse(char *name, TopoGraph *head); // Insert a new course to the graph
TopoGraph *DeleteCourse(char *name, TopoGraph *head); // Delete a course from the graph
TopoGraph *FindCourse(char *name, TopoGraph *head);   // Search for and return a course if found

PreRequisit *AddPreRequisit(char *name, TopoGraph *Node);    // Add a new prerequisit course for another course
void DeletePreRequisit(TopoGraph *course, char *name);       // Delete a prerequisit from a specific course
PreRequisit *FindPreRequisit(char *name, PreRequisit *head); // search for and return a prerequisit for a specific course if found

void PrintGraph(TopoGraph *head); // print the graph

void TopologicalSort(TopoGraph *head); // An algorithm which is used to sort courses

/*
  The following functions are used for Buildings to applay some operations on them
*/
Buildings *LoadInputFileForBuildings(Buildings *head);                     // Load data from input file and store them in the graph
Buildings *InsertBuilding(char *name, Buildings *head);                    // Insert a new building to the graph
Buildings *FindBuilding(char *name, Buildings *head);                      // Search for and return a building if found
Distination *AddDistinaion(char *name, int distance, Buildings *building); // Add a new distination for a specific building
void PrintBuildings(Buildings *head);                                      // print buildings graph

void dijkstra(Buildings *graph, char *source, char *target, int DistanceOrPathWithDistance); // An algorithm which is used to find the shortest distance between two buildings

/*
  The following functions are used to handle the heap and apply some operations on it
*/
int parent(int i);                                          // return the index of the parent of the sent index
int leftChild(int i);                                       // return the index of the left child of the sent index
int rightChild(int i);                                      // return the index of the right chinld of the sent index
void heapify(MinHeap *heap, int index);                     // a function wich is used to rearrange the heap array to follow the rules of it
void insertHeap(MinHeap *heap, char *vertex, int distance); // add a new vertex to the heap
HeapNode *RemoveRoot(MinHeap *heap);                        // remove and return the minimum value (root) in the heap

/*
  Main function which will be used to handle the various structures and functions defined previously
*/
int main(int argc, char const *argv[])
{
  TopoGraph *courses = NULL;                        // defining the head of courses
  Buildings *buildings = NULL;                      // defining the head of buildings
  int choice, flag = 0, sortFlag = 0, TopoFlag = 0; // defining two flags wich will be used to arrange the use of the functions and a choice integer
  char source[50], target[50];                      // two arrays of characters which will be used to store a source and destination for dijkstra function

  do
  {
    printf("Menu:\n" // main menue
           "1. Load the files\n"
           "2. Calculate the shortest distance between two buildings\n"
           "3. Print the shortest route between two buildings and the total distance\n"
           "4. Sort the courses using the topological sort\n"
           "5. Print the sorted courses\n"
           "6. Exit\n"
           "Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
      printf("\n-*------------------------------*-\n\n");
      printf("Loading Files...\n");
      courses = LoadInputFile(courses);
      buildings = LoadInputFileForBuildings(buildings);
      printf("Files has been loaded successfully.\n");
      flag = 1;
      // PrintBuildings(buildings);
      printf("\n-*------------------------------*-\n\n");
      break;
    }
    case 2:
    {
      printf("\n-*------------------------------*-\n\n");
      if (flag == 1)
      {
        printf("Enter source building: ");
        scanf("%s", source);
        printf("Enter target building: ");
        scanf("%s", target);
        dijkstra(buildings, source, target, 0);
      }
      else
        printf("you didn't load the files.\n");
      printf("\n-*------------------------------*-\n\n");
      break;
    }
    case 3:
    {
      printf("\n-*------------------------------*-\n\n");
      if (flag == 1)
      {
        printf("Enter source building: ");
        scanf("%s", source);
        printf("Enter target building: ");
        scanf("%s", target);
        if (strcmp(source, target) == 0)
          printf("you are in the same building :)\n");
        else
          dijkstra(buildings, source, target, 1);
      }
      else
        printf("you didn't load the files.\n");
      printf("\n-*------------------------------*-\n\n");
      break;
    }
    case 4:
    {
      printf("\n-*------------------------------*-\n\n");
      if (flag == 1 && sortFlag == 0)
      {
        printf("Sorting the course Topologically.\n");
        TopologicalSort(courses);
        sortFlag = 1;
        printf("Courses have been sorted successfully.\n");
      }
      else if (flag == 0)
        printf("you didn't load the files.\n");
      else
        printf("you have already sorted the courses\n");
      printf("\n-*------------------------------*-\n\n");
      break;
    }
    case 5:
    {
      printf("\n-*------------------------------*-\n\n");
      if (sortFlag == 1 && TopoFlag == 0)
      {
        printf("Topologically sorted courses:\n");
        while (Front != NULL)
          printf("%s -> ", Dequeue());
        printf("NULL \n");
        TopoFlag = 1;
      }
      else if (sortFlag == 0)
        printf("you didn't sort the courses.\n");
      else
        printf("You have already printed the courses :)\n");
      printf("\n-*------------------------------*-\n\n");
      break;
    }
    case 6:
    {
      printf("Exiting application.\n");
      break;
    }
    default:
      printf("Invalid choice, please try again.\n");
    }
  } while (choice != 6);

  return 0;
}
// -*---------------------------------------------*- //

/*
  First section: Courses functions
*/

// -*---------------------------------------------*- //
TopoGraph *LoadInputFile(TopoGraph *head)
{
  FILE *input = fopen("input_courses.txt", "r");
  if (input == NULL)
  {
    printf("can't open the file.\n");
    return NULL;
  }

  char string[50];
  while (fgets(string, sizeof(string), input) != NULL)
  {
    int size = strlen(string);
    if (string[size - 1] == '\n')
      string[size - 1] = '\0';

    char *course = strtok(string, "#");
    if (course != NULL)
    {
      head = InsertCourse(course, head);

      TopoGraph *courseNode = FindCourse(course, head);
      if (courseNode != NULL)
      {
        char *pre = strtok(NULL, "#");
        while (pre != NULL)
        {
          AddPreRequisit(pre, courseNode);
          pre = strtok(NULL, "#");
        }
      }
    }
  }

  fclose(input);
  return head;
}
// -*---------------------------------------------*- //

TopoGraph *InsertCourse(char *name, TopoGraph *head)
{
  TopoGraph *newNode = (TopoGraph *)malloc(sizeof(TopoGraph));
  if (newNode == NULL)
  {
    printf("Out of memory!!\n");
    return head;
  }

  strcpy(newNode->CourseName, name);
  newNode->PreRequisits = NULL;
  newNode->Next = NULL;

  if (head == NULL)
  {
    return newNode;
  }

  TopoGraph *currentNode = head;
  while (currentNode->Next != NULL)
  {
    currentNode = currentNode->Next;
  }

  currentNode->Next = newNode;
  return head;
}
// -*---------------------------------------------*- //

TopoGraph *FindCourse(char *name, TopoGraph *head)
{
  TopoGraph *current = head;
  while (current != NULL)
  {
    if (strcmp(current->CourseName, name) == 0)
    {
      return current;
    }
    current = current->Next;
  }
  return NULL;
}
// -*---------------------------------------------*- //

TopoGraph *DeleteCourse(char *name, TopoGraph *head)
{
  if (head == NULL)
  {
    printf("Out of memory!\n");
    return head;
  }

  if (strcmp(head->CourseName, name) == 0)
  {
    TopoGraph *temp = head;
    head = head->Next;
    free(temp);
    return head;
  }

  TopoGraph *current = head;
  TopoGraph *prev = NULL;

  while (current != NULL && strcmp(current->CourseName, name) != 0)
  {
    prev = current;
    current = current->Next;
  }

  if (current == NULL)
  {
    printf("Course %s not found\n", name);
    return head;
  }

  if (prev != NULL)
  {
    prev->Next = current->Next;
    free(current);
  }

  return head;
}
// -*---------------------------------------------*- //

void TopologicalSort(TopoGraph *head)
{
  if (head == NULL)
  {
    printf("No graph to sort\n");
    return;
  }

  while (head != NULL) // loop iterates for all of the vertex in the graph
  {
    TopoGraph *current = head;
    while (current != NULL) // loop iterates for all of the vertex in the graph to delete the prerequisits
    {
      if (current->PreRequisits == NULL) // checks if the Pre Requisits equals to null
      {
        Enqueue(current->CourseName); // store the name of the courses in the queue to print them in order
        TopoGraph *temp = head;
        while (temp != NULL)
        {
          DeletePreRequisit(temp, current->CourseName); // delets the prerequisit from all other vertex that contains the current course name as a prerequisit
          temp = temp->Next;
        }
        head = DeleteCourse(current->CourseName, head); // delete the current course from the graph
        break;
      }
      current = current->Next;
    }
  }
}
// -*---------------------------------------------*- //

PreRequisit *AddPreRequisit(char *name, TopoGraph *Node)
{
  PreRequisit *newPreRequisit = (PreRequisit *)malloc(sizeof(PreRequisit));
  if (newPreRequisit == NULL || Node == NULL)
  {
    printf("Out of memory!!\n");
    return NULL;
  }

  strcpy(newPreRequisit->CourseName, name);
  newPreRequisit->Next = NULL;
  if (Node->PreRequisits == NULL)
  {
    Node->PreRequisits = newPreRequisit;
  }
  else
  {
    PreRequisit *TempPreRequisit = Node->PreRequisits;
    while (TempPreRequisit->Next != NULL)
      TempPreRequisit = TempPreRequisit->Next;

    TempPreRequisit->Next = newPreRequisit;
  }
  return newPreRequisit;
}
// -*---------------------------------------------*- //

PreRequisit *FindPreRequisit(char *name, PreRequisit *head)
{
  PreRequisit *current = head;
  while (current != NULL)
  {
    if (strcmp(current->CourseName, name) == 0)
    {
      return current;
    }
    current = current->Next;
  }
  return NULL;
}
// -*---------------------------------------------*- //

void DeletePreRequisit(TopoGraph *course, char *name)
{
  if (course == NULL)
  {
    printf("Course is NULL\n");
    return;
  }

  PreRequisit *current = course->PreRequisits;
  PreRequisit *previous = NULL;

  while (current != NULL)
  {
    if (strcmp(current->CourseName, name) == 0)
    {
      if (previous == NULL)
      {
        PreRequisit *temp = course->PreRequisits;
        course->PreRequisits = current->Next;
        free(temp);
      }
      else
      {
        previous->Next = current->Next;
        free(current);
      }
      return;
    }
    previous = current;
    current = current->Next;
  }
}
// -*---------------------------------------------*- //

void PrintGraph(TopoGraph *head)
{
  TopoGraph *current = head;
  while (current != NULL)
  {
    printf("Course: %s\n", current->CourseName);
    PreRequisit *preReq = current->PreRequisits;
    while (preReq != NULL)
    {
      printf("  PreRequisite: %s\n", preReq->CourseName);
      preReq = preReq->Next;
    }
    current = current->Next;
    printf("\n");
  }
}
// -*---------------------------------------------*- //

/*
  Second Section: Functions for buildings
*/

// -*---------------------------------------------*- //
Buildings *LoadInputFileForBuildings(Buildings *head)
{
  FILE *input = fopen("input_buildings.txt", "r");
  if (input == NULL)
  {
    printf("can't open the file.\n");
    return NULL;
  }

  char string[100];
  while (fgets(string, sizeof(string), input) != NULL)
  {
    int size = strlen(string);
    if (string[size - 1] == '\n')
      string[size - 1] = '\0';

    char *building = strtok(string, "#");
    char *dest = strtok(NULL, "#");
    int distance = atoi(strtok(NULL, "#"));

    if (building != NULL)
    {
      Buildings *buildingNode = FindBuilding(building, head);
      if (buildingNode == NULL)
      {
        head = InsertBuilding(building, head);
        buildingNode = FindBuilding(building, head);
      }
      if (buildingNode != NULL && dest != NULL)
      {
        AddDistinaion(dest, distance, buildingNode);
        Buildings *destNode = FindBuilding(dest, head);
        if (destNode == NULL)
        {
          head = InsertBuilding(dest, head);
        }
      }
    }
  }
  fclose(input);
  return head;
}
// -*---------------------------------------------*- //

Buildings *InsertBuilding(char *name, Buildings *head)
{
  Buildings *newNode = (Buildings *)malloc(sizeof(Buildings));
  if (newNode == NULL)
  {
    printf("Out of memory!!\n");
    return head;
  }

  strcpy(newNode->BuildingName, name);
  newNode->NextBuilding = NULL;
  newNode->Next = NULL;

  if (head == NULL)
    return newNode;

  Buildings *currentNode = head;
  while (currentNode->Next != NULL)
    currentNode = currentNode->Next;

  currentNode->Next = newNode;
  return head;
}
// -*---------------------------------------------*- //

Buildings *FindBuilding(char *name, Buildings *head)
{
  Buildings *current = head;
  while (current != NULL)
  {
    if (strcmp(current->BuildingName, name) == 0)
    {
      return current;
    }
    current = current->Next;
  }
  return NULL;
}
// -*---------------------------------------------*- //

Distination *AddDistinaion(char *name, int distance, Buildings *building)
{
  Distination *newNode = (Distination *)malloc(sizeof(Distination));
  if (newNode == NULL || building == NULL)
  {
    printf("Out of memory!!\n");
    return NULL;
  }

  strcpy(newNode->DistinationName, name);
  newNode->weight = distance;
  newNode->Next = NULL;
  if (building->NextBuilding == NULL)
  {
    building->NextBuilding = newNode;
  }
  else
  {
    Distination *TempBuilding = building->NextBuilding;
    while (TempBuilding->Next != NULL)
      TempBuilding = TempBuilding->Next;

    TempBuilding->Next = newNode;
  }
  return newNode;
}
// -*---------------------------------------------*- //

void PrintBuildings(Buildings *head)
{
  Buildings *current = head;
  while (current != NULL)
  {
    printf("Building: %s\n", current->BuildingName);
    Distination *tempNode = current->NextBuilding;
    while (tempNode != NULL)
    {
      printf("  Distination: %s, Distance: %d\n", tempNode->DistinationName, tempNode->weight);
      tempNode = tempNode->Next;
    }
    current = current->Next;
    printf("\n");
  }
}
// -*---------------------------------------------*- //

/*
  Third Section: Functions for Queues
*/

// -*---------------------------------------------*- //
void Enqueue(char *string)
{
  Queue *newQueue = (Queue *)malloc(sizeof(Queue));
  if (newQueue == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return;
  }
  strcpy(newQueue->string, string);
  newQueue->Next = NULL;
  if (Rear == NULL)
  {
    Front = newQueue;
    Rear = newQueue;
  }
  else
  {
    Rear->Next = newQueue;
    Rear = newQueue;
  }
}
// -*---------------------------------------------*- //

char *Dequeue()
{
  if (Front == NULL)
  {
    // printf("Queue is empty\n");
    return NULL;
  }

  Queue *tempNode = Front;
  char *string = (char *)malloc(50 * sizeof(char));
  if (string == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return NULL;
  }
  strcpy(string, tempNode->string);
  Front = Front->Next;
  if (Front == NULL)
  {
    Rear = NULL;
  }
  free(tempNode);
  return string;
}
// -*---------------------------------------------*- //

/*
  Fourth Section: Functions for Heaps
*/

// -*---------------------------------------------*- //
int parent(int i)
{
  return i / 2;
}
// -*---------------------------------------------*- //

int leftChild(int i)
{
  return 2 * i;
}
// -*---------------------------------------------*- //

int rightChild(int i)
{
  return 2 * i + 1;
}
// -*---------------------------------------------*- //

void heapify(MinHeap *heap, int index)
{
  int minChild = index;
  int left = leftChild(index);
  int right = rightChild(index);

  if (left < heap->size && heap->data[left]->distance < heap->data[minChild]->distance) // compare if the parent value is less than the left child
    minChild = left;                                                                    // and swap the values if neccessary

  if (right < heap->size && heap->data[right]->distance < heap->data[minChild]->distance) // compare if the parent value is less than the right child
    minChild = right;                                                                     // and swap the values if neccessary

  if (minChild != index)
  {
    HeapNode *temp = heap->data[index];
    heap->data[index] = heap->data[minChild];
    heap->data[minChild] = temp;

    heapify(heap, minChild);
  }
}

// -*---------------------------------------------*- //

void insertHeap(MinHeap *heap, char *vertex, int distance)
{
  if (heap->size >= 1000)
  {
    printf("Heap size is over 1000\n");
    return;
  }

  heap->data[heap->size] = (HeapNode *)malloc(sizeof(HeapNode));
  strcpy(heap->data[heap->size]->BuildingName, vertex);
  heap->data[heap->size]->distance = distance;
  heap->size++;
  heapify(heap, heap->size - 1); // fix the heap to make the root minimum ater inserting a new node
}
// -*---------------------------------------------*- //

HeapNode *RemoveRoot(MinHeap *heap)
{
  if (heap->size <= 0) // Return NULL if the heap is empty
  {
    printf("Heap is empty\n");
    return NULL;
  }

  HeapNode *root = heap->data[0];
  heap->data[0] = heap->data[heap->size - 1];
  heap->size--;
  heapify(heap, 0); // Fix the heap to maintain the min-heap property

  return root;
}
// -*---------------------------------------------*- //

void dijkstra(Buildings *graph, char *source, char *target, int DistanceOrPathWithDistance)
{
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (heap == NULL)
  {
    printf("Out of memory!!\n");
    return;
  }
  heap->size = 0;

  Buildings *current = graph;
  while (current != NULL) // initialize heap data, zero for source , infinity for other buildings
  {
    if (strcmp(current->BuildingName, source) == 0)
    {
      current->distance = 0;
      current->visited = 0;
      strcpy(current->preBuilding, "");
      insertHeap(heap, source, 0); // insert the node to the heap
    }
    else
    {
      current->distance = INT_MAX;
      current->visited = 0;
    }
    current = current->Next;
  }

  while (heap->size > 0)
  {
    HeapNode *minNode = RemoveRoot(heap);                 // get the root (minimum value)
    current = FindBuilding(minNode->BuildingName, graph); // make the current node equal to the next building that the minimum value points at
    if (current->visited == 1)
      continue;
    else
    {
      current->visited = 1;                         // make the status of the current node visited (1) , if not visited it will be zero.
      Distination *DitTemp = current->NextBuilding; // temprorary Distination that points at the first distination of the new current node.
      while (DitTemp != NULL)                       // a loop that iterates for all of the buildings that the current node point at. (out degrees)
      {
        Buildings *newBuilding = FindBuilding(DitTemp->DistinationName, graph); // new node that will points at the main node of the DitTemp node
        if (newBuilding->distance > current->distance + DitTemp->weight)        // checks for the distance , if the new road is less than the old one >>
        {                                                                       // replace the old distance by the new one
          newBuilding->distance = current->distance + DitTemp->weight;
          insertHeap(heap, newBuilding->BuildingName, newBuilding->distance); // insert the short distance node to the heap
          strcpy(newBuilding->preBuilding, current->BuildingName);
        }
        DitTemp = DitTemp->Next;
      }
    }
  }
  /*
    This section is for the results
  */
  Buildings *targetBuilding = FindBuilding(target, graph);                                   // defining a building with the source name
  if (targetBuilding != NULL && DistanceOrPathWithDistance == 0)                             // checks if the building exists or not , and then checks >>
    printf("Shortest path from %s to %s is %d\n", source, target, targetBuilding->distance); // if we want to print the path or not
  else if (targetBuilding != NULL && DistanceOrPathWithDistance == 1)
  {
    printf("Shortest path from %s to %s is %d\n", source, target, targetBuilding->distance); // if the DistanceOrPathWithDistance equals 1 print the path
    printf("The path is: ");
    while (strcmp(targetBuilding->BuildingName, source) != 0)
    {
      printf("%s <- ", targetBuilding->BuildingName);
      targetBuilding = FindBuilding(targetBuilding->preBuilding, graph);
    }
    printf("%s ", source);
  }
  else // if not found print that there is no path
    printf("Building %s not found in the graph.\n", target);

  free(heap);
}
// -*---------------------------------------------*- //

/*
          ABDALHAMEED MAREE - 1220775 - SEC: 4
                      PROJECT NUM: 4
            SORTING GRAPHS USING DIJKSTRA'S
            ALGORITHM AND TOPOLOGICAL SORT
*/

// -*---------------------------------------------*- //