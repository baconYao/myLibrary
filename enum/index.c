#include <stdio.h>
enum days {
  Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

enum suits {
  Hearts, Diamonds, Clubs, Spades
};

enum numbers {
  Couple = 2, Dozen = 12, Score = 20
};

void showdaytype(enum days day) {
  if(day == Saturday || day == Sunday) {
    printf("It's the weekend!\n");
  } else {
    printf("It's a working day\n");
  }

}

void showcard(enum suits card) {
  if(card == 0 || card == 1) {
    printf("This card is red (in suit #%d)\n", card);
  } else {
    printf("This card is black card\n");
  }

}

void buyinbulk(enum numbers num) {
  printf("The customer wants to buy %d items.\n", num);
}

int main(int argc, char **argv) {
  enum days today;
  enum suits playingcard;
  enum numbers num;

  today = Saturday;
  playingcard = Diamonds;
  num = Dozen;
  showdaytype(today);
  showcard(playingcard);
  buyinbulk(num);

  return 0;
}