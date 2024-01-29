#define ACEHIGH 11
#define BALANCE 10000
#define BLACKJACK 21
#define BLACKONWHITE "\033[0;30m\033[47m"
#define CARDHEIGHT 7
#define NSUITES 4
#define NRANKS 13
#define COLOR(SUITE)                                                           \
  (((SUITE) == 1 || (SUITE) == 2) ? REDONWHITE : BLACKONWHITE)
#define DEALERMIN 16
#define DEAL(G) (G->hand[G->ncards++] = cards[--cardssize])
#define DECKSIZE 52
#define FACEVAL 10
#define GETRANK(POS) (((POS)-1) % NRANKS)
#define GETSUITE(POS) (((POS)-1) / NRANKS)
#define HELP                                                                   \
  "CARDS -- Authored by Mitch Feigenbaum\n\
Options:\n\
\t-b\t\tPlay an interactive round of Blackjack\n\
\t-c<n>\t\tPrint a specific card from an ordered deck\n\
\t-r\t\tPrint a random card\n\
\t-o\t\tPrint an ordered deck\n\
\t-s\t\tPrint a random deck.\n\
\t-h\t\tPrint this help message\n"
#define MAXHAND 5
#define PAYOUT 1.5
#define REDONWHITE "\033[0;31m\033[47m"
#define RESET "\033[0m"
#define SPACES(RANK)                                                           \
  (((RANK) == -1) ? "           " : ((RANK) == 9) ? "         " : "          ")
#define UNFLIPPED "\033[0;31m\033[44mXXXXXXXXXX\033[0m\t"
#define WHITE "\033[0;47m"
#define CLEAR "\033[1;1H\033[2J"

struct Gambler {
  int hand[BLACKJACK];
  int balance;
  int ncards;
};

const char *RANKS[NRANKS] = {"A", "2", "3",  "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const char *SUITES[NSUITES] = {"♣", "♦", "♥", "♠"};

extern void fill();

extern void print_footer(int card);

extern void print_body(int card);

extern void print_middle(int card);

extern void print_header(int card);

extern void print_hand(int *hand, int lo, int to);

extern void print_cards(int *hand, int size);

extern char action();

extern int hand_sum(int *hand, int size);

extern void dispmon(int sum);

extern int get_bet(struct Gambler *g);

extern void prep_game(struct Gambler *dealer, struct Gambler *player);

extern void show_hands(struct Gambler *dealer, struct Gambler *player);

extern void contest(struct Gambler *dealer, struct Gambler *player, int bet);

extern void play(struct Gambler *dealer, struct Gambler *player, int bet);

extern void blackjack();

