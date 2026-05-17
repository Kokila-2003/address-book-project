#include <stdio.h>
#include "file.h"
#include <unistd.h>

// Function to save all contacts into a CSV file
void saveContactsToFile(AddressBook *addressBook) 
{
  
    FILE *fp;

    // Print error if file cannot be opened
    if((fp = fopen("contact.csv","w")) == NULL)
    {
        fprintf(stderr, "File is not found\n");
        return;
    }

    // Write each contact to file in CSV format
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }

    // Display saving progress animation
    for(int j = 1; j <= 100; j++)
    {
        printf("saving....................................%d\r", j);
        fflush(stdout);
        usleep(10000);
    }

    // Close the file
    fclose(fp);
}


// Function to load contacts from CSV file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;

    // Open file in read mode
    if((fp = fopen("contact.csv","r")) == NULL)
    {
        fprintf(stderr, "File is not found\n");
        return;
    }

    // Read contacts until file ends or address book is full
    while((fscanf(fp," %[^,],%[^,],%[^\n]", addressBook -> contacts[addressBook -> contactCount].name, addressBook -> contacts[addressBook -> contactCount].phone, addressBook -> contacts[addressBook -> contactCount].email) == 3))
    {
        // Increment contact count after successful read
        addressBook->contactCount++;
    }

    // Close the file
    fclose(fp);
}
