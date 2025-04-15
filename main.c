#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Memory block structure
typedef struct MemoryBlock {
    int id;                 // Process ID (-1 for free blocks)
    int size;               // Size of the block in bytes
    int address;            // Start address of the block
    struct MemoryBlock* next;
} MemoryBlock;

// Memory allocator structure
typedef struct {
    MemoryBlock* head;      // Head of the memory blocks linked list
    int totalSize;          // Total size of memory
    int allocatedSize;      // Currently allocated memory
    int nextProcessId;      // Next available process ID
} MemoryAllocator;

// Initialize the memory allocator
MemoryAllocator* initMemoryAllocator(int size) {
    MemoryAllocator* allocator = (MemoryAllocator*) malloc(sizeof(MemoryAllocator));
    if (!allocator) {
        printf("Error: Could not allocate memory for the allocator\n");
        return NULL;
    }
    
    // Create initial free block that spans the entire memory
    MemoryBlock* initialBlock = (MemoryBlock*) malloc(sizeof(MemoryBlock));
    if (!initialBlock) {
        printf("Error: Could not allocate memory for the initial block\n");
        free(allocator);
        return NULL;
    }
    
    initialBlock->id = -1;  // Free block
    initialBlock->size = size;
    initialBlock->address = 0;
    initialBlock->next = NULL;
    
    allocator->head = initialBlock;
    allocator->totalSize = size;
    allocator->allocatedSize = 0;
    allocator->nextProcessId = 1;
    
    return allocator;
}

// Print the current state of memory
void printMemoryState(MemoryAllocator* allocator) {
    printf("\n===== Memory State =====\n");
    printf("Total Size: %d bytes\n", allocator->totalSize);
    printf("Allocated: %d bytes\n", allocator->allocatedSize);
    printf("Free: %d bytes\n", allocator->totalSize - allocator->allocatedSize);
    
    MemoryBlock* current = allocator->head;
    printf("\nMemory Layout:\n");
    printf("Address\tSize\tStatus\n");
    
    while (current != NULL) {
        printf("%d\t%d\t%s", current->address, current->size, 
               (current->id == -1) ? "Free" : "Process ");
        
        if (current->id != -1) {
            printf("%d", current->id);
        }
        
        printf("\n");
        current = current->next;
    }
    printf("=======================\n\n");
}

// First-fit memory allocation
int allocateMemory(MemoryAllocator* allocator, int size) {
    MemoryBlock* current = allocator->head;
    MemoryBlock* prev = NULL;
    
    // Find the first free block that can accommodate the requested size
    while (current != NULL) {
        if (current->id == -1 && current->size >= size) {
            // Found a suitable free block
            break;
        }
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        // No suitable free block found
        printf("Error: Not enough memory to allocate %d bytes\n", size);
        return -1;
    }
    
    int processId = allocator->nextProcessId++;
    
    // If the free block is exactly the size we need, just change its status
    if (current->size == size) {
        current->id = processId;
    } else {
        // Split the block
        MemoryBlock* newBlock = (MemoryBlock*) malloc(sizeof(MemoryBlock));
        if (!newBlock) {
            printf("Error: Could not allocate memory for new block\n");
            return -1;
        }
        
        // Set the allocated block
        newBlock->id = processId;
        newBlock->size = size;
        newBlock->address = current->address;
        newBlock->next = current;
        
        // Update the remaining free block
        current->size -= size;
        current->address += size;
        
        // Update the list
        if (prev == NULL) {
            allocator->head = newBlock;
        } else {
            prev->next = newBlock;
        }
    }
    
    allocator->allocatedSize += size;
    
    printf("Allocated %d bytes for process %d\n", size, processId);
    return processId;
}

// Free memory allocated to a process
bool freeMemory(MemoryAllocator* allocator, int processId) {
    MemoryBlock* current = allocator->head;
    MemoryBlock* prev = NULL;
    
    // Find the block with the given process ID
    while (current != NULL) {
        if (current->id == processId) {
            break;
        }
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Process %d not found\n", processId);
        return false;
    }
    
    // Mark the block as free
    allocator->allocatedSize -= current->size;
    current->id = -1;
    
    // Merge with adjacent free blocks if possible
    MemoryBlock* next = current->next;
    
    // Check if the next block is free
    if (next != NULL && next->id == -1) {
        current->size += next->size;
        current->next = next->next;
        free(next);
    }
    
    // Check if the previous block is free
    if (prev != NULL && prev->id == -1) {
        prev->size += current->size;
        prev->next = current->next;
        free(current);
    }
    
    printf("Freed memory for process %d\n", processId);
    return true;
}

