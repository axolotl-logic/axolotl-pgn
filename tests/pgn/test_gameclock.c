#include <criterion/criterion.h>

#include "pgn/gameclock.h"

Test(gameclock, gameclock_add) {
    gameclock_t* clock = gameclock_new();
    cr_assert(clock);

    gameclock_add(clock, "0:05:00");
    cr_assert_eq(clock->tail->time, 300);

    gameclock_add(clock, "0:04:00");
    cr_assert_eq(clock->tail->time, 240);

    gameclock_add(clock, "0:03:43");
    cr_assert_eq(clock->tail->time, 223);

    gameclock_free(clock);
}
