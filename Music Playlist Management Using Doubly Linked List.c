#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[50];
    struct Song *next;
    struct Song *prev;
} Song;

Song *head = NULL, *tail = NULL;

// Function to create a new song node
Song* createSong(char *title) {
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

// Function to add a song to the playlist
void addSong(char *title) {
    Song *newSong = createSong(title);
    if (head == NULL) {
        head = tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    printf("Added: %s\n", title);
}

// Function to delete a song from the playlist
void deleteSong(char *title) {
    Song *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            if (temp == head && temp == tail) {
                head = tail = NULL;
            } else if (temp == head) {
                head = head->next;
                head->prev = NULL;
            } else if (temp == tail) {
                tail = tail->prev;
                tail->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Deleted: %s\n", title);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found: %s\n", title);
}

// Function to display all songs in the playlist
void displayPlaylist() {
    Song *temp = head;
    if (temp == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    printf("Playlist:\n");
    while (temp != NULL) {
        printf("%s\n", temp->title);
        temp = temp->next;
    }
}

// Function to play the next song
void playNext(Song **current) {
    if (*current == NULL) {
        printf("The playlist is empty.\n");
    } else if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Now playing: %s\n", (*current)->title);
    } else {
        printf("This is the last song in the playlist.\n");
    }
}

// Function to play the previous song
void playPrevious(Song **current) {
    if (*current == NULL) {
        printf("The playlist is empty.\n");
    } else if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Now playing: %s\n", (*current)->title);
    } else {
        printf("This is the first song in the playlist.\n");
    }
}

// Main function
int main() {
    int choice;
    char title[50];
    Song *current = NULL;

    while (1) {
        printf("\nPlaylist Manager\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Display Playlist\n");
        printf("4. Play Next\n");
        printf("5. Play Previous\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';  // Remove newline character
                addSong(title);
                if (current == NULL) {
                    current = head;  // Set current song to the first song added
                }
                break;
            case 2:
                printf("Enter song title to delete: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';
                deleteSong(title);
                if (current != NULL && strcmp(current->title, title) == 0) {
                    current = current->next != NULL ? current->next : head;
                }
                break;
            case 3:
                displayPlaylist();
                break;
            case 4:
                playNext(&current);
                break;
            case 5:
                playPrevious(&current);
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