// Perform memory compaction
void compactMemory(MemoryAllocator* allocator) {
    if (allocator->head == NULL) {
        printf("Memory is empty, nothing to compact\n");
        return;
    }
    
    printf("Performing memory compaction...\n");
    
    // Create a new list for compacted memory
    MemoryBlock* newHead = NULL;
    MemoryBlock* newTail = NULL;
    int currentAddress = 0;
    
    // First, copy all allocated blocks to the new list
    MemoryBlock* current = allocator->head;
    while (current != NULL) {
        if (current->id != -1) {
            // This is an allocated block
            MemoryBlock* newBlock = (MemoryBlock*) malloc(sizeof(MemoryBlock));
            if (!newBlock) {
                printf("Error: Could not allocate memory during compaction\n");
                return;
            }
            
            // Copy the block properties
            newBlock->id = current->id;
            newBlock->size = current->size;
            newBlock->address = currentAddress;
            newBlock->next = NULL;
            
            // Update the address for the next block
            currentAddress += current->size;
            
            // Add to the new list
            if (newHead == NULL) {
                newHead = newBlock;
                newTail = newBlock;
            } else {
                newTail->next = newBlock;
                newTail = newBlock;
            }
        }
        current = current->next;
    }
    
    // If there's remaining free space, add a single free block at the end
    int freeSpace = allocator->totalSize - allocator->allocatedSize;
    if (freeSpace > 0) {
        MemoryBlock* freeBlock = (MemoryBlock*) malloc(sizeof(MemoryBlock));
        if (!freeBlock) {
            printf("Error: Could not allocate memory for free block during compaction\n");
            return;
        }
        
        freeBlock->id = -1;
        freeBlock->size = freeSpace;
        freeBlock->address = currentAddress;
        freeBlock->next = NULL;
        
        if (newHead == NULL) {
            newHead = freeBlock;
        } else {
            newTail->next = freeBlock;
        }
    }
    
    // Free the old list
    current = allocator->head;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }
    
    // Update the allocator with the new list
    allocator->head = newHead;
    
    printf("Memory compaction completed\n");
}

// Clean up the memory allocator
void destroyMemoryAllocator(MemoryAllocator* allocator) {
    MemoryBlock* current = allocator->head;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }
    free(allocator);
}

int main() {
    // Initialize memory allocator with 1000 bytes of memory
    MemoryAllocator* allocator = initMemoryAllocator(1000);
    if (!allocator) {
        return 1;
    }
    
    printf("Memory Allocator Demo\n");
    printf("---------------------\n");
    
    // Initial state
    printMemoryState(allocator);
    
    // Step 1: Add 3 processes consecutively
    printf("Step 1: Adding 3 processes\n");
    int proc1 = allocateMemory(allocator, 200);
    int proc2 = allocateMemory(allocator, 350);
    int proc3 = allocateMemory(allocator, 100);
    printMemoryState(allocator);
    
    // Step 2: Remove the middle process
    printf("Step 2: Removing middle process (Process %d)\n", proc2);
    freeMemory(allocator, proc2);
    printMemoryState(allocator);
    
    // Step 3: Try to add a process that won't fit due to fragmentation
    printf("Step 3: Trying to add a process that requires 400 bytes\n");
    int proc4 = allocateMemory(allocator, 400);
    printMemoryState(allocator);
    
    // Step 4: Perform memory compaction
    printf("Step 4: Performing memory compaction\n");
    compactMemory(allocator);
    printMemoryState(allocator);
    
    // Step 5: Try to add the process again after compaction
    printf("Step 5: Trying to add the same process after compaction\n");
    proc4 = allocateMemory(allocator, 400);
    printMemoryState(allocator);
    
    // Clean up
    destroyMemoryAllocator(allocator);
    
    return 0;
}