#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures for storing user, train, and booking information
typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char id[10];
    char name[50];
    char from[50];
    char to[50];
    int seats;
} Train;

typedef struct {
    int booking_id;
    char username[50];
    char train_id[10];
} Booking;

// Global arrays for storing users, trains, and bookings
User users[100];
Train trains[100];
Booking bookings[100];
int user_count = 0;
int train_count = 0;
int booking_count = 0;

// Function declarations
void register_user();
int login();
void search_trains();
void view_schedule();
void book_ticket(char *username);
void cancel_ticket(char *username);
void view_booking_history(char *username);
void main_menu();
void user_menu(char *username);

// Function to register a new user
void register_user() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Check if username already exists
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists!\n");
            return;
        }
    }

    // Add new user
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    printf("Registration successful!\n");
}

// Function to login
int login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return i;  // Return the index of the logged-in user
        }
    }
    printf("Invalid credentials!\n");
    return -1;
}

// Function to search for trains based on source and destination
void search_trains() {
    char from[50];
    char to[50];

    printf("Enter source station: ");
    scanf("%s", from);
    printf("Enter destination station: ");
    scanf("%s", to);

    printf("Available trains:\n");
    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].from, from) == 0 && strcmp(trains[i].to, to) == 0) {
            printf("Train ID: %s, Name: %s, Seats Available: %d\n", trains[i].id, trains[i].name, trains[i].seats);
        }
    }
}

// Function to view train schedule by train ID
void view_schedule() {
    char train_id[10];

    printf("Enter train ID: ");
    scanf("%s", train_id);

    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].id, train_id) == 0) {
            printf("Train ID: %s, Name: %s, From: %s, To: %s, Seats Available: %d\n",
                   trains[i].id, trains[i].name, trains[i].from, trains[i].to, trains[i].seats);
            return;
        }
    }
    printf("Train not found!\n");
}

// Function to book a ticket for a user
void book_ticket(char *username) {
    char train_id[10];

    printf("Enter train ID to book: ");
    scanf("%s", train_id);

    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].id, train_id) == 0 && trains[i].seats > 0) {
            trains[i].seats--;
            bookings[booking_count].booking_id = booking_count + 1;
            strcpy(bookings[booking_count].username, username);
            strcpy(bookings[booking_count].train_id, train_id);
            booking_count++;
            printf("Ticket booked successfully! Booking ID: %d\n", booking_count);
            return;
        }
    }
    printf("Invalid train ID or no seats available.\n");
}

// Function to cancel a ticket for a user
void cancel_ticket(char *username) {
    int booking_id;

    printf("Enter booking ID to cancel: ");
    scanf("%d", &booking_id);

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].booking_id == booking_id && strcmp(bookings[i].username, username) == 0) {
            for (int j = 0; j < train_count; j++) {
                if (strcmp(trains[j].id, bookings[i].train_id) == 0) {
                    trains[j].seats++;
                    break;
                }
            }
            for (int k = i; k < booking_count - 1; k++) {
                bookings[k] = bookings[k + 1];
            }
            booking_count--;
            printf("Ticket cancelled successfully!\n");
            return;
        }
    }
    printf("Invalid booking ID or you don't have permission to cancel this booking.\n");
}

// Function to view booking history for a user
void view_booking_history(char *username) {
    printf("Your bookings:\n");
    for (int i = 0; i < booking_count; i++) {
        if (strcmp(bookings[i].username, username) == 0) {
            printf("Booking ID: %d, Train ID: %s\n", bookings[i].booking_id, bookings[i].train_id);
        }
    }
}

// Main menu function
void main_menu() {
    int choice;
    while (1) {
        printf("\n--- Railway Ticket Booking System ---\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2: {
                int user_index = login();
                if (user_index != -1) {
                    user_menu(users[user_index].username);
                }
                break;
            }
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// User menu function
void user_menu(char *username) {
    int choice;
    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. Search Trains\n");
        printf("2. View Train Schedule\n");
        printf("3. Book Tickets\n");
        printf("4. Cancel Tickets\n");
        printf("5. View Booking History\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                search_trains();
                break;
            case 2:
                view_schedule();
                break;
            case 3:
                book_ticket(username);
                break;
            case 4:
                cancel_ticket(username);
                break;
            case 5:
                view_booking_history(username);
                break;
            case 6:
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// Initialize train data (for demonstration purposes)
void initialize_trains() {
    strcpy(trains[0].id, "101");
    strcpy(trains[0].name, "Express");
    strcpy(trains[0].from, "CityA");
    strcpy(trains[0].to, "CityB");
    trains[0].seats = 100;

    strcpy(trains[1].id, "102");
    strcpy(trains[1].name, "Local");
    strcpy(trains[1].from, "CityC");
    strcpy(trains[1].to, "CityD");
    trains[1].seats = 200;

    train_count = 2;
}

// Main function
int main() {
    initialize_trains();
    main_menu();
    return 0;
}





