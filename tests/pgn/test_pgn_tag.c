#include <criterion/criterion.h>

#include "pgn/pgn_tag.h"

Test(taglist,  taglist_add) {
    taglist_t* tags = taglist_new();
    cr_assert_not_null(tags);

    taglist_add(tags, "Event", "Fun Fest");
    cr_assert_not_null(tags->head);

    taglist_add(tags, "White", "Murphy");
    cr_assert_not_null(tags->head->next);

    taglist_free(tags);
}
