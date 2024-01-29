#include "cards.h"
#include "rnd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cards[DECKSIZE];
int cardssize = DECKSIZE;

void fill() {
  for (int i = 0; i < DECKSIZE; i++)
    cards[i] = i + 1;
}

void print_footer(int card) {
  if (card == 0) {
    fputs(UNFLIPPED, stdout);
  } else {
    int suite = GETSUITE(card), rank = GETRANK(card);
    printf("%s%s%s%s\t", COLOR(suite), SPACES(rank), RANKS[rank], RESET);
  }
}

void print_body(int card) {
  if (card == 0)
    fputs(UNFLIPPED, stdout);
  else
    printf("%s%s%s\t", WHITE, SPACES(-1), RESET);
}

void print_middle(int card) {
  if (card == 0) {
    fputs(UNFLIPPED, stdout);
  } else {
    int suite = GETSUITE(card);
    printf("%s     %s     %s\t", COLOR(suite), SUITES[suite], RESET);
  }
}

void print_header(int card) {
  if (card == 0) {
    fputs(UNFLIPPED, stdout);
  } else {
    int suite = GETSUITE(card), rank = GETRANK(card);
    printf("%s%s%s%s\t", COLOR(suite), RANKS[rank], SPACES(rank), RESET);
  }
}

void print_hand(int *hand, int lo, int to) {
  putchar('\n');
  int i, j;
  for (i = lo; i < to; print_header(hand[i++]))
    ;
  putchar('\n');
  for (i = 0; i < CARDHEIGHT / 2; i++) {
    for (j = lo; j < to; print_body(hand[j++]))
      ;
    putchar('\n');
  }
  for (i = lo; i < to; print_middle(hand[i++]))
    ;
  putchar('\n');
  for (i = 0; i < CARDHEIGHT / 2; i++) {
    for (j = lo; j < to; print_body(hand[j++]))
      ;
    putchar('\n');
  }
  for (i = lo; i < to; print_footer(hand[i++]))
    ;
  putchar('\n');
  putchar('\n');
}

void print_cards(int *hand, int size) {
  int leftover = size % MAXHAND;
  for (int i = 0; i < size - leftover; i += MAXHAND)
    print_hand(hand, i, i + MAXHAND);
  if (leftover > 0)
    print_hand(hand, size - leftover, size);
}

char action() {
  printf("[H]it\t[S]tay\t[F]old\t[Q]uit\t");
  char choice;
  while ((choice = getchar()) != 'H' && choice != 'S' && choice != 'F' &&
         choice != 'Q' && choice != 'h' && choice != 's' && choice != 'f' &&
         choice != 'q')
    ;
  return choice;
}

int hand_sum(int *hand, int size) {
  int sum = 0, aces = 0, rank;
  for (int i = 0; i < size; i++) {
    sum += ((rank = GETRANK(hand[i]) + 1) > FACEVAL) ? FACEVAL : rank;
    aces = aces || rank == 1;
  }
  return aces && sum + ACEHIGH - 1 <= BLACKJACK ? sum + ACEHIGH - 1 : sum;
}

void dispmon(int sum) {
  printf("$%d.%d%d", sum / 100, sum % 100 / 10, sum % 10);
}

int get_bet(struct Gambler *g) {
  printf("Make a bet (balance: ");
  dispmon(g->balance);
  fputs(")\t", stdout);
  int bet;
  do {
    putchar('$');
    if (!scanf("%d", &bet))
      fputs("Failed to read integer.\n", stderr);
    while (getchar() != '\n')
      ;
  } while ((bet *= 100) < 100 || bet > g->balance);
  g->balance -= bet;
  return bet;
}

void prep_game(struct Gambler *dealer, struct Gambler *player) {
  cardssize = DECKSIZE;
  shuffle(cards, DECKSIZE);
  dealer->hand[0] = 0;
  dealer->ncards = 1;
  DEAL(dealer);
  player->ncards = 0;
  for (int i = 0; i < 2; i++)
    DEAL(player);
}

void show_hands(struct Gambler *dealer, struct Gambler *player) {
  puts(CLEAR);
  printf("Player Balance: ");
  dispmon(player->balance);
  putchar('\n');
  puts("\nDealer's Hand:");
  print_cards(dealer->hand, dealer->ncards);
  puts("Player's Hand:");
  print_cards(player->hand, player->ncards);
}

void contest(struct Gambler *dealer, struct Gambler *player, int bet) {
  puts("\nDealer's turn:");
  dealer->hand[0] = cards[--cardssize];
  show_hands(dealer, player);
  int player_sum = hand_sum(player->hand, player->ncards);
  int dealer_sum;
  while ((dealer_sum = hand_sum(dealer->hand, dealer->ncards)) < DEALERMIN &&
         dealer_sum < player_sum) {
    DEAL(dealer);
    show_hands(dealer, player);
  }
  if (dealer_sum > BLACKJACK || dealer_sum < player_sum) {
    printf("You win! (+");
    dispmon(bet * PAYOUT - bet);
    puts(")");
    bet *= PAYOUT;
    player->balance += bet;
  } else if (dealer_sum == player_sum) {
    player->balance += bet;
    puts("Draw.");
  } else {
    printf("You lose! (-");
    dispmon(bet);
    puts(")");
  }
}

void play(struct Gambler *dealer, struct Gambler *player, int bet) {
PLAY:
  switch (action()) {
  case 'H':
  case 'h':
    DEAL(player);
    show_hands(dealer, player);
    if (hand_sum(player->hand, player->ncards) <= BLACKJACK)
      goto PLAY;
    fputs("You've lost this round. (-", stdout);
    dispmon(bet);
    puts(")");
    break;
  case 'S':
  case 's':
    contest(dealer, player, bet);
    break;
  case 'F':
  case 'f':
    bet /= 2;
    fputs("You've surrendered this round. (-", stdout);
    dispmon(bet);
    puts(")");
    player->balance += bet;
    break;
  case 'Q':
  case 'q':
    exit(0);
  default:
    goto PLAY;
  }
}

void blackjack() {
  struct Gambler player, bot;
  player.balance = BALANCE;
  int bet;
  do {
    bet = get_bet(&player);
    prep_game(&bot, &player);
    show_hands(&bot, &player);
    play(&bot, &player, bet);
  } while (player.balance > 99);
  puts("You've gone bust!");
}

int main(int argc, char **argv) {
  if (argc == 1) {
    fputs(HELP, stderr);
    return 1;
  }
  srnd();
  fill();
  int c;
  int card;
  while ((c = getopt(argc, argv, "bc:rosh")) != -1)
    switch (c) {
    case 'b':
      blackjack();
      break;
    case 'c':
      card = abs(atoi(optarg));
      if (card > DECKSIZE) {
        fprintf(stderr,
                "%s: option -c requires an argument within the range of a "
                "standard deck (1-52).\n",
                argv[0]);
        return 1;
      }
      print_cards(&card, 1);
      break;
    case 'r':
      card = rndint(1, DECKSIZE + 1);
      print_cards(&card, 1);
      break;
    case 'o':
      fill();
      print_cards(cards, DECKSIZE);
      break;
    case 's':
      shuffle(cards, DECKSIZE);
      print_cards(cards, DECKSIZE);
      break;
    case 'h':
      fputs(HELP, stdout);
      break;
    default:
      return 1;
    }
  for (int i = optind; i < argc;
       fprintf(stderr, "non option argument: %s\n", argv[i++]))
    ;
  return 0;
}

