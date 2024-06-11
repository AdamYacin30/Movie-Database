#include <stdio.h>
#include <string.h>

/*
    Name of Program: movieTheaterDB.c
    Purpose: Create a movie database that prints outs a movie's unique code along with its name, genre and rating
    Author: Adam Yassine (251298770)
    Student ID: ayassi
*/

struct Movie { // create a structure to represent the information about the movie
    int movieCode;
    char movieName[100]; // movie name is limited to only 100 characters
    char movieGenre[25]; // movie genre is limited to 25 characters
    float movieRating; // movie rating represented as a float and limited to 10.0
};

struct Movie movies[100]; // create a movie array structure to store the info about each movie
int movieCount = 0; // initialize movie count to 0 (will be incremented after each insertion of a movie)

int uniqueCheck(int code) { // helper method used to check if the movie code chosen by user is unique and not the same as other movies
    for (int i = 0; i < movieCount; ++i) {
        if (movies[i].movieCode == code) {
            return 0; // return 0 if movie code is not unique
        }
    }
    return 1; // return 1 if movie code is unique
}

void movieNameCheck(char movieName[]) { // helper method used to check if movie name is more than 100 characters
    do {
        printf("Enter Movie name:\n");
        scanf(" %[^\n]", movieName); // store the movie name in array and allow whitespace in the name

        if (strlen(movieName) > 100) { // check if movie name is more than 100 characters
            printf("Error: Movie name is longer than 100 characters\n");
        } else {
            break;
        }
    } while (1); // keep prompting user to enter a movie name with the correct amount of characters
}

void movieGenreCheck(char movieGenre[]) { // helper method used to check if movie genre name is more than 25 characters
    do {
        printf("Enter movie genre:\n");
        scanf(" %[^\n]", movieGenre); // store the genre of the movie in an array

        if (strlen(movieGenre) > 25) { // check if movie is more than 25 characters long
            printf("Error: Movie genre is longer than 25 characters\n");
        } else {
            break;
        }
    } while (1); // keep prompting user to enter a genre of the movie with correct amount of characters
}

void movieRatingCheck(float *movieRating) { // helper method used to check if the movie rating is more than 10.0
    do {
        printf("Enter Movie rating:\n");
        scanf("%f", movieRating); // store movie rating as a float


        if (*movieRating > 10.0) { // check if movie rating is greater than 10.0
            printf("Error: Movie rating is higher than25\n");
        } else {
            break;
        }
    } while (1); // keep prompting user to enter correct rating
}

void insertMovie () { // function used to create a movie object with the traits: name, genre and rating
    // initialize variables
    int code;
    char movieName[100];
    char movieGenre[25];
    float movieRating;

    printf("Enter Movie code:\n");
    scanf("%d", &code); // prompt the user to choose a movie code used to identify the movie

    if (code < 0 || !uniqueCheck(code) || movieCount >= 100) { // check if code is unique and less than 100
        printf("Error: invalid code or already exists");
        return;
    }

    // call the helper methods in order to store the movie traits as well as check if they follow the required attributes
    movieNameCheck(movieName);
    movieGenreCheck(movieGenre);
    movieRatingCheck(&movieRating);


    // assign the movie code to the chosen movie code choice
    movies[movieCount].movieCode = code;

    // copy the movieName and movieGenre into the movie structure and check if it is at the correct specified length
    strncpy(movies[movieCount].movieName, movieName, sizeof(movies[movieCount].movieName) - 1);
    movies[movieCount].movieName[sizeof(movies[movieCount].movieName) - 1] = '\0';
    strncpy(movies[movieCount].movieGenre, movieGenre, sizeof(movies[movieCount].movieGenre) - 1);
    movies[movieCount].movieGenre[sizeof(movies[movieCount].movieGenre) - 1] = '\0';

    // assign the movie rating to the chosen rating picked by the user
    movies[movieCount].movieRating = movieRating;

    printf("Movie added successfully \n");
    movieCount++; // increment the movie count variable after each successful insertion of a movie

}

void searchMovie() { // function used to search for a movie base on its unique code
    int code;
    printf("Enter Movie code:\n");
    scanf("%d", &code);

    int movieFound = 0;
    for (int i = 0; i < movieCount; i++) { // loop through each movie structure and check if code chosen matches a movie
        if (movies[i].movieCode == code) {  // if so print out the movie
            printf("Movie Code   Movie Name                      Movie Genre               Movie Rating\n");
            printf("%-13d%-32s%-26s%.1f\n", movies[i].movieCode, movies[i].movieName, movies[i].movieGenre, movies[i].movieRating);
            movieFound = 1; // return 1 if found
            break;
        }
    }
    if (movieFound == 0) { // return 0 and print an error if not found
        printf("Error: Movie not found\n");
        return;
    }
}

void updateMovie() { // function used to update all movie information (name, genre and rating) base on its unique code
    int code;
    printf("Enter movie code: ");
    scanf("%d", &code);

    int movieFound = 0;
    for (int i = 0; i < movieCount; i++) { // loop through the movie structure and check if code chosen is equal to a movies unique code
        if (movies[i].movieCode == code) { // if movie code is the same as code chosen re-enter the information by calling the insertMovie function
            printf("Enter updated movie information:\n"); // - and change all its traits again
            movieNameCheck(movies[i].movieName);
            movieGenreCheck(movies[i].movieGenre);
            movieRatingCheck(&(movies[i].movieRating));
            movieFound = 1;
            break;
        }

    }
    if (movieFound == 0) { // throw an error if movie is not found based on its code
        printf("Movie not found");
    }
}

void printMovieList() { // function used to print the entire list of movies with all their traits (name, genre, rating)
    printf("Movie Code   Movie Name                      Movie Genre               Movie Rating\n");
    for (int i = 0; i < movieCount; ++i) { // loop through movie count and print each movie with all its attributes
        printf("%-13d%-32s%-26s%.1f\n", movies[i].movieCode, movies[i].movieName, movies[i].movieGenre, movies[i].movieRating);
    }
}

int main() {
    char choice; // variable used to declare the operation code (i,s,u,p,q) chosen by the user

    do { // create a do-while loop in order to prompt user to pick an operation code until 'q' is chosen.
        printf("Enter operation code:\n");
        scanf(" %c", &choice); // store the user's choice for operation code in choice 'variable'

            if (choice == 'i') {
                insertMovie();
                printf("\n");
            }
            else if (choice == 's') {
                searchMovie();
                printf("\n");
            }
            else if (choice == 'u') {
                updateMovie();
                printf("\n");
            }
            else if (choice == 'p') {
                printMovieList();
                printf("\n");
            }
            else if (choice == 'q') {
                break;
            }
            else {
                printf("invalid command\n"); // if user does not choose one of the five options, print an error message
            }
        } while (choice != 'q');

    return 0;
}
