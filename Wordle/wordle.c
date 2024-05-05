#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LEN 6
#define MAX_WORDS 1000

int read_words_from_file(const char *filename, char words[][MAX_WORD_LEN],
                         int *num_words)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    printf("Error: Could not open file %s\n", filename);
    return 1;
  }

  char line[MAX_WORD_LEN];
  int i = 0;
  while (fgets(line, MAX_WORD_LEN, file) && i < MAX_WORDS)
  {
    // Remove the newline character from the end of the line
    line[strcspn(line, "\n")] = '\0';
    strcpy(words[i], line);
    i++;
  }

  *num_words = i;
  fclose(file);
  return 0;
}

void play_wordle(const char words[][MAX_WORD_LEN], int num_words)
{
  char answer[MAX_WORD_LEN];
  int answer_len;

  // Seed the random number generator
  srand(time(NULL));

  // Select a random word from the list
  int random_index = rand() % num_words;
  strcpy(answer, words[random_index]);
  answer_len = strlen(answer);

  char guess[MAX_WORD_LEN];
  int attempts = 0;
  int max_attempts = 6;

  printf("Welcome to Wordle!\n");
  printf("You have %d attempts to guess the %d-letter word.\n", max_attempts,
         answer_len);

  while (attempts < max_attempts)
  {
    printf("\nEnter your guess: ");
    scanf("%s", guess);

    if (strlen(guess) != answer_len)
    {
      printf("Invalid guess length!\n");
      continue;
    }

    int correct_letters = 0;
    int correct_positions = 0;

    // Check for correct letters and positions
    for (int i = 0; i < answer_len; i++)
    {
      if (guess[i] == answer[i])
      {
        correct_positions++;
      }
      else
      {
        for (int j = 0; j < answer_len; j++)
        {
          if (guess[i] == answer[j])
          {
            correct_letters++;
            break;
          }
        }
      }
    }

    // Print the result
    printf("Correct letters in the right position: %d\n", correct_positions);
    printf("Correct letters in the wrong position: %d\n", correct_letters);

    if (correct_positions == answer_len)
    {
      printf("\nCongratulations! You guessed the word correctly!\n");
      return;
    }

    attempts++;
  }

  printf("\nSorry, you ran out of attempts. The word was: %s\n", answer);
}

int main()
{
  char words[MAX_WORDS][MAX_WORD_LEN];
  int num_words;
  if (read_words_from_file("words.csv", words, &num_words) != 0)
  {
    return 1;
  }

  play_wordle(words, num_words);

  return 0;
}
